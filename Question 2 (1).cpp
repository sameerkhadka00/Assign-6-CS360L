// Hugeint.h
// HugeInt class definition.
#ifndef HUGEINT_H
#define HUGEINT_H

#include <array>
#include <iostream>
#include <string>
#include <cmath>

class HugeInt {
    friend std::ostream& operator<<(std::ostream&, const HugeInt&);

public:
    static const int digits = 30; // maximum digits in a HugeInt
    HugeInt(long = 0); // conversion/default constructor
    HugeInt(const std::string&); // conversion constructor

    // arithmetic operators
    HugeInt operator+(const HugeInt&) const;
    HugeInt operator-(const HugeInt&) const;
    HugeInt operator*(const HugeInt&) const;
    HugeInt operator/(const HugeInt&) const;

    // relational and equality operators
    bool operator<(const HugeInt&) const;
    bool operator>(const HugeInt&) const;
    bool operator<=(const HugeInt&) const;
    bool operator>=(const HugeInt&) const;
    bool operator==(const HugeInt&) const;
    bool operator!=(const HugeInt&) const;

private:
    std::array<short, digits> integer;
};

// constructor; conversion/default constructor
HugeInt::HugeInt(long value) {
    // initialize array to zero
    for (short& element : integer)
        element = 0;
    // place digits of argument into array
    for (size_t j = digits - 1; value != 0 && j >= 0; j--) {
        integer[j] = value % 10;
        value /= 10;
    }
}

// conversion constructor; converts a character string representing a large integer into a HugeInt object
HugeInt::HugeInt(const std::string& number) {
    // initialize array to zero
    for (short& element : integer)
        element = 0;
    // place digits of argument into array
    size_t length = number.size();
    for (size_t j = digits - length, k = 0; j < digits; ++j, ++k)
        if (isdigit(number[k])) // ensure that character is a digit
            integer[j] = number[k] - '0';
}

// addition operator; HugeInt + HugeInt
HugeInt HugeInt::operator+(const HugeInt& op2) const {
    HugeInt temp; // temporary result
    int carry = 0;
    for (int i = digits - 1; i >= 0; i--) {
        temp.integer[i] = integer[i] + op2.integer[i] + carry;
        // determine whether to carry a 1
        if (temp.integer[i] > 9) {
            temp.integer[i] %= 10; // reduce to 0-9
            carry = 1;
        } else // no carry
            carry = 0;
    }
    return temp; // return copy of temporary object
}

// subtraction operator; HugeInt - HugeInt
HugeInt HugeInt::operator-(const HugeInt& op2) const {
    HugeInt result;
    int borrow = 0;
    for (int i = digits - 1; i >= 0; i--) {
        int diff = integer[i] - op2.integer[i] - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.integer[i] = diff;
    }
    return result;
}

// multiplication operator; HugeInt * HugeInt
HugeInt HugeInt::operator*(const HugeInt& op2) const {
    HugeInt result; // Initialize result
    HugeInt temp;
    int carry = 0;

    for (int i = digits - 1; i >= 0; i--) {
        for (int j = digits - 1; j >= 0; j--) {
            int product = (integer[i] * op2.integer[j]) + carry;
            temp.integer[j] = product % 10; // Store the result
            carry = product / 10; // Carry
        }
        result = result + temp; // Add temp to result
    }
    return result;
}

// division operator; HugeInt / HugeInt
HugeInt HugeInt::operator/(const HugeInt& op2) const {
    HugeInt quotient;
    HugeInt temp(*this);
    HugeInt remainder("0");
    HugeInt one("1");
    while (temp >= op2) {
        temp = temp - op2;
        quotient = quotient + one;
    }
    return quotient;
}

// less than operator
bool HugeInt::operator<(const HugeInt& op2) const {
    for (int i = 0; i < digits; ++i) {
        if (integer[i] < op2.integer[i])
            return true;
        else if (integer[i] > op2.integer[i])
            return false;
    }
    return false;
}

// greater than operator
bool HugeInt::operator>(const HugeInt& op2) const {
    return op2 < *this;
}

// less than or equal to operator
bool HugeInt::operator<=(const HugeInt& op2) const {
    return !(op2 < *this);
}

// greater than or equal to operator
bool HugeInt::operator>=(const HugeInt& op2) const {
    return !(*this < op2);
}

// equality operator
bool HugeInt::operator==(const HugeInt& op2) const {
    for (int i = 0; i < digits; ++i) {
        if (integer[i] != op2.integer[i])
            return false;
    }
    return true;
}

// inequality operator
bool HugeInt::operator!=(const HugeInt& op2) const {
    return !(*this == op2);
}

// overloaded output operator
std::ostream& operator<<(std::ostream& output, const HugeInt& num) {
    int i;
    for (i = 0; (i < HugeInt::digits) && (0 == num.integer[i]); ++i)
        ; // skip leading zeros
    if (i == HugeInt::digits)
        output << 0;
    else
        for (; i < HugeInt::digits; ++i)
            output << num.integer[i];
    return output;
}

#endif

// main.cpp
// HugeInt test program.
#include <iostream>
#include "Hugeint.h"
using namespace std;

int main() {
    HugeInt n1(7654321);
    HugeInt n2(7891234);
    HugeInt n3("99999999999999999999999999999");
    HugeInt n4("1");
    HugeInt n5;

    cout << "n1 is " << n1 << "\nn2 is " << n2
         << "\nn3 is " << n3 << "\nn4 is " << n4
         << "\nn5 is " << n5 << "\n\n";

    n5 = n1 + n2;
    cout << n1 << " + " << n2 << " = " << n5 << "\n\n";

    cout << n3<< " + " << n4 << "\n= " << (n3 + n4) << "\n\n";
    n5 = n1 + 9;cout << n1 << " + " << 9 << " = " << n5 << "\n\n";

n5 = n2 + HugeInt("10000");
cout << n2 << " + " << "10000" << " = " << n5 << endl;

// Testing multiplication and division
HugeInt n6("123456789012345678901234567890");
HugeInt n7("987654321098765432109876543210");
HugeInt n8;

cout << "\nMultiplication:\n";
n8 = n6 * n7;
cout << n6 << " * " << n7 << " = " << n8 << endl;

cout << "\nDivision:\n";
n8 = n7 / n6;
cout << n7 << " / " << n6 << " = " << n8 << endl;

return 0;


}