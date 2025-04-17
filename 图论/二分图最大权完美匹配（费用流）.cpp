#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=1e3+5;
const int M=1e6+5;

class SimpleX
{
public:
    const int inf = 1e18;

    int head[N];
    int nxt[M];
    int from[M];
    int to[M];
    int flow[M];
    int cost[M];
    int cnt = 1;
    void addedge(int u, int v, int fl, int co)
    {
        cnt++;
        to[cnt] = v;
        from[cnt] = u; 
        nxt[cnt] = head[u];
        head[u] = cnt;
        flow[cnt] = fl;
        cost[cnt] = co;
        return;
    }
    void Add(int u, int v, int fl, int co)
    {
        addedge(u, v, fl, co);
        addedge(v, u, 0, -co);
        return;
    }

    int fa[1005];
    int fe[1005];
    int tag[1005];
    int pos;
    void gettree(int cur)
    {
        tag[cur] = pos;
        for (int i = head[cur]; i; i = nxt[i])
        {
            int v = to[i];
            if (tag[v] || !flow[i]) continue;
            fa[v] = cur;
            fe[v] = i;
            gettree(v);
        }
    }
    int pushflow(int id)
    {
        pos++;
        int u = from[id], v = to[id];
        int lca = u;
        while (lca)
        {
            tag[lca] = pos;
            lca = fa[lca];
        }
        lca = v;
        while (tag[lca] != pos)
        {
            tag[lca] = pos;
            lca = fa[lca];
        }
        int p = 2, minflow = flow[id], del;
        for (int now = u; now ^ lca; now = fa[now])
        {
            int eg = fe[now];
            if (flow[eg] < minflow)
            {
                p = 0;
                minflow = flow[eg];
                del = now;
            }
        }
        for (int now = v; now ^ lca; now = fa[now])
        { 
            int eg = fe[now] ^ 1;
            if (flow[eg] < minflow)
            {
                p = 1;
                minflow = flow[eg];
                del = now;
            }
        }
        int C = 0;
        for (int now = u; now ^ lca; now = fa[now])
        {
            int eg = fe[now];
            flow[eg] -= minflow;
            flow[eg ^ 1] += minflow;
            C = (C + minflow * cost[eg]);
        }
        for (int now = v; now ^ lca; now = fa[now])
        {
            int eg = fe[now] ^ 1;
            flow[eg] -= minflow;
            flow[eg ^ 1] += minflow;
            C = (C + minflow * cost[eg]);
        }
        flow[id] -= minflow;
        flow[id ^ 1] += minflow;
        C = (C + minflow * cost[id]);
        if (p == 2) return C;
        if (p) swap(u, v);
        int Le = id ^ p, Lu = v;
        while (Lu != del)
        {
            Le ^= 1;
            tag[u] = 0;
            swap(fe[u], Le);
            int need = fa[u];
            fa[u] = Lu;
            Lu = u;
            u = need;
        }
        return C;
    }
    int dep[N];
    int getdep(int x)
    {
        if (tag[x] == pos) return dep[x];
        tag[x] = pos;
        return dep[x] = getdep(fa[x]) + cost[fe[x]];
    }
    pair<int, int> getflow(int s, int t)
    {
        Add(t, s, inf, -inf);
        pos++;
        gettree(t);
        fa[t] = 0;
        pos++;
        tag[t] = pos;
        bool flag = true;
        while (flag)
        {
            flag = false;
            for (int i = 2; i <= cnt; i++)
            {
                int u = from[i], v = to[i];
                if (!flow[i]) continue;
                if (cost[i] + getdep(u) - getdep(v) < 0)
                {
                    flag = true;
                    pushflow(i);
                }
            }
        }
        int ansflow = flow[cnt];
        int anscost = 0;
        for (int i = 2; i <= cnt; i += 2)
            anscost = anscost + flow[i ^ 1] * cost[i];
        return make_pair(ansflow, anscost + (ansflow * inf));
    }
    int pre[N];
    void output(int n, int s, int t)
    {
        for (int i = 2; i <= cnt; i += 2)
        {
            if (flow[i ^ 1])
            {
                if (from[i] == s || to[i] == t) continue;
                pre[to[i] - n] = from[i];
            }
        }
        for (int i = 1; i <= n; i++) cout << pre[i] << ' ';
        cout << '\n';
    }
} G;
int n, m;
signed main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        G.Add(u, v + n, 1, -w);
    }
    int s = 2 * n + 1, t = 2 * n + 2;
    for (int i = 1; i <= n; i++)
    {
        G.Add(s, i, 1, 0);
        G.Add(i + n, t, 1, 0);
    }
    cout << -G.getflow(s, t).second << '\n';
    G.output(n, s, t);
    return 0;
}