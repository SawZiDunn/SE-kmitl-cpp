#include<iostream>
#include<iomanip>

using namespace std;

int main() {
    
    cout << "Face length of cube\t" << "Surface area of cube\t" << "Volume of cube" << endl;
    cout << left << setw(22) << "(cm)" << "\t" <<  left << setw(22) << "(cm^2)" << "\t" <<  left << setw(22) << "cm^3" << "\t" << endl;

    for (int i = 0; i < 5; i++) {
        float surface_area = i * i * 6;
        float volume = i * i * i;
        cout <<  left << setw(19) << i << "\t" <<  left << setw(19) << surface_area << "\t" <<  left << setw(19) << volume << "\t" << endl;
    }   


    


    return 0;
}