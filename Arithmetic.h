//
// Created by Заурбек Тедеев on 30.07.2021.
//

#ifndef ARBITRARY_PRECISION_ARITHMETIC_ARITHMETIC_H
#define ARBITRARY_PRECISION_ARITHMETIC_ARITHMETIC_H

#include <istream>
#include <vector>

class Arithmetic{
private:
    bool sign;
    unsigned int* number;
    unsigned int length;

    const unsigned long base = 1000*1000*1000;

    void AddBack(unsigned int num);
    void DeleteBack();

    void RemoveZeros();
public:

    Arithmetic();
    Arithmetic(Arithmetic& a);
    Arithmetic(Arithmetic&& a) noexcept;

    Arithmetic& operator= (Arithmetic const& a);

    friend std::istream& operator>> (std::istream& in, Arithmetic& a);
    friend std::ostream& operator<< (std::ostream& out, Arithmetic& a);

    friend Arithmetic operator+ (Arithmetic& left, Arithmetic& right);
    friend Arithmetic operator- (Arithmetic& left, Arithmetic& right);

    friend bool operator> (Arithmetic left, Arithmetic right);
    friend bool operator< (Arithmetic left, Arithmetic right);
    friend bool operator>= (Arithmetic left, Arithmetic right);
    friend bool operator<= (Arithmetic left, Arithmetic right);
    friend bool operator== (Arithmetic left, Arithmetic right);
    friend bool operator!= (Arithmetic left, Arithmetic right);




};

#endif //ARBITRARY_PRECISION_ARITHMETIC_ARITHMETIC_H
