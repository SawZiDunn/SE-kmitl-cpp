#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm> // for random_shuffle
#include <string>

using namespace std;

string scrambleWord(const string &str);

int main()
{
    ifstream file("word.txt");
    srand(time(0));
    // default_random_engine engine(static_cast<unsigned int>(time(0)));
    // uniform_int_distribution()

    if (!file)
    {
        cerr << "Error: Unable to open the file!" << endl;
        return 1;
    }

    // cout << "File opened successfully.\n";

    string line;
    vector<string> words;
    while (getline(file, line))
    {
        remove(line.begin(), line.end(), ' ');
        words.push_back(line);
    }

    cout << "Welcome to Word Jumble Game!" << endl;
    int correct{0};
    int wrong{0};
    int words_played{0};

    for (int i = 0; i < 5; ++i)
    {
        int random_no = rand() % words.size();

        cout << "Word " << i + 1 << "/5" << endl;

        string original_word = words.at(random_no);
        string scrambled_word = scrambleWord(original_word);

        cout << "Scrambled Word: " << scrambled_word << endl;

        bool isQuit{false};
        ++words_played;

        int attemp{0};
        for (int j = 0; j < 3; ++j)
        {
            string user_guess;
            cout << "\nYour guess (or 'next' to skip, 'quit' to exit) :";
            getline(cin, user_guess);

            if (user_guess.compare("next") == 0)
            {
                --words_played;

                break;
            }
            else if (user_guess == "quit")
            {

                cout << "Thanks for playing the game!" << endl;
                isQuit = true;
                break;
            }
            else if (user_guess == original_word)
            {
                cout << "Correct!" << endl;
                ++correct;
                break;
            }
            else
            {
                cout << "Wrong! " << 2 - j << " attempts left" << endl;
                ++attemp;
                ++wrong;

                continue;
            }
        }

        if (attemp == 3)
        {
            cout << "Out of attemps! The correct word was: " << original_word << endl;
        }

        if (isQuit)
        {
            break;
        }
    }

    cout << "Game Completed! Here's your summary: " << endl;
    cout << "- Words played: " << words_played << endl;
    cout << "- Correct answers: " << correct << endl;
    cout << "- Wrong attempts: " << wrong << endl;

    // for (const string &word : words) {
    //     cout << word << endl;
    // }

    file.close();
    cout << "File reading completed\n";
    return 0;
}

string scrambleWord(const string &str)
{
    string x = str;

    for (int i = 0; i < str.size(); ++i)
    {
        int a = rand() % str.size();
        int b = rand() % str.size();
        swap(x[a], x[b]);
    }

    // random_shuffle(x.begin(), x.end());
    return x;
}