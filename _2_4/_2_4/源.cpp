#include <iostream>
#include <vector>

using namespace std;

            //k
//2.1.1.3 ——A
            //n
int n, k;
vector<int> path;
vector<bool> hvgot;

void dfs(int pos)
{
    if (pos > k)
    {
        for (auto p : path) cout << p << " ";
        cout << endl;
        return;
    }
    for (int i = 1; i <= n; ++i)
    {
        if (!hvgot[i]) continue;
        path.push_back(i);
        hvgot[i] = false;
        dfs(pos + 1);
        path.pop_back();
        hvgot[i] = true;
    }
}

int main()
{
    cin >> n >> k;
    hvgot.resize(n + 1, true);
    dfs(1);
    return 0;
}

//2.1.1.4——全排列
int n;
vector<int> path;
vector<bool> ft;

void dfs(int pos)
{
    if (pos > n)
    {
        for (auto p : path) printf("%5d", p);
        cout << endl;
        return;
    }

    for (int i = 1; i <= n; ++i)
    {
        if (ft[i]) continue;
        path.push_back(i);
        ft[i] = true;
        dfs(pos + 1);
        path.pop_back();
        ft[i] = false;
    }
}

int main()
{
    cin >> n;
    ft.resize(n + 1, false);

    dfs(1);
    return 0;
}

#include <cmath>

//2.2.1——选数
int n, k;
vector<int> arr;
int sum, result;

int isPrime(int x)
{
    if (x <= 1) return 0;
    if (x == 2)return 1;
    if (x % 2 == 0) return 0;
    for (int i = 3; i <= sqrt(x); i += 2)
        if (x % i == 0) return 0;
    return 1;
}
void dfs(int pos, int begin)
{
    if (pos > k)
    {
        result += isPrime(sum);
        // cout<< result <<":"<<sum<<endl;
        return;
    }
    for (int i = begin; i < n; ++i)
    {
        sum += arr[i];
        dfs(pos + 1, i + 1);
        sum -= arr[i];
    }
}
int main()
{
    cin >> n >> k;
    arr.resize(n);
    for (auto& a : arr) cin >> a;

    sum = 0, result = 0;
    dfs(1, 0);
    cout << result;
    return 0;
}
