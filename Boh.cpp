#include <iostream>
#include <string>
using namespace std;

double cm() {
	double cm;
	cout << "Inserire altezza: ";
	cin >> cm;
	return cm;
}

string name() {
	string persona;
	cout << "Inserire nome  : ";
	cin >> persona;
	return persona;
}

struct People {
	string Name;
	double Cm;
} people[70];

int main() {
	int a;
	int i;
	double avg = 0;
	cout << "Inserire numero di persone(massimo 70): ";
	cin >> a;
	for (i = 0; i < a; i++) {
		people[i].Name = name();
		people[i].Cm = cm();
		avg += people[i].Cm;
	}
	cout << avg / a;
	system("pause");
	return 0;
}