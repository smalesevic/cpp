#include <iostream>
#include <iomanip>

using namespace std;

int main()

{
double A;
double B;


	cout << "Enter two numbers each separated by a space: ";
	cin >> A;
	cin >> B;
	cout << setprecision(20) << fixed;		
	cout << "A/B: " << A/B << endl;
return 0;
}
