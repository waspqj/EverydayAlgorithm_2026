#include <iostream>
#include <vector>

using namespace std;

// 1.9 ⻓度最⼩的⼦数组
int minSubArrayLen(int target, vector<int>& nums)
{
    int n = nums.size();
    int result = n + 1;
    int left = 0, right = 0, sum = 0;
    while (right < n)
    {
        sum += nums[right++];
        while (sum >= target)
        {
            result = min(result, right - left);
            sum -= nums[left++];
        }
    }
    return result > n ? 0 : result;
}

// 1.10 ⽆重复字符的最⻓⼦串
int lengthOfLongestSubstring(string s)
{
    int arr[1000] = { 0 }, result = 0;
    int n = s.size();
    int left = 0, right = 0;
    while (right < n)
    {
        arr[s[right]]++;
        while (arr[s[right]] > 1)
        {
            arr[s[left++]]--;
        }
        ++right;
        result = max(result, right - left);
    }
    return result;
}

// 1.11 最⼤连续 1 的个数 III
int longestOnes(vector<int>& nums, int k)
{
    int n = nums.size();
    int result = 0, count = 0;
    int left = 0, right = 0;
    while (right < n)
    {
        if (nums[right++] == 0) count++;
        while (count > k)
        {
            if (nums[left++] == 0) count--;
        }
        result = max(result, right - left);
    }
    return result;
}