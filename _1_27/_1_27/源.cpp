#include<iostream>

using namespace std;


//1.11.1汉诺塔问题（easy）
int n;
char x, y, z;

void Hanno(int n, char x, char y, char z)
{
    if (n == 0) return;

    Hanno(n - 1, x, z, y);
    printf("%c->%d->%c\n", x, n, y);
    Hanno(n - 1, z, y, x);
}

int main()
{
    cin >> n >> x >> y >> z;
    Hanno(n, x, y, z);

    return 0;
}

//1.11.2占卜DIY
int arr[14][5];
int cnt[14];//记录每堆牌中未知牌的个数


void PukDIY(int x)
{
    if (x == 13) return;

    int t = arr[x][cnt[x]];
    --cnt[x];
    PukDIY(t);
    // PukDIY(arr[x][cnt[x]--]);
}

int main()
{
    for (int i = 1; i <= 13; ++i)
    {
        for (int j = 1; j <= 4; ++j)
        {
            char x; cin >> x;
            if (x > '0' && x <= '9')
                arr[i][j] = x - '0';
            else if (x == 'A')
                arr[i][j] = 1;
            else if (x == '0')
                arr[i][j] = 10;
            else if (x == 'J')
                arr[i][j] = 11;
            else if (x == 'Q')
                arr[i][j] = 12;
            else
                arr[i][j] = 13;
        }
        cnt[i] = 4;
    }
    for (int i = 1; i <= 4; ++i)
    {
        PukDIY(arr[13][i]);
    }

    int result = 0;
    for (int i = 1; i < 13; ++i)
    {
        if (!cnt[i]) ++result;
    }
    cout << result;
    return 0;
}