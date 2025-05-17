/*
Вам дано поле размерами NхM (2<=N,M<=100). В каждой клетке поля находятся символы:
‘.’ - можно пройти;
‘#’ - нельзя пройти;
‘S’ - начальная клетка;
‘E’ - конечная клетка;
Напишите алгоритм, который определит минимальное количество шагов для перемещения из начальной клетки в конечную. Если это сделать невозможно, выведите -1. Ходить во все соседние клетки, которые отмечены ‘.’ (в том числе и по диагонали).
*/


#include <iostream>
#include <climits>
#define N_MAX 100
#define M_MAX 100
using namespace std;


struct Labyrinth 
{    // хроним данные
    char field[N_MAX][M_MAX];
    int steps[N_MAX][M_MAX]; //мин шаги
    int N, M;  

    Labyrinth(int n, int m) : N(n), M(m) 
    {  // нициализирует размер
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < M; ++j)
                steps[i][j] = INT_MAX;
    }
    

    //поиска пути
    void search(int i, int j, int step) 
    {   // Проверка выхода за границы лабиринта
        if(i < 0 || i >= N || j < 0 || j >= M) return;
        // слишком длинные и не верные пути
        if(steps[i][j] <= step || field[i][j] == '#') return;
        // Запись текущего количества шагов
        steps[i][j] = step;
        // Если достигли выхода
        if(field[i][j] == 'E') return;

        // направления
        search(i+1, j,   step+1);
        search(i-1, j,   step+1);
        search(i,   j+1, step+1);
        search(i,   j-1, step+1);
        search(i+1, j+1, step+1);
        search(i+1, j-1, step+1);
        search(i-1, j+1, step+1);
        search(i-1, j-1, step+1);
    }
};



int main() 
{
    int n, m;
    cout << "Введите размеры (N M): ";
    cin >> n >> m;
    

    Labyrinth lab(n, m);
    

    cout << "Введите лабиринт:\n";
    int start_i = -1, start_j = -1;
    for(int i = 0; i < n; ++i) 
    {
        for(int j = 0; j < m; ++j) 
        {
            cin >> lab.field[i][j];
            if(lab.field[i][j] == 'S') 
            {
                start_i = i;
                start_j = j;
            }
        }
    }


    // Запуск поиска из стартовой позиции
    lab.search(start_i, start_j, 0);
    
    // Поиск минимального пути до E
    int min_steps = INT_MAX;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            if(lab.field[i][j] == 'E' && lab.steps[i][j] < min_steps)
                min_steps = lab.steps[i][j];
    
    cout << "Результат: " << (min_steps != INT_MAX ? min_steps : -1) << endl;
    
    return 0;
}