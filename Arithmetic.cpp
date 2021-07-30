//
// Created by Заурбек Тедеев on 30.07.2021.
//
#include "Arithmetic.h"

Arithmetic::Arithmetic() {
    length = 0;
    number = new unsigned int[length];
    sign = true;
}

Arithmetic::Arithmetic(Arithmetic &a) {
    length = a.length;
    number = new unsigned int[length];
    for(int i = 0; i < length; i++){
        number[i] = a.number[i];
    }

    sign = a.sign;
}

Arithmetic::Arithmetic(Arithmetic &&a) noexcept {
    length = a.length;
    sign = a.length;
    number = a.number;

    a.number = nullptr;

}

Arithmetic& Arithmetic::operator= (Arithmetic const &a) {
    length = a.length;
    number = new unsigned int[length];
    for(int i = 0; i < length; i++){
        number[i] = a.number[i];
    }

    sign = a.sign;

    return *this;
}


void Arithmetic::AddBack(unsigned int num) {
    unsigned int* new_array = new unsigned int[length + 1];
    for(int i = 0; i < length; i++) new_array[i] = number[i];

    new_array[length] = num;

    delete[] number;
    number = new_array;
    length++;
}

void Arithmetic::DeleteBack() {
    unsigned int* new_array = new unsigned int[length - 1];
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

    if(a.length != 0 && !a.sign) out << "-";
    out << (a.length == 0 ? 0 : a.number[a.length - 1]);
    for(int i = (int)a.length - 2; i >= 0; i--){
        printf("%09d", a.number[i]);
    }

    return out;
}

bool operator== (Arithmetic left, Arithmetic right){
    if(left.length != right.length) return false;
    for(int i = 0; i < left.length; i++) if(left.number[i] != right.number[i]) return false;

    return true;
}

bool operator!= (Arithmetic left, Arithmetic right){
    if(left.length != right.length) return true;
    for(int i = 0; i < left.length; i++) if(left.number[i] != right.number[i]) return true;

    return false;
}

bool operator> (Arithmetic left, Arithmetic right){
    if(left.length > right.length) return true;
    else if(left.length < right.length) return false;

    for(int i = left.length - 1; i >= 0; i--){
        if(left.number[i] > right.number[i]) return true;
    }

    return false;
}

bool operator< (Arithmetic left, Arithmetic right){
    if(left.length < right.length) return true;
    else if(left.length > right.length) return false;

    for(int i = left.length - 1; i >= 0; i--){
        if(left.number[i] < right.number[i]) return true;
    }

    return false;
}

bool operator>= (Arithmetic left, Arithmetic right){
    return left == right || left > right;
}

bool operator<= (Arithmetic left, Arithmetic right){
    return left == right || left < right;
}

Arithmetic operator+ (Arithmetic& left, Arithmetic& right){
    int carry = 0;
    Arithmetic result(left);
    for(int i = 0; i < std::max(left.length, right.length) || carry; i++)
    {
        if(i == result.length) result.AddBack(0);

        result.number[i] += carry + (i < right.length ? right.number[i] : 0);

        carry = result.number[i] >= result.base;
        if(carry) result.number[i] -= result.base;
    }

    return result;

}

// a - b = c | a >= b
// a - b = -(b - a) = -c  | a < b
Arithmetic operator- (Arithmetic& left, Arithmetic& right){

    Arithmetic a = left;
    Arithmetic b = right;

    bool sign = true;
    if(left < right)
    {
        sign = false;
        a = right;
        b = left;
    }

    int carry = 0;
    Arithmetic result = a;
    for(int i = 0; i < b.length || carry; i++)
    {
        result.number[i] -= carry  + (i < b.length ? b.number[i] : 0);
        carry = result.number[i] < 0;
        if(carry) result.number[i] += result.base;
    }

    result.RemoveZeros();
    result.sign = sign;
    return result;

}




