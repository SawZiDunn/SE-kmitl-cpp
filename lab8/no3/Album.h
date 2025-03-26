#ifndef ALBUM_H // #pragma once
#define ALBUM_H

#include <string>
#include <iostream>

using namespace std;

class Album
{
private:
    string title;
    string artist;
    double price;
    int copies;

    static int totalAlbums;
    static double totalSales;

public:
    Album(const string &, const string &, double, int);

    bool purchaseAlbum();

    static int getTotalAlbums(); //{return totalAlbums} can directly return here

    static double getTotalSales();

    void displayInfo();
};

#endif