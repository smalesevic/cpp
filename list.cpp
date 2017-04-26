#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

void lowercase(vector<string>&some_list){
    int LENGTH = some_list.size();
    
    for (int i=0; i<LENGTH; i++){
        string word = some_list[i];
        int j=0;
        
        while (word[j] != 0){
            word[j] = tolower(word[j]);
            j++;
            some_list[i] = word;
        }
    }
}    


int main()
{
    string line;
    vector<string>listA;
    vector<string>listB;
    vector<string>listC;

    ifstream myfile("/Desktop/myfile.txt");
    ifstream qfile("/Desktop/qfile.txt");

    while (getline(myfile, line)){
        listA.push_back(line);
    }
   
    while (getline(qfile, line)){
        listB.push_back(line);
    }

    int LENGTHA = listA.size();
    int LENGTHB = listB.size();
    
    lowercase(listA);
    lowercase(listB);

    for (int i=0; i<LENGTHA; i++){
        int j=0;
        if (listA[i] == listB[j]){
                i++;
                j=0;
         }
       
        while (listA[i] != listB[j]) {
            j++;

            if (j == LENGTHB){
               listC.push_back(listA[i]);
                break;
            }
        }
    }
    
    sort (listC.begin(), listC.end());
    int LENGTHC = listC.size();
    
    for (int i=0; i<LENGTHC; i++){
        cout << listC[i] << endl;
    }

    return 0;
}
