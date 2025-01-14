#include <iostream>
#include <vector>

using namespace std;

int findSmallestNum(const vector<int> &vec);
int main()
{
    vector<int> nums;
    int count;
    cout << "Enter the number of integers: ";
    cin >> count;
    for (int i = 0; i < count; i++)
    {
        int j;
        cout << "Enter integer: ";
        cin >> j;
        if (i == 0 && j <= 0)
        {
            cout << "The first number must be greater than 0." << endl;
            return 1;
        }

        nums.push_back(j);
    }

    if (nums.empty())
    {
        cout << "The number list is empty!" << endl;
    }
    else
    {
        cout << "The smallest integer is " << findSmallestNum(nums) << endl;
    }

    return 0;
}

int findSmallestNum(const vector<int> &vec)
{
    int temp{vec.at(0)};
    for (int i : vec)
    {
        if (temp > i)
        {
            temp = i;
        }
    }

    return temp;
}