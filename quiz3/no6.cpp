#include <iostream>
using namespace std;

class Book
{
private:
    string title;

public:
    Book(string t) : title(t) {}

    string getTitle() const
    {
        return title;
    }
};

class Textbook : public Book
{
public:
    // use base class's constructor
    using Book::Book;

    // Method to print the title
    void display() const
    {
        cout << "Textbook Title: " << getTitle() << endl;
    }
};

int main()
{
    Textbook myTextbook("C++ Basics");

    myTextbook.display();

    return 0;
}
