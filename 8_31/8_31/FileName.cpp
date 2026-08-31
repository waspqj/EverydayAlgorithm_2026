#include <iostream>
#include <vector>

using namespace std;

// 2. 复写零
void duplicateZeros(vector<int>& arr)
{
    int n = arr.size(), count = 0;
    // 找到最后一位
    int i;
    for (i = 0; i < n; ++i)
    {
        if (arr[i]) count++;
        else count += 2;
        if (count >= n)
            break;
    }
    // 解析最后一位的状态
    if (count > n)
    {
        arr[n - 1] = 0;
        i--;
        count -= 2;
    }
    // count 变为从后往前的下标
    count--;
    while (count >= 0)
    {
        if (arr[i] == 0)
        {
            arr[count--] = arr[i];
            arr[count--] = arr[i];
            --i;
        }
        else {
            arr[count--] = arr[i];
            --i;
        }
    }
}

//3. 快乐数
int bitSum(int n)
{
    int sum = 0;
    while (n)
    {
        int bitcur = n % 10;
        n /= 10;
        sum += bitcur * bitcur;
    }
    return sum;
}
bool isHappy(int n)
{
    // 当数字不是1且发现陷入循环，则确认这个不是快乐数
    // 故：利用快慢指针找到循环内一个数字，若数字非1，则不是快乐数
    int slow = n, fast = n;
    while (1)
    {
        fast = bitSum(bitSum(fast));
        slow = bitSum(slow);
        if (fast == slow) break;
    }
    return (fast == 1);
}

//4. 盛最多水的容器
int maxArea(vector<int>& height)
{
    // 对撞指针
    // 两端取较低的，放弃较高的向中间靠，宽度减小，高度不可能增大可能减小，总面积必然减小
    // 所以取较高的，放弃较低的向中间靠，宽度减小，高度可能增大，总面积可能增大
    int maxResult = 0;
    int left = 0, right = height.size() - 1;
    while (left < right)
    {
        maxResult = max(maxResult, (right - left) * min(height[left], height[right]));
        if (height[left] < height[right])
        {
            ++left;
        }
        else {
            --right;
        }
    }
    return maxResult;
}

//动态规划1. 第n个泰波那契数
int tribonacci(int n)
{
    // 动态规划
    int dp[3];
    dp[0] = 0, dp[1] = 1, dp[2] = 1;
    if (n < 3) return dp[n];
    for (int i = 2; i < n; ++i)
    {
        int tmp = dp[0] + dp[1] + dp[2];
        dp[0] = dp[1];
        dp[1] = dp[2];
        dp[2] = tmp;
    }
    return dp[2];
}

// 动态规划2. 三步上楼梯方案
int waysToStep(int n)
{
    //动态规划，经典上楼梯的方案
    // dp[n] = dp[n-1] + dp[n-2] + dp[n-3]
    // vector<long long> dp(n + 10);
    // dp[1] = 1, dp[2] = 2, dp[3] = 4;
    // if(n < 4) return dp[n];
    // for(int i = 4; i <= n; ++i)
    // {
    //     dp[i] = (dp[i - 1] + dp[i - 2] + dp[i - 3]) % 1000000007;
    // }
    // return dp[n];
    long long dp[4];
    dp[1] = 1, dp[2] = 2, dp[3] = 4;
    if (n < 4) return dp[n];
    for (int i = 3; i < n; ++i)
    {
        int tmp = (dp[1] + dp[2] + dp[3]) % 1000000007;
        dp[1] = dp[2];
        dp[2] = dp[3];
        dp[3] = tmp;
    }
    return dp[3];
}

