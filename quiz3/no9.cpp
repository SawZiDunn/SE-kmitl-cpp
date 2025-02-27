#include <iostream>

using namespace std;

class Bird
{
public:
    virtual void fly()
    {
        cout << "Flying generally" << endl;
    };

    ~Bird() { cout << "Deleting Bird obj" << endl; }
};

class Eagle : public Bird
{
public:
    void fly() override
    {
        cout << "Soaring high" << endl;
        Bird::fly();
    }
};

int main()
{

    Eagle *eagle = new Eagle();
    eagle->fly();

    cout << "hello" << endl;

    delete eagle;

    return 0;
}