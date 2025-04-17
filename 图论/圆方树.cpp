#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>

// 二倍空间
const int N = 1e5 + 5;

int n, m;
int tmp, dfn[N], low[N];

int h1[N], h2[N], tot;
struct edge
{
    int next, to, dis;
} edge[N];
void add(int h[], int x, int y, int w)
{
    edge[++tot] = {h[x], y, w};
    h[x] = tot;
}

// s表示环上前缀，stot表示所在环的总权值
int s[N], stot[N], square;
// fa表示父亲节点，fw表示到达父亲节点的距离
int fa[N], fw[N];
void add_round_square(int x, int y, int w)
{
    int sum = w;
    for (int i = y; i != x; i = fa[i])
    {
        s[i] = sum;
        sum += fw[i];
    }
    stot[x] = s[x] = sum;
    add(h2, x, ++square, 0);
    for (int i = y; i != x; i = fa[i])
    {
        stot[i] = sum;
        add(h2, square, i, min(s[i], stot[i] - s[i]));
    }
}

void dfs(int u, int f)
{
    dfn[u] = low[u] = ++tmp;
    for (int i = h1[u]; i; i = edge[i].next)
    {
        int v = edge[i].to, w = edge[i].dis;
        if (v == f) continue;
        if (dfn[v] == 0)
        {
            fa[v] = u, fw[v] = w;
            dfs(v, u);
            low[u] = min(low[u], low[v]);

            // 圆点之间直接相连
            if (low[v] > dfn[u]) add(h2, u, v, w);
        }
        else low[u] = min(low[u], dfn[v]);
    }

    for (int i = h1[u]; i; i = edge[i].next)
    {
        int v = edge[i].to, w = edge[i].dis;
        if (dfn[v] > dfn[u] && fa[v] != u) add_round_square(u, v, w);
    }
}

// 任意两点最短距离
const int L = 14;
int f[N][L + 1], depth[N], dis[N];
int A, B;
void dfs2(int x, int fa) // 倍增算法预处理
{
    depth[x] = depth[fa] + 1;
    f[x][0] = fa;
    for (int i = 1; i <= L; ++i)
        f[x][i] = f[f[x][i - 1]][i - 1];
    for (int i = h2[x]; i; i = edge[i].next)
    {
        int v = edge[i].to, w = edge[i].dis;
        if (v != fa)
        {
            dis[v] = dis[x] + w;
            dfs2(v, x);
        }
    }
}

int LCA(int a, int b)
{
    if (depth[a] < depth[b]) swap(a, b);
    for (int i = L; i >= 0; --i)
        if (depth[f[a][i]] >= depth[b])
            a = f[a][i];
    if (a == b) return a;
    for (int i = L; i >= 0; --i)
        if (f[a][i] != f[b][i])
            a = f[a][i], b = f[b][i];
    A = a, B = b;
    return f[a][0];
}

int main()
{
    int q;
    cin >> n >> m >> q;
    square = n;
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        add(h1, u, v, w), add(h1, v, u, w);
    }
    dfs(1, 0); // 建圆方树

    dfs2(1, 0);
    int a, b;
    while (q--)
    {
        cin >> a >> b;
        int lca = LCA(a, b);
        if (lca <= n)
            cout << dis[a] + dis[b] - 2 * dis[lca] << endl;
        else
        {
            int res = dis[a] - dis[A] + dis[b] - dis[B];
            res += min(abs(s[A] - s[B]), stot[A] - abs(s[A] - s[B]));
            cout << res << endl;
        }
    }

    return 0;
}
