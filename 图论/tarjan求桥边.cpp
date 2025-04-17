#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
const int N = 2e5 + 5;
int n, m;
int tmp, dfn[N], low[N];
vector<pii> g[N << 1];
// 标记桥边（注意不能存在重边，如果存在请使用边双求桥边）
map<pii, bool> mp;
void dfs(int u, int fa)
{
    dfn[u] = low[u] = ++tmp;
    for (auto &i : g[u])
    {
        int v = i.first;
        if (dfn[v] == 0)
        {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u])
                mp[{u, v}] = 1, mp[{v, u}] = 1;
        }
        else if (v != fa)
            low[u] = min(low[u], dfn[v]);
    }
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        for (int i = 1; i <= m; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            g[u].push_back({v, w}), g[v].push_back({u, w});
        }
        mp.clear();
        for (int i = 1; i <= n; i++)
            if (!dfn[i]) dfs(i, 0);
    }
    return 0;
}