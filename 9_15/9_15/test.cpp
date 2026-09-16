#include <iostream>
#include <vector>

using namespace std;

// 动态规划.7 礼物的最大价值

int jewelleryValue(vector<vector<int>>& frame)
{
    int m = frame.size(), n = frame[0].size();
    // dp[x][y] 表示到达（x， y）位置获得珠宝最高价值
    vector<vector<int>> dp(m, vector<int>(n, 0));
    // 初始化第一行，第一列
    dp[0][0] = frame[0][0];
    for (int i = 1; i < m; ++i)
        dp[i][0] = dp[i - 1][0] + frame[i][0];
    for (int j = 1; j < n; ++j)
        dp[0][j] = dp[0][j - 1] + frame[0][j];
    // 动态推导
    for (int i = 1; i < m; ++i)
    {
        for (int j = 1; j < n; ++j)
        {
            dp[i][j] = frame[i][j] + max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[m - 1][n - 1];
}

// 动态规划. 8 下降路径最小和

int minFallingPathSum(vector<vector<int>>& matrix)
{
    int m = matrix.size(), n = matrix[0].size();
    // dp[x][y]表示到达该位置最小路径
    vector<vector<int>> dp(m + 1, vector<int>(n + 2, INT_MAX)); // 留出两边    
    // 初始化第0层
    for (int j = 0; j <= n + 1; ++j)
    {
        dp[0][j] = 0;
    }
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            dp[i][j] = matrix[i - 1][j - 1] + min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i - 1][j + 1]));
        }
    }
    int result = INT_MAX;
    for (int j = 1; j <= n; ++j)
        result = min(result, dp[m][j]);

    return result;
}