// ECE 108 Lab 2 -- Sat Solver
//
// Read logical expressions in DIMACS format from files specified on the
// command line, and for each one print its name and one of "satisfiable",
// "unsatisfiable" or "tautology".
#include <stdio.h>
#include "dimacs_reader.h"
#include "stdlib.h"
int num_clauses; // total number of clauses
int num_vals; // total number of variables
int index = 0;
int tautology = 0;
struct expression {
	int exp[100][32];
	int numLiterals[100];
};

struct expression newExp;

int power(int base, int exp) {
	int i;
	int result = 1;
	for (i=1; i<=exp; i++) {
		result *= base;
	}

	return result;
}

void init(int numvars, int numclauses) {
    // Callback function that gets passed to read_dimacs().
    // Indicates start of a new expression with up to numvars variables
    // and numclauses clauses.
	num_clauses = numclauses;
	num_vals = numvars;
    // expression = new int[num_clauses]; //declare how many int[] will be in expression, idk syntax
}

void add_clause(int numlits, int literals[]) {
    // Callback function that gets passed to read_dimacs().
    // The literals argument is an array of ints, numlits is its length.
    // Each literal is the index (starting from 1) of a variable.
    // Negative integers represent logical negations of variables.
	int i;
	int x;
	int y;
	
	newExp.numLiterals[index] = numlits;
	
	for (i=0; i<numlits; i++) {
        	newExp.exp[index][i] = literals[i];
    	}

	index++;

	int check = 0;
	if (numlits > 1) {
		for (x=0; x<numlits; x++) {
			for (y=x+1; y<numlits; y++) {
				if (literals[x] == (literals[y]*(-1))) {
					tautology++;
					check = 1;
					break;
				}
			}
		}
	}
}
//	for (x=0; x<numlits; x++) { // might get error here
//		for (y=x + 1; y<numlits; y++) {
//			if (literals[x] == (literals[y]*(-1))) {
//				tautology++;
//				check = 1;
//				break;
  //  			} 
//		}
//		if (check) {
//			break;
//		}
//	}
//}

// returns the absolute value at the index of vals
int getTruth(int lit){
	if (lit<0) {
		return 0;
	} else {
		return 1;
	}
}

// evaluates total expression true or false
int evaluate(int array[]) {
	int i;
	int j;
	//printf("numclauses: %d\n", num_clauses);
	for (i=0; i<num_clauses; i++) {    //clause in expression:
		//printf("literals: %d\n", newExp.numLiterals[i]);
		for (j=0; j<newExp.numLiterals[i]; j++) {  //idx in clause:
			//printf("checking clause %d literal %d should be %d but its %d\n", i, j, getTruth(newExp.exp[i][j]), array[j]);

			//if (getTruth(newExp.exp[i][j]) == array[newExp.exp[i][j] - 1]) {
                		//printf ("%s: %i\n", "newExp.exp[i][j]: ", newExp.exp[i][j]);
				//printf("%s: %i\n", "array[j]", array[j]);
			//if (j==newExp.numLiterals[i]-1){
			//	return 0;
			//}
			
			if (newExp.exp[i][j] > 0) {
			//	printf("ij is positive %d and the truth is %d and arr is %d\n", newExp.exp[i][j], getTruth(newExp.exp[i][j]), array[newExp.exp[i][j] - 1]);
				if (getTruth(newExp.exp[i][j]) == array[newExp.exp[i][j] - 1]) { 
					break;
				}
			} else if (newExp.exp[i][j] < 0) {
			//	printf("ij is negative %d and the truth is %d and arr is %d\n", newExp.exp[i][j], getTruth(newExp.exp[i][j]), array[(-1) * newExp.exp[i][j] -1]);
				if (getTruth(newExp.exp[i][j]) == array[(-1) * newExp.exp[i][j] - 1]) {
					break;
				}
			}
			
			if (j==newExp.numLiterals[i]-1){
				return 0;
			}
		}
	}
	
	return 1;
}

char *classify() {    
// Evaluate the current expression and return one of
    // "satisfiable", "unsatisfiable" or "tautology".
	int truth[32];
	int i;
	int j;
	int result = 0;
	//tautology = 1
	//printf("tautologies: %d\n", tautology);
	if (tautology == num_clauses) {
		index = 0;
		tautology = 0;
		num_clauses=0;
		num_vals =0;
		return "tautology";
	}

	//printf("num clauses %d\n", num_clauses);
	
	int twoN = power(2, num_vals);
//	printf("twoN is %d\n", twoN);
	for (i=0; i<twoN; i++) {
		for (j=0; j<num_vals; j++) {
			truth[j] = (i>>j)&1;
			//printf("%d", truth[j]);
		}
		//printf("\n");
		result = evaluate(truth);
				
		//printf("i is %d", i);
		if (result == 1) {
			result = 0;
			index = 0;
			num_clauses = 0;
			num_vals = 0;
			tautology = 0;
			//newExp = NULL;
			return "satisfiable";
		}
		//else if (i == twoN - 1) {
		//	index = 0;
		//	num_clauses = 0;
		//	num_vals = 0;
			//return "unsatisfiable";
		//}
	
	}
	index = 0;
	tautology = 0;
	num_clauses = 0;
	num_vals = 0;
	return "unsatisfied";
}

int main(int argc, char *argv[]) {
    int i;
    for (i=1; i < argc; ++i) {
        read_dimacs(argv[i], init, add_clause);
        // if each read_dimac is doing a new test remember to reset globals
        printf("%s: %s\n", argv[i], classify());
    }
    return 0;
}

