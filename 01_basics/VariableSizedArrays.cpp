#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // speeds up c++ I/O by disabling synchronization with c stdio
    // help when input large

    int rows, queries;
    cin >> rows >> queries;
    // rows = nums of var len arr
    // queries = num of queries we need to answer

    vector<vector<int>> arr(rows);
    // 2d arr
    for (int i = 0; i < rows; i++){
        int size;
        cin >> size;
        // size, num ele in this row
        
        arr[i].resize(size);
        // reseize the ith vector to hold size

        for (int j = 0; j < size; j++){
            cin >> arr[i][j];
            // fill each ele in this row
        }
    }
    while (queries--){
        // loop runs queries time
        int r, c;
        cin >> r >> c;
        cout << arr[r][c] << '\n';
        // access elements
    }
    return 0;
}
