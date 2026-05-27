//1. 翻转列表
typedef ListNode* L;
ListNode* ReverseList(ListNode* head)
{
    if (head == nullptr) return nullptr;
    L a = nullptr, b = head, c = head->next;
    while (b != nullptr)
    {
        b->next = a;
        a = b;
        b = c;
        if (c != nullptr) c = c->next;
    }
    return a;
}

//2. 翻转链表区间
ListNode* reverseBetween(ListNode* head, int m, int n) {
    // 保留反转链表前一个结点pre，和翻转之后的尾节点cur
    L pre = nullptr, cur = head;
    int cnt = 1;
    while (cnt != m)
    {
        pre = cur;
        cur = cur->next;
        ++cnt;
    }
    // 和上题同样逻辑
    L a = nullptr, b = cur, c = cur->next;
    cnt--; // 实际记录a的位置
    while (cnt != n)
    {
        b->next = a;
        a = b;
        b = c;
        if (c != nullptr) c = c->next;
        ++cnt;
    }
    // 重新连接上反转好的链表
    if (pre == nullptr) head = a;
    else pre->next = a;
    cur->next = b;
    return head;
}

// 链表中的节点每K个一组翻转

// 策略是把剩余组先反转了，最后转回来————总不能先知道后面是完整一组还是剩余
ListNode* reverseKGroup(ListNode* head, int k)
{
    if (head == nullptr) return nullptr;
    // 保留每个翻转组的末尾节点tail，做下一组的前置节点
    L tail = head;
    // 和上题同理
    L pre = nullptr, cur = head;
    while (tail->next != nullptr) // tail后头没有了，说明翻转完成了
    {
        // 同上题相似，不过必须再判b，防止后面不是完整一组
        int cnt = 0;
        L a = nullptr, b = cur, c = cur->next;
        while (cnt != k && b != nullptr)
        {
            b->next = a;
            a = b;
            b = c;
            if (c != nullptr) c = c->next;
            ++cnt;
        }
        if (cnt == k) // 正常翻转
        {
            // 反转好的链表接回去
            if (pre == nullptr) head = a;
            else pre->next = a;
            tail = cur;
            tail->next = b;
            // 给下组设置前置节点和起始节点
            pre = tail;
            cur = b;
        }
        else {  // 是剩余的情况，还得翻回来，得吧反转后的起始节点传出去——cur
            cur = a;
            break;
        }
    }
    // 翻转回剩余组
    L a = nullptr, b = cur, c = cur->next;
    while (b != nullptr)
    {
        b->next = a;
        a = b;
        b = c;
        if (c != nullptr) c = c->next;
    }
    // 注意：剩余组可能是第一组
    if (pre == nullptr) head = a;
    else pre->next = a;

    return head;
}