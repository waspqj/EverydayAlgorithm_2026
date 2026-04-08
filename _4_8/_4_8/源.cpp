#include <iostream>
#include <string.h>

using namespace std;


//线性dp，动态规划——预备
const int N = 1e3 + 5;
int n;
int arr[N][N];
int res[N];
int main()
{
    memset(arr, 0, sizeof(arr));
    cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            cin >> arr[i][j];

    for (int i = 1; i <= n; ++i)
        for (int j = i; j > 0; --j)
            res[j] = max(res[j], res[j - 1]) + arr[i][j];

    int result = -1e10;
    for (int i = 1; i <= n; ++i)
    {
        result = max(result, res[i]);
    }
    cout << result;
    return 0;
}

//基础线性dp
const int N = 1e5 + 10;

int arr[N];
int n, k;
int main()
{
    cin >> n >> k;
    memset(arr, 0, sizeof(arr));
    arr[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i - 1; j >= i - k && j >= 0; --j)
        {
            arr[i] += arr[j];
            arr[i] %= (100003);
        }
    }
    cout << arr[n];

    return 0;
}

//线性dp——解决经典最大子段问题
const int N = 2e5 + 10;

int arr[N];
int sum[N];
int n;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];

    sum[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        sum[i] = max(sum[i - 1] + arr[i], arr[i]);
    }

    int result = -1e4;
    for (int i = 1; i <= n; ++i)
    {
        result = max(sum[i], result);
    }
    cout << result;
    return 0;
}

//路径dp
const int N = 505;

int n, m;
int arr[N][N];
int road[N][N];

int main()
{
    cin >> n >> m;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
        {
            if (i && j)
                cin >> arr[i][j];
            else
                road[i][j] = 3e7;
        }
    road[1][0] = 0;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            road[i][j] = min(road[i - 1][j], road[i][j - 1]) + arr[i][j];
        }
    }

    cout << road[n][m];
    return 0;
}

//路径dp——迷雾迷宫
const int N = 3010;

char arr[N][N];
int f[N][N];
int m, n;
int main()
{
    cin >> m >> n;
    for (int i = 0; i <= m; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            if (i && j)
                cin >> arr[i][j];
            else
                f[i][j] = 0;
        }
    }
    f[m][0] = 1;

    for (int i = m; i > 0; --i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (arr[i][j] == '1')
                f[i][j] = 0;
            else
                f[i][j] = (f[i + 1][j] + f[i][j - 1]) % 2333;
        }
    }
    cout << f[1][n];
    return 0;
}

//经典线性dp——最长上升子序列
const int N = 5050;

int n;
int arr[N];
int f[N];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];

    f[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (arr[i] > arr[j])
                f[i] = max(f[i], f[j] + 1);
        }
    }

    int result = 0;
    for (int i = 1; i <= n; ++i)
    {
        result = max(result, f[i]);
    }
    cout << result;
    return 0;
}


//经典线性dp——最长上升子序列（二）——贪心+二分
int arr[N];
int f[N];//长度为i的上升子序列的最小末尾
int n, len;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> arr[i];
        f[i] = 1e6;
    }

    len = 0;
    for (int i = 1; i <= n; ++i)
    {
        int l = 0, r = len;
        while (l < r)
        {
            int mid = (r - l + 1) / 2 + l;
            if (f[mid] < arr[i]) l = mid;
            else r = mid - 1;
        }
        f[l + 1] = min(f[l + 1], arr[i]);
        if (l == len) ++len;
    }

    cout << len;
    return 0;
}