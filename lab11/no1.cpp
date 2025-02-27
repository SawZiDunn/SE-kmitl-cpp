#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

class Spacecraft
{
public:
    Spacecraft(const string &name, const string &propulsion, int hullStrength, int speed)
        : name{name}, propulsion{propulsion}
    {
        if (hullStrength > 100 || hullStrength < 0)
        {
            this->hullStrength = 50;
        }
        else
        {
            this->hullStrength = hullStrength;
        }

        if (speed > 100 || speed < 0)
        {
            this->speed = 50;
        }
        else
        {
            this->speed = speed;
        }
    }

    string getName() const
    {
        return name;
    }

    string getPropulsion() const
    {
        return propulsion;
    }

    int getHullStrength() const
    {
        return hullStrength;
    }

    int getSpeed() const
    {
        return speed;
    }

    void displayInfo() const
    {
        cout << "Name: " << name
             << " - Propulsion: " << propulsion
             << " - HullStrength: " << hullStrength
             << " - Speed: " << speed << endl;
    }

private:
    string name;
    string propulsion;
    int hullStrength; // 0-100
    int speed;        // 0-100
};

class AlienShip : public Spacecraft
{
public:
    AlienShip(const string &name, const string &propulsion, int hullStrength, int speed, int evasionChance)
        : Spacecraft::Spacecraft(name, propulsion, hullStrength, speed)
    {

        if (evasionChance < 0 || evasionChance > 100)
        {
            this->evasionChance = 50;
        }
        else
        {
            this->evasionChance = 50;
        }
    }

    int getEvasionChance() const
    {
        return evasionChance;
    }

    bool attemptFlee() const
    {

        return (rand() % 100) < evasionChance;
    }

    // void displayInfo() const {
    //     Spacecraft::displayInfo();

    // }

private:
    int evasionChance;
};

class FleetShip : public Spacecraft
{
public:
    FleetShip(const string &name, const string &propulsion, int hullStrength, int speed)
        : Spacecraft::Spacecraft(name, propulsion, hullStrength, speed) {}
};

class Scanner
{
public:
    Scanner(const string &name, int range) : name{name}
    {
        if (range < 0 || range > 100)
        {
            this->range = 40;
        }
        else
        {
            this->range = range;
        }
    }

    bool scanShip(const AlienShip &target) const
    {
        return (rand() % 100) < range;
    }

    string getName() const
    {
        return name;
    }

    int getRange() const
    {
        return range;
    }

private:
    string name;
    int range;
};

class TractorBeam
{
public:
    TractorBeam(const string &name, int strength) : name{name}
    {
        if (strength < 0 || strength > 100)
        {
            this->strength = 20;
        }
    }

    int captureShip(const AlienShip &target) const
    {
        return strength - (target.getHullStrength() / 5);
    }

    string getName() const
    {
        return name;
    }

    int getStrength() const
    {
        return strength;
    }

private:
    string name;
    int strength;
};

class Player
{
public:
    Player() : scanners{}, fleet{}, tractorBeam{nullptr}
    {
    }

    void addScanner(const Scanner &scanner)
    {
        scanners.push_back(scanner);
    }

    void equipTractorBeam(TractorBeam *beam)
    {
        tractorBeam = beam;
    }

    bool captureShip(const AlienShip &target, int scannerIndex)
    {
        if (scannerIndex >= scanners.size() || !scanners[scannerIndex].scanShip(target))
        {
            scanners.erase(scanners.begin() + scannerIndex);

            return false;
        }

        int totalChance = 50;
        if (tractorBeam != nullptr)
        {
            totalChance += tractorBeam->captureShip(target);
        }

        if (rand() % 100 < totalChance)
        {

            fleet.push_back(FleetShip(target.getName(), target.getPropulsion(), target.getHullStrength(), target.getSpeed()));
            return true;
        }

        // erase scanner_no matter what
        scanners.erase(scanners.begin() + scannerIndex);
        return false;
    }

    vector<Scanner> getScanners() const
    {
        return scanners;
    }

    vector<FleetShip> getFleet() const
    {
        return fleet;
    }

    TractorBeam *getTractorBeam() const
    {
        return tractorBeam;
    }

private:
    vector<Scanner> scanners;
    vector<FleetShip> fleet;
    TractorBeam *tractorBeam;
};

class Galaxy
{
public:
    Galaxy() : alienShips{} {}

    void addAlienShip(const AlienShip &ship)
    {
        alienShips.push_back(ship);
    }

    AlienShip *explore()
    {
        if (rand() % 100 < 25 && !alienShips.empty())
        {
            int random = rand() % alienShips.size();
            return &alienShips[random];
        }

        return nullptr;
    }

