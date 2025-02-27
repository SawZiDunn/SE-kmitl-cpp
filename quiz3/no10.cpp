#include <iostream>
using namespace std;

class Instrument
{
public:
    // pure, object of Instrument cannot be instantiated
    // child classes should implement play() method
    virtual void play() = 0;
    virtual ~Instrument() {} // virtual destructor
};

class Guitar : public Instrument
{
public:
    void play() override
    {
        cout << "Strumming the guitar" << endl;
    }
};

// Derived class Piano
class Piano : public Instrument
{
public:
    void play() override
    {
        cout << "Playing the piano" << endl;
    }
};

int main()
{
    Instrument *instruments[2];

    instruments[0] = new Guitar(); // dynamically allocated, not static
    instruments[1] = new Piano();

    for (int i = 0; i < 2; i++)
    {
        instruments[i]->play();
    }

    // Clean memory
    for (int i = 0; i < 2; i++)
    {
        delete instruments[i]; // to prevent memory leak
    }

    return 0;
}