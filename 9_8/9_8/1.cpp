#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 1.7 三数之和（等于零） 
vector<vector<int>> threeSum(vector<int>& nums)
{
    // 排序
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    for (int i = 0; i < n; )
    {
        // 确定一个，剩下的对撞指针
        if (nums[i] > 0) break;
        int target = -nums[i], left = i + 1, right = n - 1;
        while (left < right)
        {
            if (nums[left] + nums[right] < target)
                ++left;
            else if (nums[left] + nums[right] > target)
                --right;
            else
            {
                result.push_back({ nums[i], nums[left++], nums[right--] });
                // left right去重
                while (left < right && nums[left] == nums[left - 1]) left++;
                while (right > left && nums[right] == nums[right + 1]) right--;
            }
        }
        ++i;
        // 先确定的去重
        while (i < n && nums[i] == nums[i - 1]) ++i;
    }
    return result;
}

// 1.8 四数之和
vector<vector<int>> fourSum(vector<int>& nums, int target)
{
    // 三数之和再叠一层，不优化
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;

    for (int i = 0; i < n;) // 固定a
    {
        for (int j = i + 1; j < n;) // 固定b
        {
            long long cur = (long long)target - nums[i] - nums[j];
            int left = j + 1, right = n - 1;
            while (left < right)
            {
                if (nums[left] + nums[right] < cur)
                    ++left;
                else if (nums[left] + nums[right] > cur)
                    --right;
                else
                {
                    result.push_back({ nums[i], nums[j], nums[left++], nums[right--] });
                    // left right 去重
                    while (left < right && nums[left] == nums[left - 1]) ++left;
                    while (right > left && nums[right] == nums[right + 1]) --right;
                }
            }
            ++j;
            // b去重
            while (j < n && nums[j] == nums[j - 1]) ++j;
        }
        ++i;
        // a去重
        while (i < n && nums[i] == nums[i - 1]) ++i;
    }
    return result;
}