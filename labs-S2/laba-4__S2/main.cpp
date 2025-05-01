/*UPD:
Реализовать BigInt для неотрицательных чисел.
Реализуйте класс BigInt для работы со большими целыми числами (количество цифр в числе не превосходит 1000).

У вас должны быть реализованы:
1.	Базовый конструктор
2.	Конструктор копирования (если необходим)
3.	Оператор присваивания копированием (если необходим)
4.	Деструктор (если необходим)
5.	Операторы + и +=
6.	Операторы * и *=
7.	Операторы <, >, ==, !=
8.	Операторы ввода и вывода в поток
*/

#include <iostream>
#include <cstring>
#include <stdexcept>
using namespace std;

class BigInt 
{
private:
    char* digits;       // Массив для хранения цифр
    size_t length;      // Текущее количество цифр
    size_t capacity;    // Максимум (1000)
    

    void resize(size_t new_capacity) 
    {
        // Увеличиваем размер массива с сохранением данных
        char* new_digits = new char[new_capacity];
        memcpy(new_digits, digits, length);
        delete[] digits;
        digits = new_digits;
        capacity = new_capacity;
    }


    void removeLeadingZeros() 
    {
        // Удаляем нули 
        while (length > 1 && digits[length-1] == 0)
            length--;
    }


    void validateString(const char* str) 
    {
        // Проверка корректности входной строки
        if (*str == '\0') throw invalid_argument("Пустая строка");
        if (strlen(str) > 1000) throw invalid_argument("Слишком длинное число");
        if (strlen(str) > 1 && str[0] == '0') 
            throw invalid_argument("начальные нули");
    }





public:
    // 1. Базовый конструктор
    BigInt(const char* str = "0") 
    {
        validateString(str);
        
        capacity = strlen(str) + 10; // Начальная ёмкость с запасом
        digits = new char[capacity];
        length = strlen(str);
        
        // обратный порядок 
        for (size_t i = 0; i < length; i++) 
        {
            digits[i] = str[length-1-i] - '0';
        }
    }


    // 2. Конструктор копирования
    BigInt(const BigInt& other) 
    {
        capacity = other.capacity;
        length = other.length;
        digits = new char[capacity];
        memcpy(digits, other.digits, length); //копирует содержимое одной области памяти в другую
    }


    // 3. Оператор присваивания
    BigInt& operator=(const BigInt& other) 
    {
        if (this != &other) //предотвращает самоприсваивание
        {
            delete[] digits; //Освобождает старую память, выделяет новую и копирует данные.
            capacity = other.capacity;
            length = other.length;
            digits = new char[capacity];
            memcpy(digits, other.digits, length);
        }
        return *this;
    }


    // 4. Деструктор (Удаляет массив, чтобы избежать утечек памяти)
    ~BigInt() 
    {
        delete[] digits;
    }

    
    // 5. Оператор +=
    BigInt& operator+=(const BigInt& rhs) 
    {
        // Вычисляем максимальную длину результата
        size_t max_len = max(length, rhs.length) + 1;
        if (max_len > capacity) resize(max_len + 10);
        
        char carry = 0;
        size_t i;
        
        // Складываем цифры
        for (i = 0; i < max_len; i++) 
        {
            char sum = carry;
            if (i < length) sum += digits[i];
            if (i < rhs.length) sum += rhs.digits[i];
            
            carry = sum / 10;
            digits[i] = sum % 10;
        }
        
        length = i;
        if (carry) digits[length++] = carry;
        
        removeLeadingZeros();
        return *this;
    }

    // 5. Оператор + (Оператор использует +=, создавая временную копию левого операнда)
    BigInt operator+(const BigInt& a, const BigInt& b) 
    {
        BigInt result(a);
        return result += b;
    }

    // 6. Оператор *=
    BigInt& operator*=(const BigInt& rhs) 
    {
        BigInt result("0");
        char* temp = new char[length + rhs.length + 1]{}; //(хранения промежуточных результатов.)
        
        // Умножение в столбик
        for (size_t i = 0; i < rhs.length; i++) 
        {
            char carry = 0;
            for (size_t j = 0; j < length; j++) 
            {
                char product = digits[j] * rhs.digits[i] + temp[i+j] + carry;
                temp[i+j] = product % 10;
                carry = product / 10;
            }
            if (carry) temp[i+length] = carry;
        }
        
        // Обновляем данные
        delete[] result.digits;
        result.digits = temp;
        result.length = length + rhs.length;
        result.capacity = result.length + 10;
        result.removeLeadingZeros(); //удаления незначащих нулей
        
        *this = result;
        return *this;
    }

    // 6. Оператор *
    BigInt operator*(const BigInt& a, const BigInt& b) 
    {
        BigInt result(a);
        return result *= b;
    }


    // 7. Операторы сравнения
    bool operator==(const BigInt& a, const BigInt& b) 
    {
        if (a.length != b.length) return false;
        for (size_t i = 0; i < a.length; i++)
            if (a.digits[i] != b.digits[i]) return false;
        return true;
    }
//Числа равны, если совпадают все цифры
    bool operator!=(const BigInt& a, const BigInt& b) 
    {
        return !(a == b);
    }

    bool operator<(const BigInt& a, const BigInt& b) 
    {
        if (a.length != b.length) return a.length < b.length;
        for (int i = a.length-1; i >= 0; i--)
            if (a.digits[i] != b.digits[i]) 
                return a.digits[i] < b.digits[i];
        return false;
    }
//Сравнение начинается со старших разрядов
    bool operator>(const BigInt& b) 
    {
        return b < *this;
    }


    // 8. Операторы ввода/вывода
    friend ostream& operator<<(ostream& os, const BigInt& num) 
    {
        for (int i = num.length-1; i >= 0; i--) //Цифры выводятся в обратном порядке
            os << (int)num.digits[i]; 
        return os;
    }
//Строка проверяется на корректность
    friend istream& operator>>(istream& is, BigInt& num) 
    {
        string s;
        is >> s; // Считываем строку из входного потока
        num = BigInt(s.c_str());
        return is;// Возвращаем поток для цепочечных операций
    }
};










// Пример использования
int main() 
{
    BigInt a("123456789");
    BigInt b("987654321");
    
    cout << "a + b = " << a + b << endl;    // 1111111110
    cout << "a * b = " << a * b << endl;    // 121932631112635269
    
    BigInt c = a;
    c += c;
    cout << "c += a: " << c << endl;        // 246913578
    
    cout << boolalpha;
    cout << "a < b: " << (a < b) << endl;   // true
    cout << "a == b: " << (a == b) << endl; // false
}