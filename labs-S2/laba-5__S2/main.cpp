/*
Реализуйте класс MyVector, который частично повторяет работу std::vector для типа int.
У вас должны быть реализованы:
Базовый конструктор
Конструктор копирования
Оператор присваивания копированием
Деструктор
Методы:
resize;
reserve;
shrink_to_fit;
front;
back;
size;
empty;
capacity;
push_back;
insert
erase
Оператор []
*/
#include <iostream>
#include <algorithm> 
#include <stdexcept> 
using namespace std;


class MyVector 
{
private:
    int* data;         // Указатель на массив элементов
    size_t vec_size;     // Текущее количество элементов
    size_t vec_capacity; // ёмкость

    // копированием элементов
    void reallocate(size_t new_capacity) 
    {
        int* new_data = new int[new_capacity];
        copy(data, data + vec_size, new_data);
        
        delete[] data;
        data = new_data;
        vec_capacity = new_capacity;
    }



public:
    // 1. Базовый конструктор (пустой вектор)
    MyVector() : data(nullptr), vec_size(0), vec_capacity(0) {} 


    // 2. Конструктор копирования
    MyVector(const MyVector& other) 
        : vec_size(other.vec_size), vec_capacity(other.vec_capacity) 
    {
        data = new int[vec_capacity];
        copy(other.data, other.data + vec_size, data);
    }

    // 3. Оператор присваивания
    MyVector& operator=(const MyVector& other) 
    {
        if (this != &other)//Защита от самоприсваивания 
        {
            delete[] data; //Освобождает старую память перед копированием
            
            vec_size = other.vec_size;
            vec_capacity = other.vec_capacity;
            data = new int[vec_capacity];
            copy(other.data, other.data + vec_size, data);
        }
        return *this;
    }

    // 4. Деструктор
    ~MyVector() 
    {
        delete[] data; //Освобождает старую память
    }

    // 5. Изменение размера с заполнением нулями
    void resize(size_t new_size) 
    {
        if (new_size > vec_capacity) 
        {
            reserve(max(new_size, vec_capacity * 2));
        }//Если новый размер больше текущей ёмкости — увеличивает ёмкость
        vec_size = new_size;
    }

    // 6. Резервирование памяти
    void reserve(size_t new_capacity) // ёмкость не меньше
     {
        if (new_capacity > vec_capacity)
         {
            reallocate(new_capacity); //величение памяти
        }
    }

    // 7. Освобождение неиспользуемой памяти
    void shrink_to_fit() 
    {
        if (vec_capacity > vec_size) 
        {
            reallocate(vec_size);
        }
    }

    // 8. Первый элемент
    int& front() 
    {
        if (empty()) throw out_of_range("Вектор пуст");
        return data[0];
    }

    // 9. Последний элемент
    int& back() 
    {
        if (empty()) throw out_of_range("Вектор пуст");
        return data[vec_size - 1];
    }

    // 10. Текущий размер
    size_t size() const { return vec_size; }

    // 11. Проверка пустоты
    bool empty() const { return vec_size == 0; }

    // 12. Текущая ёмкость
    size_t capacity() const { return vec_capacity; }

    // 13. Добавление элемента
    void push_back(int value) 
    {
        if (vec_size == vec_capacity) 
        {
            reserve(vec_capacity == 0 ? 1 : vec_capacity * 2); //Если нет места — удваивает ёмкость
        }
        data[vec_size++] = value;
    }

    // 14. Вставка элемента
    void insert(size_t pos, int value) 
    {
        if (pos > vec_size) throw out_of_range("Неверная позиция");
        
        if (vec_size == vec_capacity) 
        {
            reserve(vec_capacity == 0 ? 1 : vec_capacity * 2);
        }
        
        for (size_t i = vec_size; i > pos; --i) 
        {
            data[i] = data[i - 1];
        }
        data[pos] = value;
        ++vec_size;
    }

    // 15. Удаление элемента
    void erase(size_t pos) 
    {
        if (pos >= vec_size) throw out_of_range("Неверная позиция");
        
        for (size_t i = pos; i < vec_size - 1; ++i) 
        {
            data[i] = data[i + 1];
        }
        --vec_size;
    }

    // 16. Доступ по индексу
    int& operator[](size_t index) 
    {
        return data[index];
    }
};






// пример
int main() 
{
    MyVector v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    cout << "Elements: ";
    for (size_t i = 0; i < v.size(); ++i) 
    {
        cout << v[i] << " "; 
    }

    v.insert(1, 15);
    cout << "\nAfter insert: ";
    for (size_t i = 0; i < v.size(); ++i) 
    {
        cout << v[i] << " "; 
    }

    v.erase(2);
    cout << "\nAfter erase: ";
    for (size_t i = 0; i < v.size(); ++i) 
    {
        cout << v[i] << " "; 
    }

    v.shrink_to_fit();
    cout << "\nCapacity: " << v.capacity(); 
}