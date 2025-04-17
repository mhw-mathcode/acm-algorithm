// 注意 int 求绝对值使用 abs，浮点数才使用 fabs

#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;      // 根据题目精度要求进行修改
const double PI = acos(-1.0); // pai, 3.1415916....

int sgn(double x)
{ // 进行判断, 提高精度
    if (fabs(x) < eps)
        return 0;          // x == 0, 精度范围内的近似相等
    return x > 0 ? 1 : -1; // 返回正负
}
bool eq(double a, double b) { return abs(a - b) < eps; } // ==
bool gt(double a, double b) { return a - b > eps; }      // >
bool lt(double a, double b) { return a - b < -eps; }     // <
bool ge(double a, double b) { return a - b > -eps; }     // >=
bool le(double a, double b) { return a - b < eps; }      // <=

// 点和向量<---------------------------------------------->
// Need: sgn()
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

    // 向量 · 向量 (点积)
    double operator*(const Point &B) const { return x * B.x + y * B.y; }

    // 点 * 数 = 点, 向量 * 数 = 向量
    Point operator*(const double &B) const { return Point(x * B, y * B); }

    // 点 / 数 = 点, 向量 / 数 = 向量
    Point operator/(const double &B) const { return Point(x / B, y / B); }

    // 判断大小, 一般用于排序
    bool operator<(const Point &B) const { 
        return x < B.x || (x == B.x && y < B.y); 
    }

    // 判断相等, 点 == 点, 向量 == 向量, 一般用于判断和去重
    bool operator==(const Point &B) const { 
        return sgn(x - B.x) == 0 && sgn(y - B.y) == 0; 
    }

    // 判断不相等, 点 != 点, 向量 != 向量
    bool operator!=(const Point &B) const { return sgn(x - B.x) || sgn(y - B.y); }
} Vector;

// 极角排序
// Need: (^, sgn)
// 基准点
Point p0 = {0, 0};
inline int check(Point p)
{
    if (p.y > p0.y || (p.y == p0.y && p.x >= p0.x))
        return 1;
    else
        return 0;
}
int cmp(Point p1, Point p2)
{
    if (check(p1) != check(p2))
        return check(p1) > check(p2);
    return sgn((p1 - p0) ^ (p2 - p0)) > 0;
}

// 两点间距离
// Need: (-, *)
double dist(Point a, Point b) { return sqrt((a - b) * (a - b)); }

// 向量的模
// Need: (*)
double len(Vector A) { return sqrt(A * A); }

// 单位向量
// Need: (/), len()
Vector norm(Vector A) { return A / len(A); }

// 两向量夹角
// Need: (*), len(), PI
double Angle(Vector A, Vector B)
{
    double t = acos((A * B) / len(A) / len(B));
    return t;              // 返回 [0, π]
    return t * (180 / PI); // 返回 [0, 180] (角度)
}

// 两向量的夹角余弦
// Need: (*), len
double cos_t(Vector u, Vector v) { return u * v / len(u) / len(v); }

// 将向量逆时针旋转90度
Vector r90a(Vector v) { return {-v.y, v.x}; }

// 将向量顺时针旋转90度
Vector r90c(Vector v) { return {v.y, -v.x}; }

// 将向量逆时针旋转
// Need: (*, ^)
// 向量 A 和要逆时针转的角度 [0, PI]
// PI / 2, 90度
Vector Rotate(Vector A, double b)
{
    Vector B(sin(b), cos(b));
    return Vector(A ^ B, A * B);
}

// 向量是否互相垂直
// Need: (*), eq
bool verti(Vector u, Vector v) { return eq(u * v, 0); }

// 向量是否互相平行
// Need: (^), eq
bool paral(Vector u, Vector v) { return eq(u ^ v, 0); }

// 向量是否与x轴平行
// Need: eq
bool paral_x(Vector v) { return eq(v.y, 0); }

// 向量是否与y轴平行
// Need: eq
bool paral_y(Vector v) { return eq(v.x, 0); }

// 直线与线段<---------------------------------------------->

struct Line
{
    Point s, e;
    Line() {}
    Line(Point x, Point y) : s(x), e(y) {}
};
struct Seg
{
    Point s, e;
};
Line read_Line()
{
    Line a;
    cin >> a.e.x >> a.e.y >> a.s.x >> a.s.y;
    return a;
}

