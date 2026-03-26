#include <iostream>
#include <vector>
#include <string>
using namespace std;

// BASE CLASS: Spell
// Every spell type inherits from this.
// Holds the scroll name for generic (unknown) spells.
class Spell {
    private:
        string scrollName;
    public:
        Spell(): scrollName("") { }           // default constructor
        Spell(string name): scrollName(name) { }
        virtual ~Spell() { }                  // virtual destructor: ensures correct
                                              // subclass destructor runs on delete
        string revealScrollName() {
            return scrollName;
        }
};

// DERIVED SPELL CLASSES
// Each stores its power and prints its own label.
// No scrollName needed -- these are known spell types.

class Fireball : public Spell {
    private: int power;
    public:
        Fireball(int power): power(power) { }
        void revealFirepower(){
            cout << "Fireball: " << power << endl;
        }
};

class Frostbite : public Spell {
    private: int power;
    public:
        Frostbite(int power): power(power) { }
        void revealFrostpower(){
            cout << "Frostbite: " << power << endl;
        }
};

class Thunderstorm : public Spell {
    private: int power;
    public:
        Thunderstorm(int power): power(power) { }
        void revealThunderpower(){
            cout << "Thunderstorm: " << power << endl;
        }
};

class Waterbolt : public Spell {
    private: int power;
    public:
        Waterbolt(int power): power(power) { }
        void revealWaterpower(){
            cout << "Waterbolt: " << power << endl;
        }
};

// SPELL JOURNAL
// Static class -- one shared journal string across the entire program.
// Stores the reference string used for LCS comparison.
class SpellJournal {
    public:
        static string journal;
        static string read() {
            return journal;
        }
};
string SpellJournal::journal = "";  // static member must be defined outside class


// COUNTERSPELL FUNCTION
// Receives a base Spell pointer and identifies the real type at runtime
// using dynamic_cast (safe downcast -- returns nullptr if cast fails).
//
// Two possible outcomes:
//   Known spell   --> cast to subclass, call its reveal method
//   Unknown spell --> extract scroll name, run LCS against the journal
void counterspell(Spell *spell) {

    // dynamic_cast<T*>(ptr) returns non-null only if the real object IS a T.
    // This is how we "identify" the spell without any type flags or enums.

    if (dynamic_cast<Fireball*>(spell) != nullptr) {
        dynamic_cast<Fireball*>(spell)->revealFirepower();

    } else if (dynamic_cast<Frostbite*>(spell) != nullptr) {
        dynamic_cast<Frostbite*>(spell)->revealFrostpower();

    } else if (dynamic_cast<Thunderstorm*>(spell) != nullptr) {
        dynamic_cast<Thunderstorm*>(spell)->revealThunderpower();

    } else if (dynamic_cast<Waterbolt*>(spell) != nullptr) {
        dynamic_cast<Waterbolt*>(spell)->revealWaterpower();

    } else {
        // GENERIC SPELL -- unknown type, compare to journal using LCS
        string s = spell->revealScrollName();
        string j = SpellJournal::read();

        // LONGEST COMMON SUBSEQUENCE (LCS) via dynamic programming
        //
        // dp[i][j] = length of LCS between s[0..i-1] and j[0..j-1]
        //
        // Table is (s.length+1) x (j.length+1), with row/col 0 as base case = 0
        //
        // Recurrence:
        //   if s[i-1] == j[j-1]:  dp[i][j] = 1 + dp[i-1][j-1]  (extend match)
        //   else:                  dp[i][j] = max(dp[i-1][j], dp[i][j-1])  (skip one)
        //
        // Example: s = "AquaVitae", j = "AruTaVae"
        //   LCS = "AuaVae", length = 6

        int slen = s.length();
        int jlen = j.length();
        vector<vector<int>> dp(slen + 1, vector<int>(jlen + 1, 0));

        for (int i = 1; i <= slen; i++) {
            for (int k = 1; k <= jlen; k++) {
                if (s[i-1] == j[k-1]) {
                    dp[i][k] = 1 + dp[i-1][k-1];   // characters match: extend
                }
                if (dp[i-1][k] > dp[i][k]) {
                    dp[i][k] = dp[i-1][k];           // skip s[i]
                }
                if (dp[i][k-1] > dp[i][k]) {
                    dp[i][k] = dp[i][k-1];           // skip j[k]
                }
            }
        }
        // bottom-right cell holds the final LCS length
        cout << dp[slen][jlen] << endl;
    }
}


// WIZARD CLASS (locked on HackerRank)
// Reads input and constructs the correct Spell subclass.
// For unknown spells, also reads the journal entry.
class Wizard {
    public:
        Spell *cast() {
            Spell *spell;
            string s;   cin >> s;
            int power;  cin >> power;

            if      (s == "fire")    spell = new Fireball(power);
            else if (s == "frost")   spell = new Frostbite(power);
            else if (s == "water")   spell = new Waterbolt(power);
            else if (s == "thunder") spell = new Thunderstorm(power);
            else {
                // Generic spell: s is the scroll name, next token is journal
                spell = new Spell(s);
                cin >> SpellJournal::journal;
            }
            return spell;   // caller owns this pointer, must delete
        }
};

// MAIN (locked on HackerRank)
int main() {
    int T;
    cin >> T;           // number of spells to process
    Wizard Arawn;
    while (T--) {
        Spell *spell = Arawn.cast();
        counterspell(spell);
        // note: spell is never deleted here -- minor leak, acceptable on HackerRank
    }
    return 0;
}