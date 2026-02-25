#include <iostream>

using namespace std;


//2.4.3 记忆化搜索——滑雪
#define N 105
int x[] = { 0, 0, +1, -1 };
int y[] = { +1, -1, 0, 0 };
int row, col, result;
int arr[N][N];
int road[N][N];

int dfs(int r, int c)
{
    //可行性剪枝——越界
    if (r > row || r < 1 || c > col || c < 1) return 0;
    //记忆化搜索——剪枝
    if (road[r][c]) return road[r][c];

    int ret = 0;
    for (int i = 0; i < 4; ++i)
    {   //剪枝——高度差
        if (arr[r][c] <= arr[r + x[i]][c + y[i]]) continue;
        ret = max(ret, dfs(r + x[i], c + y[i]));
    }
    road[r][c] = ret + 1;
    return ret + 1;
}

int main()
{
    cin >> row >> col;
    for (int i = 1; i <= row; ++i)
        for (int j = 1; j <= col; ++j)
            cin >> arr[i][j];

    result = 0;
    for (int i = 1; i <= row; ++i)
        for (int j = 1; j <= col; ++j)
            result = max(result, dfs(i, j));

    cout << result;
    return 0;
}

#include <queue>
#include <utility>
#include <cstring>


//2.5.1 BFS——马的遍历（马走日）
#define N 405

typedef pair<int, int> PII;

int r[] = { 1, -1, 1, -1, 2, -2, 2, -2 };
int c[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
int arr[N][N];
int n, m, X, Y;

void bfs()
{
    memset(arr, -1, sizeof(arr));
    queue <PII> q;
    q.push({ X, Y });
    arr[X][Y] = 0;

    while (q.size())
    {
        auto cur = q.front();
        q.pop();
        int x = cur.first, y = cur.second;

        for (int i = 0; i < 8; ++i)
        {
            int nx = x + r[i], ny = y + c[i];
            //越界剪枝
            if (nx > n || nx < 1 || ny > m || ny < 1) continue;
            //访问过的剪枝
            if (arr[nx][ny] != -1) continue;
            arr[nx][ny] = arr[x][y] + 1;
            q.push({ nx, ny });
        }
    }
}

int main()
{
    cin >> n >> m >> X >> Y;

    bfs();

    for (int x = 1; x <= n; ++x)
    {
        for (int y = 1; y <= m; ++y)
            cout << arr[x][y] << " ";
        cout << endl;
    }

    return 0;
}