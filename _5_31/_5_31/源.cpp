//5.合并k个已排序的链表

using L = ListNode*;
ListNode* mergeKLists(vector<ListNode*>& lists)
{
    int s = lists.size();
    if (s == 0) return nullptr;
    while (s > 1)
    {
        for (int i = 0; i < s / 2; ++i)
        {
            L l = lists[i * 2], r = lists[i * 2 + 1];
            if (l == nullptr) { lists[i] = r; continue; }
            if (r == nullptr) { lists[i] = l; continue; }
            L head = (l->val < r->val ? l : r);
            if (head == l) l = l->next;
            if (head == r) r = r->next;
            L cur = head;
            while (l != nullptr && r != nullptr)
            {
                if (l->val < r->val)
                {
                    cur->next = l;
                    cur = cur->next;
                    l = l->next;
                }
                else {
                    cur->next = r;
                    cur = cur->next;
                    r = r->next;
                }
            }
            if (l != nullptr) cur->next = l;
            if (r != nullptr) cur->next = r;
            lists[i] = head;
        }
        if (s % 2 == 1)
        {
            lists[s / 2] = lists[s - 1];
            ++s;
        }
        s /= 2;
    }
    return lists[0];
}

//6.链表是否有环

using L = ListNode*;
bool hasCycle(ListNode* head)
{
    L slow = head, fast = head;
    while (fast != nullptr)
    {
        slow = slow->next;
        fast = fast->next;
        if (fast == nullptr) break;
        fast = fast->next;
        if (slow == fast)
            return true;
    }
    return false;
}

// 7. 找到环入口节点
ListNode* EntryNodeOfLoop(ListNode* pHead)
{
    L fast = pHead, slow = pHead;
    while (fast != nullptr)
    {
        slow = slow->next;
        fast = fast->next;
        if (fast == nullptr) return nullptr;
        fast = fast->next;

        if (fast == slow) break;
    }
    if (fast == nullptr) return nullptr;
    slow = pHead;
    while (slow != fast)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return fast;
}

// 8. 提取尾部k个节点长度的链表 
ListNode* FindKthToTail(ListNode* pHead, int k)
{
    ListNode* tmp = pHead;
    while (pHead && k--)
        pHead = pHead->next;

    if (k && !pHead) return nullptr;
    while (pHead)
    {
        tmp = tmp->next;
        pHead = pHead->next;
    }
    return tmp;
}

// 9. 删除倒数第n个节点
ListNode* removeNthFromEnd(ListNode* head, int n)
{
    L cur = head;
    while (cur && n--)
        cur = cur->next;
    if (cur == nullptr)
    {
        if (n == 0) return head->next;
        return nullptr;
    }
    L pre = head;
    cur = cur->next;
    while (cur)
    {
        cur = cur->next;
        pre = pre->next;
    }
    pre->next = pre->next->next;
    return head;
}

//10. 找出两链表的公共部分
ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2)
{
    int n1 = 0, n2 = 0;
    L cur1 = pHead1, cur2 = pHead2;
    while (cur1)
    {
        cur1 = cur1->next;
        ++n1;
    }
    while (cur2)
    {
        cur2 = cur2->next;
        ++n2;
    }

    cur1 = pHead1, cur2 = pHead2;
    if (n1 > n2)
    {
        for (int i = 0; i < n1 - n2; ++i)
            cur1 = cur1->next;
    }
    else 
    {
        for (int i = 0; i < n2 - n1; ++i)
            cur2 = cur2->next;
    }
    while (cur1 != cur2)
    {
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    return cur1;
}

// 链表加法

ListNode* addInList(ListNode* head1, ListNode* head2)
{
    // 1.翻转
    L a = nullptr, b = head1, c = head1->next;
    while (b)
    {
        b->next = a;
        a = b;
        b = c;
        if (c != nullptr) c = c->next;
    }
    head1 = a;
    a = nullptr, b = head2, c = head2->next;
    while (b)
    {
        b->next = a;
        a = b;
        b = c;
        if (c != nullptr) c = c->next;
    }
    head2 = a;
    // 2.相加
    L cur = nullptr;
    int car = 0;
    while (head1 && head2)
    {
        int sum = head1->val + head2->val + car;
        L tmp = head1;
        head1 = head1->next;
        head2 = head2->next;

        tmp->val = sum % 10;
        car = sum / 10;

        tmp->next = cur;
        cur = tmp;
    }
    if (head2) head1 = head2;
    while (head1)
    {
        int sum = head1->val + car;
        L tmp = head1;
        head1 = head1->next;
        tmp->val = sum % 10;
        car = sum / 10;
        tmp->next = cur;
        cur = tmp;
    }
    L head = cur;
    if (car)
    {
        head = new ListNode(car);
        head->next = cur;
    }
    return head;
}