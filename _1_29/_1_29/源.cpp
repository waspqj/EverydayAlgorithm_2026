#include<iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


//1.12.2第k最小数——结合快排，快速选择算法
#define N 5000010

int n, k;
int arr[N];

int GetRandom(int left, int right)
{
    return arr[rand() % (right - left + 1) + left];
}
int quikfd(int left, int right)
{
    if (left >= right) return arr[left];

    int key = GetRandom(left, right);
    int pre = left - 1, next = right + 1, cur = left;//这种可以分区的快排，比较好理解，其中细节任不少
    while (cur < next)
    {
        if (arr[cur] < key)
        {
            swap(arr[++pre], arr[cur++]);
        }
        else if (arr[cur] == key)
        {
            ++cur;
        }
        else {
            swap(arr[--next], arr[cur]);
        }
    }
    //     cout<<pre<<":"<<next<<endl;
    // cout<<left<<":"<<right<<":"<<arr[0]<<" "<<arr[1]<<" "<<arr[2]<<" "<<arr[3]<<" "<<arr[4]<< endl;
    if (pre - left + 1 >= k)
    {
        return quikfd(left, pre);
    }
    else if (next - left + 1 > k)
    {
        return key;
    }
    else {
        k -= next - left;
        return quikfd(next, right);
    }
}
int main()
{
    srand(time(NULL));
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
        scanf("%d", &arr[i]);//这里用cin竟然会超时！！！

    ++k;
    cout << quikfd(0, n - 1);

    return 0;
}

//1.12.3 最大子段和
//分治——第三种解了已经

const int maxn = 2e5 + 10;
typedef long long LL;
int n;
LL f[maxn];

LL dfs(int left, int right)
{
    if (left >= right) return f[left] - f[left - 1];

    int mid = (left + right) / 2;
    LL lmax = -1e4 - 5, rmax = -1e4 - 5;
    int l = mid, r = mid + 1;
    while (l >= left)
        lmax = max(lmax, f[mid] - f[--l]);
    while (r <= right)
        rmax = max(rmax, f[r++] - f[mid]);

    LL ret = max(dfs(left, mid), dfs(mid + 1, right));
    return max(ret, lmax + rmax);
}
int main()
{
    cin >> n;
    f[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        int x; cin >> x;
        f[i] = f[i - 1] + x;
    }

    cout << dfs(1, n);

    return 0;
}