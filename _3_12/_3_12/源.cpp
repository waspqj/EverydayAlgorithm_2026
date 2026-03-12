#include <iostream>
#include <utility>
#include <queue>
#include <string.h>

using namespace std;

//2.8.1foolfill问题——lake counting

#define N 105

typedef pair<int, int> PII;
int dx[] = { 0,0,1,-1,-1,1,-1,1 };
int dy[] = { 1,-1,0,0,1,1,-1,-1 };
char a[N][N];
bool road[N][N];
int n, m, cnt;

void bfs(int i, int j)
{
    // if(road[i][j]) return;
    // if(a[i][j] == '.') return;
    queue<PII> q;
    q.push({ i, j });
    road[i][j] = true;

    // cout<<"I'm "<<i << " "<<endl;
    while (q.size())
    {
        auto cur = q.front(); q.pop();
        int x = cur.first, y = cur.second;
        for (int z = 0; z < 8; ++z)
        {
            int nx = x + dx[z], ny = y + dy[z];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && a[nx][ny] == 'W' && !road[nx][ny])
            {
                // cout << nx << ny<<endl;
                q.push({ nx, ny });
                road[nx][ny] = true;
            }
        }
    }
    cnt++;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> a[i][j];

    cnt = 0;
    memset(road, false, sizeof(road));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (a[i][j] == 'W' && !road[i][j])
                bfs(i, j);

    cout << cnt;
    return 0;
}