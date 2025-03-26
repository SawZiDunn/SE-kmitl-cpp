#include "Album.h"

// initialize static attributes
// no need to include static keyword
int Album::totalAlbums = 0; // need to declare int again?
double Album::totalSales = 0.0;

int Album::getTotalAlbums()
{
    return totalAlbums; // Album::totalAlbums;
}

double Album::getTotalSales()
{
    return totalSales;
}

Album::Album(const string &title, const string &artist, double price, int copies)
    : title(title), artist(artist), price(price), copies(copies)
{
    totalAlbums += copies;
}

bool Album::purchaseAlbum()
{
    if (copies > 0)
    {
        totalAlbums--;
        copies--;
        totalSales += price;
        return true;
    }
    return false;
}

void Album::displayInfo()
{
    cout << "Title: " << title << " - Artist: " << artist << " - Price: " << price << " THB - Copies: " << copies << endl;
}

// run -> g++ Album.cpp main.cpp -o output