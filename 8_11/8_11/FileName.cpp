#include<vector>
using namespace std;

class Solution {
public:
    // 移动零
    // 1)记录0的位置,一次性移动 
    void moveZeroes(vector<int>& nums)
    {
        int n = nums.size();
        // tmp记录0的位置,下标表示第几个0
        vector<int> tmp(1, -1);
        for (int i = 0; i < n; ++i)
        {
            if (nums[i] == 0)
                tmp.push_back(i);
        }
        int count = tmp.size() - 1; // 0 的数量
        if (count == 0 || count == n) return;
        // 第1~2个0中间数据往前移动1位; 第2~3...往前移动2位
        for (int i = 1; i <= count; ++i)
        {
            // tmp[0] 设置为 -1
            for (int j = tmp[i - 1] + 1; j < tmp[i]; ++j)
                nums[j - i + 1] = nums[j];
        }

        for (int i = tmp[count] + 1; i < n; ++i) nums[i - count] = nums[i];
        for (int i = n - count; i < n; ++i) nums[i] = 0;
    }

    //2) 双指针, 用双指针划分区间
    void moveZeroes(vector<int>& nums)
    {
        int n = nums.size();
        // [dest, cur)中之间都为0
        int dest = 0, cur = 0;
        while (cur < n)
        {
            if (nums[cur] == 0)
            {
                ++cur;
            }
            else
            {
                swap(nums[dest], nums[cur]);
                ++dest, ++cur;
            }
        }
    }
};