//
// Created by Заурбек Тедеев on 02.08.2021.
//

#ifndef ARBITRARY_PRECISION_ARITHMETIC_BIGINTEGER_H
#define ARBITRARY_PRECISION_ARITHMETIC_BIGINTEGER_H

#include <iostream>
#include <iomanip>
#include <vector>

class BigInteger{
private:
    std::vector<unsigned int> number;
    static const unsigned int base = 1000*1000*1000;
    bool is_negative;

    void remove_zeros();
    unsigned int back() const;
    size_t size() const;
    void add(unsigned int);

    static BigInteger plus (const BigInteger&, const BigInteger&);
    static BigInteger minus(const BigInteger&, const BigInteger&);

public:
    BigInteger();
    explicit BigInteger(std::string);

    friend std::ostream& operator<< (std::ostream&, const BigInteger&);
    friend std::istream& operator>> (std::istream&, BigInteger&);

    friend bool operator< (const BigInteger&, const BigInteger&);
    friend bool operator<= (const BigInteger&, const BigInteger&);
    friend bool operator> (const BigInteger&, const BigInteger&);
    friend bool operator>= (const BigInteger&, const BigInteger&);
    friend bool operator== (const BigInteger&, const BigInteger&);
    friend bool operator!= (const BigInteger&, const BigInteger&);

    friend BigInteger operator+ (const BigInteger&, const BigInteger&);
    friend BigInteger operator- (const BigInteger&, const BigInteger&);

    unsigned int operator[] (size_t) const;
    unsigned int& operator[] (size_t);

    BigInteger operator- () const;


};

#endif //ARBITRARY_PRECISION_ARITHMETIC_BIGINTEGER_H
