#include <iostream>
using namespace std;

class Vehicle
{
protected:
    int speed;

public:
    void setSpeed(int s)
    {
        speed = s;
    }
};

class Car : public Vehicle
{
public:
    void displaySpeed()
    {
        cout << "Speed: " << speed << " km/h" << endl;
    }
};

int main()
{
    Car myCar;
    myCar.setSpeed(120);
    myCar.displaySpeed();
    return 0;
}
