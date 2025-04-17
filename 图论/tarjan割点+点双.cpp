#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
const int N = 5e5 + 5;
// 寻找割点
int n, m;

// cnt表示割点数，buc[i]表示结点i是不是割点
int tmp, dfn[N], low[N], buc[N], cnt;
vector<int> g[N];

// bcc表示点双个数，ans存储所有点双
int bcc, top;
vector<int> ans[N];
int s[N];

void dfs(int u, int fa)
{
    dfn[u] = low[u] = ++tmp;
    int son = 0;
    s[++top] = u;
    for (auto v: g[u])
    {
        if (dfn[v] == 0)
        {
            son++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u])
            {
                // 割点
                if (u != fa) cnt += !buc[u], buc[u] = 1;

                // 点双
                bcc++;
                while (s[top + 1] != v) ans[bcc].push_back(s[top--]); // 将子树出栈
                ans[bcc].push_back(u);            // 把割点/树根也丢到点双里
            }
        }
        else if (v != fa) low[u] = min(low[u], dfn[v]);
    }

    // 点双
    if (son == 0 && fa == 0)
        ans[++bcc].push_back(u);

    // 割点
    if (fa == u && son >= 2)
        cnt += !buc[u], buc[u] = 1;
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v), g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
    {
        if (!dfn[i])
        {
            top = 0;

            // 割点
            // dfs(i, i);

            // 点双
            dfs(i,0);
        }
    }

    // cout << cnt << endl;
    // vector<int> ans;
    // for (int i = 1; i <= n; i++)
    //     if (buc[i]) ans.push_back(i);
    // sort(ans.begin(), ans.end());
    // for (auto i : ans)
    //     cout << i << " ";

    cout << bcc << '\n';
    for (int i = 1; i <= bcc; i++)
    {
        cout << ans[i].size() << " ";
        for (auto j: ans[i]) cout << j << " ";
        cout << '\n';
    }
    return 0;
}