#include <iostream>
#include <string>
#include <sstream>
#include <exception>
using namespace std;


// ─────────────────────────────────────────────────────────────────────────────
// CUSTOM EXCEPTION CLASS
// Inherits from std::exception so it can be caught like any standard exception.
// Purpose: carry the length of a too-short username as a payload.
// ─────────────────────────────────────────────────────────────────────────────
class BadLengthException : public exception{
    int num;
    public:
        // Constructor: called as  throw BadLengthException(n);
        // Saves 'n' so what() can report it later.
        BadLengthException(int n){num = n;}
        // Returns the length as a string, e.g. "2"
        // The caller prints "Too short: " + what()  →  "Too short: 2"
        string what(){
            stringstream ss;
            ss << num;  // int → stream → string  (simple int-to-string trick)
            return ss.str();
        }
};
/* Define the exception here */



// ─────────────────────────────────────────────────────────────────────────────
// VALIDATION FUNCTION
// Returns true  → username is Valid
// Returns false → username is Invalid (contains "ww")
// THROWS       → BadLengthException if length < 5  (caught in main)
// ─────────────────────────────────────────────────────────────────────────────
bool checkUsername(string username) {
	bool isValid = true;
	int n = username.length();
	if(n < 5) {
		throw BadLengthException(n);
	}
	for(int i = 0; i < n-1; i++) {
		if(username[i] == 'w' && username[i+1] == 'w') {
			isValid = false;
		}
	}
	return isValid;
}

int main() {
	int T; cin >> T;
	while(T--) {
		string username;
		cin >> username;
		try {
			bool isValid = checkUsername(username);
			if(isValid) {
				cout << "Valid" << '\n';
			} else {
				cout << "Invalid" << '\n';
			}
		} catch (BadLengthException e) {
			cout << "Too short: " << e.what() << '\n';
		}
	}
	return 0;
}
