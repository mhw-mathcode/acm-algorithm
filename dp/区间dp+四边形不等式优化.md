### **区间dp**

经典 $O(n^3)$ 状态转移方程

![image.png](https://s2.loli.net/2024/01/18/bFgAaYjDNmiy8W4.png)

例题1：[石子合并1](https://www.luogu.com.cn/problem/P1775)。

思考1：如果石子不是链形结构，是环形结构应该怎么办？

例题2：[石子合并2](https://www.luogu.com.cn/problem/P1880)。

将环形结构拆成链形结构，将原数组接到自己后面，然后区间dp。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 0x3f3f3f3f
const int N=2e5+5;
int a[310],q[310],dpmax[310][310],dpmin[310][310];
int main() 
{
    int n;cin>>n;
    //memset(dpmax,0,sizeof dpmax);
    memset(dpmin,inf,sizeof dpmin);
    for(int i=1;i<=n;i++) 
    {
        cin>>a[i];
        q[i]=q[i-1]+a[i];
        dpmin[i][i]=0,dpmax[i][i]=0;
    }
    for(int i=n+1;i<=(n<<1);i++)
    {
        a[i]=a[i-n];
        q[i]=q[i-1]+a[i];
        dpmin[i][i]=0,dpmax[i][i]=0;
    }
    for(int len=2;len<=n;len++)
    {
        for(int l=1;l<=(n<<1)-len+1;l++)
        {
            int r=l+len-1;
            for(int i=l;i<r;i++)
            {
                dpmin[l][r]=min(dpmin[l][i]+dpmin[i+1][r]+q[r]-q[l-1],dpmin[l][r]);
                dpmax[l][r]=max(dpmax[l][i]+dpmax[i+1][r]+q[r]-q[l-1],dpmax[l][r]);
            }
        }
    }
    int ansmin=inf,ansmax=0;
    for(int i=1;i<=n;i++) 
    {
        ansmin=min(ansmin,dpmin[i][i+n-1]);
        ansmax=max(ansmax,dpmax[i][i+n-1]);
    }
    cout<<ansmin<<"\n"<<ansmax<<"\n";
    return 0;
}
```


思考2：如果数据范围是 $1e3$ 怎么办？引入四边形不等式优化。

### **四边形不等式优化dp**

对于上述区间的权值函数 $w(l,r)$ ,如果其满足以下两个条件：

![image.png](https://s2.loli.net/2024/01/18/DEdYgfxZubJ84eT.png)

则有两个神奇的性质：

性质1： $dp[l][r]$ 也满足四边形不等式。  

性质2：假设 $s[l][r]$ 为 $dp[l][r]$ 的最优决策点，那么 $s[l][r]$ 满足 $s[l][r-1]≤s[l][r]≤s[l+1][r]$ 。

![image.png](https://s2.loli.net/2024/01/18/YqVZvUXR1OKfBN5.png)

对于性质2，换句话说就是最优决策点矩阵**每一行、每一列**都是**单调不减**的。

关于两个结论的证明：

性质1：

![26707d0b9ab36a04a7bee887dad5e65.png](https://s2.loli.net/2024/01/18/HaeNCvwQZkuthDT.png)

![b01afe3317176d248af536c3eb7ce02.png](https://s2.loli.net/2024/01/18/9iacg1W4ZI8xepF.png)

性质2：

![199cd28ae02d3ebad7b9a410494b8a1.png](https://s2.loli.net/2024/01/18/apfQOR1Ym8Fxzle.png)

声明一点，我并不会证明，所以大家对这个有问题千万别来问我……实际上，比赛时应该不会有人去手推证明这个事情，如果一道题目看起来像区间dp，并且发现数据范围来到了 $1e3$ ，并且通过打表发现区间最优决策点矩阵是单调不减的，那这道题大概率是用四边形不等式来优化区间dp做。

由性质2可知，每次寻找 $(l,r)$ 区间的最优决策点只需要枚举 $s[l][r-1]-s[l+1][r]$ 即可。因此核心代码如下：

![image.png](https://s2.loli.net/2024/01/18/hNTKOq7Yr5u2j9W.png)

下面证明时间复杂度优化到了 $O(n^2)$ 。

对于每个 $l$ ，循环次数为 $s[l+1][r]-s[l][r-1]$ .  
又有 $r=l+len-1$   
 $l=1$ 时，循环次数 $s[2][len]-s[1][len-1]$  
 $l=2$ 时，循环次数 $s[3][len+1]-s[2][len]$  
 $……$  
 $l=n$ 时，循环次数 $s[n+1][n+len-1]-s[n][n+len-2]$  
相加得 $s[n+1][n+len-1]-s[1][len-1]≤n$ ，得证。


但是还有一个小细节需要注意，就是我们需要对dp数组以及s数组部分值赋初值，否则就会不幸。(具体赋值思路通过下面具体题目分析)

例题3：[题目](https://www.luogu.com.cn/problem/SP33372)。

给定数组长n与划分的区间数k，求出使所有划分完的区间逆序对数最小的逆序对总和数。

二维区间dp。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
const int N=5e3+5;
//dp[i][j]表示前i个数分为j个组
int a[N],w[N][N],dp[N][N],s[N][N];
int main() 
{
    memset(dp,0x3f,sizeof dp);
    int n,k;cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int len=2;len<=n;len++)
    {
        for(int l=1;l<=n;l++)
        {
            int r=l+len-1;
            w[l][r]=w[l+1][r]+w[l][r-1]-w[l+1][r-1]+(a[l]>a[r]);
        }
    }
    //dp和s数组赋初值
    for(int i=1;i<=n;i++) dp[i][1]=w[1][i];
    for(int i=1;i<=k;i++) s[n+1][i]=n;
    //枚举分成j组
    for(int j=1;j<=k;j++)
    {
        //枚举前i个人
        for(int i=n;i>=1;i--)
        {
            for(int k=s[i][j-1];k<=s[i+1][j];k++)
            {
                if(dp[i][j]>dp[k][j-1]+w[k+1][i])
                {
                    dp[i][j]=dp[k][j-1]+w[k+1][i];
                    s[i][j]=k;
                }
            }
        }
    }
    cout<<dp[n][k]<<"\n";
    return 0;
}
```
对于 $O(n^2)$ 处理所有区间的逆序对。（同样是 $dp$ 思路）
    
对于 $dp$ 和 $s$ 数组部分赋初值。（ $w$ 能直接决定的 $dp$ ，边界的 $s$ ）

对于为什么把对$j$的枚举放在外层循环。（类似于区间长度，更大的 $j$ 需要小的 $j$ 值更新）

对于为什么将对 $i$ 进行倒序枚举。（因为 $s[i+1][j]$ ）

例题4：[题目](https://acm.tju.edu.cn/problem/2023FRESH-H)。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e3+3;
//w[i][j]表示乘客i到乘客j的不和谐度
//dp[i][j]表示前i个乘客用j艘船
int a[N][N],w[N][N],dp[N][N],s[N][N],sum[N][N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    memset(dp,0x3f,sizeof dp);
    int n,k;cin>>n>>k;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            cin>>a[i][j];
            if(i>j) a[i][j]=0;
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
    for(int i=1;i<=k;i++) s[n+1][i]=n;
    for(int i=1;i<=n;i++) dp[i][1]=sum[i][i],dp[i][i]=0;
    //枚举j艘船
    for(int j=2;j<=k;j++)
    {
        //枚举前i个人
        for(int i=n;i>=1;i--)
        {
            for(int k=s[i][j-1];k<=s[i+1][j];k++)
            {
                if(dp[i][j]>dp[k][j-1]+sum[i][i]-sum[k][i]-sum[i][k]+sum[k][k])
                {
                    dp[i][j]=dp[k][j-1]+sum[i][i]-sum[k][i]-sum[i][k]+sum[k][k];
                    s[i][j]=k;
                }
            }
        }
    }
    cout<<dp[n][k]<<"\n";
    return 0;
}
```
由以上两题发现，dp部分直接套模板，貌似算出区间权值函数 $w(l,r)$ 更难一点？

例题5：[题目](https://www.luogu.com.cn/problem/P4767)。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define pii pair<int,int>
const int V=3e3+5,P=310;
//dp[i][j]表示在前i个村庄建j个邮箱的最小距离
//w[i][j]表示村庄i到村庄j之间建一个邮局得到的最小距离，建在中位数村庄
int a[V],dp[V][P],w[V][V],s[V][P];
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    memset(dp,0x3f,sizeof dp);
    int v,p;cin>>v>>p;
    for(int i=1;i<=v;i++) cin>>a[i];
    sort(a+1,a+v+1);
    for(int i=1;i<=v;i++)
        for(int j=i+1;j<=v;j++)
            w[i][j]=w[i][j-1]+a[j]-a[(i+j)/2];
    //状态转移的边界条件
    for(int i=1;i<=v;i++) dp[i][1]=w[1][i];
    for(int i=1;i<=p;i++) s[v+1][i]=v;
    //枚举使用了j个邮箱
    for(int j=2;j<=p;j++)
    {
        //枚举前i个村庄
        for(int i=v;i>=j;i--)
        {
            for(int k=s[i][j-1];k<=s[i+1][j];k++)
            {
                if(dp[k][j-1]+w[k+1][i]<dp[i][j])
                {
                    dp[i][j]=dp[k][j-1]+w[k+1][i];
                    s[i][j]=k;
                }
            }
        }
    }
    cout<<dp[v][p]<<"\n";
    return 0;
}
```
