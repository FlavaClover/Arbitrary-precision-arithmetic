//
// Created by Заурбек Тедеев on 30.07.2021.
//
#include "Arithmetic.h"

Arithmetic::Arithmetic() {
    length = 0;
    number = new int[length];
    sign = true;
}

Arithmetic::Arithmetic(std::string long_number) {
    if(long_number[0] == '-')
    {
        long_number.erase(long_number.begin());
        this->sign = false;
    }
    for(int i = (int)long_number.length(); i > 0; i -= 9){
        if(i < 9){
            this->AddBack(atoi(long_number.substr(0, i).c_str()));
        }
        else{
            this->AddBack(atoi(long_number.substr(i - 9, 9).c_str()));
        }
    }

    this->RemoveZeros();
}

Arithmetic::Arithmetic(Arithmetic const &a) {
    length = a.length;
    number = new int[length];
    for(int i = 0; i < length; i++){
         number[i] = a.number[i];
    }

    sign = a.sign;
}

Arithmetic::Arithmetic(Arithmetic &&a) noexcept {
    length = a.length;
    sign = a.sign;
    number = a.number;

    a.number = nullptr;

}

Arithmetic& Arithmetic::operator= (Arithmetic const &a) {

    Arithmetic temp(a);
    std::swap(number, temp.number);
    std::swap(length, temp.length);
    std::swap(sign, temp.sign);

    return *this;
}

Arithmetic& Arithmetic::operator= (Arithmetic &&a) {
    length = a.length;
    number = a.number;
    a.number = nullptr;
    sign = a.sign;

    return *this;
}


Arithmetic operator-(Arithmetic& a) {
    Arithmetic r(a);
    r.sign = !r.sign;
    return r;
}
Arithmetic operator-(Arithmetic&& a) {
    Arithmetic r(a);
    r.sign = !r.sign;
    return r;
}

Arithmetic Arithmetic::plus(Arithmetic a) {
    int carry = 0;
    Arithmetic result(*this);
    for(int i = 0; i < std::max(this->length, a.length) || carry; i++)
    {
        if(i == result.length) result.AddBack(0);

        result.number[i] += carry + (i < a.length ? a.number[i] : 0);

        carry = result.number[i] >= result.base;
        if(carry) result.number[i] -= result.base;
    }

    return result;
}

Arithmetic Arithmetic::minus(Arithmetic a) {
    int carry = 0;
    Arithmetic result(*this);
    for(int i = 0; i < a.length || carry; i++)
    {
        result.number[i] -= carry  + (i < a.length ? a.number[i] : 0);
        carry = result.number[i] < 0;
        if(carry) result.number[i] += result.base;
    }

    result.RemoveZeros();

    return result;
}

void Arithmetic::AddBack(int num) {
    int* new_array = new int[length + 1];
    for(int i = 0; i < length; i++) new_array[i] = number[i];

    new_array[length] = num;

    delete[] number;
    number = new_array;
    length++;
}

void Arithmetic::DeleteBack() {
    int* new_array = new int[length - 1];
    for(int i = 0; i < length - 1; i++) new_array[i] = number[i];

    delete[] number;
    number = new_array;
    length--;
}

void Arithmetic::RemoveZeros() {
    while (length > 1 && number[length - 1] == 0) DeleteBack();
}

std::istream& operator>> (std::istream& in, Arithmetic& a)
{
    std::string input_str; in >> input_str;
    if(input_str[0] == '-')
    {
        input_str.erase(input_str.begin());
        a.sign = false;
    }
    for(int i = (int)input_str.length(); i > 0; i -= 9){
        if(i < 9){
            a.AddBack(atoi(input_str.substr(0, i).c_str()));
        }
        else{
            a.AddBack(atoi(input_str.substr(i - 9, 9).c_str()));
        }
    }

    a.RemoveZeros();

    return in;
}

std::ostream& operator<< (std::ostream& out, Arithmetic& a){

    if(a.length != 0 && !a.sign && a.number[a.length - 1] != 0) out << "-";
    out << (a.length == 0 ? 0 : a.number[a.length - 1]);
    for(int i = (int)a.length - 2; i >= 0; i--){
        printf("%09d", a.number[i]);
    }

    return out;
}

bool operator== (Arithmetic left, Arithmetic right){
    if(left.length != right.length || left.sign != right.sign) return false;
    for(int i = 0; i < left.length; i++) if(left.number[i] != right.number[i]) return false;

    return true;
}

bool operator!= (Arithmetic left, Arithmetic right){
    if(left.length != right.length || left.sign != right.sign) return true;
    for(int i = 0; i < left.length; i++) if(left.number[i] != right.number[i]) return true;

    return false;
}

