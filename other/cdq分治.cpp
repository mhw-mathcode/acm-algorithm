#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
const int N = 2e5 + 5;
const int mod = 998244353;

struct node
{
    // ans存储与该点构成偏序关系的点数目
    // w表示该点的个数（因为需要去重）
    int x, y, z, ans, w;
} a[N], b[N];

int n;
int cmpx(node a, node b)
{
    if (a.x == b.x)
    {
        if (a.y == b.y) return a.z < b.z;
        return a.y < b.y;
    }
    return a.x < b.x;
}
int cmpy(node a, node b)
{
    if (a.y == b.y) return a.z < b.z;
    return a.y < b.y;
}

struct BIT
{
    int n, t[N];
    int lowbit(int x) { return x & (-x); }
    void update(int pos, int k)
    {
        for (int i = pos; i <= n; i += lowbit(i))
            t[i] += k;
    }
    int ask(int pos)
    {
        int ans = 0;
        for (int i = pos; i; i -= lowbit(i))
            ans += t[i];
        return ans;
    }
} t;
void cdq(int l, int r)
{
    if (l == r) return;
    int mid = (l + r) >> 1;
    cdq(l, mid);
    cdq(mid + 1, r);
    sort(a + l, a + mid + 1, cmpy);
    sort(a + mid + 1, a + r + 1, cmpy);
    int j = l;
    for (int i = mid + 1; i <= r; i++)
    {
        while (a[j].y <= a[i].y && j <= mid)
            t.update(a[j].z, a[j].w), j++;
        a[i].ans += t.ask(a[i].z);
    }
    for (int i = l; i < j; i++)
        t.update(a[i].z, -a[i].w);
}
int cnt[N];
void solve()
{
    int k;
    cin >> n >> k;
    t.n = k;
    for (int i = 1; i <= n; i++)
        cin >> b[i].x >> b[i].y >> b[i].z;
    sort(b + 1, b + n + 1, cmpx);

    // 需要去重
    int num = 0, nn = 0;
    for (int i = 1; i <= n; i++)
    {
        num++;
        if (b[i].x != b[i + 1].x || b[i].y != b[i + 1].y || b[i].z != b[i + 1].z)
            a[++nn] = b[i], a[nn].w = num, num = 0;
    }
    cdq(1, nn);

    for (int i = 1; i <= nn; i++)
        cnt[a[i].ans + a[i].w - 1] += a[i].w;
    for (int i = 0; i < n; i++)
        cout << cnt[i] << endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1; // cin>>T;
    while (T--) solve();
    return 0;
}