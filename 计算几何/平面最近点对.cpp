#include <bits/stdc++.h>
using namespace std;
const int N = 400005;
int n;
struct Point
{
    long long x, y;
} p[N], q[N];
bool cmp(const Point &a, const Point &b)
{
    return a.x < b.x;
}
long long dis(const Point &a, const Point &b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
long long divide(int l, int r)
{
    if (l == r) return 1ll << 62;
    int mid = (l + r) / 2;
    long long midx = p[mid].x;
    long long d = min(divide(l, mid), divide(mid + 1, r));
    int p1 = l, p2 = mid + 1, tot = 0;
    while (p1 <= mid || p2 <= r)
    {
        if (p1 <= mid && (p2 > r || p[p1].y < p[p2].y))
            q[++tot] = p[p1++];
        else
            q[++tot] = p[p2++];
    }
    for (int i = 1; i <= tot; i++)
        p[l + i - 1] = q[i];
    tot = 0;
    long long dd = d;
    d = sqrt(dd);
    for (int i = l; i <= r; i++)
        if (abs(p[i].x - midx) <= d)
            q[++tot] = p[i];
    for (int i = 1; i <= tot; i++)
    {
        for (int j = i - 1; j >= 1 && q[i].y - q[j].y <= d; j--)
        {
            dd = min(dd, dis(q[i], q[j]));
            d = sqrt(dd);
        }
    }
    return dd; // 返回的是距离的平方
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> p[i].x >> p[i].y;
    sort(p + 1, p + n + 1, cmp); // 使用前一定要排序
    cout << fixed << setprecision(4) << sqrt(divide(1, n)) << '\n';
    return 0;
}