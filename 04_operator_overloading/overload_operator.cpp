//Operator Overloading

#include<iostream>

using namespace std;


class Complex{
public:
    int a,b;
    
    void input(string s){
        int v1 = 0;
        int i = 0;

        while(s[i] != '+'){
            v1 = v1*10 + s[i] - '0';
            i++;
        }

        i++;  // skip '+'
        i++;  // skip 'i'

        int v2 = 0;
        while(i < s.length()){
            v2 = v2*10 + s[i] - '0';
            i++;
        }
        a = v1;
        b = v2;
    }
};

Complex operator + (const Complex& A, const Complex& B){
    // because it avoids copying and makes it clear we are not modifying the inputs.
    Complex result;
    result.a = A.a + B.a;
    result.b = A.b + B.b;
    return result;
}

ostream& operator<<(ostream& out, const Complex& c){
    // ostream& → returns the output stream by reference
    // operator<< → overloads <<
    // ostream& out → usually this is cout
    // const Complex& c → the complex number to print
    out << c.a << "+i" << c.b;
    return out;
}

int main(){
    Complex x, y;
    string s1, s2;
    cin >> s1 >> s2;

    x.input(s1);
    y.input(s2);

    Complex z = x + y;
    cout << z << endl;
    return 0;
}