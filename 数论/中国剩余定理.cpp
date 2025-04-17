#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// 求解同余方程组(模数互质)
// 快速幂
ll ksm(ll x, ll y, ll mod)
{
    ll ans = 1ll;
    for (; y; y >>= 1, x = x * x % mod)
        if (y & 1) ans = ans * x % mod;
    return ans;
}
// 快速乘(防止爆掉，并不能加快乘法速度)
ll ksc(ll x, ll y, ll mod)
{
    if (x < 0) x += mod;
    if (y < 0) y += mod;
    if (y > x) swap(x, y);
    ll ret = 0;
    while (y)
    {
        if (y & 1) (ret += x) %= mod;
        (x += x) %= mod, y >>= 1;
    }
    return ret;
}
const int N = 2e5 + 5;
// a数组为余数，b数组为模数,t数组为逆元,k为同余方程组数
ll a[N], b[N], t[N], k;
// 求解nx+my=1即n在模m下的逆元
void exgcd(ll n, ll m, ll &x, ll &y)
{
    if (m == 0)
    {
        x = 1, y = 0;
        return;
    }
    exgcd(m, n % m, y, x);
    y -= (n / m) * x;
}
ll CRT()
{
    ll ans = 0, lcm = 1, x, y;
    for (int i = 1; i <= k; i++) lcm *= b[i];
    for (int i = 1; i <= k; i++)
    {
        t[i] = lcm / b[i];
        exgcd(t[i], b[i], x, y);
        x = (x % b[i] + b[i]) % b[i];
        ans = (ans + t[i] * a[i] % lcm * x % lcm) % lcm;
        // 换用快速乘
        // ans = (ans + ksc(ksc(t[i], a[i], lcm), x, lcm)) % lcm;
    }
    return (ans + lcm) % lcm;
}