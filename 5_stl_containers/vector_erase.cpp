#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main(){
    int n;
    cin >> n;

    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }

    int x;
    cin >> x;

    int a, b;
    cin >> a >> b;

    // erase single element (convert to 0 based)
    v.erase(v.begin() + (x - 1));

    // erase range [a-1, b-1)
    v.erase(v.begin() + (a - 1), v.begin() + (b - 1));  

    // output
    cout << v.size() << endl;

    for (int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    return 0;
}
