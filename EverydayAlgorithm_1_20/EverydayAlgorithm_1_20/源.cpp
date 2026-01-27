#include<iostream>

using namespace std;



//1.9 倍增思想

//1）快速幂
typedef long long LL;
LL a, b, p;

int main()
{
    cin >> a >> b >> p;
    LL acur = a, result = 1;
    for (int i = 0; (b >> i) > 0; ++i)
    {
        if (b & (1 << i))
        {
            result = (result * acur) % p;
        }
        acur = (acur * acur) % p;
    }
    cout << a << "^" << b << " mod " << p << "=" << result % p;
    return 0;
}
//快速幂模板
LL qpow(LL A, LL B, LL P)
{
    LL ret = 1;
    while (B)
    {
        if (B & 1) ret = (A * ret) % P;
        A = (A * A) % P;
        B >>= 1;
    }
    return ret;
}
int main()
{
    cin >> a >> b >> p;

    printf("%lld^%lld mod %lld=%lld\n", a, b, p, qpow(a, b, p));
    return 0;
}

//2) 快速乘（模板）
LL qmult(LL a, LL b, LL p)
{
    LL ret = 0;
    while (b)
    {
        if (b & 1) ret = (ret + a) % p;
        a = (a + a) % p;
        b >>= 1;
    }
    return ret;
}
int main()
{
    LL a, b, p;
    cin >> a >> b >> p;

    cout << qmult(a, b, p);
    return 0;
}
