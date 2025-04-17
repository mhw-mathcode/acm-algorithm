#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
#define inf 0x3f3f3f3f
#define endl '\n'
const int N = 2e5 + 5;
const int mod = 998244353;
struct node
{
    int l, y1, y2, op;
    bool operator<(const node &ot) {
        if (l == ot.l) return op > ot.op;
        return l < ot.l;
    }
} e[N << 1];

#define ls t[k].l
#define rs t[k].r

struct node1
{
    int l, r;
    int sum, tag;

    node1() {
        l = r = tag = sum = 0;
    }
} t[N * 30];

int tot = 0, rt = 0;
void pushup(int k, int l, int r)
{
    if (t[k].tag) t[k].sum = (r - l + 1);
    else t[k].sum = t[ls].sum + t[rs].sum;
}
void modify(int &k, int l, int r, int p, int q, int val)
{
    if (!k) k = ++tot;
    if (p <= l && r <= q)
    {
        t[k].tag += val;
        pushup(k, l, r);
        return;
    }

    int mid = (l + r) >> 1;
    if (p <= mid) modify(ls, l, mid, p, q, val);
    if (mid < q) modify(rs, mid + 1, r, p, q, val);
    pushup(k, l, r);
}

#undef ls
#undef rs

int b[N];
void solve()
{
    int n;
    cin >> n;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        e[++cnt] = {x1, y1, y2, 1};
        e[++cnt] = {x2, y1, y2, -1};
    }
    sort(e + 1, e + cnt + 1);

    // 求解矩阵覆盖面积
    int ans = 0, las = 0;
    for (int i = 1; i <= cnt; i++)
    {
        auto [l, y1, y2, op] = e[i];
        ans += t[1].sum * (l - las);
        las = l;
        modify(rt, 0, 1e9, y1, y2 - 1, op);
    }

    // // 求解矩阵覆盖点数
    // for (int i = 1; i <= cnt; i++)
    // {
    //     auto [l, y1, y2, op] = e[i];
    //     b[l] = max (b[l], t[1].sum);
    //     modify(rt, 0, n, y1, y2, op);
    // }
    // for (int i = 1; i <= n; i++) ans += b[i];

    cout << ans << endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1; // cin >> T;
    while (T--) solve();
    return 0;
}