#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 2e5 + 5;
const int mod = 998244353;
int cnt, rk[N];
struct node
{
    int ls, rs, val, lz;
} t[N * 30];
void build(int &k, int l, int r)
{
    k = ++cnt;
    if (l == r) return;
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
        t[k].val++;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) modify(t[k].ls, l, mid, t[pre].ls, pos, val);
    else modify(t[k].rs, mid + 1, r, t[pre].rs, pos, val);
    t[k].val = t[t[k].ls].val + t[t[k].rs].val;
}
int query(int l, int r, int p, int q, int kth)
{
    if (p == q) return p;
    // x为l~r这段区间内左儿子出现的数量
    int mid = (p + q) >> 1, x = t[t[r].ls].val - t[t[l].ls].val;
    if (x >= kth) return query(t[l].ls, t[r].ls, p, mid, kth);
    else return query(t[l].rs, t[r].rs, mid + 1, q, kth - x);
}
int a[N];
void solve()
{
    int n, m;
    cin >> n >> m;
    map<int, int> mp, num, xu;
    build(rk[0], 1, cnt);
    for (int i = 1; i <= n; i++)
        modify(rk[i], 1, cnt, rk[i - 1], num[a[i]], 1);
    while (m--)
    {
        int l, r, k;
        cin >> l >> r;
        k = (r - l) / 2  + 1;
        int t = query(rk[l - 1], rk[r], 1, cnt, k);
        cout << xu[t] << endl;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1; // cin>>T;
    while (T--) solve();
    return 0;
}