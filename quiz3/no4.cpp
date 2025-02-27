#include <iostream>
using namespace std;

class Engine
{
public:
    void start()
    {
        cout << "Engine started" << endl;
    }
};

class Wheels
{
public:
    void roll()
    {
        cout << "Wheels rolling" << endl;
    }
};

class Car : public Engine, public Wheels
{
    // inherits from both Engine and Wheels
};

int main()
{
    Car myCar;
    myCar.start();
    myCar.roll();
    return 0;
}
