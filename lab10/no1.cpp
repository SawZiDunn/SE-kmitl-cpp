#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

struct Movie
{
    string title;
    string date;                         // YYYY-MM-DD
    vector<vector<bool>> availableSeats; // 4x40 grid for 4 rounds and 40 seats each
};

struct Reservation
{
    string customerName;
    string movieTitle;
    string date;
    int round;      // 1 for 12:00, 2 for 15:00, 3 for 18:00, 4 for 21:00
    int seatNumber; // 1 to 40
};

// Function prototypes
void displaySchedule(const vector<Movie> &movies);
void makeReservation(vector<Movie> &movies, vector<Reservation> &reservations);
void cancelReservation(vector<Movie> &movies, vector<Reservation> &reservations);
void displaySeatingChart(const Movie &movie, int round);
void displayMenu();
void saveToFile(const vector<Movie> &movies, const vector<Reservation> &reservations);
void loadFromFile(vector<Movie> &movies, vector<Reservation> &reservations);
void clearInputBuffer();
bool isValidDate(const string &date);
bool isValidSeatNumber(int seat);
bool isValidRound(int round);

void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool isValidDate(const string &date)
{
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;

    for (int i = 0; i < 10; i++)
    {
        if (i != 4 && i != 7 && !isdigit(date[i]))
            return false;
    }
    return true;
}

bool isValidSeatNumber(int seat)
{
    return seat >= 1 && seat <= 40;
}

bool isValidRound(int round)
{
    return round >= 1 && round <= 4;
}

void displaySchedule(const vector<Movie> &movies)
{
    cout << "\n=== Current Movie Schedule ===\n"
         << endl;
    for (const Movie &movie : movies)
    {
        cout << movie.title << " (" << movie.date << ")" << endl;
        for (size_t i = 0; i < movie.availableSeats.size(); ++i)
        {
            int availableCount = 0;
            for (bool available : movie.availableSeats[i])
            {
                if (available)
                    ++availableCount;
            }
            cout << "- Round " << i + 1 << " (" << (12 + i * 3) << ":00): "
                 << availableCount << " seats available" << endl;
        }
        cout << endl;
    }
}

void displaySeatingChart(const Movie &movie, int round)
{
    cout << "\nSeating Chart for " << movie.title << " - Round " << round << " ("
         << (9 + round * 3) << ":00)" << endl;
    cout << "O = Available, X = Booked\n"
         << endl;

    for (int i = 0; i < 40; ++i)
    {
        if (movie.availableSeats[round - 1][i])
        {
            cout << "O ";
        }
        else
        {
            cout << "X ";
        }
        if ((i + 1) % 10 == 0)
            cout << endl;
    }
    cout << endl;
}

void makeReservation(vector<Movie> &movies, vector<Reservation> &reservations)
{
    displaySchedule(movies);

    string name, movieTitle, date;
    int round, seat;

    cout << "Enter customer name: ";
    clearInputBuffer();
    getline(cin, name);

    cout << "Enter movie title: ";
    getline(cin, movieTitle);

    cout << "Enter date (YYYY-MM-DD): ";
    getline(cin, date);

    if (!isValidDate(date))
    {
        cout << "Invalid date format! Please use YYYY-MM-DD" << endl;
        return;
    }

    // Find the movie
    Movie *selectedMovie = nullptr;
    for (Movie &movie : movies)
    {
        if (movie.title == movieTitle && movie.date == date)
        {
            selectedMovie = &movie;
            break;
        }
    }

    if (!selectedMovie)
    {
        cout << "Movie not found!" << endl;
        return;
    }

    cout << "Enter round (1-4): ";
    cin >> round;

    if (!isValidRound(round))
    {
        cout << "Invalid round number!" << endl;
        return;
    }

    displaySeatingChart(*selectedMovie, round);

    cout << "Enter seat number (1-40): ";
    cin >> seat;

    if (!isValidSeatNumber(seat))
    {
        cout << "Invalid seat number!" << endl;
        return;
    }

    if (!selectedMovie->availableSeats[round - 1][seat - 1])
    {
        cout << "This seat is already booked!" << endl;
        return;
    }

    // Make the reservation
    selectedMovie->availableSeats[round - 1][seat - 1] = false;
    reservations.push_back({name, movieTitle, date, round, seat});

    cout << "\nReservation successful!" << endl;
    cout << "Name: " << name << endl;
    cout << "Movie: " << movieTitle << endl;
    cout << "Date: " << date << endl;
    cout << "Round: " << round << " (" << (9 + round * 3) << ":00)" << endl;
    cout << "Seat: " << seat << endl;
}

