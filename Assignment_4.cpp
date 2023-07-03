// Assignment 4
// Classes for complex numbers
// Student ID: 10138372
#include<iostream>
#include<string>
#include<math.h>
class complex
{
    friend std::ostream& operator<<(std::ostream& os, const complex& v);
private:
    double re, i;
public:
    const double pi = 3.14159265358979323846;
    complex() : re{}, i{} {}
    complex(double re_in, double i_in) : re{ re_in }, i{ i_in } {}
    ~complex() {}
    // Access functions to set and get complex number components
    void set_re(double re_in) { re = re_in; }
    void set_i(double i_in) { i = i_in; }
    double get_re() const { return re; }
    double get_i() const { return i; }
    // Function that returns real part of complex number
    double real_part() const
    {
        return re;
    }
    // Function that returns imaginary part of complex number
    double imaginary_part() const
    {
        return i;
    }
    // Function to calculate the modulus
    double modulus() const
    {
        return sqrt(pow(re,2) + pow(i,2));
    }
    // Function to calculate the argument of complex number
    double argument() const
    {
        if (re == 0)
            return (i > 0) ? pi / 2 : (i < 0) ? 3 * pi / 2 : 0;
        if (i > 0 && re > 0)
            return atan(i / re);
        if (i < 0 && re > 0)
            return 2 * pi + atan(i / re);
        if (i < 0 || re < 0)
            return pi - atan(i / (-re));
        if (i > 0 || re < 0)
            return (2 * pi) - atan((-i) / (-re));
        return 0;
    }
    // Returns complex conjugate
    complex conjugate() const
    {
        return complex(re, -i);
    }
    // Function to overload + operator (addition of two complex numbers)
    complex operator+(const complex& v) const
    {
        return { re + v.re, i + v.i };
    }
    // Function to overload - operator (subtraction of two complex numbers)
    complex operator-(const complex& v) const
    {
        return { re - v.re,i - v.i };
    }
    // Function to overload * operator (multiplication of two complex numbers)
    complex operator*(const complex& v) const
    {
        return { re * v.re - i * v.i, i * v.re + re * v.i };
    }
    // Function to overload * operator (division of two complex numbers)
    complex operator/(const complex& v) const
    {
        return { (re * v.re + i * v.i) / (pow(v.re,2) + pow(v.i,2)), (i * v.re + re * v.i) / (pow(v.re,2) + pow(v.i,2)) };
    }
};
// Non-member function to overload ostream for complex class
std::ostream& operator<<(std::ostream& os, const complex& v)
{
    if (v.i < 0)
        os << "(" << v.re << "-" << -v.i << "i)";
    else
        os << "(" << v.re << "+" << v.i << "i)";
    return os;
}
// Non-member function to allow extraction of complex objects from an istream
std::istream& operator>>(std::istream& is, complex& v)
{
    double re, im;
    char sign;
    if (!(is >> re)) {
        throw std::invalid_argument("Invalid input: real part.");
    }
    if (is >> sign && sign == '-') {
        if (!(is >> im)) {
            throw std::invalid_argument("Invalid input: imaginary part.");
        }
        if (is >> sign && sign != 'i') {
            throw std::invalid_argument("Invalid input: imaginary part.");
        }
        v.set_re(re);
        v.set_i(-im);
    }
    else if (sign == '+') {
        if (!(is >> im)) {
            throw std::invalid_argument("Invalid input: imaginary part.");
        }
        if (is >> sign && sign != 'i') {
            throw std::invalid_argument("Invalid input: imaginary part.");
        }
        v.set_re(re);
        v.set_i(im);
    }
    else if (sign == 'i') {
        v.set_re(0);
        v.set_i(re);
    }
    else {
        throw std::invalid_argument("Invalid input.");
    }
    return is;
}

int main()
{
    complex a{ 3,4 };
    complex b{ 1,-2 };
    complex c;
    // Print complex numbers 
    std::cout << a << " " << b << std::endl;
    // Return real part using member function of complex
    double real_a = a.real_part();
    std::cout << "Real part of a = " << real_a << std::endl;
    double real_b = b.real_part();
    std::cout << "Real part of b = " << real_b << std::endl;
    // Return imaginary part using member function of complex
    double imaginary_a = a.imaginary_part();
    std::cout << "Imaginary part of a = " << imaginary_a << std::endl;
    double imaginary_b = b.imaginary_part();
    std::cout << "Imaginary part of b = " << imaginary_b << std::endl;
    // Returns modulus of member function of complex
    double modulus_a = a.modulus();
    std::cout << "Modulus of a = " << modulus_a << std::endl;
    double modulus_b = b.modulus();
    std::cout << "Modulus of b = " << modulus_b << std::endl;
    // Returns argument of member function of complex
    double argument_a = a.argument();
    std::cout << "Argument of a = " << argument_a << std::endl;
    double argument_b = b.argument();
    std::cout << "Argument of b = " << argument_b << std::endl;
    // Returns complex conjugate for a and b
    complex conjugate_a = a.conjugate();
    std::cout << "The complex conjugate of a = " << conjugate_a << std::endl;
    complex conjugate_b = b.conjugate();
    std::cout << "The complex conjugate of b = " << conjugate_b << std::endl;
    // Returns division, multiplication addition and subtraction of a and b
    complex add = a + b;
    std::cout << "The addition of a and b = " << add << std::endl;
    complex sub = a - b;
    std::cout << "The subtraction of a by b = " << sub << std::endl;
    complex mult = b * a;
    std::cout << "The multiplication of a and b = " << mult << std::endl;
    complex div = a / b;
    std::cout << "The division of a by b = " << div << std::endl;
    try {
        // Used the overloaded >> operator to input complex objects from cin
        std::cout << "Enter a complex number (in the form a+bi or a-bi): ";
        std::cin >> c;
        std::cout << "You entered " << c << std::endl;
        double real_c = c.real_part();
        std::cout << "Real part of c = " << real_c << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}