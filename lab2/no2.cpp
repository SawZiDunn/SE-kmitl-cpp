#include<iostream>

using namespace std;

int main() {
    int size;
    cout << "Size: ";
    cin >> size;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < i  + 1; j++) {
            cout << "*";
        }
        cout << endl;

    }

    for (int i = 1; i < size; i++) {
        for (int j = size - i; j > 0; j--) {
            cout << "*";
        }
        cout << endl;
    }
    


    


    return 0;
}