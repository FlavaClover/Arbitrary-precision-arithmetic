#include <iostream>
#include "Arithmetic.h"
using namespace std;



int main() {

    while(true) {
        Arithmetic a = Arithmetic();
        Arithmetic b = Arithmetic();

        cin >> a >> b;
        cout << a << " " << b << endl;

        Arithmetic result = a + b;
        cout << result << endl << endl;

    }
    return 0;
}
