#include "Album.h"
#include <iostream>

int Album::totalAlbums = 0;
double Album::totalSales = 0;

Album::Album(const std::string &title, const std::string &artist, double price, int copies)
    : title(title), artist(artist), price(price), copiesAvailable(copies)
{

    totalAlbums += copies;
}

void Album::purchaseAlbum()
{
    if (copiesAvailable > 0)
    {
        copiesAvailable--;
        totalSales += price;
        totalAlbums--; // Reduce total albums count
        std::cout << "Album purchased successfully!\n";
    }
    else
    {
        std::cout << "Sorry, this album is out of stock!\n";
    }
}

/*
If we want to implement static functions in cpp file, no need to include static keywork
*/
int Album::getTotalAlbums()
{
    return Album::totalAlbums; // Album::totalAlbums
}

// g++ Album.cpp main.cpp -o output