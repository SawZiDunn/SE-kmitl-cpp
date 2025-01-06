#include<iostream>
#include<string>
#include<vector>

using namespace std;

void lshift(vector<int>& vec, int n);
void rshift(vector<int>& vec, int n);

int main() {

    vector vec = {1, 2, 3, 4, 5};

    cout << "Original Sequence: ";
    for (int x : vec) {
        cout << x << ' ';
    }
    cout << endl;

    lshift(vec, 3);

    cout << "After lshift by 2: ";
    for (int x : vec) {
        cout << x << ' ';
    }

    cout << endl;

    rshift(vec, 3);

    cout << "After rshift by 2: ";
    for (int x : vec) {
        cout << x << ' ';
    }

    return 0;
}

void lshift(vector<int> &vec, int n) {
    /* to handle n larger than vec.size()
        vec.size() = 5;
        n = 17;
        n -> 2
    */
    n %= vec.size(); 

    // stores the first n elements in a temp vector
    vector<int> temp{vec.begin(), vec.begin() + n}; // () also works
    
    vec.erase(vec.begin(), vec.begin() + n); // remove the first n elements
    
    vec.insert(vec.end(), temp.begin(), temp.end()); // insert them at the end
}

void rshift(vector<int> &vec, int n) {
    // vec.insert(vec.begin(), 0); // insert 0 before the first element

    vector<int> temp = {vec.end() - n, vec.end()};
    vec.erase(vec.end() - n, vec.end());
    vec.insert(vec.begin(), temp.begin(), temp.end());
}