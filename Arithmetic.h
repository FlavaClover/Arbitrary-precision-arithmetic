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
    int* number;
    int length;

    const unsigned long base = 1000*1000*1000;

    void AddBack(int num);
    void DeleteBack();

    void RemoveZeros();

    Arithmetic plus(Arithmetic a);
    Arithmetic minus(Arithmetic a); // this >= a
public:

    Arithmetic();
    Arithmetic(std::string long_number);
    Arithmetic(Arithmetic const &a);
    Arithmetic(Arithmetic&& a) noexcept;


    Arithmetic& operator= (Arithmetic const &a);
    Arithmetic& operator= (Arithmetic &&a);
    friend Arithmetic operator- (Arithmetic& a);
    friend Arithmetic operator- (Arithmetic&& a);

    friend std::istream& operator>> (std::istream& in, Arithmetic& a);
    friend std::ostream& operator<< (std::ostream& out, Arithmetic& a);

    friend Arithmetic operator+ (Arithmetic& left, Arithmetic& right);
    friend Arithmetic operator- (Arithmetic& left, Arithmetic& right);
    friend Arithmetic operator* (Arithmetic& left, Arithmetic& right);

    friend bool operator> (Arithmetic left, Arithmetic right);
    friend bool operator< (Arithmetic left, Arithmetic right);
    friend bool operator>= (Arithmetic left, Arithmetic right);
    friend bool operator<= (Arithmetic left, Arithmetic right);
    friend bool operator== (Arithmetic left, Arithmetic right);
    friend bool operator!= (Arithmetic left, Arithmetic right);




};

#endif //ARBITRARY_PRECISION_ARITHMETIC_ARITHMETIC_H