// 直线的唯一表示
tuple<int, int, int> getLineKey(Point p1, Vector p2)
{
    int x1 = p1.x, y1 = p1.y;

    int A = p2.y;            // Δy
    int B = -p2.x;           // Δx
    int C = A * x1 + B * y1; // 直线方程 Ax + By = C

    // 标准化，使得 (A, B, C) 的表示唯一
    int g = gcd(A, B);
    A /= g, B /= g, C /= g;

    // 保证 A 为正数（或 A = 0 时，B 为正）
    if (A < 0 || (A == 0 && B < 0))
    {
        A = -A, B = -B, C = -C;
    }

    return {A, B, C};
}

// 给定直线的横坐标求纵坐标
// NOTE 请确保直线不与y轴平行
double at_x(Line l, double x)
{
    Vector lv = l.e - l.s;
    return l.s.y + (x - l.s.x) * lv.y / lv.x;
}

// 给定直线的纵坐标求横坐标
// NOTE 请确保直线不与x轴平行
double at_y(Line l, double y)
{
    Vector lv = l.e - l.s;
    return l.s.x - (y + l.s.y) * lv.x / lv.y;
}

// 角平分线
// Need: (+), len, norm
Line bisec(Point P, Vector u, Vector v) { return {P, norm(u) + norm(v)}; }

// 线段的方向向量
// Need: (-)
// NOTE 直线的方向向量直接访问属性v
Vector dvec(Seg l) { return l.s - l.e; }

// 线段中点
Point midp(Seg l) { return {(l.s.x + l.e.x) / 2, (l.s.y + l.e.y) / 2}; }

// 线段中垂线
// Need: (-), r90c, midp
Line perp(Seg l) { return {midp(l), midp(l) + r90c(l.s - l.e)}; }

// 判断点在直线的哪边
// Need: (-, ^), sgn()
// 点在直线上, 返回 0 (三点共线)
// 点在直线的逆时针方向, 返回 1
// 点在直线的顺时针方向, 返回 -1
// 点 a, b (向量ab) 所在的直线和点 c
// 使用的时候要注意 a 和 b 的顺序, 有时顺序不同, 结果不同
int Cross(Point a, Point b, Point c) { return sgn((b - a) ^ (c - a)); }
// 两种分情况使用
// double Cross(Point a, Point b, Point c) { return (b - a) ^ (c - a); }

// 判断三点共线
// Need: sgn(), 操作符重载(-, ^)
bool In_one_line(Point A, Point B, Point C) { return !sgn((B - A) ^ (C - B)); }

// 点到直线距离
// Need: (-, ^), len()
// 点 P 到直线 AB 的距离
double Dist_point_to_line(Point P, Point A, Point B)
{
    Vector v1 = B - A, v2 = P - A;
    return fabs((v1 ^ v2) / len(v1));
}

// 点到线段距离
// Need: 操作符重载(==, -, *, ^), len(), sgn()
// 点 P 到线段 AB 的距离
double Dist_point_to_seg(Point P, Point A, Point B)
{
    if (A == B)
        return len(P - A); // 如果重合, 那么就是两点的距离
    Vector v1 = B - A, v2 = P - A, v3 = P - B;
    if (sgn(v1 * v2) < 0)
        return len(v2); // AP 最短
    if (sgn(v1 * v3) > 0)
        return len(v3);               // BP 最短
    return fabs((v1 ^ v2) / len(v1)); // 垂线
}

// 点是否在直线上
// Need: (-), eq
bool onLine(Point P, Line l)
{
    Vector lv = l.e - l.s;
    return eq((P.x - l.e.x) * lv.y, (P.y - l.e.y) * lv.x);
}

// 点是否在线段上
// Need: (-, *, ^), sgn()
// 点 P 是否在线段 AB 上
bool OnSegment(Point P, Point A, Point B)
{
    Vector PA = A - P, PB = B - P;
    return sgn(PA ^ PB) == 0 && sgn(PA * PB) <= 0; // <=, 包括端点; <, 不包括端点
}

// 判断直线与线段是否相交
// Need: Cross()
// 相交, 返回 true
// 不相交, 返回 false
// 直线 ab 与线段 cd
bool Intersect_line_seg(Point a, Point b, Point c, Point d)
{
    return Cross(a, b, c) * Cross(a, b, d) <= 0; // <= 包括重合 < 不包括重合
}

