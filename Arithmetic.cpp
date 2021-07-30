//
// Created by Заурбек Тедеев on 30.07.2021.
//
#include "Arithmetic.h"

Arithmetic::Arithmetic() {
    length = 0;
    number = new unsigned int[length];
    sign = true;

    count = 0;
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

    out << (a.length == 0 ? 0 : a.number[a.length - 1]);
    for(int i = (int)a.length - 2; i >= 0; i--){
        printf("%09d", a.number[i]);
    }

    return out;
}

Arithmetic operator+ (Arithmetic& left, Arithmetic& right){
    int carry = 0;
    Arithmetic result = Arithmetic();
    for(int i = 0; i < std::max(left.length, right.length) || carry; i++)
    {
        if(i == result.length) result.AddBack(0);

        result.number[i] += carry + (i < left.length ? left.number[i] : 0);
        result.number[i] += (i < right.length ? right.number[i] : 0);

        carry = result.number[i] >= result.base;
        if(carry) result.number[i] -= result.base;
    }

    return result;

}


