#include<iostream>
#include<string>

using namespace std;

//2.4.0 记忆化搜索——斐波那契数列递归优化
class Solution {
public:
    int arr[35];

    int dfs(int n)
    {
        if (arr[n] != -1) return arr[n];
        if (n == 0 || n == 1) return n;
        arr[n] = fib(n - 1) + fib(n - 2);
        return arr[n];
    }

    int fib(int n)
    {
        memset(arr, -1, sizeof(arr));

        return dfs(n);
    }
};
