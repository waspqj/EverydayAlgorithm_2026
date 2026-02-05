#include <iostream>
#include <vector>

using namespace std;


//2.2.2 飞机降落

//1>并不是这个方案下的最好写法，可以在dfs的时候直接判断是否能降落
int T, n;
struct plane
{
    int t, d, l;
}a[15];
vector<bool> ft;
vector<int> path;

bool YorN()
{
    int prend = 0, cur = 1;
    while (cur <= n)
    {
        int ti = a[path[cur]].t;
        int di = a[path[cur]].d;
        int li = a[path[cur]].l;

        if (prend <= ti)
        {
            prend = ti + li;
        }
        else if (prend <= ti + di)
        {
            prend = prend + li;
        }
        else {
            return false;
        }
        ++cur;
    }
    return true;
}

bool dfs(int pos)
{
    if (pos > n)
    {
        return YorN();
    }

    for (int i = 1; i <= n; ++i)
    {
        if (ft[i]) continue;//        end1 > t2+d2
        if (pos > 1 && a[path[pos - 1]].t + a[path[pos - 1]].l > a[i].t + a[i].d)
            continue;//剪枝
        path[pos] = i;
        ft[i] = true;
        if (dfs(pos + 1)) return true;
        // path.pop_back();
        ft[i] = false;
    }
    return false;
}

int main()
{
    cin >> T;
    while (T--)
    {
        cin >> n;
        path.resize(n + 1);
        ft.resize(n + 1, false);//   !!!!!!!错在此处，resize并不能格式化所有数据，可以在这之前用clear()
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i].t >> a[i].d >> a[i].l;
        }
        if (dfs(1)) cout << "YES" << endl;
        else cout << "NO" << endl;

        // path.resize(0);
    }
    return 0;
}
//2》课件写法
#include <cstring>

using namespace std;

int T, n;
struct plane
{
    int t, d, l;
}a[15];
bool ft[15];

bool dfs(int pos, int end)
{
    if (pos > n)
    {
        return true;
    }
    for (int i = 1; i <= n; ++i)
    {
        if (ft[i]) continue;//        end1 > t2+d2
        if (end > a[i].t + a[i].d) continue;//剪枝
        int newend = max(end, a[i].t) + a[i].l;

        ft[i] = true;
        if (dfs(pos + 1, newend)) return true;
        ft[i] = false;
    }
    return false;
}

int main()
{
    cin >> T;
    while (T--)
    {
        cin >> n;
        memset(ft, 0, sizeof ft);
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i].t >> a[i].d >> a[i].l;
        }
        if (dfs(1, 0)) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}

//2.2.3 八皇后——dfs

int n, sum = 0;
vector<int> path;
// vector<bool> ct;//记录棋子是否已在棋盘上了
vector<bool> col, diag, anti_diag;//记录列，正反对角线是否不能用

void dfs(int row)
{
    if (row > n)
    {
        if (++sum <= 3)
        {
            for (auto p : path) cout << p << " ";
            cout << endl;
        }
        return;
    }

    for (int i = 1; i <= n; ++i)
    {
        if (col[i]) continue;//这列有人了
        if (diag[row + i]) continue;//同理
        // if(anti_diag[i - row]) continue;//注意这里i-row是会<0的，所以向左平移——映射
        if (anti_diag[i - row + n]) continue;//同理

        path.push_back(i);
        col[i] = true;
        diag[row + i] = true;
        anti_diag[i - row + n] = true;
        dfs(row + 1);
        path.pop_back();
        col[i] = false;
        diag[row + i] = false;
        anti_diag[i - row + n] = false;
    }
}
int main()
{
    cin >> n;

    col.resize(n + 1, false);
    diag.resize(n * 2 + 1, false);
    anti_diag.resize(n * 2 + 1, false);

    dfs(1);
    cout << sum << endl;
    return 0;
}

