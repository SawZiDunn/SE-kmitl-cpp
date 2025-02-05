#include <iostream>
#include <cstring>
using namespace std;

void concateateString(char *, const char *, int);
bool isSubstring(const char *, const char *);

int main()
{
    char string1[80];
    char string2[80];

    cout << "Enter two strings: ";
    cin >> string1 >> string2;

    concateateString(string1, string2, 80);
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

void concateateString(char *s1, const char *s2, int maxSize)
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    if (len2 > maxSize - len1)
    {
        cerr << "Not enough space for string2 to concatinate to string1!" << endl;
        return;
    }

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

    for (int i = 0; i < len1 - len2; ++i)
    {

        if (s1[i] == s2[i])
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
    }

    return false;
}