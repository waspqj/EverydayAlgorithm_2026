//1.排序链表

using L = ListNode*;
ListNode* sortInList(ListNode* head)
{
    vector<int> nums;
    L cur = head;
    while (cur)
    {
        nums.push_back(cur->val);
        cur = cur->next;
    }
    sort(nums.begin(), nums.end());
    cur = head;
    auto it = nums.begin();
    while (cur)
    {
        cur->val = *it;
        ++it;
        cur = cur->next;
    }
    return head;
}

//2.回文链表

using L = ListNode*;
bool isPail(ListNode* head)
{
    vector<int> nums;
    L cur = head;
    while (cur)
    {
        nums.push_back(cur->val);
        cur = cur->next;
    }
    int s = nums.size();
    for (int i = 0; i < s >> 1; ++i)
    {
        if (nums[i] != nums[s - i - 1]) return false;
    }
    return true;
}
// 链表的奇偶重排

ListNode* oddEvenList(ListNode* head) {
    vector<int> odd, even;
    L cur = head;
    int n = 1;
    while (cur)
    {
        if (n % 2) odd.push_back(cur->val);
        else even.push_back(cur->val);
        cur = cur->next;
        ++n;
    }
    cur = head;
    for (auto o : odd)
    {
        cur->val = o;
        cur = cur->next;
    }
    for (auto e : even)
    {
        cur->val = e;
        cur = cur->next;
    }
    return head;
}

// 删除有序链表中的连续数据

ListNode* deleteDuplicates(ListNode* head)
{
    L cur = head, pre = nullptr;
    int repeat = 101;
    while (cur)
    {
        if (cur->val == repeat)
        { // 删
            pre->next = cur->next;
            cur = pre->next;
        }
        else {
            repeat = cur->val;
            pre = cur;
            cur = cur->next;
        }
    }
    return head;
}

