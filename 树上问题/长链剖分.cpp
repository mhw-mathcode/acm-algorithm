#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 5;

vector<int> g[N];
// 深度，部分链长，父节点，重儿子，链头，dfs序，子树最大dfs序，dfs序对应节点
int dep[N], len[N], fa[N], hson[N];
int top[N], dfsn[N], mdfsn[N], node[N], cnt;
void dfs1(int u, int d = 1)
{
    len[u] = 1, dep[u] = d;
    for (auto v: g[u])
    {
        if (!dep[v])
        {
            dfs1(v, d + 1);
            fa[v] = u;
            if (len[v] + 1 > len[u])
                hson[u] = v, len[u] = len[v] + 1;
        }
    }
}
void dfs2(int u, int tp)
{
    dfsn[u] = ++cnt;
    top[u] = tp;
    node[cnt] = u;
    if (hson[u]) dfs2(hson[u], tp);
    for (auto v: g[u])
        if (!top[v]) dfs2(v, v);
    mdfsn[u] = cnt;
}
void cut(int r = 1)
{
    dfs1(r);
    dfs2(r, r);
}
void clear(int n)
{
    for (int i = 0; i <= n; i++)
    {
        dep[i] = len[i] = fa[i] = hson[i] = top[i] = dfsn[i] = mdfsn[i] = node[i] = 0;
        g[i].clear();
    }
}
