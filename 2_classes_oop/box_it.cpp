#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;


class Box {
private:
    int l, b, h;
    
public:
    // default constructors
    Box(): l(0), b(0), h(0) {}
    
    // param constructor
    Box(int length, int breadth, int height) : l(length), b(breadth), h(height) {}
    
    // copy constructor
    Box(const Box& box) : l(box.l), b(box.b), h(box.h) {}
    
    // getters
    int getLength() const {
        return l;
    }
    
    int getBreadth() const {
        return b;
    }
    
    int getHeight() const {
        return h;
    }
    
    // volume
    long long CalculateVolume() const {
        return 1LL * l * b * h;
    }
    
    // overload <
    bool operator<(const Box& box2) const {
        if (l < box2.l) return true;
        if (l == box2.l && b < box2.b) return true;
        if (l == box2.l && b == box2.b && h < box2.h) return true;
        return false;
    }
    
    // overload <<
    friend ostream& operator<<(ostream& out, const Box& box) {
        out << box.l << " " << box.b << " " << box.h;
        return out;
    }
};

void check2(){
    int n;
    cin >> n;
    Box temp;
    
    for (int i = 0; i < n; i++) {
        int type;
        cin >> type;

        if (type == 1) {
            cout << temp << endl;
        }
        
        if (type == 2) {
            int l, b, h;
            cin >> l >> b >> h;
            Box NewBox(l, b, h);
            temp = NewBox;
            cout << temp << endl;
        }
        
        if (type == 3) {
            int l, b, h;
            cin >> l >> b >> h;
            Box NewBox(l, b, h);

            if (NewBox < temp) {
                cout << "Lesser\n";
            } else {
                cout << "Greater\n";
            }
        }
        if (type == 4){
            cout << temp.CalculateVolume() << endl;
        }
        
        if (type == 5){
            Box NewBox(temp);
            cout << NewBox << endl;
        }
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    check2();  
    return 0;
}
