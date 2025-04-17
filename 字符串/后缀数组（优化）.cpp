#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
const int N = 1e6 + 5;
char s[N];
// key1[i] = rk[id[i]]（作为基数排序的第一关键字数组）
int n, sa[N], rk[N], oldrk[N << 1], id[N], key1[N], cnt[N];
bool cmp(int x, int y, int w)
{
    return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
}
void SA(string t)
{
    // memset(id, 0, sizeof id);
    // memset(key1, 0, sizeof key1);
    memset(cnt, 0, sizeof cnt);

    n = t.size();
    for (int i = 1; i <= n; i++) s[i] = t[i - 1];
    // 记得更改 m 
    int i, m = 127, p, w;
    for (i = 1; i <= n; i++) ++cnt[rk[i] = s[i]];
    for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (i = n; i >= 1; i--) sa[cnt[rk[i]]--] = i;

    for (w = 1;; w <<= 1, m = p) // m=p就是优化计数排序值域
    {
        for (p = 0, i = n; i > n - w; i--) id[++p] = i;
        for (i = 1; i <= n; i++)
            if (sa[i] > w) id[++p] = sa[i] - w;
        memset(cnt, 0, sizeof(cnt));
        for (i = 1; i <= n; ++i) ++cnt[key1[i] = rk[id[i]]];
        // 注意这里px[i]!=i，因为rk没有更新，是上一轮的排名数组

        for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; i--) sa[cnt[key1[i]]--] = id[i];
        memcpy(oldrk + 1, rk + 1, n * sizeof(int));
        for (p = 0, i = 1; i <= n; i++) rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
        if (p == n) break;
    }
    // for (int i = 1; i <= n; i++) cout << sa[i];
    
}
int ht[N];
void init_ht(int n)
{
    for (int i = 1, k = 0; i <= n; i++)
    {
        if (k > 0) k--;
        while (s[i + k] == s[sa[rk[i] - 1] + k]) k++;
        ht[rk[i]] = k;
    }
}
int cal_string()
{
    init_ht(n);
    int ans = 0;
    for (int i = 2; i <= n; i++) ans += ht[i];
    return n * (n + 1) / 2 - ans;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1; // cin>>T;
    while (T--) solve();
    return 0;
}