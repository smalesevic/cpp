#include <iostream>
#include <bitset>
using namespace std;

int main()
{
    int a;
    int b;
    int c;
    int d;
    
    cout << "Enter two integers numbers (each separated by a space): ";
    cin >> a;
    cin >> b;
    c = a>>b;
    d = c & 1;
    cout << "The value of Bit " << b << " is: ";
    cout << d <<endl;
    
    return 0;
}
