#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;

struct DSU_on_tree
{
    vector<int> g[N];
    // 子树大小与重儿子编号
    int siz[N], son[N];
    // dfs序
    int l[N], r[N], dfn[N], rnk[N], tot;

    void dfs1(int u, int f)
    {
        l[u] = dfn[u] = ++tot;
        rnk[tot] = u;
        siz[u] = 1;
        for (auto v : g[u])
        {
            if (v == f) continue;
            dfs1(v, u);
            siz[u] += siz[v];
            if (!son[u] || siz[v] > siz[son[u]]) son[u] = v;
        }
        r[u] = tot;
    }

    int ans[N];
    void add(int u)
    {
        // 添加节点计算贡献
    }
    void del(int u)
    {
        // 删除节点消除贡献
    }
    void dfs2(int u, int f, int keep)
    {
        for (auto v : g[u])
        {
            if (v == f || v == son[u]) continue;
            dfs2(v, u, 0); // 先计算轻儿子的答案
        }
        if (son[u]) dfs2(son[u], u, 1); // 重儿子贡献保留
        for (auto v : g[u])
        {
            if (v == f || v == son[u]) continue;
            for (int i = l[v]; i <= r[v]; i++)
                add(rnk[i]); // 添加轻的贡献儿子
        }
        add(u);
        // 计算u节点答案

        if (keep == 0)
        {
            for (int i = l[u]; i <= r[u]; i++)
                del(rnk[i]);
        }
    }
};
