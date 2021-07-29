//
// Created by Заурбек Тедеев on 30.07.2021.
//

#ifndef ARBITRARY_PRECISION_ARITHMETIC_ARITHMETIC_H
#define ARBITRARY_PRECISION_ARITHMETIC_ARITHMETIC_H

#include <istream>

class Arithmetic{
private:
    bool sign;
    unsigned int* number;
    unsigned int length;
    unsigned int count;

    const unsigned long base = 4294967296;

    void AddBack(unsigned int num);
    void DeleteBack();

    void RemoveZeros();
public:

    Arithmetic();

    friend std::istream& operator>> (std::istream& in, Arithmetic& a);
    friend std::ostream& operator<< (std::ostream& out, Arithmetic& a);


};

#endif //ARBITRARY_PRECISION_ARITHMETIC_ARITHMETIC_H
