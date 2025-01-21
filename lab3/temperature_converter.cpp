#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class TemperatureConverter
{
public:
    float c_to_f(float c)
    {
        return c * (9. / 5.) + 32.;
    }
    float f_to_c(float f)
    {
        return (f - 32) * (5. / 9.);
    }
};

int main()
{

    TemperatureConverter temperature_converter;

    while (true)
    {
        string input;
        float temperature;

        cout << "Enter temperature: ";
        cin >> input;

        try
        {
            temperature = stof(input);
        }
        catch (const exception &e)
        { // (...) to catch any error
            // cout << e.what() << endl;
            cout << "Please enter a valid temperature." << endl;
            continue;
        }

        cout << "Convert to (C)elcius or (F)ahrenheit: ";
        cin >> input; // overwrites original input value

        // setprecision affects overal precision by default
        // we need fixed to affect only decimal points

        cout << fixed << setprecision(2); // taking two decimal points
        if (input == "c" || input == "C")
        {

            cout << temperature << " Fahrenheit is " << temperature_converter.f_to_c(temperature) << " Celcius." << endl;
        }
        else if (input == "f" || input == "F")
        {
            cout << temperature << " Celcius is " << temperature_converter.c_to_f(temperature) << " Fahrenheit." << endl;
        }
        else
        {
            cout << "Enter only F or C!" << endl;
            continue;
        }

        cout << "Do you want to perform another conversion? (Y/N): ";
        cin >> input;
        if (input == "Y" || input == "y")
        {
            continue;
        }
        else if (input == "N" || input == "n")
        {
            cout << "Thanks for using our temperature converter!" << endl;
            break;
        }
        else
        {
            cout << "Invalid input!" << endl;
            continue;
        }
    }

    return 0;
}
