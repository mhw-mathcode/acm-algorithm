#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
const int N = 2e5 + 5;

// 缩点，同一连通分量里的所有点缩为一个点

// 点数，边数
int n, m;

// 前向星存图
int hea[N], tot;
struct edge
{
    int next, to;
} edge[N << 1];
void add(int x, int y)
{
    edge[++tot] = {hea[x], y};
    hea[x] = tot;
}

int w[N]; // 点的权值
int siz[N];

// dfn[i]表示结点i的搜索次序编号（时间戳）
// low[i]表示结点i或者结点i的子树最多能回溯到达的最小时间戳
// stac手写栈
// color相同的点在同一SCC
// belong表示该点所在强连通分量里的标志点
int dfn[N], low[N], stac[N], color[N], vis[N], belong[N];
// tmp表示当前时间戳，top表示栈顶，col表示强连通分量个数
int tmp, top, col;
void tarjan(int u)
{
    dfn[u] = low[u] = ++tmp;
    stac[++top] = u;
    vis[u] = 1;
    for (int i = hea[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (dfn[v] == 0)
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u])
    {
        color[u] = ++col;
        while (stac[top] != u)
        {
            int v = stac[top];
            belong[v] = u;
            vis[v] = 0;
            color[v] = col;
            w[u] += w[v]; // 将点权值都加到代表点上
            --top;

            // 维护一些信息
            siz[col]++;
        }

        // 维护一些信息（同上）
        siz[col]++;

        belong[u] = u;
        vis[u] = 0;
        --top;
    }
}

pii t[N];
int dp[N];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        t[i] = {i, x};
        add(i, x);
    }

    // 将每个结点都放进一个SCC
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            tarjan(i);

    // 重置图，新建缩点之后的图
    memset(hea, 0, sizeof hea);
    tot = 0;
    for (auto [u, v] : t)
    {
        if (color[u] != color[v])
            add(color[u], color[v]);
    }

    // 默认拓扑序，直接dp

    int ans = 0;
    for (int i = 1; i <= col; i++)
    {
        dp[i] = siz[i] * siz[i];
        for (int j = hea[i]; j; j = edge[j].next)
        {
            int v = edge[j].to;
            dp[i] += siz[v], siz[i] += siz[v];
        }
    }
    for (int i = 1; i <= col; i++)
        ans += dp[i];
    cout << ans << endl;

    return 0;
}