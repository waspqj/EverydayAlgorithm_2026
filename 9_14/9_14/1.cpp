#include <iostream>
#include <vector>
using namespace std;

// 动态规划.4 解码方式
int numDecodings(string s)
{
    int n = s.size();
    // 表示到i位置一共有多少解码方式
    vector<int> dp(n + 5, 0);
    // 初始化
    dp[0] = (s[0] - '0') ? 1 : 0;
    if (n == 1 || dp[0] == 0) return dp[0];
    dp[1] += (s[1] == '0') ? 0 : 1;
    dp[1] += ((s[0] - '0') * 10 + s[1] - '0') > 26 ? 0 : 1;
    if (n == 2) return dp[1];
    // 动态推导
    for (int i = 2; i < n; ++i)
    {
        // 第i位单独解码
        dp[i] += (s[i] == '0') ? 0 : dp[i - 1];
        // 与i - 1共同解码时
        dp[i] += ((s[i - 1] - '0') * 10 + s[i] - '0' > 26 || s[i - 1] == '0') ? 0 : dp[i - 2];
    }
    return dp[n - 1];
}

// 动态规划.5 不同路径
int uniquePaths(int m, int n)
{
    // 移动到(i, j) 位置有多少条路径
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 1));
    // 第一行和第一列都初始化为1了
    for (int i = 1; i < m; ++i)
    {
        for (int j = 1; j < n; ++j)
        {
            dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
        }
    }
    return dp[m - 1][n - 1];
}

// 动态规划.6 不同路径(2
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
{
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    // 初始化第一列第一行,一直为1,直到遇到障碍,一直为0
    if (obstacleGrid[0][0]) return 0;
    for (int i = 0; i < m; ++i)
    {
        if (!obstacleGrid[i][0]) dp[i][0] = 1;
        else break;
    }
    for (int j = 1; j < n; ++j)
    {
        if (!obstacleGrid[0][j]) dp[0][j] = 1;
        else break;
    }

    for (int i = 1; i < m; ++i)
    {
        for (int j = 1; j < n; ++j)
        {
            if (obstacleGrid[i][j]) continue;
            dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
        }
    }
    return dp[m - 1][n - 1];
}