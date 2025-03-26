#include <iostream>
#include <cstring>
#include <string>
using namespace std;

void getStringDetails(const char *, int &, int &);
void reverseString(char *);

int main()
{
    char string1[5];
    cout << "Enter a string: ";

    cin.getline(string1, 5); // reads input up to \n and stops

    int vowelCount = 0;
    int length = 0;
    getStringDetails(string1, vowelCount, length);

    cout << "Lenght: " << length << " | Vowel count: " << vowelCount << endl;

    reverseString(string1);
    cout << "Reversed String: " << string1 << endl;
    return 0;
}

void getStringDetails(const char *s, int &vowelCount, int &length)
{
    length = 0;
    vowelCount = 0;

    while (*s != '\0')
    {
        length++;
        if (*s == 'a' || *s == 'e' || *s == 'i' || *s == 'o' || *s == 'u' || *s == 'A' || *s == 'E' || *s == 'I' || *s == 'O' || *s == 'U')
        {
            vowelCount++;
        }
        s++;
    }
}

void reverseString(char *s)
{

    int length = strlen(s);
    char *start = s;
    char *end = s + length - 1;

    while (start < end) // compare memory address
    {
        swap(*start, *end);
        start++;
        end--;
    }
}