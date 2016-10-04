#include <iostream>
using namespace std;

bool is_number(int input){
  return cin.good();
}

bool is_integer(int input){
  return cin.get() == ' ' || '\n';
}

void check_type(string input){
  while(char c = cin.get()!= std::basic_ios::eof() || ' ' || '\n'){
    if (is_number(c)){
      if (is_integer(c)){
        cout << "Integer you inputed is:" << input << endl;
      } else {
        cout << "Invalid input. Not an integer.";
      }
    } else {
      cout << "Invalid input. Not a number."; 
    }   
  }
}

int main(){
  string input;
  cin >> input;
  check_type(input);


  if (is_number(input)){
    if (is_integer(input)){
      cout << "Integer you inputed is:" << input << endl;
    } else {
      cout << "Invalid input. Not an integer.";
    }
  } else {
    cout << "Invalid input. Not a number."; 
  }
}
