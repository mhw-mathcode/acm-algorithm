#include<bits/stdc++.h>
using namespace std;
//求解同余方程组(模数不互质)
typedef long long ll;  
const int N = 1e5 + 10;  
ll __gcd(ll a, ll b)  
{  
    return b ? __gcd(b, a % b) : a;  
}  
ll slowmul(ll x, ll y, ll mod)  
{  
    while (x < 0) x += mod;  
    while (y < 0) y += mod;  
    if (x < y) swap(x, y);  
    ll ret = 0;  
    while (y)  
    {  
        if (y & 1) (ret += x) %= mod;  
        (x <<= 1) %= mod, y >>= 1;  
    }  
    return ret;  
}  
void exgcd(ll n, ll m, ll& x, ll& y)  
{  
    if (m == 0) { x = 1, y = 0;return; }  
    exgcd(m, n % m, y, x);  
    y -= (n / m) * x;  
}  
//bi数组表示模数，ai数组表示余数  
ll ai[N], bi[N], k;  
ll exCRT()  
{  
    ll x, y, a, b, c, M = bi[1], ans = ai[1], gcd;  
    for (ll i = 2;i <= k;i++)  
    {  
        a = M, b = bi[i], c = (ai[i] - ans % b + b) % b, gcd = __gcd(a, b);  
        if (c % gcd) return -1;  
        a /= gcd, b /= gcd, c /= gcd;  
        exgcd(a, b, x, y);  
        x = slowmul(x, c, b), ans += x * M, M *= b;  
        ans = (ans % M + M) % M;  
    }  
    return ans;  
}  

