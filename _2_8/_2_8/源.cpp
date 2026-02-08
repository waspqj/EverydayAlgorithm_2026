#include <iostream>

using namespace std;

//dfs——数独
int nums[10][10];
bool row[10][10] = { false };
bool col[10][10] = { false };
bool nine[3][3][10] = { false };

bool dfs(int x, int y)
{
    if (x >= 9 && y >= 9)
        return true;

    if (nums[x][y])
    {
        bool flag = false;
        if (y < 8)
            flag = dfs(x, y + 1);
        else if (x < 8)
            flag = dfs(x + 1, 0);
        else
            flag = dfs(9, 9);
        return flag;
    }

    for (int n = 1; n < 10; ++n)
    {
        if (row[x][n]) continue;
        if (col[y][n]) continue;
        if (nine[x / 3][y / 3][n]) continue;

        nums[x][y] = n;
        row[x][n] = true;
        col[y][n] = true;
        nine[x / 3][y / 3][n] = true;

        bool flag = false;
        if (y < 8)
            flag = dfs(x, y + 1);
        else if (x < 8)
            flag = dfs(x + 1, 0);
        else
            flag = dfs(9, 9);
        if (flag)
            return flag;

        nums[x][y] = 0;
        row[x][n] = false;
        col[y][n] = false;
        nine[x / 3][y / 3][n] = false;
    }
    return false;
}

int main()
{
    for (int x = 0; x < 9; ++x)
    {
        for (int y = 0; y < 9; ++y)
        {
            int n; cin >> n;
            nums[x][y] = n;
            row[x][n] = true;
            col[y][n] = true;
            nine[x / 3][y / 3][n] = true;
        }
    }
    if (dfs(0, 0))
    {
        for (int x = 0; x < 9; ++x)
        {
            for (int y = 0; y < 9; ++y)
                cout << nums[x][y] << " ";
            cout << endl;
        }
    }

    return 0;
}
//这样处理好点
bool dfs(int x, int y)
{
    if (y == 9)
    {
        ++x;
        y = 0;
    }
    if (x == 9)
        return true;

    if (nums[x][y])
    {
        return dfs(x, y + 1);
    }

    for (int n = 1; n < 10; ++n)
    {
        if (row[x][n]) continue;
        if (col[y][n]) continue;
        if (nine[x / 3][y / 3][n]) continue;

        nums[x][y] = n;
        row[x][n] = true;
        col[y][n] = true;
        nine[x / 3][y / 3][n] = true;

        if (dfs(x, y + 1)) return true;

        nums[x][y] = 0;
        row[x][n] = false;
        col[y][n] = false;
        nine[x / 3][y / 3][n] = false;
    }
    return false;
}