// 判断两线段是否相交
// Need: Cross(), OnSegment()
// 相交, 返回 true (包括端点相交)
// 不相交, 返回 false
// 线段 ab 与线段 cd
bool Intersect_seg(Point a, Point b, Point c, Point d)
{
    // 第一个if是判断是否在端点处相交
    if (OnSegment(a, c, d) || OnSegment(b, c, d) || 
        OnSegment(c, a, b) || OnSegment(d, a, b))
        return 1;
    if (Cross(a, b, c) * Cross(a, b, d) >= 0)
        return 0;
    if (Cross(c, d, a) * Cross(c, d, b) >= 0)
        return 0;
    return 1;
}

// 判断两直线平行
// Need: (-, ^), sgn()
// 返回true: 平行/重合, false: 相交
bool Line_parallel(Line A, Line B) { 
    return sgn((A.s - A.e) ^ (B.s - B.e)) == 0;
}

// 判断两直线重合
// Need: Line_parallel, In_one_line
// 返回true：重合
bool Line_coincident(Line A, Line B) { 
    return Line_parallel(A, B) && In_one_line(A.s, A.e, B.s); 
}

// 判断两直线是否垂直
// Need: (-, *), sgn()
// 返回true: 垂直, false: 不垂直
bool Line_vertical(Line A, Line B) { 
    return sgn((A.e - A.s) * (B.s - B.e)) == 0; 
}

// 求两直线交点
// Need: (-, *D, ^)
// 首先要判断两直线是否相交, 即不平行(不重合)
// a, b 所在直线与 c, d 所在直线的交点
Point Intersection_line(Line l1, Line l2) // 直线交点
{
    Point a = l1.s, b = l1.e, c = l2.s, d = l2.e;
    Vector u = b - a, v = d - c;
    double t = ((a - c) ^ v) / (v ^ u);
    return a + u * t;
}

// 求点到直线的垂足
// Need: (-, *), len
// 点 p 到直线 ab 的垂足
Point FootPoint(Point p, Point a, Point b)
{
    Vector v = a - b;
    return a - v * ((a - p) * v / (v * v));
}

// 过某点作直线的垂线
// Need: (-), r90c
Line perp(Line l, Point P)
{
    Vector lv = l.e - l.s;
    return {P, r90c(lv)};
}

// 点关于直线的对称点
// Need: (-, +)
// 点P关于直线AB的对称点
Point Symmetry_PL(Point p, Point a, Point b)
{
    return p + (FootPoint(p, a, b) - p) * 2;
    // 实际上就是求垂足之后延长一倍得到的向量，与原来的点加起来就行了
}

// 两条直线是否重合
// Need: eq, onLine
bool operator==(Line a, Line b)
{
    Vector v = a.s - a.e;
    return onLine(a.s, b) && onLine(a.s + v, b);
}

// 两条线段是否重合
// Need: (==), eq
bool operator==(Seg a, Seg b) { 
    return (a.s == b.s && a.e == b.e) || (a.s == b.e && a.e == b.s); 
}

// 三角形<---------------------------------------------->

// 三角形面积
// Need: (-, *)
double area(Point p0, Point p1, Point p2)
{
    double k = p0.x * p1.y + p1.x * p2.y + p2.x * p0.y - 
               p1.x * p0.y - p2.x * p1.y - p0.x * p2.y;
    return k /= 2;
}

// 三角形四心
// 三角形的重心
Point barycenter(Point A, Point B, Point C)
{
    Line u, v;
    u.s.x = (A.x + B.x) / 2;
    u.s.y = (A.y + B.y) / 2;
    u.e = C;
    v.s.x = (A.x + C.x) / 2;
    v.s.y = (A.y + C.y) / 2;
    v.e = B;
    return Intersection_line(u, v);
}

// 三角形外心
// Need: r90c, V*V, d*V, V-V, V+V
// NOTE 给定圆上三点求圆，要先判断是否三点共线
Point circumcenter(Point A, Point B, Point C)
{
    double a = A * A, b = B * B, c = C * C;
    double d = 2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
    return r90c((B - C) * a + (C - A) * b + (A - B) * c) * (double)(1 / d);
}

