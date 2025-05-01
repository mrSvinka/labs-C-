/*
3. 	В текстовом файле input.txt записан английский текст.
 Найти в тексте слова, содержащие более семи различных букв, выделить их и указать после каждого такого слова в скобках найденные буквы. 
 Полученный текст записать в файл output.txt. Весь текст, кроме найденных слов, должен остаться неизменным, включая и знаки препинания.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <cctype>
using namespace std;

bool hasMoreThanSevenUniqueLetters(const string &word, set<char> &uniqueLetters) 
{
    uniqueLetters.clear();
    for (char ch : word) 
    {
        if (isalpha(ch)) // Проверяем, является ли символ буквой
        { 
            uniqueLetters.insert(tolower(ch));
        }
    }
    return uniqueLetters.size() > 7;
}

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open()) 
    {
        cerr << "Не удалось открыть файл input.txt" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) 
    {
        stringstream ss(line);
        string word;
        set<char> uniqueLetters;
        
        while (ss >> word) 
        {
            string originalWord = word; // Сохраняем оригинальное слово

            // Убираем знаки препинания с конца слова
            while (!word.empty() && ispunct(word.back())) 
            {
                word.pop_back();
            }
            
            if (hasMoreThanSevenUniqueLetters(word, uniqueLetters)) 
            {
                // Формируем строку для вставки
                string uniqueLettersStr(uniqueLetters.begin(), uniqueLetters.end());
                word += " (" + uniqueLettersStr + ")";
            }

            // Восстанавливаем оригинальное слово (с знаками)
            ss.str("");
            ss << originalWord; 
            // Выводим слово (с добавлением уникальных букв, если найдено)
            outputFile << word << " ";
            ss.clear();
        }
        outputFile << endl; // Переход на новую строку
    }

    inputFile.close();
    outputFile.close();
    
    return 0;
}

