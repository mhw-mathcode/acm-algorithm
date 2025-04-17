#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
const int N = 2e5 + 5;

struct node {
	int l, r, id;
} q[N];

int id[N], L[N], R[N], sz, tot;
int ans[N];

bool cmp(node x, node y) {
	if ((x.l - 1) / sz != (y.l - 1) / sz) return x.l < y.l;
	return ((x.l - 1) / sz) & 1 ? x.r < y.r : x.r > y.r;
}

void init(int n)
{
	sz = sqrt(n);
	tot = n / sz;
	for (int i = 1; i <= tot; i++)
	{
		L[i] = (i - 1) * sz + 1;
		R[i] = i * sz;
	}
	if (R[tot] < n)
	{
		++tot;
		L[tot] = R[tot - 1] + 1;
		R[tot] = n;
	}

	for (int i = 1; i <= tot; i++)
		for (int j = L[i]; j <= R[i]; j++)
			id[j] = i;
}

int x[N];
unordered_map <int, int> num;
// 增加节点更新答案
void Add(int v, int &Ans)
{
	num[v]++;
	Ans = max(Ans, v * num[v]);
}
// 删除节点只需要删除影响无需更改答案
void Del(int v) { num[v]--; }
// 同一块内直接暴力
int bf(int l, int r) 
{
	unordered_map <int, int> mp;
	for (int i = l; i <= r; i++) mp[x[i]]++;
	int res = 0;
	for (auto [x, w]: mp) res = max(res, x * w);
	return res;  
}

void solve()
{
	int n, m; cin >> n >> m;
	init(n);
	for (int i = 1; i <= n; i++) cin>>x[i];
	for (int i = 1; i <= m; i++)
	{
		int l, r; cin >> l >> r;
		q[i] = {l, r, i}; 
	}
	sort (q + 1, q + m + 1, cmp);

	int l = 1, r = 0, last_block = 0;
	int Ans = 0;
	for (int i = 1; i <= m; i++)
	{
		if (id[q[i].l] == id[q[i].r])
		{
			ans[q[i].id] = bf(q[i].l, q[i].r);
			continue;
		}

		if (id[q[i].l] != last_block)
		{
			while (r > R[id[q[i].l]]) Del(x[r--]);
			while (l < R[id[q[i].l]] + 1) Del(x[l++]);
			Ans = 0;
			last_block = id[q[i].l];
		}

		while (r < q[i].r) Add(x[++r], Ans); // right
		int lasl = l, tmp = Ans;
		while (lasl > q[i].l) Add(x[--lasl], tmp); // left
		ans[q[i].id] = tmp;

		while (lasl < l) Del(x[lasl++]); // rollback
	}

	for(int i = 1; i <= m; i++) cout << ans[i] << endl;
}

signed main()
{
	// ios::sync_with_stdio(0);
	// cin.tie(0), cout.tie(0);
	int T = 1; // cin >> T;
	while(T--) solve();
	return 0;
}
