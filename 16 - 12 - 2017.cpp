#include <iostream>
#include <string>

using namespace std;

struct person{
    string name;
    string surname;
    int age;
};

int main(){
    int i;
    person vett[2];
    for(i = 0; i < 2; i++){
        cout <<"Insert your name : " ;
        cin >> vett[i].name;
        cout <<"Insert your surname : ";
        cin >> vett[i].surname;
        cout <<"Insert your age : ";
        do{
        cin >> vett[i].age;
        } while (vett[i].age < 0);
    }

    for(i = 0; i < 2; i++){
        cout << " ------------------------------- " << endl;
        cout << " NAME    : " << vett[i].name    << endl;
        cout << " SURNAME : " << vett[i].surname << endl;
        cout << " AGE     : " << vett[i].age     << endl;
    }
    return 0;
}
