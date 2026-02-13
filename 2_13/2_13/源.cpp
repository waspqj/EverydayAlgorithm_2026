#include <iostream>

using namespace std;


//2.3.1   数的划分——剪枝与优化
int n, k;
int path;
int ret;

void dfs(int pos, int begin)
{
    if (pos > k)
    {
        if (path == n) ++ret;
        return;
    }
    //可行性剪枝——这个位置还是太深了
    // if(path + (k - pos + 1) * i > n) return;//剪枝：前面太大后面没有可能性

    for (int i = begin; i < n; ++i)
    {
        if (path + (k - pos + 1) * i > n) return;//剪枝：前面太大后面没有可能性
        path += i;
        dfs(pos + 1, i);
        path -= i;
    }
}

int main()
{
    cin >> n >> k;
    ret = path = 0;
    dfs(1, 1);
    cout << ret;
    return 0;
}

//2.3.2   小猫爬山——剪枝与优化
#include <vector>
#include <algorithm>

using namespace std;

int n, w;
vector<int> cats;//小猫重量
vector<int> culars;//缆车剩余承重
int ret;

void dfs(int pos, int cnt)
{
    if (pos >= n)
    {
        ret = min(ret, cnt);
        return;
    }

    for (int i = 0; i <= cnt; ++i)
    {
        if (cats[pos] > culars[i])//可行性剪枝 
            continue;
        culars[i] -= cats[pos];
        dfs(pos + 1, cnt);
        culars[i] += cats[pos];
    }

    if (cnt + 1 >= ret) return;//最优性剪枝
    culars[cnt + 1] -= cats[pos];
    dfs(pos + 1, cnt + 1);
    culars[cnt + 1] += cats[pos];
}

int main()
{
    cin >> n >> w;
    cats.resize(n);
    culars.resize(n, w);
    for (auto& c : cats) cin >> c;
    //优化搜索顺序
    sort(cats.begin(), cats.end(), greater<int>());

    ret = n;
    dfs(0, 0);
    cout << ret + 1;
    return 0;
}