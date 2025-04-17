#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
#define inf 0x3f3f3f3f3f3f3f3f
const int N = 1e5 + 5;

// n点数，m边数，s出发点
int tot = 0, n, m, s;
int hea[N * 30];
struct edge
{
    int next, to, dis;
} edge[N * 30];
void add(int x, int y, int w)
{
    edge[++tot] = {hea[x], y, w};
    hea[x] = tot;
}

int d[N * 30], v[N * 30];
priority_queue<pii, vector<pii>, greater<pii>> q;
void dijkstra()
{
    memset(d, 0x3f, sizeof d);
    d[s] = 0;
    q.push({0, s});
    while (!q.empty())
    {
        int x = q.top().second;
        q.pop();
        if (v[x]) continue;
        v[x] = 1;
        for (int i = hea[x]; i; i = edge[i].next)
        {
            int y = edge[i].to;
            if (d[y] > d[x] + edge[i].dis)
            {
                d[y] = d[x] + edge[i].dis;
                q.push({d[y], y});
            }
        }
    }
}

namespace segtree_for_graph // 连边都为单向边
{    
    int rt1, rt2, cnt;
    int ls[N * 30], rs[N * 30];
    int in[N * 30], out[N * 30];

    #define ls ls[rt]
    #define rs rs[rt]

    void build_in(int &rt, int l, int r)
    {
        rt = ++cnt;
        if (l == r)
        {
            in[l] = rt;
            return;
        }
        int mid = (l + r) >> 1;
        build_in(ls, l, mid);
        build_in(rs, mid + 1, r);
        add(ls, rt, 0);
        add(rs, rt, 0);
    }
    void build_out(int &rt, int l, int r)
    {
        rt = ++cnt;
        if (l == r)
        {
            out[l] = rt;
            return;
        }
        int mid = (l + r) >> 1;
        build_out(ls, l, mid);
        build_out(rs, mid + 1, r);
        add(rt, ls, 0);
        add(rt, rs, 0);
    }
    void modify_in(int rt, int l, int r, int ql, int qr, int pos, int val)
    {
        if (ql > r || qr < l) return;
        if (ql <= l && qr >= r)
        {
            add(rt, pos, val);
            return;
        }
        int mid = (l + r) >> 1;
        modify_in(ls, l, mid, ql, qr, pos, val);
        modify_in(rs, mid + 1, r, ql, qr, pos, val);
    }
    void modify_out(int rt, int l, int r, int ql, int qr, int pos, int val)
    {
        if (ql > r || qr < l) return;
        if (ql <= l && qr >= r)
        {
            add(pos, rt, val);
            return;
        }
        int mid = (l + r) >> 1;
        modify_out(ls, l, mid, ql, qr, pos, val);
        modify_out(rs, mid + 1, r, ql, qr, pos, val);
    }
    int num; // 记得赋初值，初值大于等于已有节点数
    void modify(int rt1, int rt2, int l, int r, int l1, int r1, int l2, int r2, int val) // 区间向区间连边
    {
        num++;
        modify_in(rt1, l, r, l1, r1, out[num], 0);
        modify_out(rt2, l, r, l2, r2, in[num], val);
    }
    void build(int n) // 初始化，n为总点数
    {
        build_in(rt1, 1, n);
        build_out(rt2, 1, n);
        for (int i = 1; i <= n; i++) 
        {
            add(in[i], out[i], 0);
            add(out[i], in[i], 0);
        }
    }
};
using namespace segtree_for_graph;


void solve()
{
    cin >> n >> m >> s;

    // 初始化建树
    build(n);

    for (int i = 1; i <= m; i++)
    {
        int op; cin >> op;
        if (op == 1) // 单点向单点连边
        {
            int u, v, val;
            cin >> u >> v >> val;
            add(in[u], out[v], val);
        }
        else if(op == 2) // 单点向区间连边
        {
            int u, l, r, val;
            cin >> u >> l >> r >> val;
            modify_out(rt2, 1, n, l, r, in[u], val);
        }
        else // 区间向单点连边
        {
            int v, l, r, val;
            cin >> v >> l >> r >> val;
            modify_in(rt1, 1, n, l, r, out[v], val);
        }
    }

    s = in[s];
    dijkstra();
    for (int i = 1; i <= n; i++)
    {
        if (d[out[i]] >= inf) cout << -1 << " ";
        else cout << d[out[i]] << " ";
    }
    cout << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1; // cin >> T;
    while (T--) solve();
    return 0;
}