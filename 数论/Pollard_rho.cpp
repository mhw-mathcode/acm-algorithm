#include <bits/stdc++.h>
using namespace std;
#define __int128 long long // 记得去掉（为了不报错）
#define int long long
const int P = 998244353;

// 快速质因数分解+快速求解一个数所有约数

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int mul(int a, int b, int m) { return static_cast<__int128>(a) * b % m; }
int power(int a, int b, int m)
{
    int res = 1 % m;
    for (; b; b >>= 1, a = mul(a, a, m))
        if (b & 1) res = mul(res, a, m);
    return res;
}

// Miller-Rabin
bool isprime(int n)
{
    if (n < 2) return false;
    static constexpr int B[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    for (int p : B)
    {
        if (n == p) return true;
        if (n % p == 0) return false;
    }
    int m = (n - 1) >> __builtin_ctz(n - 1);
    for (int p : B)
    {
        int t = m, a = power(p, m, n);
        while (t != n - 1 && a != 1 && a != n - 1)
        {
            a = mul(a, a, n);
            t *= 2;
        }
        if (a != n - 1 && t % 2 == 0) return false;
    }
    return true;
}

// Pollard-Rho
vector<int> factorize(int n)
{
    vector<int> p;
    function<void(int)> f = [&](int n)
    {
        if (n <= 10000)
        {
            for (int i = 2; i * i <= n; i++)
                for (; n % i == 0; n /= i)
                    p.push_back(i);
            if (n > 1) p.push_back(n);
            return;
        }
        if (isprime(n))
        {
            p.push_back(n);
            return;
        }
        auto g = [&](int x)
        {
            return (mul(x, x, n) + 1) % n;
        };
        int x0 = 2;
        while (true)
        {
            int x = x0, y = x0;
            int d = 1, pow = 1, lam = 0, v = 1;
            while (d == 1)
            {
                y = g(y);
                ++lam;
                v = mul(v, abs(x - y), n);
                if (lam % 127 == 0) d = gcd(v, n), v = 1;
                if (pow == lam) x = y, pow *= 2, lam = 0, d = gcd(v, n), v = 1;
            }
            if (d != n)
            {
                f(d), f(n / d);
                return;
            }
            ++x0;
        }
    };
    f(n);
    sort(p.begin(), p.end());
    return p;
}

const int N = 3e4;
int p[N], cnt[N]; // p[0]为数组长度
vector<int> getDivisor(int x)
{
    p[0] = cnt[0] = 0;
    unordered_map<int, int> mp;
    vector<int> temp = factorize(x);
    for (auto i : temp) mp[i]++;
    for (auto [x, w] : mp)
    {
        p[++p[0]] = x;
        cnt[++cnt[0]] = w;
    }
    vector<int> divisor(10000); // divisor[0]表示约数个数
    divisor[0] = 1;
    divisor[1] = 1;
    for (int i = 1; i <= p[0]; i++)
    {
        int nowNum = divisor[0];
        int base = 1;
        for (int j = 1; j <= cnt[i]; j++)
        {
            base *= p[i];
            for (int k = 1; k <= divisor[0]; k++)
                divisor[++nowNum] = divisor[k] * base;
        }
        divisor[0] = nowNum;
    }
    return divisor;
}
