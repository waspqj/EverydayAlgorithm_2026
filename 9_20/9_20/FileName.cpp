#include <iostream>
#include <vector>

using namespace std;

// 动态规划15. 最佳买股票时间，包含冷冻期
int maxProfit(vector<int>& prices)
{
    int n = prices.size();
    // 依旧多状态dp
    // dp[0][i] i天后为买入状态(可卖)的最大利润
    // dp[1][i] i天后为卖出状态(可买)的最大利润
    // dp[2][i] i天后为冷冻期(卖了，明天不可买)最大利润
    vector<vector<int>> dp(3, vector<int>(n, 0));
    // initialize
    dp[0][0] = -prices[0];
    dp[1][0] = 0;
    dp[2][0] = 0;
    // 动态推导
    for (int i = 1; i < n; ++i)
    {
        dp[0][i] = max(dp[0][i - 1], dp[1][i - 1] - prices[i]);
        dp[1][i] = max(dp[1][i - 1], dp[2][i - 1]);
        dp[2][i] = dp[0][i - 1] + prices[i];
    }
    return max(dp[1][n - 1], dp[2][n - 1]);
}

// 动态规划16. 最佳买入股票时机, 包含手续费

int maxProfit(vector<int>& prices, int fee)
{
    int n = prices.size();
    // 多状态dp 
    // dp[0] 可买 dp[1] 不可买
    vector<vector<int>> dp(2, vector<int>(n));
    // initialize
    dp[0][0] = 0;
    dp[1][0] = -prices[0];

    for (int i = 1; i < n; ++i)
    {
        dp[0][i] = max(dp[0][i - 1], dp[1][i - 1] + prices[i] - fee);
        dp[1][i] = max(dp[0][i - 1] - prices[i], dp[1][i - 1]);
    }
    return max(dp[0][n - 1], dp[1][n - 1]);
}