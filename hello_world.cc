#include<iostream>

using namespace std;

int add(int x, int y){
	int result = x+y;
	return result;
}

int main(){
	cout <<"Hello World!!\n";
	int a = 5;
	int b = 4;
	int result = add(a,b);
	cout << result;
	cout << "\n";
	return result;
}
