#include <iostream>


//2.4.1 记忆化搜索——function
using namespace std;
#define N 25 
typedef long long LL;

LL a, b, c;
LL mymap[N][N][N];

LL dfs(LL a, LL b, LL c)
{
    if (a <= 0 || b <= 0 || c <= 0) return 1;
    else if (a > 20 || b > 20 || c > 20) return dfs(20, 20, 20);
    else if (mymap[a][b][c]) return mymap[a][b][c];
    else if (a < b && b < c)
    {
        mymap[a][b][c] = dfs(a, b, c - 1) + dfs(a, b - 1, c - 1) - dfs(a, b - 1, c);
        return mymap[a][b][c];
    }
    else
    {
        mymap[a][b][c] = dfs(a - 1, b, c) + dfs(a - 1, b - 1, c) + dfs(a - 1, b, c - 1) - dfs(a - 1, b - 1, c - 1);
        return mymap[a][b][c];
    }
}

int main()
{
    while (cin >> a >> b >> c)
    {
        if (a == -1 && b == -1 && c == -1)
            break;
        printf("w(%lld, %lld, %lld) = %lld\n", a, b, c, dfs(a, b, c));
    }
    return 0;
}


//2.4.2 记忆化搜索——天下第一
#include <iostream>

using namespace std;

#define N 10024
int x, y, t, p;
char cur[N][N];
//int cur[N][N];空间不够就不要硬用int了

char dfs(int x, int y)
{
    if (x == 0 && y != 0)
        return '1';
    if (y == 0)
        return '2';

    if (cur[x][y])
        return cur[x][y];
    else {
        cur[x][y] = '3';
        cur[x][y] = dfs((x + y) % p, (x + y + y) % p);
        return cur[x][y];
    }
}

int main()
{
    cin >> t >> p;
    while (t--)
    {
        cin >> x >> y;
        if (dfs(x, y) == '3') printf("error\n");
        else cout << dfs(x, y) << endl;
    }
    return 0;
}