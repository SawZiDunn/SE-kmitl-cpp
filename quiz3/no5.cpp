#include <iostream>
using namespace std;

// Abstract base class
class Shape
{
public:
    virtual void draw() = 0; // Pure virtual function
    virtual ~Shape() {}      // Virtual destructor for proper cleanup
};

class Circle : public Shape
{
public:
    void draw() override
    {
        cout << "Drawing a circle" << endl;
    }
};

class Square : public Shape
{
public:
    void draw() override
    {
        cout << "Drawing a square" << endl;
    }
};

int main()
{
    Shape *shape1 = new Circle(); // Shape pointer to a Circle object
    Shape *shape2 = new Square(); // Shape pointer to a Square object

    shape1->draw(); // call from memory address
    shape2->draw();

    (*shape1).draw(); // calls by dereferencing

    // clean up
    delete shape1;
    delete shape2;

    return 0;
}
