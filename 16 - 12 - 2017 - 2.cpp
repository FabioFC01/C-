#include <iostream>
#include <string>

using namespace std;

struct person{
    string name;
    string surname;
    int age;
};

int main(){
    bool swap = true;
    int i;
    int j = 0;
    person vett[5];
    person temp;
    for(i = 0; i < 5; i++){
        cout <<"Insert your name : " ;
        cin >> vett[i].name;
        cout <<"Insert your surname : ";
        cin >> vett[i].surname;
        cout <<"Insert your age : ";
        do{
        cin >> vett[i].age;
        } while (vett[i].age < 0);
    }

    while(swap){
        swap = false;
        for(i = 0; i < 5-j-1; i++){
            if(vett[i].surname > vett[i+1].surname) {
                swap = true;
                //first part
                temp.name    = vett[i].name;
                temp.surname = vett[i].surname;
                temp.age     = vett[i].age;
                //second part
                vett[i].name    = vett[i+1].name;
                vett[i].surname = vett[i+1].surname;
                vett[i].age     = vett[i+1].age;
                //third part
                vett[i+1].name    = temp.name;
                vett[i+1].surname = temp.surname;
                vett[i+1].age     = temp.age;

            }
        }
        j++;
    }

    for(i = 0; i < 5; i++){
        cout << " ------------------------------- " << endl;
        cout << " NAME    : " << vett[i].name    << endl;
        cout << " SURNAME : " << vett[i].surname << endl;
        cout << " AGE     : " << vett[i].age     << endl;
    }
    return 0;
}
