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
using namespace std;

#define N_MAX 100
#define M_MAX 100
using ushort = unsigned short;

struct Labyrinth 
{
    char field[N_MAX][M_MAX];
    int steps[N_MAX][M_MAX];
    ushort N, M;
    bool end_found = false;

    Labyrinth(ushort n, ushort m) : N(n), M(m) 
    {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                steps[i][j] = INT_MAX;
    }

    void search(ushort i, ushort j, int step) 
    {
        if (i >= N || j >= M || field[i][j] == '#' || steps[i][j] <= step)
            return;
        
        steps[i][j] = step;
        
        if (field[i][j] == 'E') 
        {
            end_found = true;
            return;
        }

        const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int k = 0; k < 8; ++k) 
        {
            int ni = i + dx[k];
            int nj = j + dy[k];
            if (ni >= 0 && ni < N && nj >= 0 && nj < M)
                search(ni, nj, step + 1);
        }
    }

    int find_shortest_path() 
    {
        ushort start_i = 0, start_j = 0;
        bool found = false;
        
        for (ushort i = 0; i < N; ++i)
            for (ushort j = 0; j < M; ++j)
                if (field[i][j] == 'S') 
                {
                    start_i = i;
                    start_j = j;
                    found = true;
                }
        
        if (!found) return -1;
        
        search(start_i, start_j, 0);
        
        for (ushort i = 0; i < N; ++i)
            for (ushort j = 0; j < M; ++j)
                if (field[i][j] == 'E')
                    return steps[i][j] == INT_MAX ? -1 : steps[i][j];
        
        return -1;
    }
};

int main() 
{
    ushort n, m;
    cout << "Введите размеры поля (N M): ";
    cin >> n >> m;
    
    Labyrinth lab(n, m);
    cout << "Введите поле:" << endl;
    
    for (ushort i = 0; i < n; ++i)
        for (ushort j = 0; j < m; ++j)
            cin >> lab.field[i][j];
    
    int result = lab.find_shortest_path();
    cout << "Минимум шагов: " << result << endl;
    
    return 0;
}