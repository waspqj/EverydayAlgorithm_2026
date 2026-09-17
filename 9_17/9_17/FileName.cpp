#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>>& costs)
    {
        int n = costs.size();
        // 还是要分情况dp：r（红；b（蓝；g（绿 即这个位置选择了这个颜色的最少花费情况
        vector<int> r(n), b(n), g(n);
        // initialise
        r[0] = costs[0][0];
        b[0] = costs[0][1];
        g[0] = costs[0][2];
        // 动态推导
        // r[i] = min(b[i-1], g[i-1]) + costs[i][0]
        // ……
        for (int i = 1; i < n; ++i)
        {
            r[i] = min(b[i - 1], g[i - 1]) + costs[i][0];
            b[i] = min(r[i - 1], g[i - 1]) + costs[i][1];
            g[i] = min(r[i - 1], b[i - 1]) + costs[i][2];
        }
        return min(r[n - 1], min(b[n - 1], g[n - 1]));
    }
};