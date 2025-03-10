#include <iostream>
#include <vector>
#include <memory> // for std::unique_ptr

using namespace std;

class SpaceObject
{
public:
    virtual void draw() const
    {
        cout << "Drawing a generic space object.\n";
    }

    virtual ~SpaceObject() {}
};

class Martian : public SpaceObject
{
public:
    void draw() const override
    {
        cout << "Drawing a Martian with green antennas" << endl;
    }
};

class Venutian : public SpaceObject
{
public:
    void draw() const override
    {
        cout << "Venutian" << endl;
    }
};

class Plutonian : public SpaceObject
{
public:
    void draw() const override
    {
        cout << "Plutonian" << endl;
    }
};

class SpaceShip : public SpaceObject
{
public:
    void draw() const override
    {
        cout << "SpaceShip" << endl;
    }
};

class LaserBeam : public SpaceObject
{
public:
    void draw() const override
    {
        cout << "LaserBeam" << endl;
    }
};

class Mercurian : public SpaceObject
{
public:
    void draw() const override
    {
        cout << "Mercurian with a swift, silver shadow." << endl;
    }
};

class ScreenManager
{
private:
    vector<unique_ptr<SpaceObject>> objects; // vector<SpaceObject*>

public:
    void addObject(unique_ptr<SpaceObject> obj)
    { // SpaceObject* obj

        objects.push_back(move(obj));
        // objects.emplace_back(move(obj));
    }

    void
    refreshScreen()
    {
        for (const auto &obj : objects)
        {
            obj->draw();
        }
    }
};

int main()
{
    ScreenManager manager;
    manager.addObject(make_unique<Martian>()); // new Martian()
    manager.addObject(make_unique<Venutian>());
    manager.addObject(make_unique<Plutonian>());
    manager.addObject(make_unique<LaserBeam>());
    manager.addObject(make_unique<Mercurian>());

    manager.refreshScreen();
    return 0;
}