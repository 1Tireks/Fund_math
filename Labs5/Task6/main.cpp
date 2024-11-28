#include <iostream>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <vector>

class vector {
    private:
        double* data;
        int _size;
        int _capasity;

        void _realloc(int new_capasity) {
            double* new_data = new double[new_capasity];
            for (int i = 0; i < (new_capasity <= _size ? new_capasity : _size); i++) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            _capasity = new_capasity;
        }

    public:
        // Конструкторы и деструктор
        vector(int size, double default_value = 0.0) : _size(size), _capasity(size) {
            data = new double[size];

            for (int i = 0; i < size; i++) {
                data[i] = default_value;
            }
        }

        template<typename InputIter>
        vector(InputIter first, InputIter last) {
            _size = std::distance(first, last);
            _capasity = _size;
            data = new double[_size];
            std::copy(first, last, data);
        }

        vector(std::initializer_list<double> init_list) : vector(init_list.begin(), init_list.end()) {}

        vector(const vector& other) : _size(other._size), _capasity(other._capasity){
            data = new double(other._size);
            for (int i = 0; i < _size; i++) {
                data[i] = other.data[i];
            }
        }

        vector& operator=(const vector& other) {
            if (this != &other) {
                delete[] data;
                _size = other._size;
                _capasity = other._capasity;
                data = new double[_size];
                for (int i = 0; i < _size; i++) {
                    data[i] = other.data[i];
                }
            }
            return *this;
        }

        ~vector() {
            delete[] data;
        }

        // Вспомогательный метод вывода вектора
        void print_vector() const {
            for (int i = 0; i < _size; i++) {
                std::cout << data[i] << ' ';
            }
            std::cout << std::endl;
        }

        // Основные методы
        double& at(int index) {
            if (index >= _size) {
                throw std::out_of_range("Индекс вне предела вектора\n");
            }

            return data[index];
        }

        const double& at(int index) const {
            if (index >= _size) {
                throw std::out_of_range("Индекс вне предела вектора\n");
            }

            return data[index];
        }

        double& front() {
            return data[0];
        }

        const double& front() const {
            return data[0];
        }

        double& back() {
            return data[_size - 1];
        }

        const double& back() const {
            return data[_size - 1];
        }

        double* _data() {
            return data;
        }

        const double* _data() const {
            return data;
        }

        bool empty() const {
            return _size == 0;
        }

        int size() const {
            return _size;
        }

        void reserve(int new_capasity) {
            if (_capasity < new_capasity) {
                _realloc(new_capasity);
            }
        }

        int capasity() const {
            return _capasity;
        }

        void shrink_to_fit(int new_capasity) {
            if (_capasity > new_capasity) {
                _realloc(new_capasity);
            }
        }

        void clear() {
            _size = 0;
        }

        void insert(int index, double elem) {
            if (index > _size) {
                throw std::out_of_range("Index out of range");
            }
            if (_size == _capasity) {
                reserve(_capasity == 0 ? 1 : _capasity * 2);
            }

            for (int i = _size - 1; i > index; i--) {
                data[i] = data[i - 1];
            }
            data[index] = elem;
            _size++;
        }

        void erase(int index, double elem) {
            if (index > _size) {
                throw std::out_of_range("Index out of range");
            }

            for (int i = index; i < _size - 1; i++) {
                data[i] = data[i + 1];
            }
            _size--;
        }

        void push_back(double elem) {
            if (_size == _capasity) {
                reserve(_capasity == 0 ? 1 : _capasity * 2);
            }
            data[_size++] = elem;
        }

        void pop_back() {
            if (_size == 0) {
                throw std::out_of_range("Вектор пуст :(\n");
            }
            _size--;
        }

        void resize(size_t size, double elem = 0.0) {
            if (size > _capasity) {
                reserve(size);
            }
            for (int i = _size; i < size; i++)
                data[i] = elem;
            _size = size;
        }

        // Операторы сравнения
        bool operator==(const vector& other) const {
            if (_size != other._size) {
                return false;
            }
            for (int i = 0; i < _size; i++) {
                if (data[i] != other.data[i]) {
                    return false;
                }
            }
            return true;
        }

        std::strong_ordering operator<=>(const vector& other) const {
            int min_size = _size < other._size ? _size : other._size;
            for (int i = 0; i < min_size; ++i) {
                if (data[i] < other.data[i]) {
                    return std::strong_ordering::less;
                }

                if (data[i] > other.data[i]){
                    return std::strong_ordering::greater;
                }
            }
            return _size <=> other._size;
        }


        class iterator {
            private:
                double* ptr;
            public:
                explicit iterator(double* p) : ptr(p) {}

                double& operator*() { 
                    return *ptr;
                
                }
                const double& operator*() const {
                    return *ptr;
                }

                iterator& operator++() {
                    ptr++;
                    return *this;
                }

                iterator operator++(int) {
                    iterator temp = *this;
                    ptr++;
                    return temp;
                }

                iterator& operator--() {
                    ptr--;
                    return *this;
                }

                iterator operator--(int) {
                    iterator temp = *this;
                    ptr--;
                    return temp;
                }

                iterator operator+(int n) const {
                    return iterator(ptr + n);
                }

                iterator operator-(int n) const {
                    return iterator(ptr - n);
                }

                int operator-(const iterator& other) const {
                    return ptr - other.ptr;
                }


                bool operator==(const iterator& other) const {
                    return ptr == other.ptr;
                }

                bool operator!=(const iterator& other) const {
                    return ptr != other.ptr;
                }

                double& operator[](int index) {
                    return *(ptr + index);
                }

                const double& operator[](int index) const {
                    return *(ptr + index);
                }
        };

        class const_iterator {
            private:
                const double* ptr;
            public:
                explicit const_iterator(const double* p) : ptr(p) {}

                const double& operator*() {
                    return *ptr;
                }

                const double& operator*() const {
                    return *ptr;
                }

                const_iterator& operator++() = delete;

                const_iterator operator++(int) = delete;

                const_iterator& operator--() = delete;

                const_iterator operator--(int) = delete;

                bool operator==(const const_iterator& other) const {
                    return ptr == other.ptr;
                }

                bool operator!=(const const_iterator& other) const {
                    return ptr != other.ptr;
                }

                const double& operator[](int index) {
                    return *(ptr + index);
                }

                const double& operator[](int index) const {
                    return *(ptr + index);
                }
                
        };

        iterator begin() {
            return iterator(data);
        }

        iterator end() {
            return iterator(data + _size);
        }

        const_iterator begin() const {
            return const_iterator(data);
        }

        const_iterator end() const {
            return const_iterator(data + _size);
        }

};

int main() {

    vector a(5, 7.0);
    a.print_vector();

    vector b(3);
    b.print_vector();

    std::vector<double> vec = {5.0, 4.0, 5.6, 9.0, 7.0};
    vector c(vec.begin(), vec.end());
    c.print_vector();

    std::initializer_list<double> init_list = {5.0, 4.0, 5.6, 9.0, 7.0};
    vector d(init_list.begin() + 1, init_list.end() - 1);
    d.print_vector();

    vector f(c);
    f.print_vector();

    a = b;
    a.print_vector();

    vector::iterator const ptr(c._data());

    std::cout << (ptr[3]) << std::endl;

    //ptr++; - функция удалена

    std::cout << (a <= b) << std::endl;
    
}