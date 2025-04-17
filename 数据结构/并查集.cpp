#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int fa[N];
int find(int x)
{
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y)
{
    fa[find(x)] = find(y);
}
int siz[N], dep[N];
// 带权并查集
int find(int x)
{
    if (x != fa[x])
    {
        int t = fa[x];
        fa[x] = find(fa[x]);
        dep[x] += dep[t];
    }
    return fa[x];
}
void merge(int x, int y)
{
    int fx = find(x), fy = find(y);
    if (fx != fy)
    {
        fa[fy] = fx;
        dep[fy] += siz[fx];
        siz[fx] += siz[fy];
    }
}