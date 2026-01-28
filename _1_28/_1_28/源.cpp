#include <iostream>

using namespace std;

//1.11.3 FBI树
#define N 11

int n;
int f[1 << N];

//递归的顺序刚好可以满足后序遍历，前缀和优化判断方法
void dfs(int left, int right)
{
    if (left > right) return;

    dfs(left, (right + left - 1) / 2);
    dfs((right + left) / 2 + 1, right);//小心边界情况

    int ret = f[right] - f[left - 1];
    if (ret == 0) cout << 'B';
    else if (ret == right - left + 1) cout << 'I';
    else cout << 'F';
}
int main()
{
    cin >> n;
    f[0] = 0;
    for (int i = 1; i <= (1 << n); ++i)
    {
        char x; cin >> x;
        f[i] = f[i - 1] + x - '0';
    }

    dfs(1, 1 << n);

    return 0;
}

//1.12 分治——写过一次了——结合归并——比较难的 
//1.12.1 逆序对
#include<cstring>

#define N 500010
typedef long long LL;
int n;
// vector<int> arr;
// vector<int> tmp;
int arr[N];
int tmp[N];

LL fmerge(int left, int right)
{
    if (left >= right) return 0;

    LL ret = 0;
    int mid = (left + right) / 2;
    ret += fmerge(left, mid) + fmerge(mid + 1, right);

    // //归并（merge）——可以同时干
    //基于两边已经分别有序，找之间的逆序对
    int cur1 = left, cur2 = mid + 1, cur = left;
    while (cur1 <= mid && cur2 <= right)
    {
        if (arr[cur1] > arr[cur2])
        {
            ret += mid - cur1 + 1;
            tmp[cur++] = arr[cur2++];
        }
        else
        {
            tmp[cur++] = arr[cur1++];
        }
    }
    while (cur1 <= mid)
    {
        tmp[cur++] = arr[cur1++];
    }
    while (cur2 <= right)
    {
        tmp[cur++] = arr[cur2++];
    }
    memcpy(arr + left, tmp + left, sizeof(int) * (right - left + 1));
    return ret;
}
int main()
{
    cin >> n;
    // arr.resize(n);
    // tmp.resize(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }
    cout << fmerge(0, n - 1);
    return 0;
}

//1.12.2 第k最小数——失败之作

#define N 5000010

int n, k;
int arr[N];

int quikfd(int left, int right)
{
    if (left >= right) return;

    int key = arr[left];
    int pre = left, next = left, cur = left + 1;
    while (cur <= right)
    {
        if (arr[cur] < key)
        {
            swap(arr[pre], arr[cur]);
            ++pre, ++next;
        }
        else if (arr[cur] == key)
        {
            swap(arr[++next], arr[cur]);
        }
        ++cur;
    }

    if (pre <= k && next >= k)
    {
        return key;
    }
    else if (pre > k)
    {
        return quikfd(left, pre - 1);
    }
    else {
        k -= next - left + 1;
        return quikfd(next + 1, right);
    }
}
int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    cout << quikfd(0, n - 1);

    return 0;
}