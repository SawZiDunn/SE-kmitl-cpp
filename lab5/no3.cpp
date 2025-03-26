#include <limits>
#include <iostream>
#include <array>
#include <string>

using namespace std;

std::array<string, 3> drinkSize = {"SMALL", "MEDIUM", "LARGE"};
float sizePrice[3] = {0., 10., 20.};
string drinkType[4] = {"COFFEE", "TEA", "LATTE", "JUICE"};
float basePrice[4] = {35., 25., 40., 60.};

int main()
{

    int n;
    cout << "Welcome to Coffee Shop!" << endl;

    while (true)
    {
        float total_price = 0.0;

        cout << "\nSelect your drink:" << endl;
        for (int i = 0; i < 4; i++)
        {
            cout << i + 1 << ". " << drinkType[i] << ", ";
        }
        cout << endl;

        cout << "Enter number (1-4): ";
        cin >> n;

        if (n < 1 || n > 4)
        {
            cout << "Invalid Input!" << endl;
            continue;
        }

        string drink = drinkType[n - 1];
        total_price += basePrice[n - 1];

        cout << "\nSelect size: ";
        for (int i = 0; i < drinkSize.size(); i++)
        {
            cout << i + 1 << ". " << drinkSize[i] << ", ";
        }
        cout << endl;
        cout << "Enter number (1-3): ";
        cin >> n;

        if (n < 1 || n > 3)
        {
            cout << "Invalid Input!" << endl;
            continue;
        }

        string drink_size = drinkSize[n - 1];

        total_price += sizePrice[n - 1];

        cout << "\nOrder Details:\n"
             << "Drink: " << drink << "\tSize: " << drink_size << "\tPrice: $" << total_price << endl;
        string input;
        cout << "Would you like to order again? (y/n): ";

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clears any leftover newline
        getline(cin, input);

        if (input != "y" && input != "Y")
        {
            break;
        }
    }

    return 0;
}
