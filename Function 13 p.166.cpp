#include <iostream>
#include <iomanip>
using namespace std;
void function(float cm, float kg){
	if(cm-100<kg){
		cout <<"Sovrappeso" <<endl;
	}
	if(cm-100==kg){
		cout <<"Normopeso" <<endl;
	}
	if(cm-100>kg){
		cout <<"Sottopeso" <<endl;
	}
}
int main() {
	float altezza;
	float peso;
	cout <<"Inserire altezza: ";
	cin >> altezza;
	cout <<"Inserire peso   : ";
	cin >> peso;
	function(altezza, peso);
	system("pause");
	return 0;
}
