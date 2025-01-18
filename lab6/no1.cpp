#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main() {
    ifstream file("test.txt");

    if (!file) {
        cerr << "Error: Unable to open the file!" << endl;
        return 1;
    }

    cout << "File opened successfully.\n";
    string line;
    while (getline(file, line)) {
        cout << line.size() << ":" << line << endl;
    }

    file.close();
    cout << "File reading completed\n";
    return 0;
}