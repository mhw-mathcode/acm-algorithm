#include <bits/stdc++.h>
using namespace std;
// 求解a^x = b (mod m) (a^x % m = b) (m为质数)，返回的x是最小的
int bsgs(int a, int b, int m)
{
    static unordered_map<int, int> hs;
    hs.clear();
    int cur = 1, t = sqrt(m) + 1;
    for (int B = 1; B <= t; B++)
    {
        (cur *= a) %= m;
        hs[b * cur % m] = B; // 哈希表中存B的值
    }
    int now = cur; // 此时cur = a^t
    for (int A = 1; A <= t; A++)
    {
        auto it = hs.find(now);
        if (it != hs.end()) return A * t - it->second;
        (now *= cur) %= m;
    }
    return -1; // 没有找到，无解
}


// exBSGS 
// 求解a^x = b (mod m) (a^x % m = b)，返回的x是最小的
unordered_map<int, int> mp;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
inline int BSGS(int a, int n, int p, int ad)
{
    mp.clear();
    int m = ceil(sqrt(p)), s = 1;
    for (int i = 0; i < m; i++, s = 1ll * s * a % p)
        mp[1ll * s * n % p] = i;
    for (int i = 0, tmp = s, s = ad; i <= m; i++, s = 1ll * s * tmp % p)
        if (mp.find(s) != mp.end())
            if (1ll * i * m - mp[s] >= 0) // 需要正整数解还是非负整数解
                return 1ll * i * m - mp[s];
    return -1;
}
inline int exBSGS(int a, int n, int p)
{
    a %= p, n %= p;
    if (n == 1 || p == 1) return 0; // 需要正整数解还是非负整数解
    int cnt = 0, d, ad = 1;
    while ((d = gcd(a, p)) ^ 1)
    {
        if (n % d) return -1;
        cnt++, n /= d, p /= d, ad = (1ll * ad * a / d) % p;
        if (ad == n) return cnt;
    }
    int ans = BSGS(a, n, p, ad);
    if (ans == -1) return -1;
    return ans + cnt;
}