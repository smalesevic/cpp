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

void setZero(){
	index = 0;
	tautology = 0;
	num_clauses = 0;
	num_vals = 0;
}

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
	
	for (i=0; i<numlits; ++i) {
        	newExp.exp[index][i] = literals[i];
    	}

	index++;

	int check = 0;
	if (numlits > 1) {
		for (x=0; x<numlits; ++x) {
			for (y=x+1; y<numlits; ++y) {
				if (literals[x] == (literals[y]*(-1))) {
					tautology++;
					check = 1;
					break;
				}
			}
		}
	}
}

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
	for (i=0; i<num_clauses; ++i) {    //clause in expression:
		for (j=0; j<newExp.numLiterals[i]; ++j) {  //idx in clause:
			if (newExp.exp[i][j] > 0) {
				if (getTruth(newExp.exp[i][j]) == array[newExp.exp[i][j] - 1]) { 
					break;
				}
			} else if (newExp.exp[i][j] < 0) {
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
	
	if (tautology == num_clauses) {
		setZero();
		return "tautology";
	}

	int twoN = power(2, num_vals);
	
	for (i=0; i<twoN; ++i) {
		for (j=0; j<num_vals; ++j) {
			truth[j] = (i>>j)&1;
		}
		result = evaluate(truth);
				
		if (result == 1) {
			result = 0;
			setZero();
			return "satisfiable";
		}
	}
	setZero();
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

