// toStr(x): the # operator stringifies its argument at the preprocessor level.
// toStr(Result =) --> "Result =" (the text becomes a string literal, not a variable)
#define toStr(x) #x

// INF: use the platform's true integer ceiling from <climits> so this never
// INT_MAX / INT_MIN are guaranteed by the C++ standard to be the largest /
#define INF  INT_MAX
#define NINF INT_MIN

// io(v): expands to "cin >> v".
#define io(v) cin >> v

// FUNCTION(name, op): pastes a full function body, substituting name and op.
//   FUNCTION(minimum, <)  -->  void minimum(int& a, int b){ if(b < a){ a=b; } }
//   FUNCTION(maximum, >)  -->  void maximum(int& a, int b){ if(b > a){ a=b; } }
#define FUNCTION(name, op) void name(int& a, int b) { if (b op a) { a = b; } }

// foreach(v, i): expands to a standard index loop over any object with .size().
#define foreach(v, i) for (int i = 0; i < (int)v.size(); i++)


#include <iostream>
#include <vector>
#include <climits> // required for INT_MAX / INT_MIN
using namespace std;

#if !defined toStr || !defined io || !defined FUNCTION || !defined INF
#error Missing preprocessor definitions
#endif

FUNCTION(minimum, <)
FUNCTION(maximum, >)

int main() {
    int n; cin >> n;

    if (n <= 0) {
        cout << toStr(Result =) << ' ' << 0;
        return 1;
    }

    vector<int> v(n);
    foreach(v, i) {
        io(v)[i];
    }

    int mn = INF;  
    int mx = NINF; 

    foreach(v, i) {
        minimum(mn, v[i]);
        maximum(mx, v[i]);
    }

    int ans = mx - mn;
    cout << toStr(Result =) << ' ' << ans;
    return 0;
}