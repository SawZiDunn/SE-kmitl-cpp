#include <iostream>
#include <string>
using namespace std;

class Employee
{
protected:
    string name;

public:
    void setName(string n)
    {
        name = n;
    }
};

class Manager : public Employee
{
public:
    string getName()
    {
        return name;
    }
};

int main()
{
    Manager manager;
    manager.setName("Alice");
    cout << manager.getName() << endl;

    return 0;
}