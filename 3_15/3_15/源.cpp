#include <iostream>
#include <string.h>

using namespace std;

//floodfill问题——填涂颜色
#define N 35

int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
char a[N][N];
bool st[N][N];
int n;

void dfs(int i, int j)
{
    st[i][j] = true;

    for (int z = 0; z < 4; ++z)
    {
        int x = i + dx[z], y = j + dy[z];
        if (x >= 0 && x <= n + 1 && y >= 0 && y <= n + 1 && a[x][y] == '0' && !st[x][y])
        {
            dfs(x, y);
        }
    }
}

int main()
{
    cin >> n;
    memset(a, '0', sizeof(a));
    memset(st, false, sizeof(st));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> a[i][j];

    for (int i = 0; i <= n + 1; i += (n + 1))
        for (int j = 0; j <= n + 1; ++j)
            if (a[i][j] == '0' && st[i][j] == false)
                dfs(i, j);
    for (int j = 0; j <= n + 1; j += (n + 1))
        for (int i = 0; i <= n + 1; ++i)
            if (a[i][j] == '0' && st[i][j] == false)
                dfs(i, j);

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (a[i][j] == '1')
                cout << "1 ";
            else if (st[i][j])
                cout << "0 ";
            else
                cout << "2 ";
        }
        cout << endl;
    }


    return 0;
}