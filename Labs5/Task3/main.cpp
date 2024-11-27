#include <iostream>

class logical_values_array {
    private:
        unsigned int value;

    public:
        logical_values_array(unsigned int _value = 0) : value(_value) {};

        unsigned int getValue() const {
            return value;
        }

        logical_values_array NOT() const {
            return logical_values_array(~value);
        }

        logical_values_array AND(const logical_values_array& other) const {
            return logical_values_array(value & other.value);
        }

        logical_values_array OR(const logical_values_array& other) const {
            return logical_values_array(value | other.value);
        }

        logical_values_array IMPLICATION(const logical_values_array& other) const {
            return (this->NOT()).OR(other);
        }

        logical_values_array COIMPLICATION(const logical_values_array& other) const {
            return (this->IMPLICATION(other)).NOT();
        }

        logical_values_array XOR(const logical_values_array& other) const {
            return logical_values_array(value ^ other.value);
        }

        logical_values_array EQ(const logical_values_array& other) const {
            return (this->XOR(other)).NOT();
        }

        logical_values_array PIRS(const logical_values_array& other) const {
            return (this->OR(other)).NOT();
        }

        logical_values_array SHEFFER(const logical_values_array& other) const {
            return (this->AND(other)).NOT();
        }

        static bool equals(const logical_values_array& a, const logical_values_array& b) {
            return a.value == b.value;
        }

        bool get_bit(int position) const {
            if (position < 0 || position >= sizeof(unsigned int) * 8) {
                std::cerr << "Бро выходит за рамки\n";
            }
            return value & (1 << position);
        }

        void to_binary_string(char* str, int size) const {
            if (size <= sizeof(unsigned int) * 8) {
                std::cerr << "Размер слишком мал\n";
            }
            str[sizeof(unsigned int) * 8] = '\0';
            for (int i = sizeof(unsigned int) * 8 - 1; i >= 0; --i) {
                str[sizeof(unsigned int) * 8 - 1 - i] = (get_bit(i)) ? '1' : '0';
            }
        }

};

int main() {
    logical_values_array a(1358937);
    logical_values_array b(1358937);

    std::cout << "a: " << a.getValue() << "\n";
    std::cout << "b: " << b.getValue() << "\n";

    logical_values_array c = a.NOT();
    std::cout << "a NOT b: " << c.getValue() << "\n";

    c = a.AND(b);
    std::cout << "a AND b: " << c.getValue() << "\n";

    c = a.OR(b);
    std::cout << "a OR b: " << c.getValue() << "\n";

    c = a.IMPLICATION(b);
    std::cout << "a IMPLICATION b: " << c.getValue() << "\n";

    c = a.COIMPLICATION(b);
    std::cout << "a COIMPLICATION b: " << c.getValue() << "\n";

    c = a.XOR(b);
    std::cout << "a XOR b: " << c.getValue() << "\n";

    c = a.EQ(b);
    std::cout << "a EQ b: " << c.getValue() << "\n";

    c = a.PIRS(b);
    std::cout << "a PIRS b: " << c.getValue() << "\n";

    c = a.SHEFFER(b);
    std::cout << "a SHEFFER b: " << c.getValue() << "\n";

    bool bool_ = logical_values_array::equals(a, b);
    std::cout << "a SHEFFER b: " << (bool_ ? "true" : "false") << "\n";

    char binaryString[33];
    a.to_binary_string(binaryString, sizeof(binaryString));
    std::cout << "a as binary: " << binaryString << "\n";

    return 0;
}