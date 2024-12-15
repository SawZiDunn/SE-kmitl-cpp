#include<iostream>
#include<iomanip>

using namespace std;

int main() {

    string p1;
    string p2;
    cout << "Player 1: ";
    getline(cin, p1);

    cout << "Player 2: ";
    getline(cin, p2);

    string longer_str;
    if (p1.size() > p2.size()) {
        longer_str = p1;
    }
    else {
        longer_str = p2;
    }

    int longer_str_len = longer_str.size();

    // horizontal print

    int border_len = 27 + p1.size() + p2.size();

    // print border
    for (int i = 0; i < border_len; i++) {
        cout << '*';
    }
    cout << endl;

    //
    cout << "*" << setw(13 + p1.size()) << "*" << setw(13 + p2.size()) << "*" << endl;

    cout << "* Player 1: " << p1 << " * " << "Player 2: " << p2 << " *" << endl;

    //
    cout << "*" << setw(13 + p1.size()) << "*" << setw(13 + p2.size()) << "*" << endl;
    // print border
    for (int i = 0; i < border_len; i++) {
        cout << '*';
    }
    cout << endl;





    // vertical print
    
    border_len = 15 + longer_str_len;
    // print border
    for (int i = 0; i < border_len; i++) {
        cout << '*';
    }
    cout << endl;

    //
    cout << "*" << setw(border_len - 1) << "*" << endl;
    
    // print p1 name
    cout << "* Player 1 : " << setw(longer_str_len) << p1 << " *" << endl;

    //
    cout << "*" << setw(border_len - 1) << "*" << endl;

    for (int i = 0; i < border_len; i++) {
        cout << '*';
    }
    cout << endl;

    //
    cout << "*" << setw(border_len - 1) << " *" << endl;

    cout << "* Player 2 : " << setw(longer_str_len) << p2 << " *" << endl;

    //
    cout << "*" << setw(border_len - 1) << "*" << endl;

    // print border
    for (int i = 0; i < border_len; i++) {
        cout << '*';
    }
    cout << endl;


    return 0;
}