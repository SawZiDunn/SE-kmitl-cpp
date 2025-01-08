#include<iostream>

using namespace std;

void generateQuestion(int num1, int num2, int no, char optr);
int calculateAns(int num1, int num2, char optr);
void calculateFinalScore(int correct, int incorrect);
bool reset();

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int level;
    int correct_ans = 0;
    int incorrect_ans = 0;
    int num1;
    int num2;
    char optr;
    cout << "Difficulty Level: ";
    cin >> level;

    while (true) {
        for (int i = 0; i < 10; i++) {
            if (level == 1) {
                num1 = rand() % 10;
                num2 = rand() % 10;
            } else if (level == 2) {
                num1 = rand() % 90 + 10;
                num2 = rand() % 90 + 10;
            } else if (level == 3) {
                num1 = rand() % 900 + 100;
                num2 = rand() % 900 + 100;
            }

            // to decide operator -> +, -, *, /
            int optr_index = rand() % 4;

            switch (optr_index) {
                case 0:
                    optr = '+';
                    break;
                case 1:
                    optr = '-';
                    break;
                case 2:
                    optr = '*';
                    break;
                case 3:
                    optr = '/';
                    break;
            }

            int ans = calculateAns(num1, num2, optr);
            for (int j = 0; j < 3; ++j) {
                generateQuestion(num1, num2, i + 1, optr);
                
                int user_ans;
                cin >> user_ans;

                if (ans == user_ans) {
                    ++correct_ans;
                    cout << "Very good!" << endl;
                    break;
                } else {
                    // count only for the first iteration
                    if (j == 0) {
                        ++incorrect_ans;
                    }
                    cout << "No. Please try again!" << endl;
                    continue;
                }
            }
            
        }

        calculateFinalScore(correct_ans, incorrect_ans);

        if (reset()) {
            continue;
        } else {
            break;
        }
    }
    return 0;
}

void generateQuestion(int num1, int num2, int no, char optr) {
    
    cout << "Question " << no << ": How much is " 
         << num1 << " " << optr << " " << num2 << "?: ";
}

int calculateAns(int num1, int num2, char optr) {
    switch (optr) {
            case '+':
                return num1 + num2;
            case '-':
                return num1 - num2;
            case '*':
                return num1 * num2;
            case '/':
                return num1 / num2;
        }
    return 0;
}

void calculateFinalScore(int correct, int incorrect) {

    cout << "Correct Answers: " << correct << endl;
    cout << "Incorrect Answers: " << incorrect << endl;
    int score = 100 * (static_cast<float>(correct) / 10.);
    cout << "Score: " << score << "%" << endl;

    if (score >= 75) {
        cout << "Congratulations! You are ready to go to the next level." << endl;
    } else {
        cout << "Please ask your teacher for extra help." << endl;
    }
}

bool reset() {
    string input;
    cout << "Press y to try again!\n'q' to quit: ";
    cin >> input;
    if (input == "y" || input == "Y") {
        return true;

    } else if (input == "q" || input == "Q") {
        return false;
    }

    return false;
}