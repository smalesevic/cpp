#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int CHARS = 92;
const int ASCII_OFFSET = 32;
const int MAX_LENGTH = 5;
string PASSWORD; 

bool check_correct(string pw_guess){
  if(pw_guess == PASSWORD){
    cout << "hahah we know your password it's " << string(pw_guess) << endl;
    return true;
  }
  return false;
}

bool crack_w_dict(int max_length){
  ifstream common_pws;
  string pw_guess;
  common_pws.open("/Users/djole/code/algo/cplus/pw_dictionary");
  while(getline(common_pws, pw_guess)){
    if(check_correct(string(pw_guess))){
      cout << "hahah your password is basic" << string(pw_guess) << endl;
      common_pws.close();
      return true;  
    }
  }
  common_pws.close();
  return false;
}

bool crack(char passw[], int position, int length){
  if (position >= length){
    return check_correct(passw); 
  } else {
    for(int i=0;i< CHARS;i++){
      passw[position] = ASCII_OFFSET + i; 
      passw[position+1] = '\0';
      if (crack(passw, position+1, length)){
        return true; 
      } 
    }
    return false;
  }
}

bool crack_max_length(int length){
  char pw[length];
  for(int i=1;i<=length;i++){
    cout << "Trying to crack with length:" << i << endl;
    if(crack(pw, 0, i)){
      return true; 
    } 
  }
  return false; //really shouldn't reach here ever
}

int main(){
  char password[MAX_LENGTH];
  cout << "Enter password of max length:" << MAX_LENGTH <<endl;  
  cin >> password;
  PASSWORD = string(password);
  if(crack_max_length(MAX_LENGTH)){
    cout << "we cracked it we're such hackerz" << endl; 
  } else {
    cout << ":( sad day in hacker town" << endl;
  }
  return 1;
}
