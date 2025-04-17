#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;

int tot = 0, hea[N];
struct edge
{
    int next, to;
} edge[N << 1];
void add(int u, int v)
{
    edge[++tot] = {hea[u], v};
    hea[u] = tot;
}

// dep表示每个点的深度，fa[i][j]表示节点i的2^j级祖先
int dep[N], fa[N][22], lg[N];
void dfs(int now, int fath)
{
    fa[now][0] = fath;
    dep[now] = dep[fath] + 1;
    for (int i = 1; i <= lg[dep[now]]; i++)
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
    for (int i = hea[now]; i; i = edge[i].next)
        if (edge[i].to != fath) dfs(edge[i].to, now);
}
int lca(int x, int y)
{
    if (dep[x] < dep[y]) swap(x, y);
    while (dep[x] > dep[y]) x = fa[x][lg[dep[x] - dep[y]] - 1];
    if (x == y) return x;
    for (int k = lg[dep[x]] - 1; k >= 0; k--)
        if (fa[x][k] != fa[y][k]) x = fa[x][k], y = fa[y][k];
    return fa[x][0];
}

int main()
{
    int n;
    for (int i = 1; i <= n; i++)
        lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);   
}