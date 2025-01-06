#include<iostream>
#include<vector>

using namespace std;

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

void get_combinations(const string &input, vector<string> &combinations, int index, string current);
int main() {
    string input;
    cout << "Enter a string of digits (2-9):";
    getline(cin, input);

    if (input.empty()) {
        cout << "Input is empty!" << endl;
        return 0;
    }

    vector<string> combinations = {};
    get_combinations(input, combinations, 0, "");

    for (const string &x : combinations) {
        cout << "- " <<  x << endl;
    }

    cout << "Total Combinations: " << combinations.size() << endl;

    return 0;

}

void get_combinations(const string &input, vector<string> &combinations, int index, string current) {
    if (index == input.size()) {
        combinations.push_back(current);
        return;
    }

    if (input[index] < '2' || input[index] > '9') {
        get_combinations(input, combinations, index + 1, current);
        return;
    }

    string current_string = keypad[input[index] - '0' - 2];

    for (char i : current_string) {
        get_combinations(input, combinations, index + 1, current + i);
    }

}