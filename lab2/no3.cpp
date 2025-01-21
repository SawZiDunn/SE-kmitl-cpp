#include <iostream>
#include <iomanip>

using namespace std;

int main()
{

    cout << "Face length of cube (cm)\t" << "Surface area of cube (cm^2)\t" << "Volume of cube (cm^3)" << endl;

    for (int i = 0; i < 5; i++)
    {
        float surface_area = i * i * 6;
        float volume = i * i * i;
        string space = "\t\t\t\t";
        cout << setprecision(2) << fixed;
        cout << i << space << surface_area << space << volume << endl;
    }

    return 0;
}