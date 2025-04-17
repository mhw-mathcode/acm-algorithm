#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
#define int long long
const int N = 5e4 + 5;
int len, n, m, k, c;
// b是桶
int ans[N], a[N], b[N];
struct node
{
    int l, r, id;
} modui[N];
// 首先按照l所在块排序，l所在块相同则按照r排序
bool cmp(node x, node y)
{
    if ((x.l - 1) / len != (y.l - 1) / len) return x.l < y.l;
    return ((x.l - 1) / len) & 1 ? x.r < y.r : x.r > y.r;
}

// 修改add与del函数
void add(int x)
{

}
void del(int x)
{
    
}

void solve()
{
    cin >> n >> m >> k;
    len = 313;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= m; i++)
    {
        int l, r;
        cin >> l >> r;
        modui[i] = {l, r, i};
    }
    sort(modui + 1, modui + m + 1, cmp);
    // ans1是上次的左端点，ans2是上次的右端点
    int lef, rig, ans1 = 1, ans2 = 0;
    for (int i = 1; i <= m; i++)
    {
        lef = modui[i].l, rig = modui[i].r;
        while (ans1 > lef) ans1--, add(a[ans1]);
        while (ans2 < rig) ans2++, add(a[ans2]);
        while (ans1 < lef) del(a[ans1]), ans1++;
        while (ans2 > rig) del(a[ans2]), ans2--;
        ans[modui[i].id] = c;
    }
    for (int i = 1; i <= m; i++)
        cout << ans[i] << "\n";
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1; // cin>>T;
    while (T--) solve();
    return 0;
}