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