// 三角形的内心
// DEPENDS len, d*V, V-V, V+V
Point incenter(Point A, Point B, Point C)
{
    double a = len(B - C), b = len(A - C), c = len(A - B);
    double d = a + b + c;
    return (A * a + B * b + C * c) * (1.0 / d);
}

// 三角形的垂心
// DEPENDS V*V, d*V, V-V, V^V, r90c
Point orthocenter(Point A, Point B, Point C)
{
    double n = B * (A - C), m = A * (B - C);
    double d = (B - C) ^ (A - C);
    return r90c((C - B) * n - (C - A) * m) * (1.0 / d);
}

// 多边形<---------------------------------------------->
using Points = vector<Point>;

// 判断多边形poly是否是凸多边形（前提是多边形）
// Need: Cross
bool IsConvex(Points poly)
{
    int n = poly.size();
    if (n < 3)
        return false;
    Line side;
    int f1 = 1, f2 = 1;
    for (int i = 0; i < n; i++)
    {
        side.s = poly[i];
        side.e = poly[(i + 1) % n];
        if (Cross(side.s, side.e, poly[(i + 2) % n]) == -1)
            f1 = 0;
        if (Cross(side.s, side.e, poly[(i + 2) % n]) == 1)
            f2 = 0;
    }
    return f1 | f2;
}

// 求凸多边形的有向面积
// Need: (^)
// 叉积的几何意义就是三角形有向面积的二倍，所以这里要除以二
double convex_polygon_area(Points p)
{
    double area = 0;
    int n = p.size();
    for (int i = 1; i <= n - 2; ++i)
        area += (p[i] - p[0]) ^ (p[i + 1] - p[0]);
    // return area / 2;
    return fabs(area / 2); // 不加的话求的是有向面积，逆时针为负，顺时针为正
}

// 求非凸多边形的有向面积
// Need: (^)
// 我们叉积求得的三角形面积是有向的，在外面的面积可以正负抵消掉，
// 因此非凸多边形也适用，可以从任意点出发划分
// 可以取原点为起点，减少叉乘次数
double polyg_on_area(Points p)
{
    int n = p.size();
    double area = 0;
    for (int i = 1; i <= n - 2; ++i)
        area += (p[i] - p[0]) ^ (p[i + 1] - p[0]);
    return area / 2;
}

// 判断点是否在多边形内，若点在多边形内返回1，在多边形外部返回0，在多边形上返回-1
// Need: (^), OnSegment, sgn
// 待判断的点和该多边形的所有点的合集
int is_point_in_polygon(Point p, Points poly)
{
    int wn = 0;
    int n = poly.size();
    for (int i = 0; i < n; ++i)
    {
        if (OnSegment(p, poly[i], poly[(i + 1) % n]))
            return -1;
        int k = sgn((poly[(i + 1) % n] - poly[i]) ^ (p - poly[i]));
        int d1 = sgn(poly[i].y - p.y);
        int d2 = sgn(poly[(i + 1) % n].y - p.y);
        if (k > 0 && d1 <= 0 && d2 > 0)
            wn++;
        if (k < 0 && d2 <= 0 && d1 > 0)
            wn--;
    }
    if (wn != 0)
        return 1;
    return 0;
}

// 判断线段是否在多边形内
// Need: is_point_in_polygon, OnSegment
// 判断线段是否在多边形内 (线段的点可能在多边形上)
// 多边形可以是任意简单多边形
// 判断线段是否在多边形内 (线段的点可能在多边形上)
bool InsidePolygon(Points poly, Seg L)
{
    Points points;
    Point p;
    Seg side;
    int result = ((is_point_in_polygon(L.s, poly) != 0) && 
                  (is_point_in_polygon(L.e, poly) != 0));
    if (!result)
        return false;

    int n = poly.size();
    for (int i = 0; i < n; i++)
    {
        side.s = poly[i];
        side.e = poly[(i + 1) % n];

        if (OnSegment(L.s, side.s, side.e))
            points.push_back(L.s);
        else if (OnSegment(L.e, side.s, side.e))
            points.push_back(L.e);
        else if (OnSegment(side.s, L.s, L.e))
            points.push_back(side.s);
        else if (OnSegment(side.e, L.s, L.e))
            points.push_back(side.e);
        else if (Intersect_seg(side.s, side.e, L.s, L.e))
            return false;
    }
    // 对交点进行排序
    std::sort(points.begin(), points.end());

    for (int i = 1; i < points.size(); i++)
    {
        if (points[i - 1] != points[i])
        {
            p.x = (points[i - 1].x + points[i].x) / 2.0;
            p.y = (points[i - 1].y + points[i].y) / 2.0;
            if (is_point_in_polygon(p, poly) == 0)
                return false;
        }
    }
    return true;
}

