#include <cmath>
#include <cstdio>
#include <vector>
#include <tuple>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;
// Key insight: flatten nested tags into dot-separated keys at parse time.
// Instead of building a real tree, we map "tag1.tag2.tag3" -> {attr -> val}.
// Queries then become a single map lookup -- no traversal needed at query time.
//
// Stack discipline:
//   Opening tag  -> push tag name onto stack, build full dot-path, parse attrs
//   Closing tag  -> pop stack (restores parent scope for next sibling)


// Reads the next whitespace- or '>'-delimited token from input_str starting at
// index, stripping any surrounding double-quotes from values like "HelloWorld".
// Returns the token as a string (empty if nothing found).
string get_next_str(string input_str, int index){
    int start = index;
    string result = "";
    while(start < input_str.size() && input_str[start] != ' ' && input_str[start] != '>'){
        if(input_str[start] != '"'){
            result += input_str[start];
        }
        start += 1;
    }
    return result;
}

// Splits a query string on '~' into (tag-path, attribute-name).
// e.g. "tag1.tag2~name" -> ("tag1.tag2", "name")
tuple<string,string> get_tag_and_key(string input_str){
    string tag = "";
    int start = 0;
    while(input_str[start] != '~'){
        tag += input_str[start];
        start += 1;
    }
    string key = input_str.substr(start+1);
    return make_tuple(tag, key);
}

int main() {
    // Flat map: full dot-path -> (attribute-name -> value)
    // e.g. value_storage["tag1.tag2"]["name"] = "Name1"
    // Using nested unordered_map for O(1) average lookup on both levels.
    unordered_map<string, unordered_map<string, string>> value_storage;  

    int N,Q; cin >> N >> Q; cin.ignore();

    // vec acts as a stack of tag names representing the current nesting path.
    // e.g. inside <tag1><tag2>...</tag2></tag1>, vec = ["tag1", "tag2"]
    vector<string> vec;

    for(int i = 0; i < N; i++){
        string input_str;
        getline(cin, input_str);

        if(input_str[1] != '/'){
            // --- Opening tag ---
            // Format: <tag-name attr1 = "val1" attr2 = "val2" ...>
            // input_str[0] is '<', so tag name starts at index 1.

            string tag_str = get_next_str(input_str, 1);   // extract tag name
            vec.push_back(tag_str);                         // push onto path stack

            // start points just past "<tag-name" -- the space before first attr,
            // or at '>' if no attributes.
            // +2 skips the leading '<' and the space after the tag name.
            int start = 2 + tag_str.size();

            // Build the full dot-separated path from the current stack.
            // e.g. vec = ["tag1","tag2"] -> "tag1.tag2"
            string concat_tag_str = "";
            for(int i = 0; i < vec.size(); i++){
                if(i < vec.size()-1){
                    concat_tag_str += vec[i]+".";
                }else{
                    concat_tag_str += vec[i];
                }
            }
            tag_str = concat_tag_str;

            // Parse zero or more "attr = "value"" pairs from the remainder.
            // Token layout in the raw string (spaces are literal):
            //   attr_name SP = SP "value" SP attr_name ...
            // After get_next_str returns "attr_name" of length L:
            //   +L skips the token itself
            //   +3 skips " = " (space, equals, space) to land on the opening quote
            // After get_next_str returns "value" of length V (quotes stripped):
            //   +V skips the value token
            //   +3 skips closing-quote + space + (opening-quote of next token,
            //        OR '>' if this was the last attribute)
            string next_str = "";
            string val = "";
            while(start < input_str.size()){
                next_str = get_next_str(input_str, start);         // attr name
                value_storage[tag_str][next_str] = "";             // reserve slot
                start += next_str.size() + 3;                      // skip attr + " = "
                val = get_next_str(input_str, start);              // value (no quotes)
                value_storage[tag_str][next_str] = val;            // store
                start += val.size() + 3;                           // skip val + delim
            }
        } else {
            // --- Closing tag ---
            // Format: </tag-name>
            // We don't need the tag name -- stack order guarantees correct pairing
            // because the problem states HRML is always logically valid (no mismatches).
            vec.pop_back();
        }
    }

    // --- Query phase ---
    // Each query is "tag-path~attr". Split, look up, print or "Not Found!".
    for(int i = 0; i < Q; i++){
        string input_str;
        getline(cin, input_str);

        string tag, key;
        tie(tag, key) = get_tag_and_key(input_str);

        // value_storage[tag] creates an empty inner map if tag is absent --
        // that's fine here because we immediately check find(key) on it.
        // If tag doesn't exist, the empty map won't contain key, so we still
        // print "Not Found!" correctly.
        if(value_storage[tag].find(key) == value_storage[tag].end()){
            cout << "Not Found!" << endl;
        }else{
            cout << value_storage[tag][key] << endl;
        }
    }

    return 0;
}
