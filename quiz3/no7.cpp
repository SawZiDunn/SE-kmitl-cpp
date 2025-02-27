#include <iostream>
using namespace std;

class A
{
public:
    void sayHi()
    {
        cout << "Hi from A" << endl;
    }
};

// inherit virtually
class B : virtual public A
{
};
class C : virtual public A
{
};

// inherits from both B and C
class D : public B, public C
{
};

int main()
{
    D obj;
    obj.sayHi(); // Calls A::sayHi() only once due to virtual inheritance

    return 0;
}
