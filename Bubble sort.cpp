#include <iostream>
#include <iomanip>
using namespace std;
int main() {
	int vettore [6];
	int dim = 6;
	int i;
	int j;
	int x;
	bool scambio = true;
	int n = dim - 1;
	
	for (i = 0; i < 6; i++ ) {
		cout << "Inserisci un numero intero : ";
		cin >> vettore [i];
	}
	while (scambio && n > 0 ) {
		scambio = false;
		for(j = 0; j < n; j++) {
			if(vettore [j] > vettore [j+1]) {
				x = vettore [j];
				vettore [j] = vettore [j+1];
				vettore [j+1] = x;
				scambio = true;
			}
		}
	}
	cout <<"Vettore ordinato in maniera crescente" << endl;
	for (i = 0; i < 6; i++ ) {
		cout << vettore [i] << endl;
	}
	system("pause");
	return 0;
}
