#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
vector<int> g[N];
// 这个节点的「大小」（所有子树上节点数 + 该节点）
// 这个节点的「重量」，即所有子树「大小」的最大值
// 用于记录树的重心（存的是节点编号）
int siz[N], wt[N], cent[2];
int n;
void GetCentroid(int cur, int fa)
{
    siz[cur] = 1;
    wt[cur] = 0;
    for (auto i : g[cur])
    {
        if (i != fa)
        {
            GetCentroid(i, cur);
            siz[cur] += siz[i];
            wt[cur] = max(wt[cur], siz[i]);
        }
    }
    wt[cur] = max(wt[cur], n - siz[cur]);
    if (wt[cur] <= n / 2) cent[cent[0] != 0] = cur;
}
