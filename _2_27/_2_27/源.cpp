#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

#define N 1000000

int T, x, y;
int road[N];

void bfs()
{
    queue<int> q;
    q.push(x);
    road[x] = 0;

    int flag = 0;
    while (q.size())
    {
        int cur = q.front(); q.pop();
        for (int i = 0; i < 3; i++)
        {
            int next;
            if (i == 0) next = cur + 1;
            else if (i == 1) next = cur - 1;
            else if (i == 2) next = cur << 1;
            //重复性剪枝
            if (road[next] != -1) continue;
            //抓到牛牛
            if (next == y)
            {
                cout << road[cur] + 1 << endl;
                flag = 1;
                break;
            }
            road[next] = road[cur] + 1;
            q.push(next);
        }
        if (flag) break;
    }
}
int main()
{
    cin >> T;

    while (T--)
    {
        cin >> x >> y;
        memset(road, -1, ((y << 1) + 10) * sizeof(int));
        bfs();
    }

    return 0;
}

#include <string>
#include <unordered_map>


//2.5.4 bfs——八数码难题
int x[] = { 0, 0, 1, -1 };
int y[] = { 1, -1, 0, 0 };
string start;
unordered_map<string, int> road;

void bfs()
{
    queue<string> q;
    q.push(start);
    road[start] = 0;
    string success = "123804765";
    if (start == success) { cout << '0'; return; }

    int flag = 0;
    while (q.size())
    {
        auto cur = q.front(); q.pop();
        int cx, cy;
        for (int i = 0; i < 9; ++i)
            if (cur[i] == '0')
                cx = i / 3, cy = i % 3;
        for (int i = 0; i < 4; ++i)
        {
            int nx = cx + x[i], ny = cy + y[i];
            //越界剪枝
            if (nx > 2 || nx < 0 || ny > 2 || ny < 0) continue;
            //二维坐标转一维坐标
            int ni = nx * 3 + ny, ci = cx * 3 + cy;
            //交换位置，生成另一种状态
            string next = cur; next[ci] = cur[ni]; next[ni] = cur[ci];
            //重复剪枝
            if (road.count(next)) continue;

            road[next] = road[cur] + 1;
            //成功
            if (next == success)
            {
                flag = 1;
                printf("%d", road[next]);
                break;
            }
            q.push(next);
        }
        if (flag) break;
    }
}

int main()
{
    cin >> start;

    bfs();
    return 0;
}


//2.6.1 多源bfs——矩阵距离

#define N 1005

typedef pair<int, int> PII;
int x[] = { 0, 0, 1, -1 };
int y[] = { 1, -1, 0, 0 };
int n, m;
char A[N][N];
int B[N][N];


void bfs()
{
    queue<PII> q;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (A[i][j] == '1')
            {
                q.push({ i, j });
                B[i][j] = 0;
            }

    while (q.size())
    {
        auto cur = q.front(); q.pop();
        int cx = cur.first, cy = cur.second;
        for (int i = 0; i < 4; ++i)
        {
            int nx = cx + x[i], ny = cy + y[i];
            //越界剪枝
            if (nx > n || nx < 1 || ny > m || ny < 1) continue;
            //对‘1’剪枝
            if (A[nx][ny] == '1') continue;
            //重复性剪枝
            if (B[nx][ny]) continue;

            B[nx][ny] = B[cx][cy] + 1;
            q.push({ nx,ny });
        }
    }
}

int main()
{
    cin >> n >> m;

    char c;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            //             scanf("%c", &c);scanf不会跳过空格‘\0’
            //             A[i][j] = c;
            cin >> A[i][j]
        }

    bfs();

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j) printf("%d ", B[i][j]);
        printf("\n");
    }

    return 0;
}