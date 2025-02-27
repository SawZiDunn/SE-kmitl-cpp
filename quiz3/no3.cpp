#include <iostream>
using namespace std;

class Person
{
public:
    void introduce()
    {
        cout << "I am a person" << endl;
    }
};

class Student : private Person
{
public:
    void introduceAsStudent()
    {
        introduce(); // indirectly calls private method from parent class
    }
};

int main()
{
    Student s;
    // s.introduce(); // cannot access private methods, cause compilation error
    s.introduceAsStudent();
    return 0;
}
