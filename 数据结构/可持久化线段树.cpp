#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
const int N = 1e6 + 5;
// rk[i]表示第i个版本的根节点编号
int a[N], rk[N], cnt;
struct node
{
    int ls, rs, val;
} t[N * 30];
void build(int &k, int l, int r)
{
    k = ++cnt;
    if (l == r)
    {
        t[k].val = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(t[k].ls, l, mid);
    build(t[k].rs, mid + 1, r);
}
void modify(int &k, int l, int r, int pre, int pos, int val)
{
    k = ++cnt;
    t[k] = t[pre];
    if (l == r)
    {
        t[k].val = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) modify(t[k].ls, l, mid, t[pre].ls, pos, val);
    else modify(t[k].rs, mid + 1, r, t[pre].rs, pos, val);
}
int query(int k, int l, int r, int pos)
{
    if (l == r) return t[k].val;
    int mid = (l + r) >> 1;
    if (pos <= mid) return query(t[k].ls, l, mid, pos);
    else return query(t[k].rs, mid + 1, r, pos);
}

void solve()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(rk[0], 1, n);
    for (int i = 1; i <= m; i++)
    {
        int v, op, pos, val;
        cin >> v >> op >> pos;
        if (op == 1)
        {
            cin >> val;
            modify(rk[i], 1, n, rk[v], pos, val);
        }
        else
        {
            cout << query(rk[v], 1, n, pos) << '\n';
            rk[i] = rk[v];
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1; // cin>>T;
    while (T--) solve();
    return 0;
}