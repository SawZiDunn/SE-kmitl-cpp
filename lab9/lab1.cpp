#include <iostream>
#include <string>
#include <numeric> // for gcd

using namespace std;

class Fraction
{
public:
    Fraction() : numerator(0), denominator(0)
    {
    }

    friend Fraction operator+(Fraction const &f1, Fraction const &f2)
    {
        Fraction f;
        int temp_d = f1.denominator * f2.denominator;
        int temp_n1 = f1.numerator * (temp_d / f1.denominator);
        int temp_n2 = f2.numerator * (temp_d / f2.denominator);

        f.numerator = temp_n1 + temp_n2;
        f.denominator = temp_d;

        f.simplify();

        return f;
    }

    friend Fraction operator-(Fraction const &f1, Fraction const &f2)
    {
        Fraction f;
        int temp_d = f1.denominator * f2.denominator;
        int temp_n1 = f1.numerator * (temp_d / f1.denominator);
        int temp_n2 = f2.numerator * (temp_d / f2.denominator);

        f.numerator = temp_n1 - temp_n2;
        f.denominator = temp_d;

        f.simplify();

        return f;
    }

    friend Fraction operator*(Fraction const &f1, Fraction const &f2)
    {
        Fraction f;

        f.numerator = f1.numerator * f2.numerator;
        f.denominator = f1.denominator * f2.denominator;

        f.simplify();

        return f;
    }

    friend Fraction operator/(Fraction const &f1, Fraction const &f2)
    {
        Fraction f;

        if (f1.denominator == 0 || f2.denominator == 0)
        {
            cout << "undefined!" << endl;
            f.numerator = 0;
            f.denominator = 0;
        }

        f.numerator = f1.numerator * f2.denominator;
        f.denominator = f1.denominator * f2.numerator;

        f.simplify();

        return f;
    }

    friend bool operator>(Fraction const &f1, Fraction const &f2)
    {

        int temp_d = f1.denominator * f2.denominator;
        int temp_n1 = f1.numerator * (temp_d / f1.denominator);
        int temp_n2 = f2.numerator * (temp_d / f2.denominator);

        if (temp_n1 > temp_n2)
        {
            cout << "f1 is greater than f2" << endl;
            return true;
        }

        return false;
    }

    friend bool operator<(Fraction const &f1, Fraction const &f2)
    {
        int temp_d = f1.denominator * f2.denominator;
        int temp_n1 = f1.numerator * (temp_d / f1.denominator);
        int temp_n2 = f2.numerator * (temp_d / f2.denominator);

        if (temp_n1 < temp_n2)
        {
            cout << "f1 is less than f2" << endl;
            return true;
        }

        return false;
    }

    friend bool operator==(Fraction const &f1, Fraction const &f2)
    {
        int temp_d = f1.denominator * f2.denominator;
        int temp_n1 = f1.numerator * (temp_d / f1.denominator);
        int temp_n2 = f2.numerator * (temp_d / f2.denominator);

        if (temp_n1 == temp_n2)
        {
            cout << "f1 is equal to f2" << endl;
            return true;
        }

        return false;
    }

    friend istream &operator>>(istream &cin, Fraction &c)
    {
        char slash;
        cin >> c.numerator >> slash >> c.denominator;
        return cin;
    }

    friend ostream &operator<<(ostream &, Fraction &c)
    {
        cout << c.numerator << "/" << c.denominator;
        return cout;
    }

private:
    int numerator;
    int denominator;

    void simplify()
    {

        int temp_gcd = gcd(numerator, denominator);
        numerator /= temp_gcd;
        denominator /= temp_gcd;
    }
};

int main()
{

    Fraction f1, f2;

    cout << "Enter first fraction (format a/b): ";

    cin >> f1;
    cout << f1 << endl;
    cout << "Enter second fraction (format a/b): ";

    cin >> f2;
    cout << f2 << endl;

    // Fraction f1{2, 5};
    // Fraction f2{2, 5};

    Fraction f = f1 + f2;
    cout << "Sum: " << f << endl;

    f = f1 - f2;
    cout << "Difference: " << f << endl;

    f = f1 * f2;
    cout << "Product: " << f << endl;

    f = f1 / f2;
    cout << "Quotient: " << f << endl;

    f1 < f2;

    return 0;
}