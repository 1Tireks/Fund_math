#include <iostream>

class binary_int {

    private:
        int value;
        int binary_add(int a, int b) const;
        int binary_multiply(int a, int b) const;
        int decrement(int a) const;
    public:
        binary_int();
        binary_int(int);
        binary_int operator-() const;
        binary_int& operator++();
        binary_int operator++(int);
        binary_int& operator--();
        binary_int operator--(int);
        binary_int& operator+=(const binary_int);
        binary_int operator+(const binary_int) const;
        binary_int& operator-=(const binary_int);
        binary_int operator-(const binary_int) const;
        binary_int& operator*=(const binary_int);
        binary_int operator*(const binary_int) const ;
        binary_int& operator<<=(int);
        binary_int operator<<(int) const;
        binary_int& operator>>=(int);
        binary_int operator>>(int) const;
        std::pair<binary_int, binary_int> split() const;
        friend std::ostream& operator<<(std::ostream&, const binary_int&);       
        void printBinInt();
};

// конструктор без параметра
binary_int::binary_int() {

    value = 0;

}

// конструктор с параметром
binary_int::binary_int(int n) {

    value = n;

}

int binary_int::binary_add(int a, int b) const {

    while (b != 0) {
        int carry = a & b;
        a = a ^ b;
        b = carry << 1;
    }

    return a;
}

int binary_int::decrement(int a) const {

    int carry = 1;

    while(carry) {

        int result = a ^ carry;

        carry = (~(a) & carry) << 1;

        a = result;

    }

    return a;
}

int decrement(int a) {

    int carry = 1;

    while(carry) {

        int result = a ^ carry;

        carry = (~(a) & carry) << 1;

        a = result;

    }

    return a;
}

int binary_int::binary_multiply(int a, int b) const {

    int res = 0;

    while (b != 0) {
        if (b & 1)
            res = binary_add(res, a);
        a <<= 1;
        b >>= 1;
    }

    return res;
}

// унарный минус
binary_int binary_int::operator-() const {
    return binary_int(binary_add(~value, 1));
}

// Префиксный инкремент
binary_int& binary_int::operator++() {
    value = binary_add(value, 1);
    return *this;
}

// Постфиксный инкремент
binary_int binary_int::operator++(int) {
    binary_int temp = *this;
    value = binary_add(value, 1);
    return temp;
}

// Префиксный декремент
binary_int& binary_int::operator--() {
    value = decrement(value);
    return *this;
}

// Постфиксный декремент
binary_int binary_int::operator--(int) {
    binary_int temp = *this;
    value = decrement(value);
    return temp;
}

binary_int& binary_int::operator+=(const binary_int other) {
    value = binary_add(value, other.value);
    return *this;
}

binary_int binary_int::operator+(const binary_int other) const {
    binary_int temp = *this;
    temp.value = binary_add(value, other.value);
    return temp;
}

binary_int& binary_int::operator-=(const binary_int other) {
    value = binary_add(value, binary_add(~(other.value), 1));
    return *this;
}

binary_int binary_int::operator-(const binary_int other) const {
    binary_int temp = *this;
    temp.value = binary_add(value, binary_add(~(other.value), 1));
    return temp;
}

binary_int& binary_int::operator*=(const binary_int other) {
    value = binary_multiply(value, other.value);
    return *this;
}

binary_int binary_int::operator*(const binary_int other) const {
    binary_int temp = *this;
    temp.value = binary_multiply(value, other.value);
    return temp;
}

binary_int& binary_int::operator>>=(int shift) {
    value >>= shift;
    return *this;
}

binary_int binary_int::operator>>(int shift) const {
    binary_int temp = *this;
    temp.value >>= shift;
    return temp;
}

binary_int& binary_int::operator<<=(int shift) {
    value <<= shift;
    return *this;
}

binary_int binary_int::operator<<(int shift) const {
    binary_int temp = *this;
    temp.value <<= shift;
    return temp;
}

std::pair<binary_int, binary_int> binary_int::split() const {
    int highBits = value & 0xFFFF0000;
    int lowBits = value & 0x0000FFFF;
    return {binary_int(highBits), binary_int(lowBits)};
}

std::ostream& operator<<(std::ostream& os, const binary_int& obj) {
    int i = 31;
    while (i >= 0) {
        os << ((obj.value >> i) & 1);
        i = decrement(i);
    }
    return os;
}

// вывод значения 
void binary_int::printBinInt() {
    std::cout << value << std::endl;
}

int main() {

    binary_int n(2578629), m(9);

    (n).printBinInt();
    (-n).printBinInt();
    (n).printBinInt();
    (n--).printBinInt();
    (n).printBinInt();
    (++n).printBinInt();
    (n).printBinInt();
    (n += m).printBinInt();
    (n + m).printBinInt();
    (n + m).printBinInt();
    (n - m).printBinInt();
    (n - m).printBinInt();
    (n -= m).printBinInt();
    (n).printBinInt();
    (n *= m).printBinInt();
    (n *= m).printBinInt();
    (n * m).printBinInt();
    (n * m).printBinInt();
    (n).printBinInt();
    (n<<1).printBinInt();
    (n).printBinInt();
    (n<<=1).printBinInt();
    (n).printBinInt();
    (n<<=1).printBinInt();
    (n).printBinInt();
    (n>>=1).printBinInt();
    (n).printBinInt();

    auto [high, low] = n.split();
    std::cout << "High bits: " << high << ", Low bits: " << low << "\n";


}