    void removeShip(int shipIndex)
    {
        alienShips.erase(alienShips.begin() + shipIndex);
    }

    vector<AlienShip> getAlienShips() const
    {
        return alienShips;
    }

private:
    vector<AlienShip> alienShips;
};

void displayInventory(const Player &player)
{

    if (player.getScanners().empty())
    {
        cout << "\nNo Scanners!" << endl;
    }
    else
    {
        cout << "\nScanners:" << endl;
        for (const Scanner &scanner : player.getScanners())
        {
            cout << "Name: " << scanner.getName() << " - Range: " << scanner.getRange() << endl;
        }
    }

    if (player.getFleet().empty())
    {
        cout << "\nNo Captured Ship!" << endl;
    }
    else
    {
        cout << "\nFleet:" << endl;
        for (const FleetShip &fleet_ship : player.getFleet())
        {
            cout << fleet_ship.getName() << endl;
        }
    }
}

void clear_input_buffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main()
{
    srand(time(0));

    Player player;
    player.addScanner({"Basic", 40});
    player.addScanner({"Enhanced", 60});
    player.addScanner({"LongRange", 80});

    Galaxy galaxy;
    galaxy.addAlienShip({"Scout", "Ion Drive", 20, 80, 70});
    galaxy.addAlienShip({"Fighter", "Plasma Truster", 60, 50, 40});
    galaxy.addAlienShip({"Frigate", "Warp Engine", 80, 30, 20});
    galaxy.addAlienShip({"Drone", "Solar Sail", 20, 60, 60});
    galaxy.addAlienShip({"Destroyer", "Fusion Core", 90, 40, 30});

    cout << "Welcome to Space Game!" << endl;

    while (true)
    {
        int option;
        cout << "\n1. Explore\n2. Quit\n3.CheckInventory" << endl;
        cout << "Choice: ";
        cin >> option;

        // clear_input_buffer();

        if (option == 1)
        {
            AlienShip *ship = galaxy.explore();

            if (!ship)
            {
                cout << "\nNo encounter!";
                continue;
            }

            int shipIndex = 0;
            for (int i = 0; i < galaxy.getAlienShips().size(); ++i)
            {
                if (galaxy.getAlienShips()[i].getName() == ship->getName())
                {
                    shipIndex = i;
                    break;
                }
            }

            ship->displayInfo();

            int x;
            cout << "\n1.Scan";

            if (!player.getTractorBeam())
            {
                cout << "\n2.EquipTractorBeam" << endl;
            }

            cin >> x;
            // clear_input_buffer();

            if (x == 1)
            {
                displayInventory(player);
                int scanner_no;
                int max_scanner_no = player.getScanners().size();
                cout << "Scanner No: (1-" << to_string(max_scanner_no) << "): ";

                cin >> scanner_no;
                // clear_input_buffer();

                if (scanner_no < 0 || scanner_no > max_scanner_no)
                {
                    cout << "Invalid Scanner" << endl;
                    continue;
                }

                --scanner_no; // to match with index

                if (player.captureShip(*ship, scanner_no))
                {
                    cout << "A new ship is captured!" << endl;
                    cout << ship->getName() << " - Hull Strength: " << ship->getHullStrength() << endl;
                    galaxy.removeShip(shipIndex);
                    displayInventory(player);
                }
                else
                {
                    if (ship->attemptFlee())
                    {
                        cout << "\nShip fleed!" << endl;

                        galaxy.removeShip(shipIndex);
                    }
                    else
                    {
                        cout << "\nShip remained in range!" << endl;
                    }
                }
            }
            else
            {
                int option;
                cout << "\n1.Standard\n2.Heavy" << endl;
                cin >> option;

                if (option == 1)
                {
                    TractorBeam tractorBeam{"Standard", 40};
                    player.equipTractorBeam(&tractorBeam);
                }
                else if (option == 2)
                {
                    TractorBeam tractorBeam{"Heavy", 40};
                    player.equipTractorBeam(&tractorBeam);
                }
                else
                {
                    cout << "Invalid Choice!" << endl;
                    continue;
                }
                cout << "Tractor Beam Equipped!";
            }

            if (galaxy.getAlienShips().empty())
            {
                cout << "\nNo more ships in the galaxy! You win!" << endl;
                displayInventory(player);
                break;
            }
            else if (player.getScanners().empty())
            {
                cout << "\nNo more scanners! You lose!" << endl;
                displayInventory(player);
                break;
            }
        }
        else if (option == 2)
        {
            cout << "Quitting...";
            break;
        }
        else if (option == 3)
        {
            displayInventory(player);
            continue;
        }
        else
        {
            cout << "Invalid Choice!" << endl;
        }
    }

    return 0;
}