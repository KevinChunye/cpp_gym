#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Person {
public:
    string name;
    int age;

    virtual void getdata() = 0;
    virtual void putdata() = 0;

    virtual ~Person() {}
};

class Professor : public Person {
public:
    int publications;
    int cur_id;
    static int id_counter;

    Professor() {
        cur_id = ++id_counter;
    }

    void getdata() override {
        cin >> name >> age >> publications;
    }

    void putdata() override {
        cout << name << " " << age << " " << publications << " " << cur_id << endl;
    }
};

int Professor::id_counter = 0;

class Student : public Person {
public:
    int marks[6];
    int cur_id;
    static int id_counter;

    Student() {
        cur_id = ++id_counter;
    }

    void getdata() override {
        cin >> name >> age;
        for (int i = 0; i < 6; i++) {
            cin >> marks[i];
        }
    }

    void putdata() override {
        int sum = 0;
        for (int i = 0; i < 6; i++) {
            sum += marks[i];
        }
        cout << name << " " << age << " " << sum << " " << cur_id << endl;
    }
};

int Student::id_counter = 0;

int main() {
    int n;
    cin >> n;

    Person* persons[n];

    for (int i = 0; i < n; i++) {
        int type;
        cin >> type;

        if (type == 1) {
            persons[i] = new Professor;
        } else {
            persons[i] = new Student;
        }

        persons[i]->getdata();
    }

    for (int i = 0; i < n; i++) {
        persons[i]->putdata();
        delete persons[i];
    }

    return 0;
}
