#include <iostream>
using namespace std;

/*
==========================================================
Core Idea:
We are given a sequence of bool template parameters like:

    reversed_binary_value<1,0,1>()

These represent a binary number in REVERSED order:
    least significant bit first

So:
    <1,0,1> = 1*(2^0) + 0*(2^1) + 1*(2^2) = 5

We compute this using recursion over template parameters.
==========================================================
*/


// ================= BASE CASE =================
// When there is ONLY ONE bit left
// Example: reversed_binary_value<1>() -> returns 1
//          reversed_binary_value<0>() -> returns 0
template <bool a>
int reversed_binary_value() {
    return a;
}


// ================= RECURSIVE CASE =================
// When we have at least TWO bits: a, b, d...
//
// Example:
// reversed_binary_value<1,0,1>()
//   a = 1
//   rest = <0,1>
//
// Logic:
// 1. Compute value of the rest: reversed_binary_value<0,1>()
// 2. Shift it left by 1 (multiply by 2)
// 3. Add current bit 'a'
//
// So:
//   value = (rest_value << 1) + a
//
template <bool a, bool b, bool... d>
int reversed_binary_value() {
    return (reversed_binary_value<b, d...>() << 1) + a;
}


/*
==========================================================
CheckValues: Generates ALL combinations of bits

CheckValues<6>::check(x, y)

means:
- generate all 6-bit binary numbers
- for each combination, compute its value
- check if it matches x (with offset y)
==========================================================
*/


// Recursive generator of all bit combinations
template <int n, bool... digits>
struct CheckValues {

    static void check(int x, int y) {

        // Add a 0 at the front and recurse
        CheckValues<n - 1, 0, digits...>::check(x, y);

        // Add a 1 at the front and recurse
        CheckValues<n - 1, 1, digits...>::check(x, y);
    }
};


// Base case: when n == 0
// We now have a FULL sequence of bits in digits...
template <bool... digits>
struct CheckValues<0, digits...> {

    static void check(int x, int y) {

        // Convert bits into integer value
        int z = reversed_binary_value<digits...>();

        // Print 1 if condition matches, else 0
        cout << (z + 64 * y == x);
    }
};


/*
==========================================================
Main:
- Read test cases
- For each test:
    - generate all 64 (2^6) combinations
    - print a 64-length string of 0/1
==========================================================
*/
int main() {

    int t;
    cin >> t;

    for (int i = 0; i != t; ++i) {

        int x, y;
        cin >> x >> y;

        // Generate all 6-bit combinations
        CheckValues<6>::check(x, y);

        cout << "\n";
    }
}