#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define inf 0x3f3f3f3f
#define pii pair<int, int>
const int N = 5e5 + 5;

// n点数，m边数，s出发点
int tot = 0, n, m, k, s, t;
// d数组表示出发点到该点的最短距离，v数组表示是否访问过
int hea[N], d[N], v[N];

priority_queue<pii, vector<pii>, greater<pii>> q; // 小根堆
struct edge
{
    int next, to, dis;
} edge[N];                    // 链式前向星
void add(int x, int y, int w) // 起点，终点，权值
{
    edge[++tot].next = hea[x];
    edge[tot].to = y;
    edge[tot].dis = w;
    hea[x] = tot;
}

// 堆优化的dijkstra
void dijkstra()
{
    memset(d, inf, sizeof d);
    d[s] = 0;
    q.push({0, s});
    while (!q.empty())
    {
        int x = q.top().second;
        q.pop();
        if (v[x]) continue;
        v[x] = 1;
        for (int i = hea[x]; i; i = edge[i].next) // 链式前向星遍历与一点相连所有边
        {
            int y = edge[i].to;
            if (d[y] > d[x] + edge[i].dis)
            {
                d[y] = d[x] + edge[i].dis;
                if (v[y] == 0)
                    q.push({d[y], y});
            } // 松弛操作，插入堆
        }
    }
}
signed main()
{
    scanf("%d%d%d%d%d", &n, &m, &k, &s, &t);
    s++, t++;
    for (int i = 1; i <= m; i++)
    {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        x++, y++;
        add(x, y, w), add(y, x, w);
        for (int j = 1; j <= k; j++) // 一共k层
        {
            add(x + (j - 1) * n, y + j * n, 0), add(y + (j - 1) * n, x + j * n, 0);
            add(x + j * n, y + j * n, w), add(y + j * n, x + j * n, w);
        }
    }
    dijkstra();
    int ans = inf;
    for (int i = 0; i <= k; i++)
        ans = min(ans, d[t + i * n]);
    printf("%d\n", ans);
}
