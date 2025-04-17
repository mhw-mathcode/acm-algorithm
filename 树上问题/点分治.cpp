#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;
const int N = 2e5 + 10, mod = 1e9 + 7;
int n, m, k;
int sz[N], dp[N], dist[N], now, res, Tsize, cnt;
vector<pii> g[N];
bool vis[N];

// 寻找重心
void dfs1(int u, int fa)
{
    sz[u] = 1, dp[u] = 0;
    for(auto [x, w]: g[u])
    {
        if(x == fa || vis[x]) continue;
        dfs1(x, u);
        sz[u] += sz[x];
        dp[u] = max(dp[u], sz[x]);
    }
    dp[u] = max(dp[u], Tsize - sz[u]);
    if(dp[u] < dp[now]) now = u;
}
void dfs2(int u, int fa, int d)
{
    dist[++cnt] = d;
    for(auto [x, w]: g[u])
    {
        if(x == fa || vis[x]) continue;
        dfs2(x, u, d + w);
    }
}

// 注意int型函数一定要有返回值，不然会出现一些奇怪的错误
int dfs3(int u, int d)
{
    cnt = 0, dfs2(u, 0, d);
    sort(dist + 1, dist + 1 + cnt);
    
    // 统计答案（需要修改）
    int l = 1, r = cnt, ans = 0;
    while(l <= r)
    {
        while(r && dist[l] + dist[r] > k) r--;
        if(l > r) break;
        ans += r - l + 1;
        l++;    
    }
    return ans;
}
void dfs(int u)
{
    res += dfs3(u, 0);
    vis[u] = true;
    for(auto [x, w]: g[u])
    {
        if(!vis[x])
        {
            // 去除子树里面不合法的合并路径
            res -= dfs3(x, w);
            // 其实这里加一步这个才是正确的一般点分治, 但是不加也可以
            // Tsize = n, dfs1(x, 0);
            now = 0, Tsize = sz[x], dfs1(x, 0);
            dfs(now);
        }
    }
}
signed main()
{
    std::ios::sync_with_stdio(false); 
    cin.tie(0), cout.tie(0);
    cin >> n;
    for(int i = 1; i < n; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    cin >> k;
    res = 0;
    dp[now = 0] = 1e9, Tsize = n, dfs1(1, 0);
    dfs(now);
    cout << res - n << '\n';
    return 0;
}
