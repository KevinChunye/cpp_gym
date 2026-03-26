#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

int main(){
    int Q;
    cin >> Q;

    map<string, int> m;

    while (Q--){
        int type;
        cin >> type;

         if (type == 1) {
            string name;
            int marks;
            cin >> name >> marks;

            m[name] += marks; // add marks to name, if name not present it will be created with 0 marks and then marks will be added
         }
         else if (type == 2){
            string name;
            cin >> name;

            m.erase(name); // remove name from map if present

         }
         else if (type == 3){
            string name;
            cin >> name;

            cout << m[name] << endl; // print marks, 0 if name not present in map
         }
    }
    return 0;
}