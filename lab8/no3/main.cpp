#include <iostream>
#include <vector>
#include "Album.h"
#include <string>
#include <limits>

using namespace std;

void displayChoices();
void clearBuffer();
void listAlbums(vector<Album> &albums);
void purchaseAlbum(vector<Album> &albums, int id);

int main()
{
    vector<Album> albums;

    Album album{"Abbey Road", "The Beatles", 19.99, 0};
    albums.push_back(album);

    albums.push_back(Album{"Hotel California", "Eagles", 15.99, 4});

    albums.push_back({"Abbey Road", "The Beatles", 19.99, 5});

    albums.emplace_back("Abbey Road", "The Beatles", 19.99, 5);

    int choice;
    while (true)
    {
        displayChoices();
        cin >> choice;
        if (cin.fail())
        {
            cout << "clear buffer" << endl;
            clearBuffer();
            cout << "Invalid choice. Please enter a number between 1 and 5.\n";
            continue;
        }

        if (choice == 1)
        {
            listAlbums(albums);
        }
        else if (choice == 2)
        {
            int id;
            cout << "Album ID: ";
            cin >> id;
            clearBuffer();
            purchaseAlbum(albums, id);
        }
        else if (choice == 3)
        {
            cout << "Total Albums: " << Album::getTotalAlbums() << endl;
        }
        else if (choice == 4)
        {

            cout << "Total Sales: " << Album::getTotalSales() << endl;
        }
        else if (choice == 5)
        {
            break;
        }
        else
        {
            cout << "Invalid Choice!" << endl;
            continue;
        }
    }
}

void clearBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayChoices()
{
    cout << "\n1. List Available Albums" << "\n"
         << "2. Purchase Album" << "\n"
         << "3. View Total Albums" << "\n"
         << "4. View Total Revenue" << "\n"
         << "5. Exit" << "\n"
         << "Enter your choice: ";
}

void listAlbums(vector<Album> &albums)
{
    for (Album &album : albums)
    {
        album.displayInfo();
    }
}

void purchaseAlbum(vector<Album> &albums, int id)
{

    for (int i = 1; i <= albums.size(); ++i)
    {
        if (i == id)
        {
            if (!albums[i - 1].purchaseAlbum())
            {
                cout << "No copies left!" << endl;
                break;
            }
        }
    }

    cout << "Album not Found!" << endl;
}