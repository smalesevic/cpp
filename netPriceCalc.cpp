#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double a;
    double b;
    double c;
    float d;
    
    cout<< setprecision(2) <<fixed;
    cout<<"Enter the offer price of the item: ";
    cin>> a;
    cout<<endl;
    cout<<"Discount rate (%): ",
    cin>> b;
    cout<<endl;
    cout<<"Tax rate (%): ";
    cin>> c;
    cout<<endl;
    d = (a*(1-0.01*b))*(1+(.01*c));
    cout<<"The net price of the item is: ";
    cout<< d <<endl;
    return 0;
}
