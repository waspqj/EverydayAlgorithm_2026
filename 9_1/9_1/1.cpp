#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//5. 有效三角形个数
int triangleNumber(vector<int>& nums)
{
    // 暴力算法
    // int n = nums.size();
    // int result = 0;
    // sort(nums.begin(), nums.end());
    // for(int i = 0; i < n; ++i)
    // {
    //     for(int j = i + 1; j < n; ++j)
    //     {
    //         for(int k = j + 1; k < n; ++k)
    //         {
    //             if(nums[i] + nums[j] > nums[k])
    //                 result++;
    //         }
    //     }
    // }
    // return result;

    // 双指针优化
    int result = 0, n = nums.size();
    sort(nums.begin(), nums.end());
    // 从后往前遍历最长边，在前面使用对撞指针
    for (int i = n - 1; i >= 2; --i)
    {
        int left = 0, right = i - 1;
        while (left < right)
        {
            if (nums[left] + nums[right] > nums[i])
            {
                result += right - left;
                --right;
            }
            else
            {
                ++left;
            }
        }
    }
    return result;
}

// 6. 和为两个s的数字
int* twoSum(int* price, int priceSize, int target, int* returnSize)
{
    int left = 0, right = priceSize - 1;
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;
    while (left < right)
    {
        if (price[left] + price[right] > target)
        {
            --right;
        }
        else if (price[left] + price[right] < target)
        {
            ++left;
        }
        else
        {
            result[0] = price[left];
            result[1] = price[right];
            break;
        }
    }
    return result;
}