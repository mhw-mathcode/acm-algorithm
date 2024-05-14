原来也有几次想要学一下数位dp，印象里每次都放弃了，感觉不能理解。这次看来记忆化搜索写数位dp，突然顿悟了！

[题目1](https://acm.hdu.edu.cn/showproblem.php?pid=2089)不要62，典中典的数位dp题目。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
const int N=2e5+5;
const int mod=998244353;
int dp[20][20],num[20];
int dfs(int pos,int pre,int lim)
{
    if(pos<1) return 1;
    if(!lim&&dp[pos][pre]!=-1) return dp[pos][pre];
    int top=lim?num[pos]:9;
    int ans=0;
    for(int i=0;i<=top;i++)
    {
        if(pre==6&&i==2) continue;
        if(i==4) continue;
        ans+=dfs(pos-1,i,lim&&i==top);
    }
    if(!lim) dp[pos][pre]=ans;
    return ans;
}
int solve(int x)
{
    memset(dp,-1,sizeof dp);
    int t=0;
    while(x)
    {
        num[++t]=x%10;
        x/=10;
    }
    return dfs(t,0,1);
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int n,m;
    while(cin>>n>>m&&n!=0&&m!=0)
    {
        cout<<solve(m)-solve(n-1)<<"\n";
    }
    return 0;
}
```

一般来说前导0也是需要着重考虑的一个地方，因此[题目2](https://www.acwing.com/problem/content/341/)。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
const int N=2e5+5;
const int mod=998244353;
int dp[40][40][40],num[40];
int dfs(int pos,int cnt0,int cnt1,int lim,int led)
{
    if(pos<1) return cnt0>=cnt1;
    if(!lim&&!led&&dp[pos][cnt0][cnt1]!=-1) return dp[pos][cnt0][cnt1];
    int top=lim?num[pos]:1;
    int ans=0;
    for(int i=0;i<=top;i++)
    {
        if(i==0) ans+=dfs(pos-1,cnt0+(!led),cnt1,lim&&i==top,led);
        else ans+=dfs(pos-1,cnt0,cnt1+1,lim&&i==top,0);
    }
    if(!lim&&!led) dp[pos][cnt0][cnt1]=ans;
    return ans;
}
int solve(int x)
{
    memset(dp,-1,sizeof dp);
    int t=0;
    while(x)
    {
        num[++t]=x&1;
        x>>=1;
    }
    return dfs(t,0,0,1,1);
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int n,m; cin>>n>>m;
    cout<<solve(m)-solve(n-1)<<endl;
    return 0;
}
```

如果上面两题都已经清楚了的话，那么[题目3](https://atcoder.jp/contests/arc173/tasks/arc173_a)有点难度但是希望可以（或者说完全可以）自己a掉。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
const int N=2e5+5;
const int mod=998244353;
int dp[20][20],num[20],k;
int dfs(int pos,int pre,int lim,int led)
{
    if(pos<1) return !led;
    if(!lim&&!led&&dp[pos][pre]!=-1) return dp[pos][pre];
    int top=lim?num[pos]:9;
    int ans=0;
    for(int i=0;i<=top;i++)
    {
        if(i==0&&led) ans+=dfs(pos-1,i,lim&&i==top,1);
        else if(i==pre) continue;
        else ans+=dfs(pos-1,i,lim&&i==top,0);
    }
    if(!lim&&!led) dp[pos][pre]=ans;
    return ans;
}
int solve(int x)
{
    memset(dp,-1,sizeof dp);
    int t=0;
    while(x)
    {
        num[++t]=x%10;
        x/=10;
    }
    return dfs(t,-1,1,1);
}
bool check(int mid)
{
    int t=solve(mid);
    if(t>=k) return 1;
    else return 0;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T;cin>>T;
    while(T--)
    {
        cin>>k;
        int l=1,r=1e13;
        while(l<=r)
        {
            int mid=(l+r)/2;
            if(check(mid)) r=mid-1;
            else l=mid+1;
        }
        cout<<l<<endl;
    }
    return 0;
}
```

[题目4](https://www.acwing.com/problem/content/4642/)题意转化有点难想。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
const int N=2e5+5;
const int mod=998244353;
int dp[20][2000],num[20],zhong;
int dfs(int pos,int val,int lim,int led)
{
    if(pos<1) return val==0;
    if(!lim&&!led&&dp[pos][val]!=-1) return dp[pos][val];
    int top=lim?num[pos]:9;
    int ans=0;
    for(int i=0;i<=top;i++)
    {
        if(i==0&&led&&pos==zhong) continue;
        int v=val+(pos-zhong)*i;
        ans+=dfs(pos-1,v,lim&&i==top,led&&i==0);
    }
    if(!lim&&!led) dp[pos][val]=ans;
    return ans;
}
int solve(int x)
{
    int t=0,res=1;
    while(x)
    {
        num[++t]=x%10;
        x/=10;
    }
    for(int i=1;i<=t;i++) 
    {
        zhong=i;
        memset(dp,-1,sizeof dp);
        res+=dfs(t,0,1,1);
    }
    return res;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T;cin>>T;
    while(T--)
    {
        int n,m;cin>>n>>m;
        if(n==0) cout<<solve(m)<<"\n";
        else cout<<solve(m)-solve(n-1)<<"\n";
    }
    return 0;
}
```

[题目5](https://www.luogu.com.cn/problem/U410278)

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
const int N=2e5+5;
const int mod=998244353;
int dp[40][40],num[40],k,n,m;
//还需要考虑前导0
int dfs(int pos,int zer,int lim,int led)
{
    if(pos<1) return zer==k;
    if(!lim&&!led&&dp[pos][k-zer]!=-1) return dp[pos][k-zer];
    int top=lim?num[pos]:9;
    int ans=0;
    for(int i=0;i<=top;i++)
    {
        if(i==6||i==9) ans+=dfs(pos-1,zer+1,lim&&i==top,0);
        else if(i==0) ans+=dfs(pos-1,zer+(!led),lim&&i==top,led);
        else if(i==8) ans+=dfs(pos-1,zer+2,lim&&i==top,0);
        else ans+=dfs(pos-1,zer,lim&&i==top,0);
    }
    if(!lim&&!led) dp[pos][k-zer]=ans;
    return ans;
}
int solve(int x)
{
    memset(dp,-1,sizeof dp);
    int t=0;
    while(x)
    {
        num[++t]=x%10;
        x/=10;
    }
    return dfs(t,0,1,1);
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>k;
    cout<<solve(m)-solve(n-1)+(n==0&&k==1)<<endl;
    return 0;
}
```