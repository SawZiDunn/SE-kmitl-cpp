#include <iostream>
#include <vector>
#include "Album.h"

using namespace std;

void displayMenu() {
    cout << "\nMENU:\n";
    cout << "1. List Albums\n";
    cout << "2. Purchase Album\n";
    cout << "3. View Total Albums\n";
    cout << "4. View Total Sales\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    vector<Album> albums;
    
    // Adding sample albums
    // albums.push_back({"Abbey Road", "The Beatles", 19.99, 5});
    albums.emplace_back("The Dark Side of the Moon", "Pink Floyd", 21.99, 3);
    albums.emplace_back("Thriller", "Michael Jackson", 25.50, 4);
    albums.emplace_back("Hotel California", "Eagles", 15.99, 4);
    albums.emplace_back("Back in Black", "AC/DC", 18.75, 2);
    albums.emplace_back("Rumors", "Fleetwood Mac", 16.99, 3);
    albums.emplace_back("The Wall", "Pink Floyd", 22.99, 2);

    int choice;
    while (true) {
        displayMenu();
        cin >> choice;


        switch (choice) {
            case 1: {  // List albums
                cout << "\nAvailable Albums:\n";
                for (size_t i = 0; i < albums.size(); i++) {
                    cout << i + 1 << ". " << albums[i].getTitle() << " by " << albums[i].getArtist()
                         << " - $" << albums[i].getPrice() << " (" << albums[i].getCopiesAvailable() << " in stock)\n";
                }
                break;
            }
            case 2: {  // Purchase an album
                int index;
                cout << "Enter the album number to purchase: ";
                cin >> index;
                
                if (index > 0 && index <= albums.size()) {
                    albums[index - 1].purchaseAlbum();
                } else {
                    cout << "Invalid choice. Try again.\n";
                }
                break;
            }
            case 3:  // View total albums
                cout << "Total albums in stock: " << Album::getTotalAlbums() << endl;
                break;
            case 4:  // View total sales
                cout << "Total sales: $" << Album::getTotalSales() << endl;
                break;
            case 5:  // Exit program
                cout << "Exiting program. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    }
}
