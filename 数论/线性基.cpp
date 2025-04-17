#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll a[120], n, cnt;
bool Ins(ll val) // 插入
{
    for (int i = 63; i >= 0; i--)
    {
        if ((val >> i) & 1)
        {
            if (!a[i])
            {
                a[i] = val;
                return 1;
            }
            else val ^= a[i];
        }
    }
    return 0;
}
void Work()
{
    // 预处理
    for (int i = 63; i >= 0; i--)
    {
        for (int j = i + 1; j <= 63; j++)
        {
            if ((a[j] >> i) & 1ll) a[j] ^= a[i];
        }
    }
    cnt = 0;
    for (int i = 0; i <= 63; i++)
        if (a[i]) a[cnt++] = a[i];
}
ll Max() // 查找最大值
{
    ll ans = 0;
    for (int i = 0; i <= 63; i++)
        if ((ans ^ a[i]) > ans) ans = ans ^ a[i];
    return ans;
}
ll Min() // 最小值
{
    ll ans = 0;
    for (int i = 0; i < 63; i++)
        if ((ans ^ a[i]) < ans) ans = ans ^ a[i];
    return ans;
}
ll Query(ll k) // 查询第k大
{
    if (cnt != n) k--; // 存在0的情况
    if (k >= (1ll << cnt)) return -1;
    ll ans = 0;
    for (int i = 0; i <= 63; i++)
        if ((k >> i) & 1ll) ans ^= a[i];
    return ans;
}

signed main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        ll x;
        cin >> x;
        Ins(x);
    }
    Work(); // 初始化

    return 0;
}