#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> keypad = {
    "",   
    "",   
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs"
    "tuv",
    "wxyz"
};

void generateCombinations(const string &digits, int index, string current, vector<string> &results) {
    if (index == digits.size()) { 
        results.push_back(current);
        return;
    }

    char digit = digits[index];
    if (digit < '2' || digit > '9') {  
        cout << "Invalid digit encountered: " << digit << endl;
        return;
    }

    string letters = keypad[digit - '0'];  
    for (char letter : letters) {
        generateCombinations(digits, index + 1, current + letter, results);  
    }
}

int main() {
    string input;
    cout << "Enter the digit string (2-9): ";
    cin >> input;

    if (input.empty()) {
        cout << "No input provided!" << endl;
        return 0;
    }

    vector<string> results; 
    generateCombinations(input, 0, "", results);

    cout << "Output:" << endl;
    for (const string &combination : results) {
        cout << "- " << combination << endl;
    }

    cout << "Total combinations: " << results.size() << endl;

    return 0;
}
