// Complex.h
// Complex class definition.
#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex {
public:
    explicit Complex(double = 0.0, double = 0.0); // constructor
    Complex operator+(const Complex&) const; // addition
    Complex operator-(const Complex&) const; // subtraction
    Complex operator*(const Complex&) const; // multiplication
    bool operator==(const Complex&) const; // equality
    bool operator!=(const Complex&) const; // inequality

    friend std::ostream& operator<<(std::ostream&, const Complex&);
    friend std::istream& operator>>(std::istream&, Complex&);

private:
    double real; // real part
    double imaginary; // imaginary part
}; // end class Complex

#endif

// Complex.cpp
// Complex class member-function definitions.
#include "Complex.h" // Complex class definition

// Constructor
Complex::Complex(double realPart, double imaginaryPart)
    : real(realPart), imaginary(imaginaryPart) {
    // empty body
} // end Complex constructor

// addition operator
Complex Complex::operator+(const Complex& operand2) const {
    return Complex(real + operand2.real, imaginary + operand2.imaginary);
} // end function operator+

// subtraction operator
Complex Complex::operator-(const Complex& operand2) const {
    return Complex(real - operand2.real, imaginary - operand2.imaginary);
} // end function operator-

// multiplication operator
Complex Complex::operator*(const Complex& operand2) const {
    return Complex(
        (real * operand2.real) - (imaginary * operand2.imaginary),
        (real * operand2.imaginary) + (imaginary * operand2.real)
    );
} // end function operator*

// equality operator
bool Complex::operator==(const Complex& operand2) const {
    return (real == operand2.real) && (imaginary == operand2.imaginary);
} // end function operator==

// inequality operator
bool Complex::operator!=(const Complex& operand2) const {
    return !(*this == operand2);
} // end function operator!=

// output operator
std::ostream& operator<<(std::ostream& os, const Complex& complex) {
    os << '(' << complex.real << ", " << complex.imaginary << "i)";
    return os;
} // end function operator<<

// input operator
std::istream& operator>>(std::istream& is, Complex& complex) {
    char dummy;
    is >> complex.real >> dummy >> complex.imaginary >> dummy;
    return is;
} // end function operator>>

// main.cpp
// Complex class test program.
#include <iostream>
#include "Complex.h"
using namespace std;

int main() {
    Complex x;
    Complex y(4.3, 8.2);
    Complex z(3.3, 1.1);

    cout << "Enter complex number x in the form (a, b): ";
    cin >> x;

    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    cout << "z: " << z << endl;

    Complex sum = y + z;
    cout << "x = y + z: " << sum << endl;

    Complex difference = y - z;
    cout << "x = y - z: " << difference << endl;

    Complex product = y * z;
    cout << "x = y * z: " << product << endl;

    cout << "Comparison: ";
    if (x == y)
        cout << "x is equal to y";
    else
        cout << "x is not equal to y";
    cout << endl;

    return 0;
}

