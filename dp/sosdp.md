用于解决这类问题：

对于所有的i， $0\leq i \leq 2^n-1,求解\sum_{j\subset i}a_{j}$ 。

```cpp
for(int j = 0; j < n; j++) 
    for(int i = 0; i < 1 << n; i++)
        if(i >> j & 1) f[i] += f[i ^ (1 << j)];
```
[题目1](https://www.luogu.com.cn/problem/CF383E)
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define inf 0x3f3f3f3f
#define db double
#define il inline
#define x first
#define y second
#define endl '\n'
const int N=2e5+5;
const int mod=998244353;
string a[N];
int dp[1<<24];
void solve()
{
    int n;cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        int u=(1<<(a[i][0]-'a')|(1<<(a[i][1]-'a'))|(1<<(a[i][2]-'a')));
        dp[u]++;
    }
    for(int j=0;j<24;j++)
    {
        for(int i=0;i<(1<<24);i++)
        {

            if(i>>j&1) dp[i]+=dp[i^(1<<j)];
        }
    }
    int ans=0;
    for(int i=0;i<(1<<24);i++) ans^=(n-dp[i])*(n-dp[i]);
    cout<<ans<<endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T=1;//cin>>T;
    while(T--)
    {
        solve();
    }
    return 0;
}
```
