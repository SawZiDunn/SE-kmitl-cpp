#include <iostream>
#include <random>
#include <chrono>
#include <string>

using namespace std;

// Structure to hold question details
struct Question
{
    int num1;
    int num2;
    char operation;
    int correctAnswer;
};

// Function prototypes
Question generateQuestion(int level, mt19937 &gen);
int calculateAnswer(int num1, int num2, char operation);
bool checkAnswer(int studentAnswer, int correctAnswer);
void displayProgress(int correctCount, int totalAttempts);
void displayFinalFeedback(int correctCount, int totalQuestions);
int getRandomNumber(int max, mt19937 &gen);

int main()
{
    // Initialize random number generator with time-based seed
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);

    char playAgain = 'y';
    bool switchPlayer = true;

    while (switchPlayer && (playAgain == 'y' || playAgain == 'Y'))
    {
        int level;
        cout << "Difficulty Level (1-3): ";
        cin >> level;

        while (level < 1 || level > 3)
        {
            cout << "Please enter a valid level (1-3): ";
            cin >> level;
        }

        int correctCount = 0;
        int totalQuestions = 10;
        int questionNumber = 1;
        int totalAttempts = 0;

        while (questionNumber <= totalQuestions)
        {
            Question q = generateQuestion(level, gen);
            bool answered = false;
            int attempts = 0;

            const int MAX_ATTEMPTS = 2;
            while (!answered && attempts <= MAX_ATTEMPTS)
            {
                cout << "\nQuestion " << questionNumber << ": How much is "
                     << q.num1 << " " << q.operation << " " << q.num2 << "? ";
                int studentAnswer;
                cin >> studentAnswer;

                if (checkAnswer(studentAnswer, q.correctAnswer))
                {
                    cout << "Very good!\n";
                    correctCount++;
                    answered = true;
                }
                else
                {
                    attempts++;
                    if (attempts <= MAX_ATTEMPTS)
                    {
                        cout << "No. Please try again. (Attempt " << attempts << "/" << MAX_ATTEMPTS << ")\n";
                    }
                    else
                    {
                        cout << "Sorry, the correct answer was: " << q.correctAnswer << "\n";
                    }
                }
            }
            totalAttempts += attempts;

            displayProgress(correctCount, questionNumber);
            questionNumber++;
        }

        displayFinalFeedback(correctCount, totalQuestions);

        cout << "\nWould you like to play again? (y/n/q to quit): ";
        cin >> playAgain;

        if (playAgain == 'q' || playAgain == 'Q')
        {
            switchPlayer = false; // Immediate program exit
            cout << "\nQuitting program...\n";
        }
        else if (playAgain == 'n' || playAgain == 'N')
        {
            cout << "\nSwitching to new player...\n";
            playAgain = 'y'; // Reset for new player
            cout << "\n--- New Player Session ---\n";
        }
    }

    cout << "\nThank you for practicing arithmetic!\n";
    return 0;
}

Question generateQuestion(int level, mt19937 &gen)
{
    Question q;
    int maxNum;

    // Set maximum number based on level
    switch (level)
    {
    case 1:
        maxNum = 9;
        break; // Single digit
    case 2:
        maxNum = 99;
        break; // Two digits
    case 3:
        maxNum = 999;
        break; // Three digits
    default:
        maxNum = 9;
    }

    // Generate random numbers and operation
    uniform_int_distribution<> num_dist(1, maxNum);
    q.num1 = num_dist(gen);
    q.num2 = num_dist(gen);

    // Generate random operation (+, -, *)
    uniform_int_distribution<> op_dist(0, 2);
    int op = op_dist(gen);
    switch (op)
    {
    case 0:
        q.operation = '+';
        break;
    case 1:
        q.operation = '-';
        break;
    case 2:
        q.operation = '*';
        break;
    }

    q.correctAnswer = calculateAnswer(q.num1, q.num2, q.operation);
    return q;
}

int calculateAnswer(int num1, int num2, char operation)
{
    switch (operation)
    {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    default:
        return 0;
    }
}

bool checkAnswer(int studentAnswer, int correctAnswer)
{
    return studentAnswer == correctAnswer;
}

void displayProgress(int correctCount, int totalQuestions)
{
    cout << "Progress: " << correctCount << "/" << totalQuestions << " correct\n";
}

void displayFinalFeedback(int correctCount, int totalQuestions)
{
    double percentage = (correctCount * 100.0) / totalQuestions;

    cout << "\nFinal Results:\n";
    cout << "Correct Answers: " << correctCount << endl;
    cout << "Incorrect Answers: " << (totalQuestions - correctCount) << endl;
    cout << "Score: " << percentage << "%\n";

    if (percentage < 75)
    {
        cout << "Please ask your teacher for extra help.\n";
    }
    else
    {
        cout << "Congratulations, you are ready to go to the next level!\n";
    }
}

int getRandomNumber(int max, mt19937 &gen)
{
    uniform_int_distribution<> dist(0, max - 1);
    return dist(gen);
}