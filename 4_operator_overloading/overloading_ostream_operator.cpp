#include <iostream>

using namespace std;

class Person{
public:
    Person(const string& first_name, const string& last_name) : first_name(first_name), last_name(last_name) {}

    const string& getFirstName() const { return first_name; }
    const string& getLastName() const { return last_name; }

private:
    string first_name;
    string last_name;

};

ostream& operator<<(ostream& out, const Person& p){
    out << "first_name =" << p.getFirstName() << " " << "last_name =" << p.getLastName();
    return out;
}

int main(){
    string first_name, last_name, event;
    cin >> first_name >> last_name >> event;

    Person p(first_name, last_name);
    cout << p << " is attending " << event << endl;
    return 0;
}