
/*
2. 	Дана строка, содержащая английский текст.
 Если в тексте есть слова-палиндромы длиной более 2-х букв, то вывести слова текста в   соответствии с долей гласных,
  в противном случае удалить из слов   текста гласные буквы, продублировать согласные и вывести полученные слова в алфавитном порядке.
*/
#include <iostream>
#include <set>
#include <cstring>
#include <algorithm>
using namespace std;

bool isPalindrome(const char *word) 
{
    int len = strlen(word);
    for (int i = 0; i < len / 2; i++)
        if (tolower(word[i]) != tolower(word[len - i - 1]))
            return false;
    return true;
}

double vowelRatio(const char *word) 
{
    int vowelCount = 0, length = strlen(word);
    for (int i = 0; i < length; i++)
        if (strchr("aeiouAEIOU", word[i]))
            vowelCount++;
    return static_cast<double>(vowelCount) / length;
}

void transformWord(const char *word, char *result) 
{
    int j = 0;
    for (int i = 0; word[i]; i++) 
    {
        if (!strchr("aeiouAEIOU", word[i])) 
        {
            result[j++] = word[i];
            result[j++] = word[i]; // Дублируем согласные
        }
    }
    result[j] = '\0';
}

int main() 
{
    char input[2000], transformed[50];
    cout << "Введите строку: ";
    cin.getline(input, sizeof(input));

    char *tokens[200]; 
    int tokenCount = 0;

    char *token = strtok(input, " ");
    while (token) 
    {
        tokens[tokenCount++] = token;
        token = strtok(nullptr, " ");
    }

    set<string> palindromes;
    bool hasPalindrome = false;

    for (int i = 0; i < tokenCount; i++) 
    {
        if (strlen(tokens[i]) > 2 && isPalindrome(tokens[i])) 
        {
            palindromes.insert(tokens[i]);
            hasPalindrome = true;
        }
    }

    if (hasPalindrome) 
    {
        for (int i = 0; i < tokenCount; i++) 
        {
            cout << tokens[i] << " (доля гласных: " << vowelRatio(tokens[i]) << ")\n";
        }
    } 
    else 
    {
        set<string> transformedWords;

        for (int i = 0; i < tokenCount; i++) 
        {
            transformWord(tokens[i], transformed);
            transformedWords.insert(transformed);
        }

        for (const auto &w : transformedWords) 
        {
            cout << w << endl;
        }
    }

    return 0;
}