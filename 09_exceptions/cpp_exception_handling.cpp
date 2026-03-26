#include <iostream>
#include <stdexcept>

using namespace std;

// Finds the largest proper divisor of n
int largest_proper_divisor(int n) {
    // Edge case: 0 has no proper divisors
    if (n == 0) {
        throw invalid_argument("largest proper divisor is not defined for n=0");
    }

    // Edge case: 1 has no proper divisors
    if (n == 1) {
        throw invalid_argument("largest proper divisor is not defined for n=1");
    }

    // Start from n/2 and go downward
    // because the largest proper divisor must be <= n/2
    for (int i = n / 2; i >= 1; --i) {
        if (n % i == 0) {
            return i;  // first match is the largest
        }
    }

    return -1; 
}

// Handles input and exception flow
void process_input(int n) {
    try {
        int d = largest_proper_divisor(n);

        // If successful, print result
        cout << "result=" << d << endl;
    }
    catch (const invalid_argument& e) {  
        // Catch exception by const reference avoid copying
        cout << e.what() << endl;
    }

    cout << "returning control flow to caller" << endl;
}

int main() {
    int n;
    cin >> n;

    process_input(n);

    return 0;
}