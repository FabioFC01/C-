#include <iostream>
#include <cmath>
using namespace std;
int main() {
	int ip [4];
	int ip1[4];
	int byte1 [8];
	int byte2 [8];
	int byte3 [8];
	int byte4 [8];
	int i;
	
	cout <<"Inserire per 4 volte un numero." << endl;
	cout <<"Il numero deve essere compreso tra 0 e 255" << endl;
	for( i = 0; i < 4; i++) {
		cout << "Inserire numero " << i << "  : ";
		do {
			cin >> ip [i];
			ip1 [i] = ip [i];
		} while (ip [i] < 0 || ip[i] > 255);
	}
	//primo byte
	for(i = 8; i > 0 ; i--) {
		if( pow (2,i) > ip1[0] ) {
			byte1[i] = 1;
			ip1[0] - pow(2,i);
		}
		else {
		   byte1[i] = 0;
	}
	for(i = 0; i < 8 ; i++) {
		cout << byte1[i];
	}
	//secondo byte
	for(i = 8; i > 0 ; i--) {
		if( pow (2,i) > ip1[1] ) {
			byte2[i] = 1;
			ip1[1] - pow(2,i);
		}
		else {
		  byte2[i] = 0;
	}
	for(i = 0; i < 8 ; i++) {
		cout << byte2[i];
	}
	//terzo byte
	for(i = 8; i > 0 ; i--) {
		if( pow (2,i) > ip1[2] ) {
			byte3[i] = 1;
			ip1[2] - pow(2,i);
		}
		else{
		   byte3[i] = 0;
	}
	for(i = 0; i < 8 ; i++) {
		cout << byte3[i];
	}
	//quarto byte
	for(i = 8; i > 0 ; i--) {
		if( pow (2,i) > ip1[3] ) {
			byte4[i] = 1;
			ip1[3] - pow(2,i);
		}
		else{
		   byte3[i] = 0;
	}
	for(i = 0; i < 8 ; i++) {
		cout << byte3[i];
	}
	//robbe
	cin >> i;
	return 0;
}
