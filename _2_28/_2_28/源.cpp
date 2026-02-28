#include <iostream>
#include <queue>
#include <cstring>
#include <utility>

using namespace std;

#define N 1024

//2.6.2 多源bfs+二分答案——刺杀大使
typedef pair<int, int> PII;
int x[] = { 0, 0, -1, 1 };
int y[] = { 1, -1, 0, 0 };
int n, m;
int a[N][N];
bool road[N][N];

bool bfs(int mid)
{
    queue<PII> q;
    for (int i = 1; i <= m; ++i)
    {
        q.push({ 1, i });
        road[1][i] = true;
    }
    while (q.size())
    {
        auto cur = q.front(); q.pop();
        int cx = cur.first, cy = cur.second;
        for (int i = 0; i < 4; ++i)
        {
            int nx = cx + x[i], ny = cy + y[i];
            //越界剪枝
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;

            //arrived
            if (nx == n) return true;

            //路径重复剪枝
            if (road[nx][ny]) continue;
            //超出限定mid——剪枝
            if (a[nx][ny] > mid) continue;

            q.push({ nx,ny });
            road[nx][ny] = true;
        }
    }
    return false;
}

int main()
{
    cin >> n >> m;

    int l = 0, r = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> a[i][j];
            r = max(r, a[i][j]);
        }
    }

    while (l < r)
    {
        memset(road, false, sizeof(road));
        int mid = (l + r) / 2;
        if (!bfs(mid)) l = mid + 1;
        else r = mid;
    }
    cout << l;
    return 0;
}