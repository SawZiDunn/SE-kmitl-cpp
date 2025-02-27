#include <iostream>

using namespace std;

class Animal
{
public:
    void speak()
    {
        cout << "I am an animal" << endl;
    }
};

class Dog : public Animal
{
public:
    void speak() // overridden
    {
        cout << "Woof!" << endl;
    }
};

int main()
{
    Dog myDog;
    myDog.speak();
    return 0;
}