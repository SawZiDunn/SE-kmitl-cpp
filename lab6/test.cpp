#include <iostream>
using namespace std;
int mystery(int, int);
int main()

{
    int x = 0;
    int y = 0;
    cout << "Enter two integers: ";
    cin >> x >> y;
    cout << "The result is " << mystery(x, y) << endl;
    return 0;
}
int mystery(int a, int b)
{
    if (b == 1)
    { // Base case
        return a;
    }
    else
    { // Recursion step
        return a + mystery(a, b - 1);
    }
}