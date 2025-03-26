#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class SpaceShip
{

public:
    SpaceShip(string type, string name, int age, double avg_speed, bool is_active)
        : type(type), name(name), age(age), avg_speed(avg_speed), is_active(is_active) {}

    string type;
    string name;
    int age;
    double avg_speed;
    bool is_active;
};

// function prototypes
void saveToFile(const vector<SpaceShip *> &ships);
void loadFromFile(vector<SpaceShip *> &ships);
void displayShips(const vector<SpaceShip *> &ships);

int main()
{
    vector<SpaceShip *> ships;

    // ships.push_back(new SpaceShip("A", "Big Thing", 50, 25.6, true));

    loadFromFile(ships);
    displayShips(ships);

    return 0;
}

void saveToFile(const vector<SpaceShip *> &ships)
{
}

void loadFromFile(vector<SpaceShip *> &ships)
{

    ifstream file("data.txt");

    if (file.is_open())
    {

        string line;
        getline(file, line); // skips the first line

        while (getline(file, line))
        {
            stringstream ss(line);

            string type, name, age, avg_speed, is_active;
            getline(ss, type, ','); // get the substring until comma exclusively
            getline(ss, name, ',');
            getline(ss, age, ',');
            getline(ss, avg_speed, ',');
            getline(ss, is_active, ',');

            bool active = is_active == "true" ? true : false;

            ships.push_back(new SpaceShip(type, name, stoi(age), stod(avg_speed), active));
        }

        file.close();
    }
    else
    {
        cerr << "File not Found!" << endl;
    }
}

void displayShips(const vector<SpaceShip *> &ships)
{

    for (const auto &ship : ships)
    {
        cout << "Type: " << ship->type << ", "
             << "Name: " << ship->name << ", "
             << "Age: " << ship->age << ", "
             << "Average Speed: " << ship->avg_speed << ", "
             << "is Active: " << boolalpha << ship->is_active << endl;
    }
}