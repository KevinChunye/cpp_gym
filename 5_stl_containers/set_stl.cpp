#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

// insert / erase / find = O(log n), set = unique + sorted
int main(){
    int Q;
    cin >> Q;

    set<int> s;

    while (Q--){
        int type, x;

        cin >> type >> x;

         if (type == 1) {
            s.insert(x); // insert x into set, if x already present it will not be inserted again
         }
         else if (type == 2){
            s.erase(x); // remove x from set if present

         }
         else if (type == 3){
            if (s.find(x) != s.end()){
                cout << "Yes" << endl; // x found in set
            }
            else{
                cout << "No" << endl; // x not found in set
            }
         }
    }
    return 0;
}


