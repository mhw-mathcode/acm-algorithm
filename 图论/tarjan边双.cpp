#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define inf 0x3f3f3f3f
const int N = 5e5 + 5;
int n, m;
int tmp, dfn[N], low[N];
vector<pii> g[N << 1];
// 无向图缩点
// 求边双连通分量，注意可能出现重边
// 标记桥边
map<pii, bool> mp;
void dfs(int u, int las)
{
    dfn[u] = low[u] = ++tmp;
    for (auto [v, w] : g[u])
    {
        if (dfn[v] == 0)
        {
            dfs(v, w);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u])
                mp[{u, v}] = 1, mp[{v, u}] = 1;
        }
        else if (w != (las ^ 1))
            low[u] = min(low[u], dfn[v]);
    }
}

int vis[N], cnt;
vector<int> ans[N];
void dfs2(int u)
{
    ans[cnt].push_back(u);
    for (auto [v, w] : g[u])
    {
        if (vis[v]) continue;
        if (mp[{u, v}] || mp[{v, u}]) continue;
        vis[v] = 1;
        dfs2(v);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back({v, i << 1}),
        g[v].push_back({u, i << 1 | 1});
    }
    mp.clear();
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) dfs(i, 0);
    for (int i = 1; i <= n; i++)
    {
        if (vis[i] == 0)
        {
            cnt++;
            vis[i] = 1;
            dfs2(i);
        }
    }
    cout << cnt << endl;
    for (int i = 1; i <= cnt; i++)
    {
        cout << ans[i].size() << " ";
        for (auto j : ans[i])
            cout << j << " ";
        cout << endl;
    }
    return 0;
}