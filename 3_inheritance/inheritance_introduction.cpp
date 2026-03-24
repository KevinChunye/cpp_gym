#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


class Triangle{
public:
    void triangle(){
        cout << "I am a triangle\n";
    }
};

class Isoceles: public Triangle{
public:
    void isoceles(){
        cout << "I am an isosceles triangle\n";
    }
    
    void description(){
        cout << "In an isosceles triangle two sides are equal\n";
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    Isoceles isc;
    isc.isoceles();
    isc.description();
    isc.triangle();
    return 0;
}
