#include <iostream>

using namespace std;

//经典dp——合唱队列（两个上升子区间）
const int N = 105;
int n;
int f1[N];
int f2[N];
int arr[N];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];

    f1[0] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < i; ++j)
            if (arr[i] > arr[j])
                f1[i] = max(f1[i], f1[j] + 1);

    f2[n + 1] = 0;
    for (int i = n; i > 0; --i)
        for (int j = n + 1; j > i; --j)
            if (arr[i] > arr[j])
                f2[i] = max(f2[i], f2[j] + 1);

    int result = 0;
    for (int i = 1; i <= n; ++i)
    {
        result = max(result, f1[i] + f2[i] - 1);
    }
    cout << n - result;

    return 0;
}

//经典dp2——最长公共子区间
#include <string>
const int N = 5050;

int f[N][N];
string s, t;

int main()
{
    while (cin >> s >> t)
    {
        for (int i = 0; i < s.size(); ++i)
        {
            for (int j = 0; j < t.size(); ++j)
            {
                if (s[i] == t[j])
                    f[i + 1][j + 1] = f[i][j] + 1;
                else
                    f[i + 1][j + 1] = max(f[i][j + 1], f[i + 1][j]);
            }
        }
        cout << f[s.size()][t.size()] << endl;
    }

    return 0;
}

//经典dp——修改字符串
const int N = 2007;
int f[N][N];
string a, b;
int main()
{
    cin >> a >> b;
    //注意初始化
    for (int i = 1; i <= b.size(); ++i)
        f[0][i] = i;
    for (int i = 1; i <= a.size(); ++i)
        f[i][0] = i;

    for (int i = 0; i < a.size(); ++i)
    {
        for (int j = 0; j < b.size(); ++j)
        {
            if (a[i] == b[j])
                f[i + 1][j + 1] = f[i][j];
            else                                      //注意还有在a[i]后面加上b[j],的情况
                f[i + 1][j + 1] = min(min(f[i][j + 1], f[i][j]), f[i + 1][j]) + 1;
        }
    }
    cout << f[a.size()][b.size()];
    return 0;
}

//01 背包—— 模板
//const int N = 1010;
//int w[N];
//int v[N];
//int f[N][N];//前i个物品 占用空间为j时能装下的最大价值
//int n, V;
//int main()
//{
//    cin >> n >> V;
//    for (int i = 1; i <= n; ++i)
//        cin >> v[i] >> w[i];
//
//    for (int i = 1; i <= n; ++i)
//    {
//        for (int j = 0; j <= V; ++j)
//        {
//            f[i][j] = f[i - 1][j];
//            if (j - v[i] >= 0)
//                f[i][j] = max(f[i][j], f[i - 1][j - v[i]] + w[i]);
//        }
//    }
//    cout << f[n][V] << endl;
//
//    memset(f, -0x3f, sizeof f);
//    f[0][0] = 0;
//    for (int i = 1; i <= n; ++i)
//    {
//        for (int j = 0; j <= V; ++j)
//        {
//            f[i][j] = f[i - 1][j];
//            if (j - v[i] >= 0)
//                f[i][j] = max(f[i][j], f[i - 1][j - v[i]] + w[i]);
//        }
//    }
//    //     cout<< f[n][V];
//    if (f[n][V] < 0) cout << "0";
//    else cout << f[n][V];
//    return 0;
//}
//空间优化版
int w[N];
int v[N];
int f[N];//前i个物品 占用空间为j时能装下的最大价值
int n, V;
//int main()
//{
//    cin >> n >> V;
//    for (int i = 1; i <= n; ++i)
//        cin >> v[i] >> w[i];
//
//    for (int i = 1; i <= n; ++i)
//    {
//        for (int j = V; j >= v[i]; --j)
//        {
//            f[j] = max(f[j], f[j - v[i]] + w[i]);
//        }
//    }
//    cout << f[V] << endl;
//
//    memset(f, -0x3f, sizeof f);
//    f[0] = 0;
//    for (int i = 1; i <= n; ++i)
//    {
//        for (int j = V; j >= v[i]; --j)
//        {
//            f[j] = max(f[j], f[j - v[i]] + w[i]);
//        }
//    }
//    //     cout<< f[n][V];
//    if (f[V] < 0) cout << "0";
//    else cout << f[V];
//    return 0;
//}

//终极版——要求装满背包，不就包含了背包能装的最大价值吗，不一定是满的而已
//我是天才
int main()
{
    cin >> n >> V;
    for (int i = 1; i <= n; ++i)
        cin >> v[i] >> w[i];

    memset(f, -0x3f, sizeof f);
    f[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = V; j >= v[i]; --j)
        {
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }

    int wmax = 0;
    for (int i = 1; i <= V; ++i)
        wmax = max(wmax, f[i]);
    cout << wmax << endl;
    if (f[V] < 0) cout << "0";
    else cout << f[V];
    return 0;
}

//01背包——采菜
const int N = 1050;

int T, m;
int t[N], w[N];
int f[N];

int main()
{
    cin >> T >> m;
    for (int i = 1; i <= m; ++i)
        cin >> t[i] >> w[i];

    // memset(f, -0x3f, sizeof f);
    memset(f, 0, sizeof f);
    // f[0] = 0;
    for (int i = 1; i <= m; ++i)
    {
        for (int j = T; j >= t[i]; --j)
        {
            f[j] = max(f[j], f[j - t[i]] + w[i]);
        }
    }
    cout << f[T];
    return 0;
}


//真题 遍历日期
int s[105];
const int _day[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int main()
{
    for (int i = 1; i <= 100; ++i)
        cin >> s[i];

    int result = 0;
    for (int m = 1; m <= 12; ++m)
    {
        for (int d = 1; d <= _day[m]; ++d)
        {
            int date[] = { 2, 0, 2, 3, m / 10, m % 10, d / 10, d % 10 };
            int t = 0;
            for (int i = 1; i <= 100; ++i)
            {
                if (t == 8)
                {
                    ++result;
                    break;
                }
                // cout<< date[t]<<":"<< s[i]<<endl;
                if (date[t] == s[i])
                    ++t;
            }
        }
    }

    cout << result << endl;
    // cout<< "235";

    return 0;
}

//蓝桥真题——该死的二分答案
#include <vector>

const int N = 1e9;
int n;
vector<int> a, b;

bool cmp1(int r)
{
    for (int i = 0; i < n; ++i)
    {
        if (a[i] / r > b[i])
            return false;
    }
    return true;
}

bool cmp2(int r)
{
    for (int i = 0; i < n; ++i)
    {
        if (a[i] / r < b[i])
            return false;
    }
    return true;
}

int main()
{
    cin >> n;
    a.resize(n);
    b.resize(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i] >> b[i];
        // cout<<a[i]<<b[i];
    }

    int l = 0, r = N;
    while (l < r)
    {
        // cout<<l<<":"<<r<<endl;
        int mid = (r - l) / 2 + l;
        if (cmp1(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l << " ";

    l = 0, r = N;
    while (l < r)
    {
        // cout<<l<<":"<<r<<endl;
        int mid = (r - l + 1) / 2 + l;
        if (cmp2(mid)) l = mid;
        else r = mid - 1;
    }
    cout << l;
    return 0;
}