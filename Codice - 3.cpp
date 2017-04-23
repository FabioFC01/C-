#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

struct tm newtime;
__time32_t aclock;

int main() {
	//declaration
	string Phrase;
	int a;
	int b;
	int c;
	int l;
	int n;
	int i = 0;

	//time
	char buffer[32];
	errno_t errNum;
	_time32(&aclock);   // Get time in seconds
	_localtime32_s(&newtime, &aclock);   // Tempo in struct tm
	errNum = asctime_s(buffer, 32, &newtime); // Cout time

											  //open data
	fstream phrase;
	phrase.open("phrase.txt", ios::out | ios::app);

	//in case of error during opening file
	if (!phrase) {
		cout << "ERROR during opening file" << endl << endl;
		cout << "End ";
		system("pause");
		return 1;
	}
	//writing time in cmd
	if (errNum)
	{
		printf("Error code: %d", (int)errNum);
		return 1;
	}
	printf("%s", buffer);

	//writing time in txt
	if (errNum)
	{
		phrase << ("Error code: %d", (int)errNum);
		return 1;
	}
	phrase << ("%s", buffer);

	//output program
	cout << "Insert a phrase(only capital letters and do not use punctuation or accents)" << endl;
	getline(cin, Phrase);
	l = Phrase.length();
	for (a = 0; a < 26; a++) {
		for (b = 0; b < 26; b++) {
			for (c = 0; c < 26; c++) {
				for (n = 0; n < l; n++) {
					if (n % 3 == 0) { // if the position is 1
						if (char(Phrase[n] == 32)) {
							cout << char(32);
							phrase << char(32);
						}
						else
							if (char(Phrase[n] + a <= 90)) {
								cout << char(Phrase[n] + a);
								phrase << char(Phrase[n] + a);
							}
							else {
								cout << char(Phrase[n] + a - 26);
								phrase << char(Phrase[n] + a - 26);
							}
					}
					if (n % 3 == 1) {	//if the position is 2
						if (char(Phrase[n] == 32)) {
							cout << char(32);
							phrase << char(32);
						}
						else
							if (char(Phrase[n] + b <= 90)) {
								cout << char(Phrase[n] + b);
								phrase << char(Phrase[n] + b);
							}
							else {
								cout << char(Phrase[n] + b - 26);
								phrase << char(Phrase[n] + b - 26);
							}
					}
					if (n % 3 == 2) {	//if the position is 2
						if (char(Phrase[n] == 32)) {
							cout << char(32);
							phrase << char(32);
						}
						else
							if (char(Phrase[n] + c <= 90)) {
								cout << char(Phrase[n] + c);
								phrase << char(Phrase[n] + c);
							}
							else {
								cout << char(Phrase[n] + c - 26);
								phrase << char(Phrase[n] + c - 26);
							}
					}
					
				}	//end of fourth for
				i++;
				cout << "   " << i;
				phrase << "   " << i;
				cout << endl;
				phrase << endl;
			}	//end of third for

		}//end of second for
	}//end of first for
	phrase << endl << endl;
	system("pause");
	return 0;
}