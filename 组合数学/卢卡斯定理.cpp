#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 5;
// 解决C(m,n)%p
int fac[N], p;
int ksm(int a, int b)
{
    int ans = 1;
    for (; b; b >>= 1, a = a * a % p)
        if (b & 1) ans = ans * a % p;
    return ans;
}
int c(int m, int n)
{
    // m<=n
    if (n < m || m < 0) return 0;
    return (fac[n] * ksm(fac[m], p - 2) % p * ksm(fac[n - m], p - 2) % p);
}
int lucas(int m, int n)
{
    if (n < p && m < p) return c(m, n);
    return c(m % p, n % p) * lucas(m / p, n / p) % p;
}
void init()
{
    fac[0] = 1ll; // 阶乘预处理
    for (int i = 1; i <= N - 5; i++)
        fac[i] = fac[i - 1] * i % p;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m >> p;
        init();
        cout << lucas(m, n + m) << "\n";
    }
}