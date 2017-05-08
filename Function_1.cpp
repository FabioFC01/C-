#include<iostream>
#include<iomanip>
using namespace std;
double multiplication (double base,double height) {
	return base*height;
}
int main(){
	double a;
	double b;
	cout <<"Insert first number :";
	cin>> a;
	cout <<"Insert second number :";
	cin>> b;
	cout<<multiplication(a,b);
	system("pause");
	return 0;
}
