#include <iostream>
#include <cmath>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;


//1.8.4 区间问题

//2）Radar Installation——雷达安装
vector<pair<float, float>> arr;

int main()
{
    for (int c = 1; ; ++c)
    {
        int n, d; cin >> n >> d;
        if (n == 0) break;

        arr.resize(n);
        int flag = 1;
        for (int i = 0; i < n; ++i)
        {
            float x, y, h; cin >> x >> y;
            h = d * d - y * y;
            if (h >= 0)
            {
                arr[i].first = x - sqrt(h);
                arr[i].second = x + sqrt(h);
            }
            else {
                flag = 0;
                break;
            }
        }
        if (!flag)
        {
            cout << "Case " << c << ": -1\n";
            continue;
        }
        sort(arr.begin(), arr.end());
        int result = 1;
        int r = arr[0].second;
        for (int i = 1; i < n; ++i)
        {
            if (arr[i].first > r)
            {
                ++result;
                r = arr[i].second;
            }
            else {
                r = min<float>(arr[i].second, r);
            }
        }
        cout << "Case " << c << ": " << result << endl;
    }
    return 0;
}

//3）Sunscreen G —— 小奶牛的防晒霜
int C, L;
vector<pair<int, int>> cows;
vector<pair<int, int>> suns;

int main()
{
    cin >> C >> L;
    cows.resize(C);
    suns.resize(L);
    for (int i = 0; i < C; ++i)
    {
        cin >> cows[i].first >> cows[i].second;
    }
    for (int i = 0; i < L; ++i)
    {
        cin >> suns[i].first >> suns[i].second;
    }
    sort(cows.begin(), cows.end(), greater<pair<int, int>>());
    sort(suns.begin(), suns.end(), greater<pair<int, int>>());

    int ret = 0;
    for (int c = 0; c < C; ++c)
    {
        for (int l = 0; l < L; ++l)
        {
            if (suns[l].second == 0) continue;

            if (suns[l].first >= cows[c].first && suns[l].first <= cows[c].second)
            {
                --suns[l].second;
                ++ret;
                break;
            }
            else if (suns[l].first < cows[c].first)
            {
                break;
            }
        }
    }
    cout << ret;
    return 0;
}

#include <queue>

using namespace std;

//3）设置牛棚——Stall Reservations S（牛牛挤奶时不愿意让别的牛看见）
int N;   //     l    r     index 
vector<pair<pair<int, int>, int>> cows;
//牛棚编号
int S;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> shed;
vector<int> result;

int main()
{
    cin >> N;
    cows.resize(N + 1);
    result.resize(N + 1);
    for (int i = 1; i <= N; ++i)
    {
        cows[i].second = i;
        cin >> cows[i].first.first >> cows[i].first.second;
    }
    sort(cows.begin(), cows.end());

    S = 1;
    shed.push({ cows[1].first.second, S });
    result[cows[1].second] = S;
    for (int i = 2; i <= N; ++i)
    {
        if (shed.top().first < cows[i].first.first)
        {
            int tmpS = shed.top().second;
            shed.pop();
            shed.push({ cows[i].first.second, tmpS });
            result[cows[i].second] = tmpS;
        }
        else {
            shed.push({ cows[i].first.second, ++S });
            result[cows[i].second] = S;
        }
    }

    cout << S << endl;
    for (int i = 1; i <= N; ++i)
    {
        cout << result[i] << endl;
    }

    return 0;
}