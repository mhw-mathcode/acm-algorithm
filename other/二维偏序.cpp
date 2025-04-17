#include <bits/stdc++.h>
using namespace std;
const int N = 1e7 + 5;
int n, m, t[N], ans[N], num;
int lowbit(int x) { return x & (-x); }
// 单点修改
void update(int pos, int k)
{
    for (int i = pos; i <= num; i += lowbit(i))
        t[i] += k;
}
// 区间查询
int ask(int pos)
{
    int ans = 0;
    for (int i = pos; i; i -= lowbit(i))
        ans += t[i];
    return ans;
}
struct node
{
    int x, y, op, id;
};
int cmp(node a, node b)
{
    return a.x < b.x;
}
void solve()
{
    cin >> n >> m;
    vector<tuple<int, int, int>> v, vv;
    vector<tuple<int, int, int, int>> qq;
    map<int, int> mp, num0;
    for (int i = 1; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        mp[x]++, mp[y]++;
        vv.push_back({x, y, 1});
    }
    for (int i = 1; i <= m; i++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        mp[x1]++, mp[y1]++, mp[x2]++, mp[y2]++;
        qq.push_back({x1, y1, x2, y2});
    }
    num = 1;
    for (auto i : mp)
        num0[i.first] = num++;
    for (auto [x, y, w] : vv)
        v.push_back({num0[x], num0[y], w});
    sort(v.begin(), v.end());
    vector<node> q;
    for (int i = 0; i < m; i++)
    {
        auto [x1, y1, x2, y2] = qq[i];
        x1 = num0[x1], y1 = num0[y1], x2 = num0[x2], y2 = num0[y2];
        q.push_back({x1 - 1, y1 - 1, 1, i});
        q.push_back({x1 - 1, y2, -1, i});
        q.push_back({x2, y1 - 1, -1, i});
        q.push_back({x2, y2, 1, i});
    }
    sort(q.begin(), q.end(), cmp);
    int cnt = 0;
    for (auto [x, y, op, id] : q)
    {
        while (cnt < n && get<0>(v[cnt]) <= x)
            update(get<1>(v[cnt]), get<2>(v[cnt])), cnt++;
        ans[id] += op * ask(y);
    }
    for (int i = 0; i < m; i++)
        cout << ans[i] << endl;
}
signed main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);cout.tie(0);
    int T = 1; // cin>>T;
    while (T--) solve();
    return 0;
}