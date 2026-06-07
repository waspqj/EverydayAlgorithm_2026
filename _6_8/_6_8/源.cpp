#include <iostream>
#include <vector>
using namespace std;
//BM20 数组中的逆序对
 
// 归并排序 + 双指针
typedef long long LL;
LL mod = 1000000007;
int InversePairs(vector<int>& nums)
{
    LL result = 0;
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
                    result += (end1 - cur1) % mod;
                    result %= mod;
                    tmp[x++] = nums[cur2++];
                }
            }
            while (cur1 < end1) tmp[x++] = nums[cur1++];
            while (cur2 < end2) tmp[x++] = nums[cur2++];
        }
        gap <<= 1;
        nums.swap(tmp);
    }
    return result;
}

//BM21 旋转数组的最小数字

// 数组不降序，要小心相等的情况
int minNumberInRotateArray(vector<int>& nums)
{
    int left = 0, right = nums.size() - 1;
    while (left < right)
    {
        // 除了最小点，两边都是升序，所以这里就是最小的右边升序，left就是最小
        if (nums[left] < nums[right]) return nums[left];
        int mid = left + (right - left) / 2;
        // 小心连续相等的情况，无法确定最小在mid👈还是👉，所以一步一步遍历，才不会跳过
        if (nums[left] == nums[mid])
        {
            if (nums[left] > nums[left + 1]) return nums[left + 1];
            ++left;
        }
        else if (nums[left] < nums[mid])
        {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }
    return nums[left];
}

//BM22 比较版本号

int compare(string version1, string version2)
{
    int s1 = version1.size(), s2 = version2.size();
    int cur1 = 0, cur2 = 0;
    while (cur1 < s1 && cur2 < s2)
    {
        int n1 = 0, n2 = 0;
        while (cur1 < s1 && version1[cur1] != '.')
        {
            n1 = n1 * 10 + version1[cur1++] - '0';
        }
        while (cur2 < s2 && version2[cur2] != '.')
        {
            n2 = n2 * 10 + version2[cur2++] - '0';
        }
        if (n1 > n2) return 1;
        if (n2 > n1) return -1;
        ++cur1, ++cur2;
    }
    while (cur1 < s1)
    {
        int n1 = 0;
        while (cur1 < s1 && version1[cur1] != '.')
        {
            n1 = n1 * 10 + version1[cur1++] - '0';
        }
        if (n1 != 0) return 1;
        ++cur1;
    }
    while (cur2 < s2)
    {
        int n2 = 0;
        while (cur2 < s2 && version2[cur2] != '.')
        {
            n2 = n2 * 10 + version2[cur2++] - '0';
        }
        if (n2 != 0) return -1;
        ++cur2;
    }
    return 0;
}