#include <iostream>
#include <limits>
using namespace std;


/*
1) переменная - поименованная, либо адресуемая иным способом область памяти,
 адрес которой можно использовать для осуществления доступа к данным. 

2)Целочисленные: long, int, short, long long.
Целочисленные без знака: unsigned short, unsigned long, unsigned int, unsigned long long.
Вещественные:  long double, float, double.
Символьные: unsigned char, char.
Логические: bool.

3)                             4)      (min/max)
long - 4B/8B                   [-1 * 2^31; 2^31 - 1] / [-1 * 2^63; 2^63 - 1]
int - 4B                       [-1 * 2^31; 2^31 - 1]
short - 2B                     [-1 * 2^15; 2^15 - 1]
unsigned int - 4B              [0; 2^32 - 1]
unsigned short - 2B            [0; 2^16 - 1]
unsigned long - 4B/8B          [0; 2^32 - 1] / [0; 2^64 - 1]
long double - 8B/16B           [-1.7E+308; 1.7E+308] / [-1.1E+4932; 1.1E+4932]
float - 4B                     [-3.4E+38; 3.4E+38]
double - 8B                    [-1.7E+308; 1.7E+308]
float - 4B                     [-3.4E+38; 3.4E+38]
unsigned char - 1B             [0; 2^8 - 1]
char - 1B                      [-1 * 2^7; 2^7 - 1]
bool - 1B                      [0; 1]
long long - 8B                 [-1 * 2^63; 2^63 - 1]
unsigned long long - 8B        [0; 2^64 - 1]


5)
*/
int main()
{
    cout << "long            " << sizeof(long) << "B  " << numeric_limits<long>::min() << " | " <<
        numeric_limits<long>::max() << endl;

    cout << "int             " << sizeof(int) << "B  " << numeric_limits<int>::min() << " | " <<
        numeric_limits<int>::max() << endl;

    cout << "short           " << sizeof(short) << "B  " << numeric_limits<short>::min() << " | " <<
     numeric_limits<short>::max() << endl;

    cout << "unsigned int    " << sizeof(unsigned int) << "B  " << numeric_limits<unsigned int>::min() << " | " <<
     numeric_limits<unsigned int>::max() << endl;

    cout << "unsigned short  " << sizeof(unsigned short) << "B  " << numeric_limits<unsigned short>::min() << " | " <<
     numeric_limits<unsigned short>::max() << endl;

    cout << "unsigned long   " << sizeof(unsigned long) << "B  " << numeric_limits<unsigned long>::min() << " | " <<
     numeric_limits<unsigned long>::max() << endl;

    cout << "long double     " << sizeof(long double) << "B  " << numeric_limits<long double>::min() << " | " <<
     numeric_limits<long double>::max() << endl;

    cout << "float           " << sizeof(float) << "B  " << numeric_limits<float>::min() << " | " << 
    numeric_limits<float>::max() << endl;

    cout << "unsigned char   " << sizeof(unsigned char) << "B  " << (int)numeric_limits<unsigned char>::min() << " | " <<
     (int)numeric_limits<unsigned char>::max() << endl;

    cout << "char            " << sizeof(char) << "B  " << (int)numeric_limits<char>::min() << " | " <<
     (int)numeric_limits<char>::max() << endl;

     cout << "bool           " << sizeof(bool) << "B " << endl;
    
    cout << "unsigned long long" << sizeof(unsigned long long) << "B  " << numeric_limits<unsigned long long>::min() << " | " <<
     numeric_limits<unsigned long long>::max() << endl; 

    cout << "long long       " << sizeof(long long) << "B  " << numeric_limits<long long>::min() << " | " <<
     numeric_limits<long long>::max() << endl;
//6)
    cout << endl << endl;

    long a =4 , b = 2;
        cout << "long: " << a << " + " << b << " = " << (a + b) << endl;

    int a_i = 6, b_i = 2;
        cout << "int: " << a_i << " + " << b_i << " = " << (a_i + b_i) << endl;

    short a_s = 1, b_s = 7;
        cout << "short: " << a_s << " + " << b_s << " = " << (a_s + b_s) << endl;

    unsigned short a_u = 133, b_u = 22;
        cout << "unsigned short: " << a_u << " + " << b_u << " = " << (a_u + b_u) << endl;

    unsigned long a_l = 142, b_l = 12;
        cout << "unsigned long: " << a_l << " + " << b_l << " = " << (a_l + b_l) << endl;

    unsigned int a_m = 231, b_m = 242;
        cout << "unsigned int: " << a_m << " + " << b_m << " = " << (a_m + b_m) << endl;

    long double a_d = 51.0, b_d = 52.0;
        cout << "long double: " << a_d << " + " << b_d << " = " << (a_d + b_d) << endl;

    float a_f = 19.0f, b_f = 21.0f;
        cout << "float: " << a_f << " + " << b_f << " = " << (a_f + b_f) << endl;

    double a_dy = 1.0, b_dy = 2.0;
        cout << "double: " << a_dy << " + " << b_dy << " = " << (a_dy + b_dy) << endl;

    unsigned char a_y = 65, b_y = 782;
        cout << "unsigned char: " << a_y << " + " << b_y << " = " << (a_y + b_y) << endl;

    char a_c = 69, b_c = 34;
        cout << "char: " << a_c << " + " << b_c << " = " << (a_c + b_c) << endl;

 long long a_w = 3, b_w = 8;
    cout << "long long: " << a_w << " + " << b_w << " = " << (a_w + b_w) << endl;

 unsigned long long a_p = 9, b_p = 7;
    cout << "unsigned long long: " << a_p << " + " << b_p << " = " << (a_p + b_p) << endl;

    return 0;
}












