#include <iostream>
#include "Arithmetic.h"
#include "BigInteger.h"
using namespace std;



int First() {

    Arithmetic n("1190");
    while(true) {
        Arithmetic a;
        Arithmetic b;

        std::cout.setf(std::ios_base::boolalpha);

        cin >> a >> b;

        cout << "a == b = " << (a == b) << endl;
        cout << "a != b = " << (a != b) << endl;
        cout << "a > b = " << (a > b) << endl;
        cout << "a < b = " << (a < b) << endl;
        cout << "a >= b = " << (a >= b) << endl;
        cout << "a <= b = " << (a <= b) << endl;

        cout << endl;
        Arithmetic result = a + b;
        cout << a <<  " + " << b  << " = " << result << endl;

        result = a - b;
        cout << a <<  " - " << b  << " = " << result << endl;

        result = a * b;
        cout << a <<  " * " << b  << " = " << result << endl;

        result = -a;
        cout << "-a = " << result << endl;

        cout << endl;

    }
    return 0;
}


int main(){
    std::cout.setf(std::ios_base::boolalpha);
    while(true){
        BigInteger a, b;
        cin >> a >> b;

        cout << a << " == " << b << " -> " << (a == b) << endl;
        cout << a << " != " << b << " -> " << (a != b) << endl;
        cout << a << " < " << b << " -> " << (a < b) << endl;
        cout << a << " <= " << b << " -> " << (a <= b) << endl;
        cout << a << " > " << b << " -> " << (a > b) << endl << endl;

        cout << a << " + " << b << " = " << a + b << endl;
        cout << a << " - " << b << " = " << a - b << endl;

        cout << endl << endl;
        string command;
        cout << "Continue?(y/n): "; cin >> command;
        if(command == "n") break;
    }
}

