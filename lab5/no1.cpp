#include<iostream>

using namespace std;

int fibonacci(int n);

int main() {
    int n;
    cout << "Input: ";
    cin >> n;

    if (n < 0) {
        cout << "Please input a non-negative integer." << endl;
        return 1;
    }

    for (int i = 0; i <= n; i++) {
        cout << "F(" << i << ") = " << fibonacci(i);
        if (i != n) {
            cout << ", ";
        }
    }

    return 0;
}

int fibonacci(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}