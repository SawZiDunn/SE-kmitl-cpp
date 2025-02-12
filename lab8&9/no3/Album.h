#pragma once
#include <string>
using namespace std;

class Album
{
public:
    Album(const std::string &title, const std::string &artist, double price, int copies);
    void purchaseAlbum();

    // static int getTotalAlbums() {return totalAlbums;};
    static int getTotalAlbums();
    static double getTotalSales() { return totalSales; };

    // Getter methods to access album details
    string getTitle() const { return title; }
    string getArtist() const { return artist; }
    double getPrice() const { return price; }
    int getCopiesAvailable() const { return copiesAvailable; }

private:
    string title;
    string artist;
    double price;
    int copiesAvailable;

    static int totalAlbums;
    static double totalSales;
};
