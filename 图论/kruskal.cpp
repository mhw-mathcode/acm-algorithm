#include <bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f;
// #define int long long
const int N = 3e5 + 5;
int fa[N], n, m; // n为结点数，m为边数
struct edge
{
    int a, b, w;
    bool operator<(const edge &W) const
    {
        return w < W.w;
    }
} edge[N];
int find(int x) // 并查集（路径压缩版）
{
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}
int kruskal()
{
    sort(edge + 1, edge + m + 1);
    for (int i = 1; i <= n + 1; i++) fa[i] = i; // 初始并查集
    int res = 0, cnt = 0;
    for (int i = 1; i <= m; i++)
    {
        int a = edge[i].a, b = edge[i].b, w = edge[i].w;
        a = find(a), b = find(b);
        if (a != b) // 两个部分不连通
        {
            fa[a] = b;
            res += w;
            cnt++;
        }
    }
    if (cnt < n - 1) return inf;
    return res;
}
