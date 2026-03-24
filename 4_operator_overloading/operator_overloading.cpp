#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Matrix{
public:
    vector<vector<int>> a;
    // Matrix operator+
    // Matrix operator+(const Matrix& y)
    // works on custom types
    // defined inside a class
    // tied to object (this)
    Matrix operator+(const Matrix& y) const { // Same idea as: int add(int a, int b); y is not a fresh copy, but refers to the original object and not to modify
        // here define what + do 
        int n = a.size();
        int m = a[0].size();

        Matrix result;
        result.a.resize(n, vector<int>(m)); // makes result.a an n x m matrix.

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                result.a[i][j] = a[i][j] + y.a[i][j];
            }
        }
        return result;
    }
};

int main () {
    int cases;
    cin >> cases;
    while(cases--){
        int n, m;
        cin >> n >> m;
        
        Matrix x, y;
        x.a.resize(n, vector<int>(m));
        y.a.resize(n, vector<int>(m));
        
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                cin >> x.a[i][j];
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> y.a[i][j];
            }
        }

        Matrix result = x + y;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << result.a[i][j] << " ";
            }
            cout << endl;
        }
    }
   return 0;
}