// 求多边形重心
// Need: area
Point barycenter(Points p)
{
    int n = p.size();
    Point p0 = p[0], p1 = p[1], p2, center;
    double Area, sumarea = 0, sumx = 0, sumy = 0;
    for (int i = 2; i < n; i++)
    {
        p2 = p[i];
        center.x = p0.x + p1.x + p2.x;
        center.y = p0.y + p1.y + p2.y;
        Area = area(p0, p1, p2);
        sumarea += Area; // 图形总面积
        sumx += center.x * Area;
        sumy += center.y * Area;
        p1 = p2;
    }
    return {sumx / sumarea / 3, sumy / sumarea / 3};
}

// 圆<---------------------------------------------->
struct Circle
{
    Point c;
    double r;
    Circle(Point c = Point(), double r = 0) : c(c), r(r) {}
    inline Point point(double a) // 通过圆心角求坐标
    {
        return Point(c.x + cos(a) * r, c.y + sin(a) * r);
    }
};

// 读入
inline Circle read_circle()
{
    Circle C;
    scanf("%lf%lf%lf", &C.c.x, &C.c.y, &C.r);
    return C;
}

double distance(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// 计算圆上到点p最近点,如p与圆心重合,返回p本身
Point dot_to_circle(Circle pc, Point p)
{
    Point c = pc.c;
    double r = pc.r;
    Point u, v;
    if (distance(p, c) < eps)
        return p;
    u.x = c.x + r * fabs(c.x - p.x) / distance(c, p);
    u.y = c.y + r * fabs(c.y - p.y) / distance(c, p) 
                  * ((c.x - p.x) * (c.y - p.y) < 0 ? -1 : 1);
    v.x = c.x - r * fabs(c.x - p.x) / distance(c, p);
    v.y = c.y - r * fabs(c.y - p.y) / distance(c, p) 
                  * ((c.x - p.x) * (c.y - p.y) < 0 ? -1 : 1);
    return distance(u, p) < distance(v, p) ? u : v;
}

// 点到圆的切线
// 过点p到圆c的切线，v[i]是第i条切线
vector<Vector> get_tangents(Point p, Circle C)
{
    Vector u = C.c - p;
    double dist = len(u);
    if (dist < C.r)
        return {}; // 点在内部，没有切线
    else if (sgn(dist - C.r) == 0)
    { // p在圆上，只有一条切线
        return {Rotate(u, PI / 2)};
    }
    else
    { // 否则是两条切线
        double ang = asin(C.r / dist);
        return {Rotate(u, -ang), Rotate(u, +ang)};
    }
}

// 求圆与直线交点
// Need: (-,*), FootPoint, gt, eq, len
// 根据返回vector大小判断情况
vector<Point> inter_line_circle(Line l, Circle C)
{
    Point P = FootPoint(C.c, l.s, l.e);
    double h = len(P - C.c);
    if (gt(h, C.r))
        return {};
    if (eq(h, C.r))
        return {P};
    double d = sqrt(C.r * C.r - h * h);
    Vector fx = l.e - l.s;
    Vector vec = fx * (d / len(fx));
    return {P + vec, P - vec};
}

// 求两圆交点
vector<Point> inter_circle_circle(Circle C1, Circle C2)
{
    Vector v1 = C2.c - C1.c, v2 = r90c(v1);
    double d = len(v1);
    if (gt(d, C1.r + C2.r) || gt(abs(C1.r - C2.r), d))
        return {};
    if (eq(d, C1.r + C2.r) || eq(d, abs(C1.r - C2.r)))
        return {C1.c + v1 * (C1.r / d)};
    double a = ((C1.r * C1.r - C2.r * C2.r) / d + d) / 2;
    double h = sqrt(C1.r * C1.r - a * a);
    Vector av = v1 * (a / len(v1)), hv = v2 * (h / len(v2));
    return {C1.c + av + hv, C1.c + av - hv};
}

// 两圆相交面积
// Need: (-,*), len
double K(double x) { return x * x; }
double AreaOfOverlap(Circle c1, Circle c2)
{
    double dis = dist(c1.c, c2.c);
    if (c1.r == 0 || c2.r == 0 || dis >= c1.r + c2.r)
        return 0;
    else if (dis <= fabs(c1.r - c2.r))
        return PI * K(min(c1.r, c2.r));
    else
    {
        double angA = 2 * acos((K(c1.r) + K(dis) - K(c2.r)) / (2 * c1.r * dis));
        double angB = 2 * acos((K(c2.r) + K(dis) - K(c1.r)) / (2 * c2.r * dis));
        double areaA = K(c1.r) * (angA - sin(angA)) / 2;
        double areaB = K(c2.r) * (angB - sin(angB)) / 2;
        return areaA + areaB;
    }
}

// 两圆的公切线
// 返回切线的条数，-1表示无穷条切线
// a[i]和b[i] 分别是第i条切线在圆A和圆B上的切点
int get_tangents(Circle A, Circle B, Point *a, Point *b)
{
    int cnt = 0;
    if (A.r < B.r)
        swap(A, B), swap(a, b);
    int d2 = (A.c.x - B.c.x) * (A.c.x - B.c.x) + 
             (A.c.y - B.c.y) * (A.c.y - B.c.y);
    int rdiff = A.r - B.r;
    int rsum = A.r + B.r;
    if (d2 < rdiff * rdiff)
        return 0; // 内含
    double base = atan2(B.c.y - A.c.y, B.c.x - A.c.x);
    if (d2 == 0 && A.r == B.r)
        return -1; // 无限多条切线
    if (d2 == rdiff * rdiff)
    { // 内切，1条切线
        a[cnt] = A.point(base);
        b[cnt] = B.point(base);
        cnt++;
        return 1;
    }
    // 有外共切线
    double ang = acos((A.r - B.r) / sqrt(d2));
    a[cnt] = A.point(base + ang);
    b[cnt] = B.point(base + ang);
    cnt++;
    a[cnt] = A.point(base - ang);
    b[cnt] = B.point(base - ang);
    cnt++;
    if (d2 == rsum * rsum)
    { // 一条内公切线
        a[cnt] = A.point(base);
        b[cnt] = B.point(PI + base);
        cnt++;
    }
    else if (d2 > rsum * rsum)
    { // 两条内公切线
        double ang = acos((A.r + B.r) / sqrt(d2));
        a[cnt] = A.point(base + ang);
        b[cnt] = B.point(PI + base + ang);
        cnt++;
        a[cnt] = A.point(base - ang);
        b[cnt] = B.point(PI + base - ang);
        cnt++;
    }
    return cnt;
}

// 求三角形外接圆
Circle WaiJieYuan(Point p1, Point p2, Point p3)
{
    double Bx = p2.x - p1.x, By = p2.y - p1.y;
    double Cx = p3.x - p1.x, Cy = p3.y - p1.y;
    double D = 2 * (Bx * Cy - By * Cx);
    double ansx = (Cy * (Bx * Bx + By * By) - By * (Cx * Cx + Cy * Cy)) / D 
                    + p1.x;
    double ansy = (Bx * (Cx * Cx + Cy * Cy) - Cx * (Bx * Bx + By * By)) / D 
                    + p1.y;
    Point p(ansx, ansy);
    return Circle(p, len(p1 - p));
}

// 求三角形内接圆
Circle NeiJieYuan(Point p1, Point p2, Point p3)
{
    double a = len(p2 - p3);
    double b = len(p3 - p1);
    double c = len(p1 - p2);
    Point p = (p1 * a + p2 * b + p3 * c) / (a + b + c);
    return Circle(p, Dist_point_to_line(p, p1, p2));
}

// 两圆的关系
// 5 相离
// 4 外切
// 3 相交
// 2 内切
// 1 内含
int relationcircle(Circle p1, Circle p2)
{
    double d = distance(p1.c, p2.c);
    double r1 = p1.r, r2 = p2.r;
    if (sgn(d - r1 - r2) > 0) return 5;
    if (sgn(d - r1 - r2) == 0) return 4;
    double l = fabs(r1 - r2);
    if (sgn(d - r1 - r2) < 0 && sgn(d - l) > 0) return 3;
    if (sgn(d - l) == 0) return 2;
    if (sgn(d - l) < 0) return 1;
    return 0;
}