#include <iostream>
#include <vector>

using namespace std;

// 动态规划3.最下爬楼费用
int minCostClimbingStairs(vector<int>& cost)        
{
    int n = cost.size();
    int arr[4];
    arr[1] = cost[0], arr[2] = cost[1];
    if (n <= 2) return min(arr[1], arr[2]);

    for (int i = 2; i < n; ++i)
    {
        arr[3] = min(arr[1], arr[2]) + cost[i];
        arr[1] = arr[2];
        arr[2] = arr[3];
    }
    return min(arr[1], arr[2]);
}   
    
// 动态规划4. 解码方法
