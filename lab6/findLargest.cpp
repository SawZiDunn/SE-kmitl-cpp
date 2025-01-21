/*
Write a C++ program that generates an array of 10 random integers between 1 and 100, and then finds the
maximum number in this array using a recursive func on.
Output: Display the generated numbers to the user. And show the maximum number in the array.
*/

#include <iostream>
#include <string>
#include <array>

using namespace std;

int findLargest(int index, int largest, array<int, 5> arr);

int main()
{
    array<int, 5> arr{5, 8, -10, 36, 0};
    cout << findLargest(0, 0, arr) << endl;

    return 0;
}

int findLargest(int index, int largest, array<int, 5> arr)
{
    if (index == arr.size())
    {
        return largest;
    }

    if (largest < arr[index])
    {
        largest = arr[index];
    }

    return findLargest(index + 1, largest, arr);
}