void cancelReservation(vector<Movie> &movies, vector<Reservation> &reservations)
{
    string name, movieTitle, date;
    int round, seat;

    cout << "Enter customer name: ";
    clearInputBuffer();
    getline(cin, name);

    cout << "Enter movie title: ";
    getline(cin, movieTitle);

    cout << "Enter date (YYYY-MM-DD): ";
    getline(cin, date);

    cout << "Enter round (1-4): ";
    cin >> round;

    cout << "Enter seat number (1-40): ";
    cin >> seat;

    // Find and remove the reservation
    bool found = false;
    for (auto it = reservations.begin(); it != reservations.end(); ++it)
    {
        if (it->customerName == name &&
            it->movieTitle == movieTitle &&
            it->date == date &&
            it->round == round &&
            it->seatNumber == seat)
        {

            // Update movie seat availability
            for (Movie &movie : movies)
            {
                if (movie.title == movieTitle && movie.date == date)
                {
                    movie.availableSeats[round - 1][seat - 1] = true;
                    break;
                }
            }

            reservations.erase(it);
            found = true;
            cout << "\nReservation successfully cancelled!" << endl;
            break;
        }
    }

    if (!found)
    {
        cout << "Reservation not found!" << endl;
    }
}

void saveToFile(const vector<Movie> &movies, const vector<Reservation> &reservations)
{
    // Save movies
    ofstream movieFile("movies.txt");
    for (const Movie &movie : movies)
    {
        movieFile << movie.title << "," << movie.date << ",";
        for (const auto &round : movie.availableSeats)
        {
            for (bool seat : round)
            {
                movieFile << seat << ",";
            }
        }
        movieFile << endl;
    }
    movieFile.close();

    // Save reservations
    ofstream resFile("reservations.txt");
    for (const Reservation &res : reservations)
    {
        resFile << res.customerName << ","
                << res.movieTitle << ","
                << res.date << ","
                << res.round << ","
                << res.seatNumber << endl;
    }
    resFile.close();
}

void loadFromFile(vector<Movie> &movies, vector<Reservation> &reservations)
{
    // Load movies
    ifstream movieFile("movies.txt");
    if (movieFile.is_open())
    {
        string line;
        while (getline(movieFile, line))
        {
            stringstream ss(line);
            string title, date, seatStr;

            getline(ss, title, ',');
            getline(ss, date, ',');

            vector<vector<bool>> seats(4, vector<bool>(40));
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 40; j++)
                {
                    getline(ss, seatStr, ',');
                    seats[i][j] = (seatStr == "1");
                }
            }

            movies.push_back({title, date, seats});
        }
        movieFile.close();
    }

    // Load reservations
    ifstream resFile("reservations.txt");
    if (resFile.is_open())
    {
        string line;
        while (getline(resFile, line))
        {
            stringstream ss(line);
            string name, title, date, roundStr, seatStr;

            getline(ss, name, ',');
            getline(ss, title, ',');
            getline(ss, date, ',');
            getline(ss, roundStr, ',');
            getline(ss, seatStr, ',');

            reservations.push_back({name, title, date,
                                    stoi(roundStr),
                                    stoi(seatStr)});
        }
        resFile.close();
    }
}

void displayMenu()
{
    cout << "\n=== Movie Theater Reservation System ===\n"
         << "1. View Schedule\n"
         << "2. Make Reservation\n"
         << "3. Cancel Reservation\n"
         << "4. Exit\n"
         << "Enter your choice: ";
}

int main()
{
    vector<Movie> movies;
    vector<Reservation> reservations;

    // Try to load saved data first
    loadFromFile(movies, reservations);

    // Only initialize with sample data if no data was loaded
    if (movies.empty())
    {
        movies = {
            {"Captain America Brave New World", "2024-02-16",
             vector<vector<bool>>(4, vector<bool>(40, true))},
            {"Bridget Jones Mad About the Boy", "2024-02-17",
             vector<vector<bool>>(4, vector<bool>(40, true))},
            {"Flat Girls", "2024-02-18",
             vector<vector<bool>>(4, vector<bool>(40, true))},
            {"Heretic", "2024-02-19",
             vector<vector<bool>>(4, vector<bool>(40, true))},
            {"Dark Nuns", "2024-02-20",
             vector<vector<bool>>(4, vector<bool>(40, true))}};
    }

    while (true)
    {
        displayMenu();
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            displaySchedule(movies);
            break;
        case 2:
            makeReservation(movies, reservations);
            break;
        case 3:
            cancelReservation(movies, reservations);
            break;
        case 4:
            saveToFile(movies, reservations);
            cout << "Thank you for using our system. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}