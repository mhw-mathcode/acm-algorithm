#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define inf 0x3f3f3f3f
#define db double
#define il inline
#define x first
#define y second
const int N = 2e5 + 5;
const int mod = 998244353;
// n为要处理字符串（不限于）长度，下标从1开始
char s[N];
// sa[i]表示字典序第i小的后缀字符串的编号（即开始位置）
int n, w, sa[N], rk[N << 1], oldrk[N << 1];
bool cmp(int x, int y)
{
    return rk[x] == rk[y] ? rk[x + w] < rk[y + w] : rk[x] < rk[y];
}
void solve()
{
    for (int i = 1; i <= n; i++)
        sa[i] = i, rk[i] = s[i];
    for (w = 1; w < n; w <<= 1)
    {
        sort(sa + 1, sa + n + 1, cmp);
        memcpy(oldrk, rk, sizeof rk);
        for (int p = 0, i = 1; i <= n; i++)
        {
            if (oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) rk[sa[i]] = p;
            else rk[sa[i]] = ++p;
        }
    }
    // for (int i = 1; i <= n; i++)
    //     cout << sa[i] << endl;
    // cout << "\n";
}
// ht[i]表示sa[i]与sa[i-1]的最长公共前缀
// O(n)求出字符串本质不同的子串数量
// 求两个子串s1[l1,r1],s2[l2,r2]的最长公共前缀min(|s1|,|s2|,lcp(sa[l1],sa[l2]))，问题转化到求两个后缀的lcp，结合st表/线段树
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
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1; // cin>>T;
    while (T--) solve();
    return 0;
}