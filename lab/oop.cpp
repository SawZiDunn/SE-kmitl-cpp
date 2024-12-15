#include <iostream>
#include <iomanip>

using namespace std;

class Animal {
    public:
    void eat() {
        string s = "I can eat";
        // transform(s.begin(), s.end(), s.begin(),
        //       ::toupper);

        for (int i = 0; i < s.length(); i++) {
            s[i] = toupper(s[i]);
        }

  
        cout << setw(20) << s << endl;
    }

    void sleep() {
        string s = "I can sleep";
        for (int i = 0; i < s.length(); i++) {
            s[i] = toupper(s[i]);
        }
        

        cout << setw(20) << s << endl;
    }
};

class Dog: public Animal {
    public:
    void bark() {

         std::string s =  "I can bark!";


        for (int i = 0; i < s.length(); i++) {
            s[i] = toupper(s[i]);
        }


        cout << std::setw(20) << s << std::endl;
    }
};

int main() {
    Dog dog;

    dog.eat();
    dog.sleep();
    dog.bark();
    return 0;
}