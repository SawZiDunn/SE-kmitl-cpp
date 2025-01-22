#include <iostream>
#include <string>

using namespace std;

class HeartRateMonitor
{
public:
    HeartRateMonitor(string f_name, string l_name, int birth_yr, int birth_month, int birthday)
        : f_name(f_name), l_name(l_name), birth_yr(birth_yr), birth_month(birth_month), birthday(birthday)
    {
        calculate_age();
        calculateHeartRates();
    }

    void displayInformation()
    {
        cout << "Hello, " << user_age << "-year-old " << f_name + ' ' + l_name << '.' << endl;
        cout << "Your maximum heartrate should be " << max_heart_rate << " beats per minute." << endl;
        cout << "Your target heartrate range is " << lower_target_heart_rate << " - " << upper_target_heart_rate << " beats per minute." << endl;
    }

    void calculate_age()
    {
        int current_yr{2023};
        int current_month{12};
        int current_day{18};

        user_age = current_yr - birth_yr;

        if ((birth_month > current_month) || (birth_month == current_month && birthday > current_day))
        {
            --user_age;
        }
    }

    void calculateHeartRates()
    {
        max_heart_rate = 220 - user_age;
        lower_target_heart_rate = max_heart_rate * 0.5;
        upper_target_heart_rate = max_heart_rate * 0.85;
    }

private:
    string f_name;
    string l_name;
    int user_age;
    int birth_yr;
    int birth_month;
    int birthday;
    int max_heart_rate;
    int lower_target_heart_rate;
    int upper_target_heart_rate;
};

int main()
{
    string first_name;
    string last_name;
    int birth_yr, birth_month, birthday;

    cout << "Enter your first name: ";
    cin >> first_name;

    cout << "Enter your last name: ";
    cin >> last_name;

    cout << "Enter your birth year (YYYY): ";
    cin >> birth_yr;

    cout << "Enter your birth month (MM): ";
    cin >> birth_month;

    cout << "Enter your birth day (DD): ";
    cin >> birthday;

    HeartRateMonitor heart_rate_monitor{first_name, last_name, birth_yr, birth_month, birthday};
    heart_rate_monitor.displayInformation();

    return 0;
}