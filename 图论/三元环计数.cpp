#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 4e5 + 5;

int n, m;
int deg[N], u[N], v[N];
int edgeId[N];

int cntEdge, head[N];
struct Edge
{
    int to, nxt;
} edge[N];
void addEdge(int u, int v)
{
    edge[++cntEdge] = {v, head[u]};
    head[u] = cntEdge;
}


void solve()
{
    cin >> n >> m;
    cntEdge = 0;
    for (int i = 1; i <= n; i++) 
    {
        head[i] = deg[i] = 0;
    }

    for (int i = 1; i <= m; i++)
    {
        cin >> u[i] >> v[i];
        deg[u[i]]++, deg[v[i]]++;
    }
    for (int i = 1; i <= m; i++)
    {
        if ((deg[u[i]] == deg[v[i]] && u[i] > v[i]) || deg[u[i]] < deg[v[i]]) swap(u[i], v[i]);
        addEdge(u[i], v[i]);
    }

    int ans = 0;
    for (int u = 1; u <= n; u++)
    {
        for (int i = head[u]; i; i = edge[i].nxt) edgeId[edge[i].to] = i;
        for (int i = head[u]; i; i = edge[i].nxt)
        {
            int v = edge[i].to;
            for (int j = head[v]; j; j = edge[j].nxt)
            {
                int w = edge[j].to;
                if (edgeId[w]) // 编号为i j edgeID[w]的边形成一个三元环
                {
                    ans++;
                }
            }
        }
        for (int i = head[u]; i; i = edge[i].nxt) edgeId[edge[i].to] = 0;
    }
    
    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
