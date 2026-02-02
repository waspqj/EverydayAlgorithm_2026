#include<iostream>
#include<string>

using namespace std;

//2.1.1 递归dfs——枚举子集
int n;
string result;

void dfs(int x)
{
    if (x > n)
    {
        cout << result << endl;
        return;
    }
    //不选
    result += 'N';
    dfs(x + 1);
    result.pop_back();

    //选
    result += 'Y';
    dfs(x + 1);
    result.pop_back();
}

int main()
{
    cin >> n;
    dfs(1);
    return 0;
}

//2.1.2 组合型枚举
#include <vector>

int n, m;
vector<int> path;

void dfs(int i, int x)
{
    if (i > m)
    {
        for (auto p : path)
            cout << p << " ";
        cout << endl;
        return;
    }

    for (int j = x; j <= n; ++j)
    {
        path.push_back(j);
        dfs(i + 1, j + 1);
        path.pop_back();
    }
}

int main()
{
    cin >> n >> m;

    dfs(1, 1);
    return 0;
}