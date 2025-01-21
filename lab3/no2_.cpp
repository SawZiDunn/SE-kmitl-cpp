// same with no1, but using recursion

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> keypad = {
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz"};

void get_combinations(const string &input_digits, vector<string> &result_combinations, int index, string current);
int main()
{
    string input_digits;
    cout << "Enter a string of digits (2-9):";
    getline(cin, input_digits);

    if (input_digits.empty())
    {
        cout << "Input is empty!" << endl;
        return 0;
    }

    vector<string> result_combinations = {};
    get_combinations(input_digits, result_combinations, 0, "");

    // output
    for (const string &x : result_combinations)
    {
        cout << "- " << x << endl;
    }

    cout << "Total Combinations: " << result_combinations.size() << endl;

    return 0;
}

void get_combinations(const string &input_digits, vector<string> &result_combinations, int index, string current)
{
    if (index == input_digits.size())
    {
        result_combinations.push_back(current);
        return;
    }

    if (input_digits[index] < '2' || input_digits[index] > '9')
    {
        cout << "Invalid digit encountered: " << input_digits[index] << endl;
        get_combinations(input_digits, result_combinations, index + 1, current);
        return;
    }

    string current_string = keypad[input_digits[index] - '0' - 2];

    for (char letter : current_string)
    {
        get_combinations(input_digits, result_combinations, index + 1, current + letter);
    }
}