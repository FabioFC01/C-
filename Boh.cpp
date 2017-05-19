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
	double max = 0;
	double min = 9541651563;
	cout << "Inserire numero di persone(massimo 70): ";
	cin >> a;
	for (i = 0; i < a; i++) {
		people[i].Name = name();
		people[i].Cm = cm();
			if (people[i].Cm > max) {
				max = people[i].Cm;
		}
			if (people[i].Cm < min) {
				min = people[i].Cm;
			}
	}
	cout << "il valore maggiore e' "<< max << " e il valore minore e' "<< min <<endl;
	system("pause");
	return 0;
}