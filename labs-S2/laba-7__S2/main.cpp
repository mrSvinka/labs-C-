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
#include <algorithm>
#include <stdexcept>
using namespace std;  // Добавлено использование стандартного пространства имён

template <typename T>
class Vector { };

// Специализация для bool
template <>
class Vector<bool> 
{
private:
    unsigned char* data_ = nullptr;  // Массив для хранения битов (char = 8бит)
    size_t size_ = 0;                // Количество булевых элементов
    size_t capacity_ = 0;            // Вместимость

    // Вспомогательный класс для доступа к отдельным битам
    class BitReference 
    {
        unsigned char* byte_;  // Указатель на байт, содержащий бит
        size_t bit_pos_;       // Позиция бита в байте (0-7)

    public:
        // Конструктор инициализирует указатель на байт и позицию бита
        BitReference(unsigned char* byte, size_t bit_pos)
            : byte_(byte), bit_pos_(bit_pos) {}

        // Преобразование в bool (чтение)
        operator bool() const 
        {
            return (*byte_ >> bit_pos_) & 1; // Сдвигаем нужный бит в нулевую позицию и применяем маску 1
        }

        // Присваивание значения биту (запись)
        BitReference& operator=(bool value) 
        {
            if (value) 
            {
                *byte_ |= (1 << bit_pos_);    // Установить бит в 1
            } 
            else 
            {
                *byte_ &= ~(1 << bit_pos_);   // Установить бит в 0
            }
            return *this;
        }

        // Запрет присваивания временных объектов
        BitReference& operator=(const BitReference&) = delete;
    };

public:
    // Конструктор по умолчанию
    Vector() = default;
    
    // Конструктор копирования
    Vector(const Vector& other) 
        : size_(other.size_), capacity_(other.size_) 
    {
        if (size_ > 0) 
        {
            allocate_memory(); // Выделяем память под копию
            // Копируем байты из исходного массива
            copy(other.data_, other.data_ + bytes_count(), data_);
        }
    }
    
    // Конструктор перемещения
    Vector(Vector&& other) noexcept 
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) 
    {
        // Обнуляем перемещаемый объект
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // Деструктор - освобождает память
    ~Vector() 
    {
        delete[] data_;
    }

    // Операторы присваивания
    Vector& operator=(const Vector& other) 
    {
        if (this != &other) 
        {
            Vector temp(other); // Создаем временную копию
            swap(temp);        // Обмениваем содержимое с текущим объектом
        }
        return *this;
    }

    // Оператор присваивания (перемещение)
    Vector& operator=(Vector&& other) noexcept 
    {
        if (this != &other) 
        {
            delete[] data_;                // Освобождаем текущие ресурсы
            data_ = other.data_;          // Перехватываем указатель
            size_ = other.size_;         // Копируем размер
            capacity_ = other.capacity_;// Копируем емкость
            // Обнуляем исходный объект
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    // Добавление элемента в конец вектора
    void push_back(bool value) 
    {
        // Проверка необходимости расширения
        if (size_ == capacity_) 
        {
            // Увеличиваем емкость: в 2 раза или до 1 
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        // Установка значения бита и увеличение размера
        set_bit(size_++, value);
    }

    // Доступ к элементу для модификации
    BitReference operator[](size_t index) 
    {
        // Рассчитываем байт: index / 8 (целочисленное деление)
        // Рассчитываем позицию бита: index % 8 (остаток от деления)
        return { data_ + index / 8, index % 8 };
    }

    // Константный доступ к элементу (возвращает значение)
    bool operator[](size_t index) const 
    {
        // Извлекаем нужный байт и бит внутри него
        return (data_[index / 8] >> (index % 8)) & 1;
    }
    
    // Вставка элемента в произвольную позицию
    void insert(size_t pos, bool value) 
    {
        // Проверка корректности позиции
        if (pos > size_) throw out_of_range("Index out of range");
        
        // Увеличиваем размер 
        push_back(false);
        // Сдвиг элементов вправо 
        for (size_t i = size_ - 1; i > pos; --i) 
        {
            // Копируем значение предыдущего элемента
            set_bit(i, (*this)[i - 1]);
        }
        // Устанавливаем новое значение
        set_bit(pos, value);
    }

    // Удаление элемента из произвольной позиции
    void erase(size_t pos) 
    {
        // Проверка корректности позиции
        if (pos >= size_) throw out_of_range("Index out of range");
        // Сдвиг элементов влево (начиная с позиции удаления)
        for (size_t i = pos; i < size_ - 1; ++i) 
        {
            // Копируем значение следующего элемента
            set_bit(i, (*this)[i + 1]);
        }
        // Уменьшаем размер вектора
        --size_;
    }

    // Возвращает текущее количество элементов
    size_t size() const 
    { 
        return size_; 
    }

    // Резервирование памяти 
    void reserve(size_t new_cap) 
    {
        // Если текущей емкости достаточно - ничего не делаем
        if (new_cap <= capacity_) return;
        
        // Вычисляем необходимое количество байт 
        size_t new_bytes = (new_cap + 7) / 8;
        // Выделяем новый массив с нулевой инициализацией
        unsigned char* new_data = new unsigned char[new_bytes]{};
        
        // Переносим существующие данные
        if (data_) 
        {
            // Копируем байты из старого массива
            copy(data_, data_ + bytes_count(), new_data);
            delete[] data_;  // Освобождаем старую память
        }

        // Обновляем указатель на данные и емкость
        data_ = new_data;
        capacity_ = new_cap;
    }
    
    // Обмен содержимого двух векторов
    void swap(Vector& other) noexcept 
    {
        ::swap(data_, other.data_);
        ::swap(size_, other.size_);
        ::swap(capacity_, other.capacity_);
    }

private:
    // Устанавливает бит по индексу в указанное значение
    void set_bit(size_t index, bool value) 
    {
        // Вычисляем индекс байта и позицию бита в нем
        size_t byte_idx = index / 8;
        size_t bit_idx = index % 8;
        
        if (value) 
        {
            // Установка бита: битовая операция OR
            data_[byte_idx] |= (1 << bit_idx);
        } 
        else 
        {
            // Сброс бита: битовая операция AND с инвертированной маской
            data_[byte_idx] &= ~(1 << bit_idx);
        }
    }

    // Вычисляет количество используемых байтов
    size_t bytes_count() const 
    { 
        // Округление вверх: (элементы + 7) / 8
        return (size_ + 7) / 8; 
    }

    // Выделяет память под текущее количество элементов
    void allocate_memory() 
    {
        // Выделение с инициализацией нулями
        data_ = new unsigned char[bytes_count()]{};
    }
};

int main() 
{
    Vector<bool> vec;

    // Добавление элементов
    vec.push_back(true);
    vec.push_back(false);
    vec.push_back(true);
    vec.push_back(false);

    // Изменение элементов через []
    vec[1] = true;
    vec[3] = true;

    // Вставка и удаление
    vec.insert(2, false);  // Вставляем false на позицию 2
    vec.erase(0);           // Удаляем первый элемент

    // Вывод элементов
    cout << "Vector elements: ";
    for (size_t i = 0; i < vec.size(); ++i) 
    {
        cout << vec[i] << " ";
    }
    cout << "\nSize: " << vec.size() << endl;

    return 0;
}