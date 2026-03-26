#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
/*
key concepts:
inheritance
virtual functions
abstract base classes
base-class pointers
static class variables

Person
├── Professor
└── Student

*/
class Person{
    public:
        string name;
        int age;
        virtual void getdata()  = 0; // set to 0, so makes them pure virtual functions.
        virtual void putdata() = 0; // So Person becomes an abstract class, Person p; not allowed
        
        virtual ~Person(){}
        /*
        You cannot create a plain Person.
        You can only create derived classes like: Professor,Student

        we use virtual function cuz: C++ needs to decide whether to call:

        Professor::getdata()
        or Student::getdata()

        Because the functions are virtual, C++ uses the actual object type at runtime.
        That is polymorphism.
        So if persons[i] points to a Professor, it calls professor version.
        If it points to a Student, it calls student version.
        */
};

class Professor : public Person{
    public:
        int publications;
        int cur_id;
        static int id_counter;

        Professor(){
            cur_id = ++ id_counter;
        }

        void getdata() override {
            cin >> name >> age >> publications;
        }

        void putdata() override {
            cout << name << " " << age << " " << publications << " " << cur_id << endl;
        }
};

int Professor :: id_counter = 0;

class Student : public Person{
    public:
    int marks[6];
    int cur_id;
    static int id_counter;

    Student(){
        cur_id = ++ id_counter;
    }

    void getdata() override {
        cin >> name >> age;
        for (int i = 0; i < 6; i++){
            cin >> marks[i];
        }
    }

    void putdata() override{
        int sum = 0;
        for (int i = 0; i < 6; i++){
            sum += marks[i];
        }
        cout << name << " " << age << " " << cur_id << endl;
    }
};

int Student :: id_counter = 0;
int main(){
    int n;
    cin >> n; //The number of objects that is going to be created.
    Person *persons[n];

    for(int i = 0;i < n;i++){
        int type;
        cin >> type;

        if (type == 1){
            persons[i] = new Professor;
        } else {
            persons[i] = new Student;
        }
        persons[i]-> getdata();
    }

    for (int i = 0; i < n; i++){
        persons[i] -> putdata();
        delete persons[i];
    }
    return 0;
}
