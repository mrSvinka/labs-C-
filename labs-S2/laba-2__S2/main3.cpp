/*
Вам дано поле размерами NхM (2<=N,M<=100). В каждой клетке поля находятся символы:
‘.’ - можно пройти;
‘#’ - нельзя пройти;
‘S’ - начальная клетка;
‘E’ - конечная клетка;
Напишите алгоритм, который определит минимальное количество шагов для перемещения из начальной клетки в конечную. Если это сделать невозможно, выведите -1. Ходить во все соседние клетки, которые отмечены ‘.’ (в том числе и по диагонали).
*/



#include <iostream>
#include <queue>
using namespace std;

struct Node { int x, y, steps; }; //храним координаты и  кол-во шагов.

int minSteps(char grid[100][100], int n, int m) 
{
    Node start, end;
    bool foundS = false, foundE = false;

    // Поиск начальной и конечной точек
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            if (grid[i][j] == 'S') 
            {
                start = {i, j, 0};
                foundS = true;
            } else if (grid[i][j] == 'E') 
            {
                end = {i, j, 0};
                foundE = true;
            }
        }
    }
    if (!foundS || !foundE) return -1; // нет точки, возвращаем -1

    //посещенные клетки
    bool visited[100][100] = {false};
    queue<Node> q; //поиска в ширину
    q.push(start); //старт
    visited[start.x][start.y] = true; //стартовали
//направления движения
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    while (!q.empty()) 
    {
        Node curr = q.front(); //взяли клетку
        q.pop(); //убрали из очереди на праверку

        if (curr.x == end.x && curr.y == end.y)
            return curr.steps; //финиш

        for (int i = 0; i < 8; i++) 
        {   //точка следом
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && //держим себя в рамках
                !visited[nx][ny] && grid[nx][ny] != '#') //не тыкаемся в стены
                {
                visited[nx][ny] = true;
                q.push({nx, ny, curr.steps + 1}); //очередь
            }
        }
    }
    return -1;
}

int main() 
{
    int n, m;
    char grid[100][100];

    cout << "Введите размеры поля (N M): ";
    cin >> n >> m;
    cout << "Введите поле:" << endl;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> grid[i][j];

    cout << "Минимум шагов: " << minSteps(grid, n, m) << endl;
    return 0;
}