一直练思维题，真的不太容易突破，还是学点新东西吧。

正好一场校内个人赛，除了一道博弈论差一点点，剩下的看了看确实不像自己能做出来的hh，挑剩下的相较来说最简单的一道，考点状压dp。

所以思路是不可能有一点的，还是先从状压dp学起吧。（狂肝一天）

引入一道经典题：[互不侵犯](https://www.luogu.com.cn/problem/P1896)。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
const int N=2e5+5;
//cnt[i]表示第i中状态的二进制有几个1，ok[i]表示第i个行内合法的状态
int cnt[N],ok[N],numok;
//dp[i][j][s]表示放了i行，用了j个国王，第i行状态是s的方案数
int dp[10][100][2000];
signed main() 
{
    int n,kk;cin>>n>>kk;
    //枚举所有状态，更新cnt数组
    for(int s=0;s<(1<<n);s++)
    {
        for(int i=0;i<=10;i++) if((s>>i)&1) cnt[s]++;
        if((((s<<1)|(s>>1))&s)==0) ok[++numok]=s;
    }
    dp[0][0][0]=1;
    for(int i=1;i<=n;i++)
    {
        //枚举该行合法的状态
        for(int j=1;j<=numok;j++)
        {
            int s=ok[j];
            //枚举上一行的状态
            for(int k=1;k<=numok;k++)
            {
                int ss=ok[k];
                if(((ss|(ss<<1)|(ss>>1))&s)==0)
                {
                    for(int p=0;p<=kk;p++)
                    {
                        if(p-cnt[s]>=0) 
                        {
                            dp[i][p][s]+=dp[i-1][p-cnt[s]][ss];
                        }
                    }
                }
            }
        }
    }
    int ans=0;
    for(int i=1;i<=numok;i++) ans+=dp[n][kk][ok[i]];
    cout<<ans<<endl;
    return 0;
}
```
[蒙德里安的梦想](https://www.acwing.com/problem/content/description/293/)

感觉比上面那道更难一点，思路难出一点，不过写起来更简单。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
const int N=(1<<11);
//dp[i][s]表示第i行状态为s的情况数
int v[N],dp[12][N],ok[N],num;
int main() 
{
    int n,m;
    while(cin>>n>>m&&n&&m)
    {
        num=0;
        for(int i=0;i<(1<<n);i++)
        {
            int cnt=0,f=1;
            v[i]=0;
            for(int j=0;j<n;j++)
            {
                if((i>>j)&1) 
                {
                    if(cnt&1) f=0; 
                    cnt=0;
                }
                else cnt++;
            }
            if(f&&!(cnt&1)) v[i]=1;
        }
        memset(dp,0,sizeof dp);
        dp[0][0]=1;
        for(int i=1;i<=m;i++)
            for(int j=0;j<(1<<n);j++) //枚举本列状态
                for(int k=0;k<(1<<n);k++) //枚举上一列状态
                    if(((j&k)==0)&&(v[(j|k)])) dp[i][j]+=dp[i-1][k];
        cout<<dp[m][0]<<endl;
    }
    return 0;
}
```
[炮兵阵地](https://www.luogu.com.cn/problem/P2704)

虽然是基础题，但是感觉这个难度真的很大（蒟蒻颤抖），看了题解有点恍然大悟，据说需要滚动数组不然会mle，自己没用还是ac了hh不知道为啥。

一个比较重要的点就是，每次dp数组需要记录本行还有上一行的状态。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
const int N=2e5+5;
string a[110];
//cnt表示每个状态的炮台数，ok表示合法的状态
int cnt[1100],ok[1100],num;
//dp[i][s][k]表示第i行，该行状态为s，上一行状态为k，此时的炮台数
int dp[102][(1<<10)][(1<<10)];
//第i行行内合法的状态
vector<int>v[105];
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];

    for(int s=0;s<(1<<m);s++)
        for(int i=0;i<15;i++)
            if((s>>i)&1) cnt[s]++;

    for(int s=0;s<(1<<m);s++)
    {
        //枚举每一行
        for(int j=1;j<=n;j++)
        {
            int f=0;
            for(int i=0;i<15;i++) if(((s>>i)&1)&&a[j][i]=='P') f++; 
            if((((s>>1)&s)==0)&&(((s>>2)&s)==0)&&f==cnt[s]) v[j].push_back(s);
        }
    }
    v[0].push_back(0);

    //处理第一行
    for(auto j:v[1]) dp[1][j][0]=cnt[j];
    //处理第二行
    for(auto i:v[2])
        for(auto j:v[1])
            if((i&j)==0) dp[2][i][j]=cnt[i]+cnt[j];

    //处理剩余行
    for(int i=3;i<=n;i++)
    {
        //枚举本行状态
        for(auto j:v[i])
        {
            //枚举上一行状态
            for(auto k:v[i-1])
            {
                if(j&k) continue;
                //枚举上两行状态
                for(auto p:v[i-2])
                {
                    if((p&j)||(p&k)) continue;
                    dp[i][j][k]=max(dp[i][j][k],dp[i-1][k][p]+cnt[j]);
                }
            }
        }
    }
    int ans=0;
    for(auto i:v[n])
        for(auto j:v[n-1])
            ans=max(ans,dp[n][i][j]);
    cout<<ans<<endl;
    return 0;
}
```


[玉米地](https://www.luogu.com.cn/problem/P1879)

很简单的一道小题，上面的都明白以后可以自己独立a掉这道（自己第一道没有借助任何帮助做出来的状压dp）。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
const int N=2e5+5;
int a[15][15],cnt[(1<<12)],dp[15][(1<<12)];
vector<int>v[15];
int main() 
{
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>a[i][j];
    for(int s=0;s<(1<<m);s++)
        for(int i=0;i<15;i++) if((s>>i)&1) cnt[s]++;
    for(int i=1;i<=n;i++)
    {
        for(int s=0;s<(1<<m);s++)
        {
            int f=0;
            for(int j=0;j<15;j++) if(((s>>j)&1)&&a[i][j+1]) f++;
            if(f==cnt[s]&&(((s<<1)&s)==0)) v[i].push_back(s);
        }
    }
    v[0].push_back(0);
    dp[0][0]=1;
    for(int i=1;i<=n;i++) //枚举每一行
        for(auto j:v[i]) //枚举本行状态
            for(auto k:v[i-1]) //枚举上一行状态
                if(!(j&k)) dp[i][j]+=dp[i-1][k];
    int ans=0;
    for(auto i:v[n]) ans+=dp[n][i];
    cout<<ans%100000000<<endl;
    return 0;
}
```