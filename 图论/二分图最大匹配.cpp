#include <bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
const int N = 2e5 + 5;

// 顶点数，边数，源点，汇点
int n, m, s, t;

int tot = 1, hea[N];
struct edge
{
    int next, to, dis;
} edge[N];                    // 链式前向星
void add(int u, int v, int w) // 起点，终点，权值
{
    edge[++tot] = {hea[u], v, w};
    hea[u] = tot;
}

// lv是每个点的层数，cur用于当前弧优化标记增广起点
int lv[N], cur[N];
int bfs() // bfs分层
{
    memset(lv, -1, sizeof lv);
    lv[s] = 0;
    memcpy(cur, hea, sizeof(hea)); // 当前弧优化初始化
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        int p = q.front();
        q.pop();
        for (int i = hea[p]; i; i = edge[i].next)
        {
            int v = edge[i].to, w = edge[i].dis;
            if (w > 0 && lv[v] == -1) lv[v] = lv[p] + 1, q.push(v);
        }
    }
    return lv[t] != -1; // 如果汇点未访问过说明已经无法达到汇点，此时返回false
}
int dfs(int p = s, int flow = inf)
{
    if (p == t) return flow;
    int rmn = flow; // 剩余的流量
    for (int i = cur[p]; i && rmn; i = edge[i].next)
    {
        cur[p] = i;
        int v = edge[i].to, w = edge[i].dis;
        if (w > 0 && lv[v] == lv[p] + 1)
        {
            int c = dfs(v, min(w, rmn));
            rmn -= c;
            edge[i].dis -= c;
            edge[i ^ 1].dis += c;
        }
    }
    return flow - rmn;
}
int dinic()
{
    int ans = 0;
    while (bfs()) ans += dfs();
    return ans;
}

void solve()
{
    int e;
    cin >> n >> m >> e;
    for (int i = 1; i <= e; i++)
    {
        int u, v;
        cin >> u >> v;
        add(u, v + n, 1);
        add(v + n, u, 0);
    }
    s = n + m + 1, t = n + m + 2;
    for (int i = 1; i <= n; i++)
    {
        add(s, i, 1);
        add(i, s, 0);
    }
    for (int i = 1; i <= m; i++)
    {
        add(i + n, t, 1);
        add(t, i + n, 0);
    }
    cout << dinic() << endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1; // cin>>T;
    while (T--) solve();
    return 0;
}