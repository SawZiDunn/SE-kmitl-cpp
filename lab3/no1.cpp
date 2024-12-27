#include <iostream>
#include <string>
#include <vector>
using namespace std;


int main(){
    vector<string> keypad = {
        "abc",
        "def",
        "ghi",
        "jkl",
        "mno",
        "pqrs",
        "tuv",
        "wxyz"
    };

    string input;
    cout << "Input: ";
    getline(cin, input);
    // We should initialize combinations vector with an empty string
    // so that when we loop through it, the first iteration happens.
    vector<string> combinations = {""};

    if (input.empty()) {
        cout << "Empty Input!\nNo combination is generated." << endl;
        return 1;
    }

    for (char i : input) {
        // We can directly compare numbers in character type with characters.
        // '5' > '4' or
        // '5' - '0' > 4
        if (i < '2' || i > '9') {
            cout << "Input string must only contain digits from 2 to 9!" << endl;
            
            return 1;
            // exit(1);
        }

        string characters = keypad[i - '0' - 2]; // minus two to adjust index
        vector<string> temp_combinations = {};
        for (const string& j : combinations) {
            for (char k : characters) {
                temp_combinations.push_back(j + k);
            }
        }
        combinations = temp_combinations;

        // swap is better
        // combinations.swap(temp_combinations);
    }

    // output

    for (const string& x : combinations) {
        cout <<  "- "<< x << endl;
    }
    cout << "Total Combinations: " << combinations.size() << endl;

    return 0;
}