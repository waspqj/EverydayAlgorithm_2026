// 16. 删除有序链表中的连续节点(只保留单个节点, 有多个的统统删掉)
using L = ListNode*;
ListNode* deleteDuplicates(ListNode* head)
{// cur表示遍历过的最后一个有效节点, nxt表示正在遍历节点
    L cur = nullptr, nxt = head;
    head = nullptr;
    int repeat = 1001; // 前一个节点的值
    while (nxt)
    {       // 如果和前后节点相同,那么这个节点无效,保存值作为下次判断
        if ((nxt->next && nxt->val == nxt->next->val) || nxt->val == repeat)
        {
            repeat = nxt->val;
            nxt = nxt->next;
        }
        // 有效节点, 更新cur
        else {
            if (cur) cur->next = nxt;
            else head = nxt;
            cur = nxt;
            repeat = nxt->val;
            nxt = nxt->next;
        }
    }

    if (cur && cur->next) cur->next = nullptr;

    return head;
}

// 1. 二分查找

int search(vector<int>& nums, int target)
{
    int left = 0, right = nums.size() - 1;
    if (right < 0) return -1;
    while (left < right)
    {
        int mid = (right - left + 1) / 2 + left;
        if (nums[mid] == target)
        {
            left = mid;
            break;
        }
        else if (nums[mid] > target) right = mid - 1;
        else left = mid;
    }
    if (left >= right && nums[left] != target) return -1;
    return left;
}

// 2. 上下左右有序的二维数组的查找
// 从左下角开始找, 向上变小,向右变大
bool Find(int target, vector<vector<int> >& array)
{
    int n = array.size(), m = array[0].size();
    int x = n - 1, y = 0;
    while (x >= 0 && y < m)
    {
        if (array[x][y] < target) ++y;
        else if (array[x][y] > target) --x;
        else return true;
    }
    return false;
}

//3. 寻找任一山峰
int findPeakElement(vector<int>& nums)
{
    int s = nums.size();
    if (s == 1) return 0;
    if (nums[0] > nums[1]) return 0;
    if (nums[s - 1] > nums[s - 2]) return s - 1;
    for (int i = 1; i < nums.size() - 1; ++i)
    {
        if (nums[i - 1] < nums[i] && nums[i + 1] < nums[i])
            return i;
    }
    return -1;
}
