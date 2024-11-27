#include <iostream>
#include <cmath>

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    Complex add(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex subtract(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex multiply(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                       real * other.imag + imag * other.real);
    }

    Complex divide(const Complex& other) const {
        double denom = other.real * other.real + other.imag * other.imag;
        return Complex((real * other.real + imag * other.imag) / denom,
                       (imag * other.real - real * other.imag) / denom);
    }

    double modulus() const {
        return std::sqrt(real * real + imag * imag);
    }

    double argument() const {
        return std::atan2(imag, real);
    }

    void print() const {
        std::cout << real;
        if (imag >= 0) {
            std::cout << " + " << imag << "i";
        } else {
            std::cout << " - " << -imag << "i";
        }
        std::cout << std::endl;
    }
};

int main() {
    Complex complex1(4.0, 2.0);
    Complex complex2(2.0, 6.0);

    std::cout << "complex1: ";
    complex1.print();

    std::cout << "complex2: ";
    complex2.print();

    Complex sum = complex1.add(complex2);
    std::cout << "Сумма complex1 и complex2: ";
    sum.print();

    Complex diff = complex1.subtract(complex2);
    std::cout << "Разность complex1 и complex2: ";
    diff.print();

    Complex prod = complex1.multiply(complex2);
    std::cout << "Произведение complex1 и complex2: ";
    prod.print();

    Complex quot = complex1.divide(complex2);
    std::cout << "Частное complex1 и complex2: ";
    quot.print();

    std::cout << "Модуль complex1: " << complex1.modulus() << std::endl;
    std::cout << "Аргумент complex1: " << complex1.argument() << std::endl;

    return 0;
}