#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

class Book
{
public:
    Book(string title = "Unknown", string author = "Unknown", int quantity = 0)
    {
        set_title(title);
        set_author(author);
        set_quantity(quantity);
    }

    string get_title() const
    {
        return title;
    }

    void set_title(string title)
    {
        if (title != "")
        {
            // title = title won't work for same parameter name and class attribute name
            this->title = title;
        }
        else
        {
            cout << "Title cannot be empty!" << endl;
            return;
        }
    }

    string get_author() const
    {
        return author;
    }

    void set_author(string author)
    {

        if (author != "")
        {
            this->author = author;
        }
        else
        {
            cout << "Author cannot be empty!" << endl;
            return;
        }
    }

    int get_quantity() const
    {
        return quantity;
    }

    void set_quantity(int quantity)
    {
        if (quantity < 0)
        {
            cout << "Quantity must be more than 0." << endl;
        }
        else
        {
            this->quantity = quantity;
        }
    }

private:
    string title;
    string author;
    int quantity;
};

class Inventory
{
public:
    void addBook(Book book)
    {
        books.push_back(book);
        cout << "A new book is successfully added!" << endl;
    }

    void removeBook(string title)
    {
        bool flag = false;
        for (auto i = books.begin(); i != books.end(); ++i)
        {
            if (toLower(i->get_title()) == toLower(title))
            {
                books.erase(i);
                cout << title << " is removed!" << endl;
                flag = true;
                break;
            }
        }

        if (!flag)
        {
            cout << "Book with this title does not exist!" << endl;
        }
    }

    void findBook(string title)
    {
        bool flag = false;
        for (auto i = books.begin(); i != books.end(); ++i)
        {
            if (toLower(i->get_title()) == toLower(title))
            {
                cout << "Title: " << i->get_title()
                     << ", Author: " << i->get_author()
                     << ", Quantity: " << i->get_quantity() << endl;
                flag = true;
                break;
            }
        }

        if (!flag)
        {
            cout << "Book with title - " << title << " does not exist!" << endl;
        }
    }

    void printInventory()
    {
        int count = 0;

        if (books.empty())
        {
            cout << "No books in the inventory!" << endl;
            return;
        }

        cout << "All books: " << endl;
        for (const Book &i : books)
        {
            cout << count << " - Title: " << i.get_title()
                 << ", Author: " << i.get_author()
                 << ", Quantity: " << i.get_quantity() << endl;
            ++count;
        }
    }

private:
    vector<Book> books;

    string toLower(string x)
    {
        for (char &i : x)
        {
            i = tolower(i);
        }

        return x;
    }
};

int main()
{

    string title, author, input;
    int quantity;
    Inventory inventory;

    while (true)
    {

        cout << "Enter command (a: add, s: search, l: list, r: remove, q: quit): ";
        cin >> input;

        if (input == "a")
        {
            cin.ignore();
            cout << "Enter title: ";
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);

            if (title.empty() || author.empty())
            {
                cout << "Title or author cannot be empty!" << endl;
                continue;
            }

            cout << "Enter quantity: ";
            cin >> input;

            stringstream ss(input);
            if (!ss >> quantity || !ss.eof())
            {
                cout << "Please enter a valid quantity!" << endl;
                cin.clear(); // clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            inventory.addBook({title, author, quantity});
        }
        else if (input == "l")
        {
            inventory.printInventory();
        }
        else if (input == "s")
        {
            cout << "Enter title: ";
            cin >> title;
            inventory.findBook(title);
        }
        else if (input == "r")
        {
            cout << "Enter title: ";
            cin >> title;
            inventory.removeBook(title);
        }
        else if (input == "q")
        {
            return 0;
        }
        else
        {
            cout << "Invalid Input!" << endl;
        }
    }

    return 0;
}
