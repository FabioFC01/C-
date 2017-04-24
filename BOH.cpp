#include <iostream>
#include <string>
using namespace std;


struct student {
	string Name;
	string Surname;
	string Class;
	float marks[20];
}student1;

int main(){
	int i;
	int d;
	float somma=0;
	
	cout <<"Insert student's name: ";
	cin >>student1.Name;
	cout <<"Insert student's surname: ";
	cin >> student1.Surname;
	cout <<"Insert student's class: ";
	cin >> student1.Class;
	cout <<"Insert number of marks";
	cin >> d;
	cout <<" ------------------------------------- " <<endl;
	for(i=0;i<d;i++) {
		cout <<"Insert mark number "<< i+1 <<": ";
		cin >> student1.marks[i];
		somma+= student1.marks[i];
	}
	cout <<"The average mark is " <<somma / (float)d <<endl;
	return 0;
}
