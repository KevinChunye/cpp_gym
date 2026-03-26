#include <iostream>
#include <deque> 
#include <vector>

using namespace std;

void printKMax(const vector<int>& arr, int k) {
    deque<int> dq;  // stores indices

    for (int i = 0; i < arr.size(); i++) {
        // Remove indices that are out of this window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }

        // Remove indices whose values are <= current value
        while (!dq.empty() && arr[dq.back()] <= arr[i]) {
            dq.pop_back();
        }

        // Add current index
        dq.push_back(i);

        // Start printing once first full window is formed
        if (i >= k - 1) {
            cout << arr[dq.front()];
            if (i != arr.size() - 1) cout << " ";
        }
    }
    cout << "\n";
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N, K;
        cin >> N >> K;

        vector<int> arr(N);
        for (int i = 0; i < N; i++) {
            cin >> arr[i];
        }

        printKMax(arr, K);
    }

    return 0;
}
