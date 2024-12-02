#include <iostream>
using namespace std;

int main() {
    float num1, f,c;
    int op;

    cout << "Select what you want to convert: Celsius to Fahrenheit or Fahrenheit to Celsius (1 or 2)" << endl;
    cout << "1 or 2? " << endl;
    cin >> op;
    
    switch (op) {
        case 1:
            cout << "Enter the temperature in Celsius: ";
            cin >> num1;
            c = (num1 * 9 / 5) + 32;
            cout << num1 << " Celsius is " << f << " Fahrenheit." << endl;
            break;

        case 2:
            cout << "Enter the temperature in Fahrenheit: ";
            cin >> num1;
            f = (num1 - 32) * 5 / 9;
            cout << num1 << " Fahrenheit is " << f << " Celsius." << endl;
            break;

        default:
            cout << "Invalid option selected." << endl;
    }
    
    return 0;
}
