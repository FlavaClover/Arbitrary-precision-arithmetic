#include <iostream>
#include "Arithmetic.h"
using namespace std;



int main() {

    while(true) {
        Arithmetic a;
        Arithmetic b;

        std::cout.setf(std::ios_base::boolalpha);

        cin >> a >> b;
        cout << a << " " << b << endl;

        cout << "a == b = " << (a == b) << endl;
        cout << "a != b = " << (a != b) << endl;
        cout << "a > b = " << (a > b) << endl;
        cout << "a < b = " << (a < b) << endl;
        cout << "a >= b = " << (a >= b) << endl;
        cout << "a <= b = " << (a <= b) << endl;

        cout << endl;
        Arithmetic result = a + b;
        cout << "a + b = " << result << endl;

        result = a - b;
        cout << "a - b = " << result << endl;

        cout << endl;

    }
    return 0;
}
