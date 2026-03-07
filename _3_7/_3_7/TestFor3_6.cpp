#include <deque>
#include <utility>
#include <iostream>
#include <cstring>

using namespace std;

#define N 505

typedef pair<int, int> PII;
int x[] = { 0, 0, 1, -1 };
int y[] = { 1, -1, 0, 0 };
int n, m, x1, _y, x2, y2;//y1在别的头文件中以函数的形式被定义过
char arr[N][N];
int road[N][N];

void bfs()
{
    memset(road, -1, sizeof(road));
    deque<PII> q;
    q.emplace_back(x1, _y);
    road[x1][_y] = 0;

    while (q.size())
    {
        auto cur = q.front(); q.pop_front();
        int cx = cur.first, cy = cur.second;
        //在第一个一定是最小了，可以退出——剪枝
        if (cx == x2 && cy == y2) return;

        for (int i = 0; i < 4; ++i)
        {
            int nx = cx + x[i], ny = cy + y[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            //提前求权值
            //int w = a[cx][cy] == a[nx][ny] ? 0 : 1;
            int w = 0;
            if (arr[cx][cy] != arr[nx][ny]) ++w;

            if (road[nx][ny] == -1)
            {
                road[nx][ny] = road[cx][cy] + w;

                //01BFS
                if (w) q.emplace_back(nx, ny);
                else q.emplace_front(nx, ny);
            }
            else if (road[nx][ny] > road[cx][cy] + w)
            {//松弛操作
                road[nx][ny] = road[cx][cy] + w;
            }
        }
    }
}

int main()
{
    while (cin >> n >> m)
    {
        if (!n) break;
        // for (int i = 1; i < n; ++i)//bushi 这是从0开始的
        //     for (int j = 1; j < m; ++j)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cin >> arr[i][j];
        cin >> x1 >> _y >> x2 >> y2;

        bfs();
        cout << road[x2][y2] << endl;
    }
    return 0;
}