#include <bits/stdc++.h>
using namespace std;

#define ls t[k].lson
#define rs t[k].rson

const int N = 2e5 + 5;
const int mod = 998244353;
int a[N], cnt, rk;
struct node
{
    int lson, rson;
    int sum, lazy;
} t[N << 2];

// 动态开点
void modify(int &k, int l, int r, int p, int q, int val)
{
    if (!k) k = ++cnt;
    t[k].sum += val * (q - p + 1);
    if (p == l && q == r)
    {
        t[k].lazy += val;
        return;
    }

    int mid = (l + r) >> 1;
    if (q <= mid) modify(ls, l, mid, p, q, val);
    else if (p > mid) modify(rs, mid + 1, r, p, q, val);
    else modify(ls, l, mid, p, mid, val), modify(rs, mid + 1, r, mid + 1, q, val);
}

// 永久化懒标记
int query(int k, int l, int r, int p, int q, int lz)
{
    if (!k) return 0;
    if (p == l && q == r) return t[k].sum + lz * (r - l + 1);
    int mid = (l + r) >> 1;
    if (q <= mid) return query(ls, l, mid, p, q, lz + t[k].lazy);
    else if (p > mid) return query(rs, mid + 1, r, p, q, lz + t[k].lazy);
    else return query(ls, l, mid, p, mid, lz + t[k].lazy) + query(rs, mid + 1, r, mid + 1, q, lz + t[k].lazy);
}

void solve()
{
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    // bulid(1, 1, n);
    for (int i = 1; i <= n; i++) modify(rk, 1, n, i, i, a[i]);
    while (q--)
    {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1)
        {
            int k;
            cin >> k;
            modify(rk, 1, n, x, y, k);
        }
        else cout << query(1, 1, n, x, y, 0) << endl;
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
