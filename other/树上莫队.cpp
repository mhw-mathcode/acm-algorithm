#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;

struct node
{
    int l, r, ll, rr, id, lca;
} q[N];
int n, m, a[N];

// 树剖相关
int st[N], ed[N], dfn[N], f[N], num, siz[N], his[N];
int dep[N], son[N], top[N];

int c[N], tmp, blo;
int use[N], ans[N], temp[N];
vector<int> g[N];
void dfs1(int u, int fa) // 树剖第一次深搜
{
    f[u] = fa;
    st[u] = ++num;
    siz[u] = 1;
    his[num] = u;
    dep[u] = dep[fa] + 1;
    for (auto v: g[u])
    {
        if (v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]])
            son[u] = v;
    }
    ed[u] = ++num;
    his[num] = u;
}
void dfs2(int u, int to) // 树剖第二次深搜
{
    top[u] = to;
    if (son[u]) dfs2(son[u], to);
    for (auto v: g[u])
    {
        if (v != son[u] && v != f[u])
            dfs2(v, v);
    }
}
int Lca(int x, int y) // 树剖求lca
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = f[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    return x;
}
void add(int x)
{
    if (c[a[x]] == 0) tmp++;
    c[a[x]]++;
}
void del(int x)
{
    c[a[x]]--;
    if (c[a[x]] == 0) tmp--;
}
void calc(int x) // 对点进行加入或删除
{
    (!use[x]) ? add(x) : del(x);
    use[x] ^= 1;
}
int cmp(node x, node y) // 排序
{
    return (x.ll == y.ll) ? (x.ll % 2 == 1 ? x.r < y.r : x.r > y.r) : x.l < y.l;
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i], temp[i] = a[i];
    sort(temp + 1, temp + n + 1);
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(temp + 1, temp + n + 1, a[i]) - temp; // 离散化
    int x, y;
    for (int i = 1; i < n; i++)
    {
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    blo = n * 2 / sqrt(m * 2 / 3);
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++)
    {
        cin >> x >> y;
        if (st[x] > st[y]) swap(x, y); // 保证stx<sty
        q[i].id = i;
        q[i].lca = Lca(x, y);
        if (q[i].lca == x) // x,y在以x为根的子树中
        {
            q[i].l = st[x];
            q[i].r = st[y];
            q[i].ll = st[x] / blo;
            q[i].rr = st[y] / blo;
            q[i].lca = 0;
        }
        else
        {
            q[i].l = ed[x];
            q[i].r = st[y];
            q[i].ll = ed[x] / blo;
            q[i].rr = st[y] / blo;
        }
    }
    sort(q + 1, q + m + 1, cmp);
    for (int i = 1; i <= m; i++)
    {
        while (l > q[i].l) calc(his[--l]);
        while (r < q[i].r) calc(his[++r]);
        while (l < q[i].l) calc(his[l++]);
        while (r > q[i].r) calc(his[r--]);
        if (q[i].lca) calc(q[i].lca);
        ans[q[i].id] = tmp;
        if (q[i].lca) calc(q[i].lca);
    }
    for (int i = 1; i <= m; i++) cout << ans[i] << '\n';
    return 0;
}