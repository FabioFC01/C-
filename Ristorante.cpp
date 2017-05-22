#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct piatto {
	string nome;
	float prezzo;
	float calorie;
}menu[10];

int main() {
	int a;
	int n=99;
	float prezzo_tot = 0;
	float calorie_tot = 0;
	
	menu [0] = {"Pasta alla carbonara", 10.99, 579};
	menu [1] = {"Pasta al pomodoro", 5.99, 479};
	menu [2] = {"Insalata cappuccina", 0.99,19};
	menu [3] = {"Fagiolini", 1.49,20};
	menu [4] = {"Patate al forno", 2.99, 209};
	menu [5] = {"Pizza con pomodoro e mozzarella", 7.99,315};
	menu [6] = {"Petto di pollo", 8.59, 478};
	menu [7] = {"Coca cola" , 0.99, 400};
	menu [8] = {"Acqua", 0.49, 0};
	menu [9] = {"Caffe'",0.99,25};
	
	for(a=0;a<10;a++) {
		cout <<a << setw(10) << menu[a].prezzo << setw(10) << menu[a].calorie << setw(30) << menu[a].nome << endl;
	}
	cout <<"-------------------------" <<endl;
	do{
		cout <<"Scegli un cibo scrivendone il numero corrispondente (premi 100 per terminare): ";
		cin >> n;
		prezzo_tot += menu[n].prezzo;
		calorie_tot += menu[n].calorie;
		cout <<"Hai scelto " <<menu[n].nome << endl;
		cout <<"Prezzo attuale :" << prezzo_tot << " e calorie: " << calorie_tot << endl;
		cout <<"------------------------------" << endl; 
	}
	while(n != 100);
	cout <<"Il prezzo da pagare e' di: "<< prezzo_tot << endl;
	cout <<"Le calorie ingerite sono : "<< calorie_tot << endl;
	system("pause");
	return 0;
}
