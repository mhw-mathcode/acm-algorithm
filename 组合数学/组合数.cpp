#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10; // 需要的最大组合数n，m的范围
const int mod = 1e9 + 7;
int fac[N], ifac[N];
int ksm(int x, int y)
{
    int ans = 1ll;
    for (; y; y >>= 1, x = x * x % mod)
        if (y & 1) ans = ans * x % mod;
    return ans;
}
int C(int n, int m)
{
    // m是小的数字,n是大的
    if (n < m || m < 0) return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int A(int n, int m)
{
    // m是小的数字,n是大的
    if (n < m || m < 0) return 0;
    return fac[n] * ifac[n - m] % mod;
}
void init()
{
    fac[0] = 1ll; // 阶乘预处理
    for (int i = 1; i <= N - 5; i++)
        fac[i] = fac[i - 1] * i % mod;
    ifac[N - 5] = ksm(fac[N - 5], mod - 2);
    for (int i = N - 5; i; i--)
        ifac[i - 1] = ifac[i] * i % mod;
}
signed main()
{
    init();
}