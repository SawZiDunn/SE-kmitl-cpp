#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Book
{
protected:
    string bookID;
    double baseFineRate;
    virtual double calculateFine(int daysOverdue) = 0; // pure virtua method

public:
    Book(string bookID, double baseFineRate) : bookID{bookID}, baseFineRate{baseFineRate} {}
    virtual void displayInfo() = 0;
};

class Textbook : public Book
{

private:
    string subject;

    double calculateFine(int daysOverdue) override
    {
        return baseFineRate + (daysOverdue * 0.5); // Book::baseFineRate
    }

public:
    Textbook(string bookID, double baseFineRate, string subject) : Book::Book(bookID, baseFineRate), subject{subject} {}

    void displayInfo() override
    {
        cout << "ID: " << bookID << endl;
        cout << "Base Fine Rate: $" << baseFineRate << endl;
        cout << "Subject: " << subject << endl;
        cout << "Fine for overdue: $" << calculateFine(5) << endl;
    }
};

class Novel : public Book
{

private:
    string genre;

    double calculateFine(int daysOverdue) override
    {
        return Book::baseFineRate + (daysOverdue * 0.2);
    }

public:
    Novel(string bookID, double baseFineRate, string genre) : Book(bookID, baseFineRate), genre{genre} {}

    void displayInfo() override
    {
        cout << "ID: " << bookID << endl;
        cout << "Base Fine Rate: $" << baseFineRate << endl;
        cout << "Genre: " << genre << endl;
        cout << "Fine for overdue: $" << calculateFine(5) << endl;
    }
};

int main()
{
    vector<Book *> books;

    books.push_back(new Textbook{"T001", 1, "Physics"});
    books.push_back(new Novel{"N001", 0.5, "Mystery"});

    for (Book *book : books)
    {
        book->displayInfo();
    }

    for (Book *book : books)
    {
        delete book;
    }

    return 0;
}