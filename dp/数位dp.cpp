#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
const int N = 2e5 + 5;

int dp[20][20], num[20];
int dfs(int pos, int pre, int lim)
{
    if (pos < 1) return 1;
    if (!lim && dp[pos][pre] != -1) return dp[pos][pre];
    int top = lim ? num[pos] : 9;
    int ans = 0;
    for (int i = 0; i <= top; i++)
    {
        // 计数
        ans += dfs(pos - 1, i, lim && i == top);
    }
    if (!lim) dp[pos][pre] = ans;
    return ans;
}
int solve(int x)
{
    memset(dp, -1, sizeof dp);
    int t = 0;
    while (x)
    {
        num[++t] = x % 10;
        x /= 10;
    }
    return dfs(t, 0, 1);
}


// 考虑前导0
int dfs(int pos, int pre, int lim, int led)
{
    if (pos < 1) return 1;
    if (!lim && !led && dp[pos][pre] != -1) return dp[pos][pre];
    int top = lim ? num[pos] : 9;
    int ans = 0;
    for (int i = 0; i <= top; i++)
    {
        // 计数

        if (i == 0 && led) ans += dfs(pos - 1, i, lim && i == top, 1);
        else ans += dfs(pos - 1, i, lim && i == top, 0);
    }
    if (!lim && !led) dp[pos][pre] = ans;
    return ans;
}
int solve(int x)
{
    memset(dp, -1, sizeof dp);
    memset(num, 0, sizeof num);
    int t = 0;
    while (x)
    {
        num[++t] = x % 10;
        x /= 10;
    }
    return dfs(t, -1, 1, 1);
}