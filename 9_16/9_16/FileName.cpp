#include <iostream>
#include <vector>

using namespace std;

// 动态规划9. 最小路径
int minPathSum(vector<vector<int>>& grid)
{
    int m = grid.size(), n = grid[0].size();
    // dp[x][y]指的是到达该位置最小路径
    vector<vector<int>> dp(m, vector<int>(n));
    // 初始化
    dp[0][0] = grid[0][0];
    for (int i = 1; i < m; i++)
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    for (int j = 1; j < n; j++)
        dp[0][j] = dp[0][j - 1] + grid[0][j];

    // 动态推导
    for (int i = 1; i < m; ++i)
    {
        for (int j = 1; j < n; ++j)
        {
            dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[m - 1][n - 1];
}

// 动态规划10. 地下城游戏 *******

// 这个状态表示就不够用了, 上一个是伤害还是回血对下一次最低血量的判断有影响
// 
//int calculateMinimumHP(vector<vector<int>>& dungeon)
//{
//    int m = dungeon.size(), n = dungeon[0].size();
//    // dp[x][y] 指的是到达这个位置需要的最低血量
//    vector<vector<int>> dp(m, vector<int>(n, 0));
//    // 初始化
//    dp[0][0] = dungeon[0][0] > 0 ? 0 : -dungeon[0][0];
//    for (int i = 1; i < m; ++i)
//        dp[i][0] = dungeon[i][0] > 0 ? ;
//    for (int j = 1; j < n; ++j)
//        dp[0][j] = dp[0][j - 1] + dungeon[0][j];
//    // 动态推导
//    for (int i = 1; i < m; ++i)
//    {
//        for (int j = 1; j < n; ++j)
//        {
//            dp[i][j] = dungeon[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
//        }
//    }
//
//}

// 将状态表示反过来, 表示从该位置到终点的最小血量, 这样,基于下一步至少的血量,只要能通过这个位置,就能以最少血量到达终点,不用管下一步到终点的过程
// 而如果状态表示为起始位置到该位置的最小血量, 遇到掉血最小血量当然可以叠加,如果遇到回血,最小血量不会变小,因为要通过上一步必须用那么多, 
// 但是之后的过程就没法算了, 之后的过程只能忽略前面的回血
int calculateMinimumHP(vector<vector<int>>& dungeon)
{
    int m = dungeon.size(), n = dungeon[0].size();
    // dp[x][y] 表示从该位置到终点的最小血量(不可能为负，)
    vector<vector<int>> dp(m, vector<int>(n, 0));
    // 初始化最后一行和最后一列
    dp[m - 1][n - 1] = dungeon[m - 1][n - 1] > 0 ? 0 : -dungeon[m - 1][n - 1];
    for (int i = m - 2; i >= 0; --i)
    {
        dp[i][n - 1] = dp[i + 1][n - 1] - dungeon[i][n - 1];
        // <0 说明肯定是回血了,而且还回过头了
        if (dp[i][n - 1] < 0) dp[i][n - 1] = 0;
    }
    for (int j = n - 2; j >= 0; --j)
    {
        dp[m - 1][j] = dp[m - 1][j + 1] - dungeon[m - 1][j];
        // 同理
        if (dp[m - 1][j] < 0) dp[m - 1][j] = 0;
    }
    // 同样的向前动态推理
    for (int i = m - 2; i >= 0; --i)
    {
        for (int j = n - 2; j >= 0; --j)
        {
            dp[i][j] = min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j];
            if (dp[i][j] < 0) dp[i][j] = 0;
        }
    }
    // 上面算的是0滴血, 得加一滴吊着命
    return dp[0][0] + 1;
}

// 动态规划.11 多状态dp--按摩师

int massage(vector<int>& nums)
{
    int n = nums.size();
    if (n < 1) return 0;
    //     多状态dp
    // 到该位置并选择这个预约的最长预约时间
    vector<int> f(n);
    // 到该位置并不选择这个预约的最长预约时间
    vector<int> g(n);
    // 初始化
    f[0] = nums[0];
    g[0] = 0;

    // 动态推导
    for (int i = 1; i < n; ++i)
    {
        // i选了i-1必不选
        f[i] = g[i - 1] + nums[i];
        // i不选i-1可选可不选
        g[i] = max(f[i - 1], g[i - 1]);
    }
    return max(f[n - 1], g[n - 1]);
}

// 动态规划12. 打家劫舍
 // 环形问题, 分为两个单排问题

int _rob(vector<int>& nums, int left, int right)
{
    if (left > right)
        return nums[left];

    int n = nums.size();
    // 多状态dp f[]选中时最多, g[]不选中时最多
    vector<int> f(n), g(n);
    // initialise
    f[left] = nums[left];
    g[left] = 0;
    // 动态推导
    for (int i = left + 1; i <= right; ++i)
    {
        f[i] = g[i - 1] + nums[i];
        g[i] = max(f[i - 1], g[i - 1]);
    }
    return max(f[right], g[right]);
}
int rob(vector<int>& nums)
{
    // 环形问题, 分为两个单排问题
    int n = nums.size();
    if (n == 1) return nums[0];
    // [0, n-2]                 [1, n-1]
    return max(_rob(nums, 0, n - 2), _rob(nums, 1, n - 1));
}

#include <algorithm>
// 动态规划13. 删除并获得点数
    // 据题目推出不可选择相邻两数字, 和之前不可选相邻房子偷盗的问题很像了
    // 转换一下,用多状态dp解
int deleteAndEarn(vector<int>& nums)
{
    int n = nums.size();
    sort(nums.begin(), nums.end());
    int maxValue = nums[n - 1];
    // sumValue[i]指数值i在nums里出现的所有的和
    vector<int> sumValue(maxValue + 2, 0);
    for (auto& x : nums)
    {
        sumValue[x] += x;
    }
    // f[i] 表示从0到i,并选择i,获得最大的点数 ,g[i] 即不选i
    vector<int> f(maxValue + 2), g(maxValue + 2);
    // initialise
    f[0] = sumValue[0];
    g[0] = 0;

    // 动态推导
    for (int i = 1; i <= maxValue; ++i)
    {
        f[i] = g[i - 1] + sumValue[i];
        g[i] = max(f[i - 1], g[i - 1]);
    }
    return max(g[maxValue], f[maxValue]);
}

