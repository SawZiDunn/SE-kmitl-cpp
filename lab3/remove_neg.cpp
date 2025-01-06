#include<iostream>
#include<vector>
#include<list>

using namespace std;
void remove_negative(vector<double>& vec);
void remove_negative(list<double>& my_list);

int main() {
    vector<double> vec{-0.8, -5.1, -1.6, -6.5, 10.5};
    list<double> my_list{-0.8, -5.1, -1.6, -6.5, 10.5};

    cout << "Original: ";
    for (auto x : my_list) {
        cout << x << ' ';
    }
    cout << endl;

    remove_negative(my_list);
    cout << "After removing negative numbers: ";
    for (auto x : my_list) {
        cout << x << ' ';
    }


    return 0;
}

void remove_negative(vector<double>& vec) {

    for (auto i = vec.begin(); i != vec.end();) {
        if (*i < 0) {
            i = vec.erase(i); // returns the next element
        } else {
            ++i; // move by one element only if current value is not negative
        }
    }
}

void remove_negative(list<double>& myList) {
    for (auto i = myList.begin(); i != myList.end();) {
        if (*i < 0) {
            i = myList.erase(i); // returns the next valid iterator
        } else {
            ++i; // move to the next only if no erase occurs
        }
    }
}

