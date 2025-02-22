#include <iostream>
#include <cstring> // strlen() -> no of chars until the first null terminator, doesn't count \n
#include <limits>
using namespace std;

void concatenateString(char *, const char *, int);
bool isSubstring(const char *, const char *);

int main()
{
    char string1[80]; // Read max 79 chars + '\0'
    char string2[80];

    cout << "Enter two strings: ";
    cin >> string1; // doesn't prevent buffer overflow

    // Clear buffer before the next input
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cin >> string2;

    cout << "s1 " << string1 << endl;
    cout << "s2 " << string2 << endl;

    concatenateString(string1, string2, 80);
    cout << "Concatenated string: " << string1 << endl;

    cout << "Enter a string to check for substring: ";
    cin >> string2;

    if (isSubstring(string1, string2))
    {
        cout << "\"" << string2 << "\" is a substring of \"" << string1 << "\"." << endl;
    }
    else
    {
        cout << "\"" << string2 << "\" is not a substring of \"" << string1 << "\"." << endl;
    }

    return 0;
}

void concatenateString(char *s1, const char *s2, int maxSize)
{
    int len1 = strlen(s1); // can be used on char *
    int len2 = strlen(s2);

    if (len1 + len2 >= maxSize)
    {
        cerr << "Not enough space for string2 to concatinate to string1!" << endl;
        return;
    }

    // "hi" is the same as {'h', 'i', '\0'}
    // moves pointer to the end of the string1
    while (*s1 != '\0') // (*s1)
    {
        ++s1;
    }

    while (*s2 != '\0') // (*s2)
    {
        *s1 = *s2;
        ++s1;
        ++s2;
    }

    // adding null terminator at the end
    *s1 = '\0';

    // for (; *s1 = *s2; ++s1, ++s2)
    //     ; // append string2 to string1
}

bool isSubstring(const char *s1, const char *s2)
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    if (len2 == 0)
    {
        return true; // empty string is substring of any string
    }

    for (int i = 0; i <= len1 - len2; ++i)
    {
        int j{0};

        for (int j = 0; j < len2; ++j)
        {
            if (s1[i + j] != s2[j])
            {
                break;
            }
        }

        if (j == len2)
        {
            return true;
        }
    }

    return false;
}