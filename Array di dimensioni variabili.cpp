#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct student {
	string Name;
	string Surname;
	string Class;
	float marks[200];
}student[200];

int main() {
	float *sum; // Sarà il mio array
	float *avg;
	int i;
	int a;
	int d;
	int k;

	printf("Quanti elementi deve avere l'array? ");
	scanf_s("%d", &k);

	// Alloco il mio array:
	sum = (float *)malloc(k * sizeof(int));
	avg = (float *)malloc(k * sizeof(int));

	//insert data
	for (a = 0; a < k; a++) {
		avg[a] = 0;
		sum[a] = 0;
		cout << endl;
		cout << "Insert student's name "<< a+1 <<": ";
		cin >> student[a].Name;
		cout << "Insert student's surname "<< a+1 <<": ";
		cin >> student[a].Surname;
		cout << "Insert student's class "<< a+1 <<": ";
		cin >> student[a].Class;
		cout << "Insert number of marks(max 200) " << a + 1 <<": ";
		cin >> d;
		for (i = 0; i<d; i++) {
			cout << "    ";
			cout << "Insert mark number " << i + 1 << ": ";
			cin >> student[a].marks[i];
			sum[a] += student[a].marks[i];
		}
		avg[a] = sum[a] / d;
	}
	//cout data
	for (a = 0; a < k; a++) {
		cout << "The average mark of student " << student[a].Surname << " " << student[a].Name << " is " << avg [a] << endl;
	}
	system("pause");
	return 0;
}