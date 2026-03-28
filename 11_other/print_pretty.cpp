
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    int T; cin >> T;

    while (T--) {
        double A, B, C;
        cin >> A >> B >> C;

        // Snapshot the current flag state before we touch anything.
        // cout.flags() returns a bitmask of all active format flags.
        ios_base::fmtflags saved_flags(cout.flags());

        // ----------------------------------------------------------------
        // A: truncate to integer, print as lowercase hex with "0x" prefix
        // ----------------------------------------------------------------
        // trunc() drops the fractional part toward zero (not floor).
        // Cast to long long so cout treats it as an integer, not a double.
        long long A_int = static_cast<long long>(trunc(A));

        // showbase   -- prepend "0x" for hex, "0" for octal
        // hex        -- switch integer output to base 16
        // nouppercase (default) -- letters a-f, not A-F
        cout << showbase << nouppercase << hex << A_int << "\n";

        // ----------------------------------------------------------------
        // B: signed, 2 decimal places, right-justified, 15 chars, '_' fill
        // ----------------------------------------------------------------
        // Flag interactions to watch here:
        //   showpos   -- prepend '+' for positive numbers (required by spec)
        //   fixed     -- use fixed-point notation (not scientific)
        //   setprecision(2) -- 2 digits after decimal point
        //   setw(15)  -- field width of 15 characters total
        //   setfill('_') -- pad with underscores instead of spaces
        //   right     -- padding goes on the LEFT (right-justify the value)

        cout << dec << right << setfill('_') << setw(15)
             << showpos << fixed << setprecision(2) << B << "\n";

        // ----------------------------------------------------------------
        // C: scientific notation, uppercase E, 9 decimal places, no sign
        // ----------------------------------------------------------------
        // scientific -- switches to N.NNNNe+EE format
        // uppercase  -- uses E instead of e
        // setprecision(9) -- 9 digits after the decimal point
        // noshowpos  -- suppress the '+' that showpos left sticky from B
        cout << noshowpos << scientific << uppercase << setprecision(9)
             << C << "\n";

        cout.flags(saved_flags);
    }

    return 0;
}