#include <iostream>
#include <exception>
#include <string>
#include <stdexcept>
#include <vector>
#include <cmath>
using namespace std;

class Server {
public:
    static int load;

    static int compute(long long A, long long B) {
        load += 1; 

        // Case 1: invalid input → standard exception
        if (A < 0) throw invalid_argument("A is negative");

        // Case 2: may throw bad_alloc if A is huge
        vector<int> v(A, 0); // vector of integers with: size = A, all elements initialized to 0, If A is very large:

        // vector<int> v(1435434255433, 0);

        // 👉 the program tries to allocate huge memory
        // 👉 system says “nope”
        // 👉 throws: bad_alloc

        // Case 3: non-standard exception (int)
        if (B == 0) throw 0;

        // Normal computation
        int real = -1;
        real = (A / B) * real;

        // May throw out_of_range (standard exception)
        int ans = v.at(B);

        return real + A - B * ans;
    }
};

// init static variable
int Server::load = 0;

int main() {
    int T;
    cin >> T;

    while (T--) {
        long long A, B;
        cin >> A >> B;

        try {
            // Try to run computation
            cout << Server::compute(A, B) << endl;
        }

        //  Must come FIRST (most specific)
        catch (const bad_alloc&) {
            cout << "Not enough memory" << endl;
        }

        // Handles all standard exceptions
        catch (const exception& e) {
            cout << "Exception: " << e.what() << endl;
        }

        // Catch anything else (non-standard)
        catch (...) {
            cout << "Other Exception" << endl;
        }
    }

    // output total number of compute calls
    cout << Server::load << endl;

    return 0;
}