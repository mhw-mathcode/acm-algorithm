#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
vector<int>g[N];

int v2[N], pre[N], d[N];
vector<int> ans;
int dfs(int u, int f)
{
    pre[u] = f;
    v2[u] = 1;
    d[u] = d[f] + 1;
    for (auto i: g[u])
    {
        if (i == f) continue;
        if (v2[i])
        {
            if ((d[u] - d[i]) % 2 == 0)
            {
                int now = u;
                while(now != i)
                {
                    ans.push_back(now);
                    now = pre[now];
                }
                ans.push_back(now);
                return 1;
            }
        }
        else  {
            if (dfs(i, u)) return 1;
        }
    }
    return 0;
}
void solve()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    dfs(1, 0);
    cout << ans.size() << '\n';
    for (auto i: ans) cout << i << ' ';
    cout << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1; // cin >> T;
    while (T--) solve();
    return 0;
}
