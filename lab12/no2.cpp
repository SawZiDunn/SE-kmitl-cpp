#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class CarbonEmitter
{
public:
    CarbonEmitter(string uniqueId) : id(uniqueId) {}
    virtual double getCarbonFootprint() = 0;
    virtual void displayDetails() = 0;
    string getId() const { return id; }

protected:
    string id;
};

class Factory : public CarbonEmitter
{
public:
    Factory(string id, double prodHours, double energyHr, double wasteHr)
        : CarbonEmitter(id), productionHours(prodHours),
          energyPerHour(energyHr), wastePerHour(wasteHr) {}

    double getCarbonFootprint() override
    {
        return (energyPerHour * productionHours * 0.5) + (wastePerHour * productionHours * 0.2);
    }

    void displayDetails() override
    {
        cout << "Factory Details:" << endl;
        cout << "ID: " << id << endl;
        cout << "Production Hours: " << productionHours << endl;
        cout << "Energy per Hour: " << energyPerHour << endl;
        cout << "Waste per Hour: " << wastePerHour << endl;
        cout << "Carbon Footprint: " << getCarbonFootprint() << " kg CO2" << endl;
    }

protected:
    double productionHours;
    double energyPerHour;
    double wastePerHour;
};

class Car : public CarbonEmitter
{
public:
    Car(string id, double miles, double efficiency)
        : CarbonEmitter(id), milesDriven(miles), fuelEfficiency(efficiency) {}

    double getCarbonFootprint() override
    {
        return (milesDriven / fuelEfficiency) * 8.8;
    }

    void displayDetails() override
    {
        cout << "Car Details:" << endl;
        cout << "ID: " << id << endl;
        cout << "Miles Driven: " << milesDriven << endl;
        cout << "Fuel Efficiency: " << fuelEfficiency << endl;
        cout << "Carbon Footprint: " << getCarbonFootprint() << " kg CO2" << endl;
    }

protected:
    double milesDriven;
    double fuelEfficiency;
};

class ElectricCar : public Car
{
public:
    ElectricCar(string id, double miles, double efficiency, double batCapacity, double chargeEff)
        : Car(id, miles, efficiency), batteryCapacity(batCapacity), chargeEfficiency(chargeEff) {}

    double getCarbonFootprint() override
    {
        return (milesDriven / fuelEfficiency) * (1 / chargeEfficiency) * 0.5;
    }

    void displayDetails() override
    {
        cout << "Electric Car Details:" << endl;
        cout << "ID: " << id << endl;
        cout << "Miles Driven: " << milesDriven << endl;
        cout << "Fuel Efficiency: " << fuelEfficiency << endl;
        cout << "Battery Capacity: " << batteryCapacity << endl;
        cout << "Charge Efficiency: " << chargeEfficiency << endl;
        cout << "Carbon Footprint: " << getCarbonFootprint() << " kg CO2" << endl;
    }

protected:
    double batteryCapacity;
    double chargeEfficiency;
};

class Building : public CarbonEmitter
{
public:
    Building(string id, double energy, int occupants)
        : CarbonEmitter(id), energyUsage(energy), numberOfOccupants(occupants) {}

    double getCarbonFootprint() override
    {
        return (energyUsage / static_cast<double>(numberOfOccupants)) * 0.5 * numberOfOccupants;
    }

    void displayDetails() override
    {
        cout << "Building Details:" << endl;
        cout << "ID: " << id << endl;
        cout << "Energy Usage: " << energyUsage << endl;
        cout << "Number of Occupants: " << numberOfOccupants << endl;
        cout << "Carbon Footprint: " << getCarbonFootprint() << " kg CO2" << endl;
    }

protected:
    double energyUsage;
    int numberOfOccupants;
};

class Bicycle : public CarbonEmitter
{
public:
    Bicycle(string id, double miles, double manuEmissions)
        : CarbonEmitter(id), milesRidden(miles), manufacturingEmissions(manuEmissions) {}

    double getCarbonFootprint() override
    {
        return manufacturingEmissions / 365;
    }

    void displayDetails() override
    {
        cout << "Bicycle Details:" << endl;
        cout << "ID: " << id << endl;
        cout << "Miles Ridden: " << milesRidden << endl;
        cout << "Manufacturing Emissions: " << manufacturingEmissions << endl;
        cout << "Carbon Footprint: " << getCarbonFootprint() << " kg CO2" << endl;
    }

protected:
    double milesRidden;
    double manufacturingEmissions;
};

int main()
{
    // Create a vector to store CarbonEmitter pointers
    vector<CarbonEmitter *> carbonEmitters;

    // Validate inputs and get user input for each type of object
    Factory *factory = new Factory("FAC001", 10, 5.5, 0.3);
    carbonEmitters.push_back(factory);

    Car *car = new Car("CAR001", 100, 25);
    carbonEmitters.push_back(car);

    ElectricCar *electricCar = new ElectricCar("ECAR001", 80, 4, 50, 0.9);
    carbonEmitters.push_back(electricCar);

    Building *building = new Building("BLD001", 500, 10);
    carbonEmitters.push_back(building);

    Bicycle *bicycle = new Bicycle("BIC001", 20, 250);
    carbonEmitters.push_back(bicycle);

    double totalCarbonFootprint = 0.0;
    cout << "Carbon Footprint Calculation System" << endl;
    cout << "-----------------------------------" << endl;

    for (CarbonEmitter *emitter : carbonEmitters)
    {
        emitter->displayDetails();
        totalCarbonFootprint += emitter->getCarbonFootprint();
        cout << endl;
    }

    cout << "Total Carbon Footprint: " << fixed << setprecision(2) << totalCarbonFootprint << " kg CO2" << endl;

    for (CarbonEmitter *emitter : carbonEmitters)
    {
        delete emitter;
    }

    return 0;
}