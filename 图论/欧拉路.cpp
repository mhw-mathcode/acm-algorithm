#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define inf 0x3f3f3f3f
#define db double
#define il inline
#define x first
#define y second
const int N = 2e5 + 5;
const int mod = 1e9 + 7;
int n;
struct DSU
{
    int fa[N];
    void init()
    {
        for (int i = 1; i <= n; i++) fa[i] = i;
    }
    int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
    void merge(int x, int y) { fa[find(x)] = find(y); }
} d;
struct Euler_Approach
{
    int du[N], tmp[N], top, n, st; // n是节点数量，st是起始点
    int ans[N];
    int ru[N], chu[N];

    vector<int> g[N];
    map<pii, int> mp;
    map<pii, deque<string>> lj;

    void init()
    {
        top = 0, st = n;
        for (int i = 1; i <= n; i++)
        {
            du[i] = tmp[i] = ans[i] = ru[i] = chu[i] = 0;
            g[i].clear();
        }
    }

    void add_directed(int u, int v) // 有向边
    {
        if (d.find(u) != d.find(v)) d.merge(u, v);
        g[u].push_back(v);
        chu[u]++, ru[v]++;
        mp[{u, v}]++;
        st = min(st, min(u, v));
    }
    void add_undirected(int u, int v) // 无向边
    {
        g[u].push_back(v), g[v].push_back(u);
        du[u]++, du[v]++;
        mp[{u, v}]++, mp[{v, u}]++;
        st = min(st, min(u, v));
    }

    bool directed_Euler_Approach()
    {
        for (int i = 1; i <= n; i++)
            if (d.find(i) != d.find(1))
                return 0;
        int s = 0, t = 0, z = 0;
        for (int i = 1; i <= n; i++)
        {
            if (chu[i] - ru[i] == 1) s++;
            else if (chu[i] == ru[i]) z++;
            else if (ru[i] - chu[i] == 1) t++;
            else return 0;
        }
        return (s == 1 && t == 1) || (s == 0 && t == 0);
    }
    bool undirected_Euler_Approach()
    {
        int ji = 0, ou = 0;
        for (int i = 1; i <= n; i++)
        {
            if (du[i] & 1) ji++;
            else ou++;
        }
        return (ji == 2) || (ji == 0);
    }
    bool directed_Euler_Loop()
    {
        for (int i = 1; i <= n; i++)
            if (d.find(i) != d.find(1)) return 0;
        for (int i = 1; i <= n; i++)
            if (chu[i] != ru[i]) return 0;
        return 1;
    }
    bool undirected_Euler_Loop()
    {
        for (int i = 1; i <= n; i++)
            if (du[i] & 1) return 0;
        return 1;
    }

    void Euler()
    {
        for (int i = 1; i <= n; i++)
            sort(g[i].begin(), g[i].end()); // 最小字典序
        for (int i = 1; i <= n; i++)
        {
            if (ru[i] + 1 == chu[i])
            {
                st = i;
                break;
            } // 有向图
            // if(du[i]&1) { st=i;break; } //无向图
        }
        euler(st);
    }
    void euler(int u)
    {
        while (1)
        {
            while (tmp[u] < (int)g[u].size() && !mp[{u, g[u][tmp[u]]}]) tmp[u]++;
            if (tmp[u] >= (int)g[u].size()) break;
            int v = g[u][tmp[u]];

            mp[{u, v}]--; // 有向图
            // mp[{u,v}]--,mp[{v,u}]--; //无向图

            ++tmp[u];
            euler(v);
        }
        ans[++top] = u;
    }

    void out()
    {
        while (top)
            cout << ans[top--] << " ";
        // 输出特殊路径
        // for(int i=top;i>1;i--)
        // {
        //     cout<<lj[{ans[i],ans[i-1]}].front()<<"."[i==2];
        //     lj[{ans[i],ans[i-1]}].pop_front();
        // }
    }
} E;

void solve()
{
    // 注意初始化（E和并查集）
    int m;
    cin >> n >> m;
    E.n = n;
    E.init();
    d.init();
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        E.add_directed(u, v);
    }
    if (E.directed_Euler_Approach() == 0)
        cout << "No" << endl;
    else
        E.Euler(), E.out();
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1; // cin>>T;
    while (T--)
        solve();
    return 0;
}