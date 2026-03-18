#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

vector<int> parseInts(string str){ // Function signature
    stringstream ss(str); // Now the stream contains: 23,4,56; (23)pointer starts here
    vector<int> vec; // prep storage
    int num;
    char ch;
    while (ss >> num){ // >> returns true if extraction succeeds, keep reading integers until reading fails, fail if no int left
        vec.push_back(num); // Push into vector vec.push_back(num);Vector now: [23]
        ss >> ch; // discard comma
    }
    return vec;
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    string str;
    cin >> str;
    vector<int> integers = parseInts(str);
    for(int i = 0; i < integers.size(); i++){
        cout << integers[i] << "\n";
    } 
    return 0;
}
