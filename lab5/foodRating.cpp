// array practice

#include <iostream>
#include <array>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

void collectRatings(const array<string, 5> &dishes, array<array<int, 10>, 5> &responses);
void displayResults(const array<string, 5> &dishes, const array<array<int, 10>, 5> &responses);
int findSmallestNum(const vector<int> &vec);
int findLargestNum(const vector<int> &vec);

int main()
{
    array<string, 5> dishes{"Pad Thai", "Som Tam", "Mango Sticky Rice", "Tom Yum Goong", "Green Curry"};
    array<array<int, 10>, 5> responses{0};
    collectRatings(dishes, responses);
    displayResults(dishes, responses);

    return 0;
}

void collectRatings(const array<string, 5> &dishes, array<array<int, 10>, 5> &responses)
{
    for (size_t i{0}; i < 5; ++i)
    {
        cout << "\nPool " << i + 1 << ":" << endl;

        for (size_t j{0}; j < dishes.size(); ++j)
        {

            int rating;
            cout << "Rate " << dishes.at(j) << " on a scale of 1 to 10: ";
            while (true)
            {
                string input;
                getline(cin, input);
                try
                {
                    rating = stoi(input);
                }
                catch (...)
                {
                    cout << "Invalid input. Please enter a number between 1 and 10: ";
                    continue;
                }

                if (rating > 0 && rating <= 10)
                {
                    break;
                }
                cout << "Invalid input. Please enter a number between 1 and 10: ";
            }

            ++responses[j][rating - 1];
        }
    }
}

void displayResults(const array<string, 5> &dishes, const array<array<int, 10>, 5> &responses)
{
    vector<int> total_ratings{};

    cout << "Survey Results" << endl;
    cout << left << setw(25) << "Dish";
    for (int i = 0; i < 10; ++i)
    {
        cout << i + 1 << "\t";
    }

    cout << "Average" << endl;

    for (size_t j{0}; j < dishes.size(); ++j)
    {
        int total{0};
        int rating_count{0};

        cout << left << setw(25) << dishes[j];
        for (int k = 0; k < responses[j].size(); ++k)
        {
            rating_count += responses[j][k];
            total += responses[j][k] * (k + 1);

            cout << responses[j][k] << "\t";
        }

        total_ratings.push_back(total);
        cout << setprecision(2) << total / static_cast<float>(rating_count) << endl;
    }

    int smallest_index = findSmallestNum(total_ratings);
    int largest_index = findLargestNum(total_ratings);

    cout << "Highest Rated Dish: " << dishes[largest_index] << " (" << total_ratings[largest_index] << ")" << endl;
    cout << "Lowest Rated Dish: " << dishes[smallest_index] << " (" << total_ratings[smallest_index] << ")" << endl;
}

// returns index of smallest num
int findSmallestNum(const vector<int> &vec)
{
    int smallest_index{0};

    for (int i{0}; i < vec.size(); ++i)
    {
        if (vec.at(smallest_index) > vec.at(i))
        {
            smallest_index = i;
        }
    }

    return smallest_index;
}

// returns index of largest num
int findLargestNum(const vector<int> &vec)
{
    int largest_index{0};

    for (int i{0}; i < vec.size(); ++i)
    {
        if (vec.at(largest_index) < vec.at(i))
        {
            largest_index = i;
        }
    }

    return largest_index;
}