#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>

#define ls k << 1
#define rs k << 1 | 1

const int N = 5e5 + 5;
int n;
struct BCJ // 可撤销并查集
{
    int n, fa[N], dep[N];
    void init(int x)
    {
        n = x;
        for (int i = 1; i <= 2 * n; i++)
            fa[i] = i, dep[i] = 1;
    }
    int find(int x)
    {
        // 不能使用路径压缩
        return x == fa[x] ? x : find(fa[x]);
    }
    void merge(int x, int y, stack<int> &sta)
    {
        x = find(x), y = find(y);
        if (x == y) return;
        if (dep[x] < dep[y]) swap(x, y);
        fa[y] = x;
        dep[x] = max(dep[x], dep[y] + 1);
        sta.push(y);
    }
    void roll_back(stack<int> &sta)
    {
        while (!sta.empty())
        {
            int x = sta.top();
            sta.pop();
            fa[x] = x;
        }
    }
} b;

vector<pii> t[N << 2];
void update(int k, int l, int r, int p, int q, int u, int v)
{
    if (p <= l && r <= q)
    {
        t[k].push_back({u, v});
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) update(ls, l, mid, p, q, u, v);
    if (q > mid) update(rs, mid + 1, r, p, q, u, v);
}
int ans[N];
void dfs(int k, int l, int r)
{
    stack<int> s;
    for (auto [u, v] : t[k]) // 遍历节点k的所有操作
    {
        if (b.find(u) == b.find(v))
        {
            for (int i = l; i <= r; i++) ans[i] = 0;
            b.roll_back(s);
            return;
        }
        b.merge(u, v + n, s);
        b.merge(u + n, v, s);
    }
    if (l != r)
    {
        int mid = (l + r) >> 1;
        dfs(ls, l, mid);
        dfs(rs, mid + 1, r);
    }
    b.roll_back(s);
}

void solve()
{
    int m, k;
    cin >> n >> m >> k;
    b.init(n);
    for (int i = 1; i <= n; i++) ans[i] = 1;
    for (int i = 1; i <= m; i++)
    {
        int x, y, l, r;
        cin >> x >> y >> l >> r;
        update(1, 1, k, l + 1, r, x, y);
    }
    dfs(1, 1, k);
    for (int i = 1; i <= n; i++)
        cout << (ans[i] ? "Yes" : "No") << endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1; // cin>>T;
    while (T--) solve();
    return 0;
}