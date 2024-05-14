今天牛客小白月赛偶然路过，看到C题立刻想到百度之星的A题，不能说一模一样，只能说毫无差别……

[C题](https://ac.nowcoder.com/acm/contest/70845/C)题意很简单，就是给定一个n表示字符串的长度，问该字符串含至少一个txt的种类数。

不知道大家第一时间会不会感觉很简单然后想到了容斥？百度之星因为容斥把自己整疯掉了……正解是计数dp。

dp[i][j]表示产长度为i的不含txt的字符串，j=1表示以t结尾，j=2表示以tx结尾，j=0表示其他情况。对于每次统计长度i的字符串对应的答案，即为i-1对应答案乘以26加上dp[i][2]。状态转移方程也就很明显了。

简单说明为什么这样是可以的。因为每次数的都是只有末尾为txt的字符串，前一种情况乘以26都是前面至少有一个txt的字符串，故不会数重。显然也不会数漏，因为每次乘以26表示所有可行方案最后带上了所有情况。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+10;
const int mod=998244353;
int dp[maxn][3];
signed main()
{
    map<int,int>out;
    int n=2e5+5,res=0;
    dp[0][0]=1;
    for(int i=1;i<=n;i++)
    {
        //dp[i][j]表示长度为i的不含txt的字符串
        //j=1表示以t结尾，j=2表示以tx结尾，j=0表示其他情况
        dp[i][0]=(dp[i-1][1]*24+dp[i-1][0]*25+dp[i-1][2]*26)%mod;
        dp[i][1]=(dp[i-1][0]+dp[i-1][1])%mod;
        dp[i][2]=(dp[i-1][1])%mod;
        res=(res*26+dp[i-1][2])%mod;
        out[i]=res;
    }
    int t;cin>>t;
    while(t--)
    {
        int x;cin>>x;
        cout<<out[x]<<"\n";
    }
    return 0;
}
```


[百度之星](https://www.matiji.net/exam/brushquestion/17/4347/179CE77A7B772D15A8C00DD8198AAC74?from=1)那题难度更大一点，限定了shs数量在3个及以上，只需要多一层小循环更新即可，注意多一点细节。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+10;
const int mod=1e9+7;
//dp[size][i][j]表示长度为size，i为此时字符串中shs的数量
//j=1表示以s结尾(注意shs这种情况不算在里面)，j=2表示以sh结尾，j=0表示其他情况(shs算在这里)
int dp[maxn][4][3];
signed main()
{
    int n;cin>>n;
    int res=0;
    dp[0][1][0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=3;j++)
        {
            dp[i][j][0]=dp[i-1][j][2]*25+dp[i-1][j][1]*24+dp[i-1][j][0]*25+dp[i-1][j-1][2];
            dp[i][j][1]=dp[i-1][j][0]+dp[i-1][j][1];
            dp[i][j][2]=dp[i-1][j][1];
        }
        res=(res*26+dp[i-1][3][2]);
    }
    cout<<res<<endl;
}
```
