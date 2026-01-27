#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

//1.10离散化

//1)火烧赤壁——难：离散化+差分
typedef long long LL;
int n;
vector<LL> pos;
int p;//去重后的区间长度
vector<LL> sortpos;
unordered_map<int, int> posmap;//<real pos, mapping pos> 
vector<int> f;//差分数组

int main()
{
    cin >> n;
    pos.resize(2 * n + 1);
    sortpos.resize(2 * n + 1);
    for (int i = 1; i <= 2 * n; ++i)
    {
        cin >> pos[i];
        sortpos[i] = pos[i];
    }
    //sort(sortpos.begin(), sortpos.end());//这里的第一个数是0，后面才是-1，这样后面
                                                    //sortpos【1】处就是0了
    sort(sortpos.begin() + 1, sortpos.end());
    //一定记得去重
    p = unique(sortpos.begin() + 1, sortpos.end()) - (sortpos.begin() + 1);

    int cnt = 0;
    for (int i = 1; i <= p; ++i)
    {
        if (posmap.count(sortpos[i])) continue;
        posmap[sortpos[i]] = ++cnt;
    }

    //在离散化的基础上差分
    f.resize(cnt + 1, 0);
    for (int i = 1; i <= 2 * n; i += 2)
    {
        f[posmap[pos[i]]]++;
        f[posmap[pos[i + 1]]]--;
    }
    //还原差分
    for (int i = 1; i <= cnt; ++i) f[i] += f[i - 1];

    LL ret = 0;//结果
    for (int i = 1; i <= cnt; ++i)
    {
        if (f[i] > 0)
        {
            int pre = i, cur = i;
            while (cur <= cnt && f[cur] > 0)
                ++cur;
            // cout<<cur<<":"<<sortpos[cur]<<" "<<pre<<":"<<sortpos[pre]<<endl;
            ret += (sortpos[cur] - sortpos[pre]);
            i = cur;
        }
    }
    cout << ret;
    return 0;
}


//2）贴海报

//1.有错（傻子忘记给sortlr开空间了）
int N, M;
vector<int> lr;
int pos;//去重后的坐标数
vector<int> sortlr;
unordered_map<int, int> lrmap;//<real pos, mapping pos>
vector<int> wall;
vector<bool> paper;

int main()
{
    cin >> N >> M;
    lr.resize(2 * M + 1);
    for (int i = 1; i <= 2 * M; ++i)
    {
        cin >> lr[i];
        sortlr[i] = lr[i];
    }
    sort(sortlr.begin() + 1, sortlr.end());
    //去重
    // pos = unique(sortlr.begin()+1, sortlr.end()) - (sortlr.begin() + 1);
    // 离散化(将x和x+1都离散出来)
    int cnt = 0;
    for (int i = 1; i <= 2 * M; ++i)
    {
        if (!lrmap.count(sortlr[i]))
            lrmap[sortlr[i]] = ++cnt;
        if (!lrmap.count(sortlr[i] + 1))
            lrmap[sortlr[i] + 1] = ++cnt;
    }
    //模拟
    wall.resize(cnt + 1);
    for (int i = 1; i <= 2 * M; i += 2)
    {
        int l = lrmap[lr[i]], r = lrmap[lr[i + 1]];
        for (int j = l; j <= r; ++j)
        {
            wall[j] = (i + 1) / 2;
        }
    }
    //结果
    paper.resize(M + 1, false);
    for (int i = 1; i <= cnt; ++i)
    {
        paper[wall[i]] = true;
    }
    int sum = 0;
    for (int i = 1; i <= M; ++i)
    {
        if (paper[i]) ++sum;
    }
    cout << sum;
    return 0;
}