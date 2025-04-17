#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
#define inf 0x3f3f3f3f
const int N = 5e5 + 5;
const int mod = 998244353;
int n;

int tot, hea[N];
struct edge
{
    int next, to, dis;
} edge[N];
void add(int x, int y, int w)
{
    edge[++tot] = {hea[x], y, w};
    hea[x] = tot;
}

int a[N], at[N];

//----------以下是线段树
#define ls p << 1
#define rs p << 1 | 1
struct tree
{
    int l, r;
    int mx, lz1, lz2; // lz1为区间加，lz2为区间覆盖
} t[4 * N + 2];
void build(int p, int l, int r)
{
    t[p].l = l;
    t[p].r = r; 
    t[p].lz2 = -inf;
    if (l == r) 
    {
        t[p].mx = at[l];
        return;
    }

    int mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    t[p].mx = max(t[ls].mx, t[rs].mx);
}
void spread(int p)
{
    if (t[p].lz2 != -inf) 
    {
        t[ls].mx = t[rs].mx = t[p].lz2;
        t[ls].lz2 = t[rs].lz2 = t[p].lz2;

        t[ls].lz1 = t[rs].lz1 = 0;
        t[p].lz2 = -inf;
    }
    if (t[p].lz1)
    {
        t[ls].mx += t[p].lz1;
        t[rs].mx += t[p].lz1;
        t[ls].lz1 += t[p].lz1; 
        t[rs].lz1 += t[p].lz1;
        t[p].lz1 = 0;
    }
}
void change(int p, int x, int y, int z, int op)
{
    if (x <= t[p].l && y >= t[p].r)
    {
        if (op == 1) // 区间加
        {
            t[p].mx += z;
            t[p].lz1 += z;
        }
        else // 区间赋值
        {
            t[p].mx = z;
            t[p].lz2 = z;
            t[p].lz1 = 0;
        }
        return;
    }
    spread(p); 
    int mid = (t[p].l + t[p].r) >> 1;
    if (x <= mid) change(ls, x, y, z, op); 
    if (y > mid) change(rs, x, y, z, op);
    t[p].mx = max(t[ls].mx, t[rs].mx); 
}
int ask(int p, int x, int y)
{
    if (x <= t[p].l && y >= t[p].r) return t[p].mx;
    spread(p); 
    int mid = (t[p].l + t[p].r) >> 1;
    int ans = 0;
    if (x <= mid) ans = max(ans, ask(ls, x, y));
    if (y > mid) ans = max(ans, ask(rs, x, y)); 
    return ans;
}
//----------以上是线段树

// dep深度，fa父节点，siz子树大小，son重儿子结点
int dep[N], fa[N], siz[N], son[N];
// id重链剖分后每个结点新编号，at新编号的初始值，top重链的顶节点
int dfn[N], cnt, top[N];
int btd[N];
// 重链剖分
void dfs1(int u, int f, int deep)
{
    dep[u] = deep;   // 标记每个结点的深度
    fa[u] = f;       // 标记每个结点的父节点
    siz[u] = 1;      // 标记每个结点的子树大小
    int maxson = -1; // 记录重儿子的儿子数
    for (int i = hea[u]; i; i = edge[i].next)
    {
        int v = edge[i].to, w = edge[i].dis;
        if (v == f) continue;
        btd[i / 2] = v;
        a[v] = w;
        dfs1(v, u, deep + 1);
        siz[u] += siz[v];
        if (siz[v] > maxson) son[u] = v, maxson = siz[v];
    }
}
void dfs2(int u, int topf) // u当前结点，topf是当前重链的顶端结点
{
    dfn[u] = ++cnt;  
    at[cnt] = a[u]; // dfn序数组
    top[u] = topf;
    if (!son[u]) return;
    dfs2(son[u], topf);
    for (int i = hea[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v); // 对于每一个轻儿子都有从他开始的一条链
    }
}

// 注意如果是边权转移到点权上的话，寻找路径时不要记录lca的贡献
int qrange(int x, int y)
{
    int ans = -inf;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        ans = max(ans, ask(1, dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    // ans = max(ans, ask(1, dfn[x], dfn[y]));
    ans = max(ans, ask(1, dfn[x] + 1, dfn[y]));
    return ans;
}
void uprange(int x, int y, int k, int op)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        change(1, dfn[top[x]], dfn[x], k, op);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    // change(1, dfn[x], dfn[y], k, op);
    change(1, dfn[x] + 1, dfn[y], k, op);
}

// 修改/查询子树信息
// int qson(int x)
// {
//     return ask(1, dfn[x], dfn[x] + siz[x] - 1);
// }
// void upson(int x, int k)
// {
//     change(1, dfn[x], dfn[x] + siz[x] - 1, k);
// }

signed main()
{
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        add(x, y, w), add(y, x, w);
    }
    dfs1(1, 0, 1);
    dfs2(1, 1);
    build(1, 1, n);
    
    return 0;
}
