//4. 合并两个排序链表
using L = ListNode*;
ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
    L cur1 = pHead1, cur2 = pHead2, head = nullptr;
    if (cur1 == nullptr) return cur2;
    if (cur2 == nullptr) return cur1;

    if (cur1->val < cur2->val)
    {
        head = cur1;
        cur1 = cur1->next;
    }
    else
    {
        head = cur2;
        cur2 = cur2->next;
    }
    L cur = head;
    while (cur1 && cur2)
    {
        if (cur1->val < cur2->val)
        {
            cur->next = cur1;
            cur = cur1;
            cur1 = cur1->next;
        }
        else {
            cur->next = cur2;
            cur = cur2;
            cur2 = cur2->next;
        }
    }
    if (cur1) cur->next = cur1;
    if (cur2) cur->next = cur2;

    return head;
}