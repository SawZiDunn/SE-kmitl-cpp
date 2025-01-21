#include <iostream>
#include <iomanip>
using namespace std;

class PopulationGrowth
{
public:
    PopulationGrowth(double current_population, double annual_growth_rate)
        : current_population{current_population}, annual_growth_rate{annual_growth_rate}
    {
    }

    void calculate_population_growth(int year_span = 75)
    {
        cout << "Year\t\t" << "Projected Population\t" << "Annual Increase" << endl;
        bool is_doubled = false;

        double projected_population = current_population;

        for (int i = 0; i < year_span; i++)
        {
            double annual_increase = (projected_population * annual_growth_rate) / 100.0;
            projected_population += annual_increase;

            cout << i + 1 << "\t\t" << fixed << setprecision(0) << projected_population << "\t\t" << annual_increase << endl;

            // projected_population / current_population >= 2
            if (projected_population >= 2 * current_population && !is_doubled)
            {
                population_doubled_year = i + 1;
                is_doubled = true;
            }
        }

        if (is_doubled)
        {
            cout << "The population is doubled in the " << population_doubled_year << "th year." << endl;
        }
        else
        {
            cout << "The population was not dubled within " << year_span << " years." << endl;
        }
    }

private:
    double current_population;
    double annual_growth_rate;
    int population_doubled_year;
};

int main()
{
    double current_population;
    double annual_growth_rate;

    // 7.8e9
    cout << "Enter current population: ";
    cin >> current_population;

    if (current_population <= 0)
    {
        cerr << "Error: Population must be a positive number!" << endl;
        return 1;
    }

    cout << "Enter annual growth rate (%): ";
    cin >> annual_growth_rate;
    if (annual_growth_rate <= 0)
    {
        cerr << "Error: Growth rate must be a positive number!" << endl;
        return 1;
    }

    PopulationGrowth populationGrowth = {current_population, annual_growth_rate};
    populationGrowth.calculate_population_growth();

    return 0;
}