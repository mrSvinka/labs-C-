/*
1. 	Дан файл, содержащий английский текст. Найти в тексте N<=2000 самых длинных слов,
 начинающихся заданной буквой. Записать найденные слова в текстовый файл в порядке невозрастания длины.
  Все найденные слова должны быть разными!
*/

#include <iostream>
#include <set>
#include <string>
#include <cctype>
#include <sstream> 
using namespace std;

int main() 
{
    set<string> wordsSet;
    char Letter;
    int N;

    cout << "Введите текст, для окончания ввода введите END:\n";
    string text, line;
    while (getline(cin, line) && line != "END") 
    {
        text += line + " ";
    }

    cout << "Введите букву: ";
    cin >> Letter;
    cout << "Введите количество слов (N <= 2000): ";
    cin >> N;

    // Разделение текста на слова
    istringstream stream(text);
    string word;
    while (stream >> word) 
    {
        if (!word.empty() && tolower(word[0]) == tolower(Letter)) 
        {
            wordsSet.insert(word);
        }
    }

    // Результат
    int count = 0;
    for (const auto& w : wordsSet) 
    {
        cout << w << "\n";
        if (++count == N) break;
    }

    return 0;
}
