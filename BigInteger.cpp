//
// Created by Заурбек Тедеев on 02.08.2021.
//

#include "BigInteger.h"

BigInteger::BigInteger() {
    number = std::vector<unsigned int>();
    is_negative = false;
}

BigInteger::BigInteger(std::string long_number) {

    std::string data(std::move(long_number));
    is_negative = false;
    if(data[0] == '-') {
        is_negative = true;
        data.erase(data.begin());
    }
    for(int i = data.length(); i > 0; i -= 9){
        if(i < 9){
            number.push_back(atoi(data.substr(0, i).c_str()));
        }
        else{
            number.push_back(atoi(data.substr(i - 9, 9).c_str()));
        }
    }

    remove_zeros();
}

unsigned int BigInteger::back() const {
    return number.back();
}

size_t BigInteger::size() const {
    return number.size();
}

void BigInteger::remove_zeros() {
    while (size() > 1 && back() == 0)
        number.pop_back();
}

void BigInteger::add(unsigned int a) {
    number.push_back(a);
}

unsigned int BigInteger::operator[](size_t index) const {
    return number[index];
}

unsigned int & BigInteger::operator[](size_t index) {
    return number[index];
}

BigInteger BigInteger::operator-() const {
    BigInteger result(*this);
    result.is_negative = !result.is_negative;
    return result;
}

BigInteger BigInteger::plus(const BigInteger &a, const BigInteger &b) {
    BigInteger result(a);

    int carry = 0;
    for(int i = 0; i < std::max(result.size(), b.size()) || carry != 0; i++){
        if(i == result.size()) result.add(0);

        result[i] += carry + (i < b.size() ? b[i]: 0);
        carry = result[i] >= BigInteger::base;
        if(carry) result[i] -= BigInteger::base;
    }

    return result;
}

BigInteger BigInteger::minus(const BigInteger &a, const BigInteger &b) {
    BigInteger result;

    int carry = 0;
    for(int i = 0; i < b.size() || carry != 0; i++){
        int current = (int)a[i];
        current -= carry + (i < b.size() ? (int)b[i] : 0);
        carry = current < 0;
        if(carry) current += BigInteger::base;

        result.add(current);
    }

    result.remove_zeros();

    return result;
}

std::ostream& operator<< (std::ostream& out, const BigInteger& integer){
    if(integer.size() != 0) {
        out << (integer.is_negative && integer.back() != 0 ? "-": "");
        out <<  integer.back();
    }
    for(int i = (int)integer.size() - 2; i >= 0; i--){
        out << std::setfill('0') << std::setw(9) << integer[i];
    }

    return out;
}

std::istream& operator>> (std::istream& in, BigInteger& integer){
    std::string data; in >> data;
    if(data[0] == '-') {
        integer.is_negative = true;
        data.erase(data.begin());
    }
    for(int i = data.length(); i > 0; i -= 9){
        if(i < 9){
            integer.number.push_back(atoi(data.substr(0, i).c_str()));
        }
        else{
            integer.number.push_back(atoi(data.substr(i - 9, 9).c_str()));
        }
    }
    integer.remove_zeros();
    return in;
}

bool operator== (const BigInteger &a, const BigInteger &b){
    if(a.is_negative != b.is_negative) return false;
    if(a.size() != b.size()) return false;

    for(size_t i = 0; i < a.size(); i++){
        if(a[i] != b[i]) {
            return false;
        }
    }

    return true;
}

bool operator!= (const BigInteger &a, const BigInteger &b){
    return !(a == b);
}

bool operator< (const BigInteger &a, const BigInteger &b) {
    if(a == b) return false;

    if(a.is_negative && !b.is_negative) return true;
    else if(!a.is_negative && b.is_negative) return false;

    //-20 -2
    if(a.is_negative && b.is_negative){
        if(a.size() > b.size()) return true;
        else if(a.size() < b.size()) return false;
    }
    else {
        if(a.size() < b.size()) return true;
        else if(a.size() > b.size()) return false;
    }

    for(int i = (int)a.size() - 1; i >= 0; i--){
        if(a[i] != b[i]){
            if(a.is_negative && b.is_negative){
                return a[i] > b[i];
            }
            else return a[i] < b[i];
        }
    }

    return false;
}

bool operator<= (const BigInteger &a, const BigInteger &b){
    return a == b || a < b;
}

bool operator> (const BigInteger &a, const BigInteger &b){
    return !(a <= b);
}

bool operator>= (const BigInteger &a, const BigInteger &b){
    return a == b || a > b;
}

/*
 * a > 0, a > 0:
 *      a + b
 * a < 0, b > 0:
 *      -a + b = b - a -> -(a - b)
 *
 *      -5 + 10 = 10 - 5
 * a > 0, b < 0:
 *      a + (-b) = a - b
 * a < 0, b < 0:
 *      -a + (-b) = -a - b = -(a + b)
 *
 */
BigInteger operator+ (const BigInteger& a, const BigInteger &b){
    if(!a.is_negative && !b.is_negative){
        return BigInteger::plus(a, b);
    }
    else if(a.is_negative && !b.is_negative){
        BigInteger a_positive = -a;
        return -(a_positive - b);
    }
    else if(!a.is_negative && b.is_negative){
        BigInteger b_positive = -b;
        return a - b_positive;
    }
    else{
        BigInteger a_positive = -a;
        BigInteger b_positive = -b;
        return -BigInteger::plus(a_positive, b_positive);
    }

}

/*
 * a > 0, b > 0:
 *      a > b:
 *          a - b
 *      a <= b:
 *          a - b = -(b - a)
 * a < 0, b > 0:
 *      -a - b = -(a + b)
 *
 * a > 0, b < 0:
 *      a - (-b) = a + b;
 *
 * a < 0, b < 0:
 *
 *      -a - (-b) = -a + b = -(a - b)
 *      a <= b:
 *          -(a - b) -> -(-(b - a)) = b - a
 *
 */
BigInteger operator- (const BigInteger& a, const BigInteger&b){

    if(!a.is_negative && !b.is_negative){
        if(a > b){
            return BigInteger::minus(a, b);
        }
        else{
            return -(BigInteger::minus(b, a));
        }
    }
    else if(a.is_negative && !b.is_negative){
        BigInteger a_positive = -a;
        return -(a_positive + b);
    }
    else if(!a.is_negative && b.is_negative){
        BigInteger b_positive = -b;
        return a + b_positive;
    }
    else{
        BigInteger a_positive = -a;
        BigInteger b_positive = -b;
        if(a_positive > b_positive){
            return -BigInteger::minus(a_positive, b_positive);
        }
        else{
            return BigInteger::minus(b_positive, a_positive);
        }
    }

}
