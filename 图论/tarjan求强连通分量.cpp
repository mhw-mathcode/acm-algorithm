#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
const int N = 1e5 + 5;
// 求解强连通分量SCC
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

// dfn[i]表示结点i的搜索次序编号（时间戳）
// low[i]表示结点i或者结点i的子树最多能回溯到达的最小时间戳
// stac手写栈
// color相同的点在同一SCC
int dfn[N], low[N], stac[N], color[N];
// tmp表示当前时间戳，top表示栈顶，col表示强连通分量个数
int tmp, top, col;
void tarjan(int u)
{
    dfn[u] = low[u] = ++tmp;
    stac[++top] = u;
    for (int i = hea[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (dfn[v] == 0)
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (color[v] == 0)
            low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u])
    {
        color[u] = ++col;
        while (stac[top] != u)
        {
            color[stac[top]] = col;
            --top;
        }
        --top;
    }
}

int v[N];
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        add(u, v);
    }

    // 将每个结点都放进一个SCC
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            tarjan(i);

    cout << col << "\n";
    for (int i = 1; i <= n; i++)
    {
        if (v[i] == 0)
        {
            cout << i << " ";
            for (int j = i + 1; j <= n; j++)
            {
                if (color[i] == color[j])
                {
                    cout << j << " ";
                    v[j] = 1;
                }
            }
            cout << "\n";
        }
    }
    return 0;
}