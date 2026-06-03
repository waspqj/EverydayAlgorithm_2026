#include <iostream>

// 未完成
int InversePairs(vector<int>& nums)
{
    int result = 0;
    // 边归并排序, 边匹配
    int n = nums.size();
    int gap = 1;
    while (gap < n)
    {
        vector<int> tmp(nums);

        for (int i = 0; i + gap < n; i += 2 * gap)
        {
            int x = i;
            int begin1 = i, begin2 = i + gap;
            int end1 = begin2, end2 = ((i + 2 * gap) <= n ? i + 2 * gap : n);
            int cur1 = begin1, cur2 = begin2;
            while (cur1 < end1 && cur2 < end2)
            {
                if (nums[cur1] <= nums[cur2])
                {
                    tmp[x++] = nums[cur1++];
                }
                else {
                    result += (end1 - cur1);
                    tmp[x++] = nums[cur2++];
                }
            }
            while (cur1 < end1) tmp[x++] = nums[cur1++];
            while (cur2 < end2) tmp[x++] = nums[cur2++];
        }
        gap <<= 1;
        nums.swap(tmp);
        // cout<< gap<< ": ";
        // for(auto n : nums) cout<< n << " ";
        // cout<< endl;
    }
    return result;
}