#include <iostream>

using namespace std;

//01背包——hard (%f的下标环回直接把能力值的1e5空间变为1000）
//                同时带来的是换回是遇到负数的下标转换
const int N = 2020;
const int MO = 1e8;

int n, f;
int w[N];
int cf[N][N];

int main()
{
    cin >> n >> f;
    for (int i = 1; i <= n; ++i)
        cin >> w[i];

    cf[0][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < f; ++j)
        {
            cf[i][j] = cf[i - 1][j] % MO;
            int tmp = j - (w[i] % f);
            if (tmp < 0)
                tmp += f;
            cf[i][j] += cf[i - 1][tmp] % MO;
            // cout<<nf[j]<<" ";
        }
    }
    cout << (cf[n][0] - 1) % MO;
    return 0;
}

//蓝桥真题——飞机起飞（写过）dfs（有点忘了）——dfs全排列
#include <string.h>
const int N = 15;

int T, n;
int pt[N], lt[N], l[N];
bool st[N];

bool dfs(int pos, int end)
{
    if (pos > n) return true;

    for (int i = 1; i <= n; ++i)
    {
        if (st[i]) continue;
        if (pt[i] + lt[i] < end) continue;

        st[i] = true;
        int newend = max(end, pt[i]) + l[i];
        if (dfs(pos + 1, newend)) return true;
        st[i] = false;
    }
    return false;
}
int main()
{
    cin >> T;
    while (T--)
    {
        memset(st, false, sizeof(st));
        cin >> n;
        for (int i = 1; i <= n; ++i)
            cin >> pt[i] >> lt[i] >> l[i];

        if (dfs(1, 0)) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}

//dfs——复习 组合数之和为素数
const int N = 25;

int n, k;
int x[N];
int result;
int path;

bool isprime(int c)
{
    if (c < 2) return false;
    for (int i = 2; i < c / i; ++i)
        if (c % i == 0) return false;
    return true;
}
void dfs(int c, int begin)
{
    if (c > k)
    {
        // cout<<c<<":"<<path<<endl;
        if (isprime(path)) ++result;
        return;
    }
    if (begin > n) return;

    for (int i = begin; i <= n; ++i)
    {
        path += x[i];
        dfs(c + 1, i + 1);
        path -= x[i];
    }
}

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        cin >> x[i];

    result = 0, path = 0;
    dfs(1, 1);
    cout << result;
    return 0;
}

//完全背包——模板——f[i][j - v[i]] = max(f[i-1][j-v[i]], f[i-1][j-2*v[i]]+w[i]……）
const int N = 1010;

int n, V;
int v[N], w[N];
int f[N][N];

int main()
{
    cin >> n >> V;
    for (int i = 1; i <= n; ++i)
        cin >> v[i] >> w[i];

    memset(f, -0x3f, sizeof f);
    f[0][0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= V; ++j)
        {
            f[i][j] = f[i - 1][j];
            if (j >= v[i])
                f[i][j] = max(f[i][j], f[i][j - v[i]] + w[i]);
        }
    }
    int maxw = 0;
    for (int i = 1; i <= V; ++i)
    {
        maxw = max(maxw, f[n][i]);
    }
    cout << maxw << endl;
    if (f[n][V] > 0)
        cout << f[n][V];
    else
        cout << "0";

    return 0;
}

//完全背包模板——空间优化版（从左至右更新就行）
int f[N];
int main()
{
    cin >> n >> V;
    for (int i = 1; i <= n; ++i)
        cin >> v[i] >> w[i];

    memset(f, -0x3f, sizeof f);
    f[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = v[i]; j <= V; ++j)
        {
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }
    int maxw = 0;
    for (int i = 1; i <= V; ++i)
    {
        maxw = max(maxw, f[i]);
    }
    cout << maxw << endl;
    if (f[V] > 0)
        cout << f[V];
    else
        cout << "0";

    return 0;
}

//完全背包——疯狂采药——必须空间优化
const int M = 1e4 + 10;
const int N = 1e7 + 10;

int T, m;
int t[M], w[M];
long long f[N];

int main()
{
    cin >> T >> m;
    for (int i = 1; i <= m; ++i)
        cin >> t[i] >> w[i];

    for (int i = 1; i <= m; ++i)
    {
        for (int j = t[i]; ; ++j)
        {
            if (j > T) break;
            f[j] = max(f[j], f[j - t[i]] + w[i]);
        }
    }
    cout << f[T];
    return 0;
}


//完全背包问题——至少购入问题——j < v[i]时合法, 在f[0]处，即f[max(0, j-v[i])]
const int H = 5e4 + 10;
const int N = 110;

int n, h;
int p[N], c[N];
int f[H];

int main()
{
    cin >> n >> h;
    for (int i = 1; i <= n; ++i)
        cin >> p[i] >> c[i];

    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= h; ++j)
        {
            f[j] = min(f[j], f[max(0, j - p[i])] + c[i]);
        }
    }
    cout << f[h];
    return 0;
}

//真题——线性dp
const int N = 1e5 + 10;

int n;
int a[N];
// int f[N];
int Mlen[10];

int preN(int a)
{
    int pre;
    while (a)
    {
        pre = a % 10;
        a /= 10;
    }
    return pre;
}
int lastN(int a)
{
    return a % 10;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    // f[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        Mlen[lastN(a[i])] = max(Mlen[preN(a[i])] + 1, Mlen[lastN(a[i])]);
    }

    int result = 0;
    for (int i = 1; i <= 9; ++i)
        result = max(result, Mlen[i]);

    cout << n - result;
    return 0;
}