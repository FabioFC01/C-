#include<iostream>
#include<iomanip>
using namespace std;
double calcola_area(int base,int altezza) {
	return base*altezza;
}
int main(){
	int a;
	int b;
	cin>> a;
	cin>> b;
	cout<<calcola_area(a,b);
	system("pause");
	return 0;
}
