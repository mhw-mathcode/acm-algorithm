#include <bits/stdc++.h>
#define ll long long
const int N = 1e3 + 5;
const double eps = 1e-8;
const double Pi = acos(-1.0);
using namespace std;

int sgn(double x)
{ // 进行判断, 提高精度
    if (fabs(x) < eps)
        return 0;          // x == 0, 精度范围内的近似相等
    return x > 0 ? 1 : -1; // 返回正负
}

typedef struct Point
{
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {} // 构造函数, 初始值为 0

    // 重载运算符
    // 点 - 点 = 向量(向量AB = B - A)
    Point operator-(const Point &B) const { return Point(x - B.x, y - B.y); }

    // 点 + 点 = 点, 点 + 向量 = 向量, 向量 + 向量 = 向量
    Point operator+(const Point &B) const { return Point(x + B.x, y + B.y); }

    // 向量 × 向量 (叉积)
    double operator^(const Point &B) const { return x * B.y - y * B.x; }

    // 点 * 数 = 点, 向量 * 数 = 向量
    Point operator*(const double &B) const { return Point(x * B, y * B); }

} Vector;

struct Line
{
    Point s, e;
};

Point Intersection_line(Line l1, Line l2) // 直线交点
{
    Point a = l1.s, b = l1.e, c = l2.s, d = l2.e;
    Vector u = b - a, v = d - c;
    double t = ((a - c) ^ v) / (v ^ u);
    return a + u * t;
}
bool cross(Line a, Line b, Line c) // 判断b和c的交点是否在直线a的右侧
{
    Point p = Intersection_line(b, c);
    return ((a.e - a.s) ^ (p - a.s))< 0;
}

double Angle(Line a) { return atan2(a.e.y - a.s.y, a.e.x - a.s.x); } // 夹角
bool cmp(Line a, Line b)                                             // 极角排序
{
    double A = Angle(a), B = Angle(b);
    return fabs(A - B) > eps ? A < B : ((a.e - a.s) ^ (b.e - a.s)) < 0;
}

Point p[N];
Line a[N], q[N];
int cnt, k;
double res;
double HalfPlane()
{
    // 共有cnt条边
    sort(a + 1, a + cnt + 1, cmp);
    int head = 1, tail = 1;
    q[1] = a[1];
    for (int i = 2; i <= cnt; i++)
    {
        if (Angle(a[i]) - Angle(a[i - 1]) < eps) continue;
        while (head < tail && cross(a[i], q[tail], q[tail - 1])) tail--;
        while (head < tail && cross(a[i], q[head], q[head + 1])) head++;
        q[++tail] = a[i];
    }
    while (head < tail && cross(q[head], q[tail], q[tail - 1])) tail--;
    q[++tail] = q[head];
    for (int i = head; i < tail; i++) p[++k] = Intersection_line(q[i], q[i + 1]);
    if (k <= 2) return 0;
    for (int i = 1; i <= k; i++) res += p[i] ^ p[i % k + 1];
    return res / 2;
}

// 注意如何使用，直接将所有点读入p，一个多边形中相邻点连线读入a
// 保证多边形是逆时针顺序

int main()
{
    int n; cin >> n;
    while (n--)
    {
        int m; cin >> m;
        for (int i = 1; i <= m; i++) cin >> p[i].x >> p[i].y;
        for (int i = 1; i <= m; i++) a[++cnt] = {p[i], p[i % m + 1]};
    }
    cout << fixed << setprecision(3) << HalfPlane() << endl;
    return 0;
}