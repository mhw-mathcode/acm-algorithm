#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 2147483647
#define pii pair<int, int>
const int N = 5e5 + 5;

// n点数，m边数，s出发点
int n, m, s;
// d数组表示出发点到该点的最短距离，v数组表示是否访问过
int d[N], v[N];

priority_queue<pii, vector<pii>, greater<pii>> q; // 小根堆
vector<pii> g[N];

// 堆优化的dijkstra
void dijkstra()
{
    for (int i = 1; i <= n; i++) d[i] = inf;
    d[s] = 0;
    q.push({0, s}); // 起点
    while (!q.empty())
    {
        int x = q.top().second;
        q.pop();
        if (v[x]) continue;
        v[x] = 1;
        for (auto [y, w]: g[x]) // 链式前向星遍历与一点相连所有边
        {
            if (d[y] > d[x] + w)
            {
                d[y] = d[x] + w;
                q.push({d[y], y});
            } // 松弛操作，插入堆
        }
    }
}
