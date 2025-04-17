#include <bits/stdc++.h>
using namespace std;
// 扩展欧几里得
void exgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return;
    }
    exgcd(b, a % b, x, y);
    int t = y;
    y = x - (a / b) * y, x = t;
}
int main()
{
    int a, b, c, x, y;
    // 对于ax+by=c(c%gcd(a,b)==0)
    a /= gcd(a, b), b /= gcd(a, b), c /= gcd(a, b);
    if (a < b) swap(a, b);
    exgcd(a, b, x, y);
    x *= c, y *= c;
    // 通解为x+bn和y-an，找到绝对值最小的解
    y += x / b * a, x %= b;
}
