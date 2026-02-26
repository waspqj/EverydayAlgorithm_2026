#include <iostream>
#include <queue>
#include <utility>
#include <cstring>

using namespace std;


//2.5.2 kotori和他的迷宫
#define N 35

typedef pair<int, int> PII;
int x[] = { 0, 0, -1, 1 };
int y[] = { 1, -1, 0, 0 };
int n, m, X, Y, cnt, minr;
char maze[N][N];
int road[N][N];

void bfs()
{
    memset(road, -1, sizeof(road));
    queue<PII> q;
    q.push({ X, Y });
    road[X][Y] = 0;
    minr = -1, cnt = 0;

    while (q.size())
    {
        auto cur = q.front(); q.pop();
        int cx = cur.first, cy = cur.second;
        for (int i = 0; i < 4; ++i)
        {
            int nx = cx + x[i], ny = cy + y[i];
            //越界剪枝
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            //撞墙剪枝
            if (maze[nx][ny] == '*') continue;
            //重复性剪枝
            if (road[nx][ny] != -1) continue;
            //             if(maze[nx][ny] != 'e' && road[nx][ny] != -1) continue;

            road[nx][ny] = road[cx][cy] + 1;
            if (maze[nx][ny] == 'e')
            {
                if (minr == -1)
                    minr = road[nx][ny];
                cnt++;
            }
            else {
                q.push({ nx, ny });
            }
        }
    }
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            cin >> maze[i][j];
            if (maze[i][j] == 'k')
                X = i, Y = j;
        }

    bfs();
    if (cnt)
        cout << cnt << " " << minr;
    else cout << "-1";
    return 0;
}

//