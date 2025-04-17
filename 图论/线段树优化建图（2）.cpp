#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
#define inf 0x3f3f3f3f
#define endl '\n'
const int N = 2e6 + 5;
const int mod = 998244353;

vector<pii> g[N * 2];

void add(int u, int v, int w)
{
	g[u].push_back({v, w});
}

// [1...N] 是 out-tree的范畴，[N+1...2N] 是in-tree的范畴
#define lc (cur << 1)
#define rc (cur << 1 | 1)
int in[N * 2], out[N * 2];
void build(int cur, int l, int r)
{
	if (l == r)
	{
		out[l] = cur;
		in[l] = cur + N;
		add(out[l], in[l], 0);
		add(in[l], out[l], 0);
		return;
	}
	int mid = (l + r) >> 1;
	add(cur, lc, 0);
	add(cur, rc, 0);
	add(lc + N, cur + N, 0);
	add(rc + N, cur + N, 0);
	build(lc, l, mid);
	build(rc, mid + 1, r);
}
void modify(int cur, int l, int r, int u, int L, int R, int w, int type)
{
	if (L <= l && R >= r)
	{
		if (type == 2) add(in[u], cur, w); // 点向区间连边
		else add(cur + N, out[u], w); // 区间向点连边
		return;
	}
	int mid = (l + r) >> 1;
	if (L <= mid) modify(cur << 1, l, mid, u, L, R, w, type);
	if (R > mid) modify(cur << 1 | 1, mid + 1, r, u, L, R, w, type);
}

int s;
int d[N * 2], v[N * 2];

priority_queue<pii, vector<pii>, greater<pii>> q;
void dijkstra()
{
	d[s] = 0;
	q.push({0, s});
	while (!q.empty())
	{
		int x = q.top().second;
		q.pop();
		if (v[x]) continue;
		v[x] = 1;
		for (auto [y, w] : g[x])
		{
			if (d[y] > d[x] + w)
			{
				d[y] = d[x] + w;
				q.push({d[y], y});
			}
		}
	}
}

void solve()
{
	memset(d, inf, sizeof d);
	int n, m;
	cin >> n >> m >> s;
	int E = n + 2 * m;
	build(1, 1, E);
	int num = n;
	for (int i = 1; i <= m; i++)
	{
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		num++;
		modify(1, 1, E, num, a, b, 0, 1);
		modify(1, 1, E, num, c, d, 1, 2);

		num++;
		modify(1, 1, E, num, a, b, 0, 2);
		modify(1, 1, E, num, c, d, 1, 1);
	}
	s = in[s];
	dijkstra();
	for (int i = 1; i <= n; i++) 
	{
		cout << d[out[i]] << '\n';
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T = 1; // cin >> T;
	while (T--) solve();
	return 0;
}