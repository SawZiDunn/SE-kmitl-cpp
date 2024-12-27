#include<iostream>
#include<list>
using namespace std;

// a program that can merge two sorted lists
list<int> mergeLists(const list<int>& list1, const list<int>& list2);

int main() {
    list<int> list1 = {1, 3, 5, 7};
    list<int> list2 = {2, 4, 6, 8, 9};

    list<int> outputList = mergeLists(list1, list2);
    for (auto i : outputList) {
        cout << i << ", ";
    }
    cout << "\n";

    return 0;
}

// this function also handles lists with different lengths
list<int> mergeLists(const list<int>& list1, const list<int>& list2) {
    list<int> outputList = {};
    // .begin() returns the iterator pointing to the first element of the list
    auto list1_value = list1.begin(); // std::list<int>::iterator
    auto list2_value = list2.begin();

    while (list1_value != list1.end() && list2_value != list2.end()) {
        
        if (*list1_value < *list2_value) {
            outputList.push_back(*list1_value);
            outputList.push_back(*list2_value);
        } else {
            outputList.push_back(*list2_value);
            outputList.push_back(*list1_value);
            
        }
        ++list1_value; // we cannot use list1_value += 1 or list1_value = list1_value + 1
        ++list2_value;
    }

    // for handling lists with different lengths
    // if list1 has not ended yet?
    while (list1_value != list1.end()) {
        outputList.push_back(*list1_value);
        list1_value++;
    }

    while (list2_value != list2.end()) {
        outputList.push_back(*list2_value);
        list2_value++;
    }
    
    return outputList;
}