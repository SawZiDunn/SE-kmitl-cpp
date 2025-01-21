/*
Write a C++ program that uses a recursive func on to reverse a user-entered string. The program should
prompt the user to input a string, and then it should display the string in reverse order.
 */

#include <iostream>
#include <string>

using namespace std;

string reverseString(const string &x);

int main()
{
    string x;
    cout << "Enter a string: ";

    getline(cin, x);
    cout << reverseString(x) << endl;

    return 0;
}

string reverseString(const string &x)
{
    if (x.size() == 1)
    {
        return x;
    }

    // x.at(x.size() - 1) or *(x.end() - 1)
    char temp = x.back(); // get the last value

    // x.erase(x.end() - 1); // remove the last value
    string y = x.substr(0, x.size() - 1);

    return temp + reverseString(y);
}