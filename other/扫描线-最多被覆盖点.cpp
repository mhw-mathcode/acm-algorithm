#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
#define inf 0x3f3f3f3f
#define endl '\n'
const int N = 2e4 + 5; 
const int mod = 998244353;
struct node
{
    int l, y1, y2, op;
    bool operator<(const node &ot) {
        if(l == ot.l) return op > ot.op;
        return l < ot.l;
    }
} e[N << 2];

#define ls t[k].l
#define rs t[k].r
struct node1
{
    int l, r, mx;
    int tag;

    node1() {
        l = r = mx = tag = 0;
    }
} t[N * 180]; // 注意空间，256M空间2e5大概对应30倍

int tot = 0, rt = 0;
void pushdown(int k)
{
    if (!ls) ls = ++tot;
    t[ls].mx += t[k].tag;
    t[ls].tag += t[k].tag;

    if (!rs) rs = ++tot;
    t[rs].mx += t[k].tag;
    t[rs].tag += t[k].tag;

    t[k].tag = 0;
}
void modify(int &k, int l, int r, int p, int q, int val)
{
    if (!k) k = ++tot;
    if (p <= l && r <= q)
    {
        t[k].mx += val;
        t[k].tag += val;
        return;
    }
    pushdown(k);
    int mid = (l + r) >> 1;
    if (mid >= p) modify(ls, l, mid, p, q, val);
    if (mid < q) modify(rs, mid + 1, r, p, q, val);

    t[k].mx = max (t[ls].mx, t[rs].mx);
}
#undef ls
#undef rs

void solve()
{
    int n, h, w; 
    cin >> n >> h >> w;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        int x, y, v; cin >> x >> y >> v;
        e[++cnt] = {x, y, y + w - 1, v};
        e[++cnt] = {x + h - 1, y, y + w - 1, -v};
    }
    sort(e + 1, e + cnt + 1);
    int ans = 0;
    for (int i = 1; i <= cnt; i++)
    {
        auto [l, y1, y2, op] = e[i];
        modify(rt, 0, 2e9, y1, y2, op);
        ans = max(ans, t[1].mx);
    }
    cout << ans << endl;
    
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1; cin >> T;
    while (T--) solve();
    return 0;
}


/*
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
#define inf 0x3f3f3f3f
#define endl '\n'
const int N = 1e6 + 5;
const int mod = 998244353;
struct node
{
    int l, y1, y2, op;
    bool operator<(const node &ot) {
        if(l == ot.l) return op > ot.op;
        return l < ot.l;
    }
} e[N << 2];

#define ls t[k].l
#define rs t[k].r

struct node1
{
    int l, r, mx, id;
    int tag;

    node1() {
        l = r = mx = id = tag = 0;
    }
} t[N << 4];

int tot = 0, rt = 0;
void pushdown(int k, int l, int r)
{
    int mid = (l + r) >> 1;
    if (!ls)
    {
        ls = ++tot;
        t[ls].id = l;
    }
    t[ls].mx += t[k].tag;
    t[ls].tag += t[k].tag;

    if (!rs)
    {
        rs = ++tot;
        t[rs].id = mid + 1;
    }
    t[rs].mx += t[k].tag;
    t[rs].tag += t[k].tag;

    t[k].tag = 0;
}
void modify(int &k, int l, int r, int p, int q, int val)
{
    if (!k)
    {
        k = ++tot;
        t[k].id = l;
    }
    if (p <= l && r <= q)
    {
        t[k].mx += val;
        t[k].tag += val;
        return;
    }
    pushdown(k, l, r);
    int mid = (l + r) >> 1;
    if (mid >= p) modify(ls, l, mid, p, q, val);
    if (mid < q) modify(rs, mid + 1, r, p, q, val);

    if (t[ls].mx >= t[rs].mx) 
        t[k].id = t[ls].id, t[k].mx = t[ls].mx;
    else 
        t[k].id = t[rs].id, t[k].mx = t[rs].mx;
}

#undef ls
#undef rs

void solve()
{
    int n; cin >> n;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        int l, r;
        cin >> l >> r;
        e[++cnt] = {0, l + 1, r - 1, 1};
        e[++cnt] = {l - 1, l + 1, r - 1, -1};
        e[++cnt] = {l + 1, r + 1, (int)1e9, 1};
        e[++cnt] = {r - 1, r + 1, (int)1e9, -1};
    }
    sort(e + 1, e + cnt + 1);
    int ans = 0, ansl = 0, ansr = 1;
    for (int i = 1; i <= cnt; i++)
    {
        auto [l, y1, y2, op] = e[i];
        modify(rt, 0, 1e9, y1, y2, op);
        if(l >=0 && t[1].mx > ans) 
        {
            ans = t[1].mx;
            ansl = l; 
            ansr = t[1].id;
        }
    }
    cout << ansl << " " << ansr <<'\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1; // cin >> T;
    while (T--) solve();
    return 0;
}
*/