bool operator> (Arithmetic left, Arithmetic right){
    if(left.sign && !right.sign) return true;
    else if(!left.sign && right.sign) return false;

    if(left.length > right.length) return true;
    else if(left.length < right.length) return false;

    for(int i = left.length - 1; i >= 0; i--){
        if(left.sign && right.sign) if(!(left.number[i] > right.number[i])) return false;
        if(!left.sign && !right.sign) if(!(left.number[i] < right.number[i])) return false;
    }

    return true;
}

bool operator< (Arithmetic left, Arithmetic right){
    if(left.sign && !right.sign) return false;
    else if(!left.sign && right.sign) return true;

    if(left.length < right.length) return true;
    else if(left.length > right.length) return false;

    for(int i = left.length - 1; i >= 0; i--){
        if(left.sign && right.sign) if(left.number[i] >= right.number[i]) return false;
        if(!left.sign && !right.sign) if(left.number[i] <= right.number[i]) return false;
    }

    return true;
}

bool operator>= (Arithmetic left, Arithmetic right){
    return left == right || left > right;
}

bool operator<= (Arithmetic left, Arithmetic right){
    return left == right || left < right;
}

Arithmetic operator+ (Arithmetic& left, Arithmetic& right){
    Arithmetic result;
    if(left.sign && right.sign) {
        result = left.plus(right);
    }
    if(!left.sign && right.sign){
        Arithmetic a(left);
        a = -a;
        result = a - right;
        result = -result;
    }
    if(left.sign && !right.sign){
        Arithmetic b(right);
        b = -b;
        result = left - b;
    }
    if(!left.sign && !right.sign){

        Arithmetic a(left);
        a = -a;

        Arithmetic b(right);
        b = -b;

        result = a + b;
        result = -result;
    }

    return result;
}

/*
 * +:
 * a >= 0, b >= 0
 *      a > b, a < b:
 *          a + b
 * a < 0, b > 0:
 *      -2 + 3 = -(2 - 3)
 *      -a + b = -(a - b)
 * a >= 0, b < 0:
 *      5 + (-6) = 5 - 6
 *
 *      a + (-b) = a - b
 * a < 0, b < 0:
 *      a > b:
 *          -2 + (-5) = -2 - 5 = -(2 + 5) = -7
 *          -a + (-b) = -(a + b)
 *      a < b:
 *          -5 + (-2) = -(5 + 2)
 */

/*
 * -:
 * a > 0, b > 0:
 *      a > b:
 *          a - b
 *      a <= b:
 *          a - b = -(b - a)
 * a < 0, b > 0:
 *      -5 - 7 = -(5 + 7) = -13
 *      -a - b = -(a + b)
 * a > 0, b < 0:
 *      5 - (-7) = 5 + 7
 *      a - (-b) = a + b
 * a < 0, b < 0
 *      a > b:
 *          -7 - (-5) = -7 + 5 = -(7 - 5) = -2
 *          -a - (-b) = -a + b = -(a - b)
 *      a < b:
 *          -5 - (-7) = -5 + 7 = -(5 - 7) = -(-(7 - 5)) = 7 - 5
 *          -a - (-b) = -a + b = b - a
 */


Arithmetic operator- (Arithmetic& left, Arithmetic& right){
    Arithmetic result;
    if(left.sign && right.sign){
        if(left > right){
            result = left.minus(right);
        }
        else{
            result = right.minus(left);
            result = -result;
        }
    }
    if(!left.sign && right.sign){
        Arithmetic a(left);
        a = -a;

        result = a + right;
        result = -result;
    }
    if(left.sign && !right.sign){
        Arithmetic b(right);
        b = -b;

        result = left + right;
    }
    if(!left.sign && !right.sign){
        Arithmetic a(left);
        a = -a;

        Arithmetic b(right);
        b = -b;

        if(a > b){
            result = a - b;
            result = -result;
        }
        else{
            result = b - a;
        }
    }
    return result;
}

Arithmetic operator* (Arithmetic& left, Arithmetic& right){
    Arithmetic result;
    while (result.length != left.length + right.length) result.AddBack(0);

    for(int i = 0; i < left.length; i++){
        for(int j = 0, carry = 0; j < right.length || carry; j++){
            long long current = result.number[i + j] + left.number[i] * 1ll * (j < right.length ? right.number[j]: 0) + carry;
            result.number[i + j] = current % result.base;
            carry = (int)(current / result.base);
        }
    }
    /*
     * - - = +
     * + + = +
     * - + = -
     * + - = -
     */

    result.sign = left.sign == right.sign;
    result.RemoveZeros();

    return result;
}





