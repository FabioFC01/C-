#include <iostream>
#include <string>
using namespace std;

double cm(){
	double cm;
	cout <<"Inserire altezza: ";
	cin >> cm;
	return cm;
}

string name(){
	string persona;
	cout <<"Inserire nome  : ";
	cin >> persona;
	return persona;
}

struct People {
	int n=70;
	string Name;
	double Cm;
}; people[n];

int main(){
	int i=0;
	int a=0;
	int 
	double somma=0;
	do{
		people[i].Name=name
		people[i].Cm=cm;
		i++;
		somma+= people[i].Cm;
		cout <<"Inserire 0 per continuare, un altro numero per terminare: ";
		cin >> a;
	}
	while(a=0);
	cout <<somma/(i+1);
	return 0;
}
