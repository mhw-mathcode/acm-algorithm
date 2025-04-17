#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 2;
// 物品容积与权重
int c[N], w[N], dp[N];
int main()
{
    // 01背包
    // 物品数目与背包体积
    int n, v;
    for (int i = 1; i <= n; i++)        // 枚举所有物品
        for (int j = v; j >= c[i]; j--) // 枚举背包体积
            dp[j] = max(dp[j], dp[j - c[i]] + w[i]);

    // 分组背包
    // t[k][i]表示第k组的第i件物品的编号是多少
    int ts, m, cnt[N], t[N][N];
    for (int k = 1; k <= ts; k++)                                        // 循环每一组
        for (int i = m; i >= 0; i--)                                     // 循环背包容量
            for (int j = 1; j <= cnt[k]; j++)                            // 循环该组的每一个物品
                if (i >= w[t[k][j]])                                     // 背包容量充足
                    dp[i] = max(dp[i], dp[i - w[t[k][j]]] + c[t[k][j]]); // 像0-1背包一样状态转移
}