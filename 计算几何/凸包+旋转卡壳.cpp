#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;

const double eps = 1e-8;
int sgn(double x)
{
    // 进行判断, 提高精度
    if (fabs(x) <= eps)
        return 0;          // x == 0, 精度范围内的近似相等
    return x > 0 ? 1 : -1; // 返回正负
}
bool eq(double a, double b) { return abs(a - b) < eps; } // ==
bool le(double a, double b) { return a - b < eps; }      // <=
typedef struct Point
{
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {} // 构造函数, 初始值为 0

    // 重载运算符
    // 点 - 点 = 向量 (向量AB = B - A)
    Point operator-(const Point &B) const { return Point(x - B.x, y - B.y); }

    // 点 + 点 = 点, 点 + 向量 = 向量, 向量 + 向量 = 向量
    Point operator+(const Point &B) const { return Point(x + B.x, y + B.y); }

    // 向量 · 向量 (点积)
    double operator*(const Point &B) const { return x * B.x + y * B.y; }

    // 向量 × 向量 (叉积)
    double operator^(const Point &B) const { return x * B.y - y * B.x; }

    // 判断大小, 一般用于排序
    bool operator<(const Point &B) const { return x < B.x || (x == B.x && y < B.y); }

} Vector;

// 凸包
// Andrew算法求凸包，最后一个点与第一个点重合
// Need: (^,-,<), sgn, le
using Points = vector<Point>;
bool check(Point p, Point q, Point r) { return le(0, (q - p) ^ (r - q)); }
vector<Point> Andrew(Points poly)
{
    int n = poly.size(), top = 0;
    vector<int> stk(n + 10, 0), used(n + 10, 0);
    sort(poly.begin(), poly.end());
    stk[++top] = 0;
    for (int i = 1; i < n; i++)
    {
        while (top > 1 && sgn((poly[stk[top]] - poly[stk[top - 1]]) ^ (poly[i] - poly[stk[top]])) <= 0)
            used[stk[top--]] = 0;

        used[i] = 1;
        stk[++top] = i;
    }
    int tmp = top;
    for (int i = n - 2; i >= 0; i--)
    {
        if (used[i]) continue;
        while (top > tmp && sgn((poly[stk[top]] - poly[stk[top - 1]]) ^ (poly[i] - poly[stk[top]])) <= 0)
            used[stk[top--]] = 0;

        used[i] = 1;
        stk[++top] = i;
    }
    vector<Point> a;
    for (int i = 1; i <= top; i++) a.push_back(poly[stk[i]]);
    return a;
}

// 旋转卡壳
// 求解凸包直径（需要把第一个点在加进集合最后）
// Need: (*,-,^)
double len(Vector A) { return sqrt(A * A); }
double Dist_point_to_line(Point P, Point A, Point B)
{ 
    // 点到直线距离
    Vector v1 = B - A, v2 = P - A;
    return fabs((v1 ^ v2) / len(v1));
}
double RoatingCalipers(vector<Point> poly)
{
    if (poly.size() == 3) return len(poly[1] - poly[0]);
    int cur = 0, n = poly.size();
    double ans = 0;
    for (int i = 0; i < n - 1; i++)
    {
        while (Dist_point_to_line(poly[cur], poly[i], poly[i + 1]) <=
               Dist_point_to_line(poly[(cur + 1) % n], poly[i], poly[i + 1]))
        {
            cur = (cur + 1) % n;
        }
        ans = max(ans, max(len(poly[i] - poly[cur]), len(poly[i + 1] - poly[cur])));
    }
    return ans;
}


// 旋转卡壳
// 求解最小矩形覆盖
struct Line { Point s, e; };
double area(Point p0, Point p1, Point p2)
{
    double k = p0.x * p1.y + p1.x * p2.y + p2.x * p0.y - 
               p1.x * p0.y - p2.x * p1.y - p0.x * p2.y;
    return k /= 2;
}

double ans = -1;
Point a, la, ra;
Line d;
void get_minest(Points ch)
{
    int t = ch.size();
    int j = 2, l = 1, r = 1;
    double t1, t2, t3;
    for (int i = 0; i < t; i++)
    {
        // i,i+1为矩形底 ,设长度为d
        while (fabs((ch[(i + 1) % t] - ch[i]) ^ (ch[j] - ch[i])) < fabs((ch[(i + 1) % t] - ch[i]) ^ (ch[(j + 1) % t] - ch[i])))
            j = (j + 1) % t; // 矩形上端
        while (sgn(((ch[i + 1] - ch[i]) * (ch[r + 1] - ch[i])) - ((ch[i + 1] - ch[i]) * (ch[r] - ch[i]))) > 0)
            r = (r + 1) % t; // 矩形右端(相对于矩形底)

        l = max(l, j); // l必须比j大 ，既在逆时针方向上的下一个点

        while (sgn(((ch[i + 1] - ch[i]) * (ch[l + 1] - ch[i])) - ((ch[i + 1] - ch[i]) * (ch[l] - ch[i]))) < 0)
            l = (l + 1) % t; // 矩形左端

        t1 = fabs((ch[i] - ch[i + 1]) ^ (ch[j] - ch[i + 1]));                                           // h*d
        t2 = fabs((ch[i + 1] - ch[i]) * (ch[r] - ch[i])) + fabs((ch[i + 1] - ch[i]) * (ch[l] - ch[i])); // l1*d+l2*d
        t3 = len(ch[i + 1] - ch[i]) * len(ch[i + 1] - ch[i]);                                           // d*d

        double ins = t1 * t2 / t3; // s= (l1+l2)*h
        if (ans < 0 || ans > ins)
        {
            ans = ins;
            d = {ch[i], ch[i + 1]};
            a = ch[j];
            la = ch[l];
            ra = ch[r];
        }
    }
}
Point FootPoint(Point p, Point a, Point b)
{
    Vector v = a - b;
    return a - v * ((a - p) * v / (v * v));
}
void output() // ans是面积，坐标按照逆时针输出
{
    cout << fixed << setprecision(6) << ans << '\n';
    Point pt[5];                       // 方向保持l->r即可保证逆时针,因为此代码求的凸包方向就是逆时针
    pt[0] = FootPoint(la, d.s, d.e);   // 左下(相对于直线d)
    pt[1] = FootPoint(ra, d.s, d.e);   // 右下
    Line de = {a, a + d.s - d.e};      // 上端点所过直线,且和底边平行
    pt[2] = FootPoint(ra, de.s, de.e); // 右上
    pt[3] = FootPoint(la, de.s, de.e); // 左上

    for (int i = 0; i < 4; i++)
        cout << fixed << setprecision(6) << pt[(i + 1) % 4].x << ' ' << pt[(i + 1) % 4].y << '\n';
}

void solve()
{
    int n;
    cin >> n;
    Points ans, p;
    for (int i = 0; i < n; i++)
    {
        double a, b;
        cin >> a >> b;
        p.push_back({a, b});
    }
    ans = Andrew(p);
}