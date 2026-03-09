#include <iostream>
#include <deque>
#include <utility>
#include <cstring>

using namespace std;


//2.7.2 01BFS + 多源bfs ——three states

#define N 1006

typedef pair<int, int> PII;
int x[] = { 0, 0, 1, -1 };
int y[] = { 1, -1, 0, 0 };
char road[N][N];
int gap[3][N][N];
int n, m;

void bfs(int state)
{
    deque<PII> d;
    memset(gap[state], -1, sizeof gap[state]);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (state + '1' == road[i][j])
            {
                gap[state][i][j] = 0;
                d.emplace_back(i, j);
            }

    while (d.size())
    {
        auto cur = d.front(); d.pop_front();
        int cx = cur.first, cy = cur.second;
        // cout << cx << " " << cy << endl;
        for (int s = 0; s < 4; ++s)
        {
            int i = cx + x[s], j = cy + y[s];
            if (i >= 1 && i <= n && j >= 1 && j <= m && road[i][j] != '#')
            {
                int w = (road[i][j] == '.' ? 1 : 0);
                if (gap[state][i][j] == -1)
                {
                    gap[state][i][j] = gap[state][cx][cy] + w;
                    if (w) d.emplace_back(i, j);
                    else d.emplace_front(i, j);
                }
                else if (gap[state][i][j] > gap[state][cx][cy] + w)
                {
                    gap[state][i][j] = gap[state][cx][cy] + w;
                }
            }
        }
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> road[i][j];

    bfs(0); bfs(1); bfs(2);

    int ret = 1e6;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            // if(road[i][j] == '#') continue;
            if (gap[0][i][j] == -1 || gap[1][i][j] == -1 || gap[2][i][j] == -1) continue;

            if (road[i][j] == '.')
            {
                // cout<< gap[state][i][j] << endl;
                ret = min(ret, gap[0][i][j] + gap[1][i][j] + gap[2][i][j] - 2);
            }
            else
            {
                ret = min(ret, gap[0][i][j] + gap[1][i][j] + gap[2][i][j]);
            }
        }
    if (ret == 1e6)
        cout << "-1";
    else
        cout << ret;
    return 0;
}