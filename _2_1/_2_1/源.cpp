#include <iostream>

using namespace std;



//1.12.4分治 or 递归——地毯填补问题（恶心的一批）

void dfs(int a, int b, int x, int y, int len)
{
    if (len <= 1) return;
    len /= 2;
    if (x < a + len && y < b + len)
    {
        cout << a + len << " " << b + len << " " << "1" << endl;
        dfs(a, b, x, y, len);
        dfs(a + len, b, a + len, b + len - 1, len);
        dfs(a, b + len, a + len - 1, b + len, len);
        dfs(a + len, b + len, a + len, b + len, len);
    }
    else if (x < a + len && y >= b + len)
    {
        cout << a + len << " " << b + len - 1 << " " << "2" << endl;
        dfs(a, b, a + len - 1, b + len - 1, len);
        dfs(a + len, b, a + len, b + len - 1, len);
        dfs(a, b + len, x, y, len);
        dfs(a + len, b + len, a + len, b + len, len);
    }
    else if (x >= a + len && y < b + len)
    {
        cout << a + len - 1 << " " << b + len << " " << "3" << endl;
        dfs(a, b, a + len - 1, b + len - 1, len);
        dfs(a + len, b, x, y, len);
        dfs(a, b + len, a + len - 1, b + len, len);
        dfs(a + len, b + len, a + len, b + len, len);
    }
    else if (x >= a + len && y >= b + len)
    {
        cout << a + len - 1 << " " << b + len - 1 << " " << "4" << endl;
        dfs(a, b, a + len - 1, b + len - 1, len);
        dfs(a + len, b, a + len, b + len - 1, len);
        dfs(a, b + len, a + len - 1, b + len, len);
        dfs(a + len, b + len, x, y, len);
    }
}

int main()
{
    int k, x, y;
    cin >> k >> x >> y;
    k = (1 << k);

    dfs(1, 1, x, y, k);
    return 0;
}