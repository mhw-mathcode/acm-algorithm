#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 4e5 + 5;
const int M = 1e6 + 5; // x范围
int n, m, k, cnt;

struct line
{
    int k, b;
    int calc(int x) {
        return k * x + b;
    }
};
struct tree
{
    line l;
    int ls, rs;
} t[N * 4];

#define ls t[k].ls
#define rs t[k].rs

void insert(int &k, int L, int R, line g)
{
    if (!k)
    {
        k = ++cnt;
        // t[k].lazy = 1;
        t[k].l = g;
        return;
    }
    if (L == R)
    {
        if (g.calc(L) < t[k].l.calc(L)) t[k].l = g;
        // if (g.calc(L) > t[k].l.calc(L)) t[k].l = g;
        return;
    }
    int mid = (L + R) >> 1;
    if (g.calc(mid) < t[k].l.calc(mid)) swap(t[k].l, g);
    // if (g.calc(mid) > t[k].l.calc(mid)) swap(t[k].l, g);

    if (g.k > t[k].l.k) insert(ls, L, mid, g);
    else if (g.k < t[k].l.k) insert(rs, mid + 1, R, g);
    // if (g.k < t[k].l.k) insert(ls, L, mid, g);
    // else if (g.k > t[k].l.k) insert(rs, mid + 1, R, g);
}

// find_min
int find(int k, int L, int R, int x)
{
    if (!k) return 1e18;
    if (L == R) return t[k].l.calc(x);
    int mid = (L + R) >> 1;
    if (x <= mid) return min(find(ls, L, mid, x), t[k].l.calc(x));
    return min(find(rs, mid + 1, R, x), t[k].l.calc(x));
}

// find_max
int find(int k, int L, int R, int x)
{
    if (!k) return -1e18;
    if (L == R) return t[k].l.calc(x);
    int mid = (L + R) >> 1;
    if (x <= mid) return max(find(ls, L, mid, x), t[k].l.calc(x));
    return max(find(rs, mid + 1, R, x), t[k].l.calc(x));
}

void update(line g) { insert(k, -M, M, g); }
int ask(int x) { return find(k, -M, M, x); }
