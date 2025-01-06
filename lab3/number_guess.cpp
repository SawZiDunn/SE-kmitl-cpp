#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib> // For srand() and rand()
#include <ctime>   // For time()
using namespace std;

class GuessNumberGame {
    public:
        int generate_random_no() {
            return rand() % 101;
        }
};
    
int main(){
    srand(static_cast<unsigned int>(NULL));

    GuessNumberGame guess_number_game;
    int num = guess_number_game.generate_random_no();
    int count{0};
    cout << "Guess the number (between 0 and 100): ";

    while (count < 10) {
        int user_guess;
        
        cin >> user_guess;

        if (user_guess == num) {
            cout << "Congratulations! You win." << endl;
            return 0;
        } else if (num > user_guess) {
            cout << "Higher than your number. Try again: ";
        } else {
            cout << "Lower than your number. Try again: ";
        }

        ++count;
        
    }
    cout << '\n';

    cout << "You lose!\nThe correct number is " << num << "." << endl;

    return 0;

}

    

