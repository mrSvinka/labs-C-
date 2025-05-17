/*Лабораторная работа №7
“Шаблонная специализация VectorBool”

Реализуйте специализацию шаблона для вектора из булевских значений. Помните, что на каждое значение должен быть потрачен только 1 бит памяти.
Предусмотрите следующие операции:
Метод добавления в конец вектора
Метод и оператор получения и изменения значения по индексу
Метод size
Метод insert и erase
 
Продемонстрируйте работу с классом.
*/

#include <iostream>
#include <stdexcept>
#include <memory>
#include <algorithm>

template<typename T>
class Vector {
    // Базовая реализация для других типов
};

template<>
class Vector<bool> {
private:
    struct BitProxy;

    size_t _size = 0;
    size_t _capacity = 0;
    std::unique_ptr<uint8_t[]> data;

    static constexpr size_t bytes_for_bits(size_t bits) {
        return (bits + 7) / 8;
    }

public:
    Vector() = default;

    Vector(size_t initial_size) : _size(initial_size), _capacity(initial_size) {
        if (_capacity > 0) {
            data = std::make_unique<uint8_t[]>(bytes_for_bits(_capacity));
            std::fill(data.get(), data.get() + bytes_for_bits(_capacity), 0);
        }
    }

    BitProxy operator[](size_t index) {
        if (index >= _size) throw std::out_of_range("Index out of range");
        if (!data) throw std::logic_error("Accessing empty vector");
        return BitProxy(&data[index/8], index%8);
    }

    bool operator[](size_t index) const {
        if (index >= _size) throw std::out_of_range("Index out of range");
        if (!data) return false;
        return (data[index/8] >> (index%8)) & 1;
    }

    size_t size() const { return _size; }

    void push_back(bool value) {
        if (_size == _capacity) {
            reserve(std::max(_capacity * 2, static_cast<size_t>(1)));
        }
        (*this)[_size++] = value;
    }

    // Исправленный метод insert
    void insert(size_t pos, bool value) {
        if (pos > _size) throw std::out_of_range("Insert position out of range");
        
        // Резервируем память перед изменением размера
        if (_size == _capacity) {
            reserve(std::max(_capacity * 2, static_cast<size_t>(1)));
        }
        
        _size++; // Увеличиваем размер вручную
        
        // Сдвигаем биты, начиная с конца
        for (size_t i = _size - 1; i > pos; --i) {
            (*this)[i] = (*this)[i - 1];
        }
        
        (*this)[pos] = value;
    }

    // Исправленный метод erase
    void erase(size_t pos) {
        if (pos >= _size) throw std::out_of_range("Erase position out of range");
        
        for (size_t i = pos; i < _size - 1; ++i) {
            (*this)[i] = (*this)[i + 1];
        }
        _size--;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity <= _capacity) return;
        
        auto new_data = std::make_unique<uint8_t[]>(bytes_for_bits(new_capacity));
        std::fill(new_data.get(), new_data.get() + bytes_for_bits(new_capacity), 0);
        
        if (data) {
            size_t copy_bytes = bytes_for_bits(std::min(_capacity, new_capacity));
            std::copy(data.get(), data.get() + copy_bytes, new_data.get());
        }
        
        data.swap(new_data);
        _capacity = new_capacity;
    }

private:
    struct BitProxy {
        uint8_t* byte;
        uint8_t bit_pos;

        BitProxy(uint8_t* b, uint8_t pos) : byte(b), bit_pos(pos) {
            if (!byte) throw std::logic_error("Null byte access");
        }

        operator bool() const {
            return (*byte >> bit_pos) & 1;
        }

        BitProxy& operator=(bool value) {
            if (value) *byte |= (1 << bit_pos);
            else       *byte &= ~(1 << bit_pos);
            return *this;
        }

        BitProxy& operator=(const BitProxy&) = delete;
    };
};





int main() {
    Vector<bool> vb;

    for (int i = 0; i < 10; ++i) {
        vb.push_back(i % 2);
    }

    std::cout << "Size: " << vb.size() << std::endl;

    vb[3] = true;
    vb.insert(5, false);
    vb.erase(2);
    
    std::cout << "Elements: ";
    for (size_t i = 0; i < vb.size(); ++i) {
        std::cout << vb[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}