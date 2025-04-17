#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 2e5 + 5;
const int mod = 998244353;

int a[N];

// 计算数组a区间l-r本质不同的子序列数
int temp[N], dp[N], last[N];
int cal(int l, int r)
{
    int n = r - l + 1;
    for (int i = l; i <= r; i++)
        temp[i] = a[l + i - 1];
    for (int i = 1; i <= n; i++)
    {
        if (!last[a[i]]) dp[i] = (dp[i - 1] * 2 + 1) % mod;
        else dp[i] = (((dp[i - 1] * 2 - dp[last[a[i]] - 1]) % mod) + mod) % mod;

        dp[i] = (dp[i] + mod) % mod;
        last[a[i]] = i;
    }
    return dp[n];
}

void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    cout << cal(1, n) << endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1; // cin>>T;
    while (T--)
        solve();
    return 0;
}