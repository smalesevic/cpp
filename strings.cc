#include <iostream>
#include <string>

using namespace std;


void alter_things(char chars[]){
  for(int i=0; i<9;i++){
    chars[i] = 'b';
  }

  cout << chars << endl;
}


int main(){
  string str;
  string *pstr;

  char chars[9];
  char *pchars[9];
  //cout << sizeof(chars);
  

  for(int i = 0;i<9;i++){
    chars[i] = 'a';
  }
  chars[8] = '\0';

  cout << chars << endl;

  alter_things(chars);
  
}
