#include <bits/stdc++.h>

#define int long long
#define lc c[x][0]
#define rc c[x][1]
#define inf 0x3f3f3f3f
using namespace std;
const int N = 1e6 + 9;

int vw[N], id[N];

int f[N], c[N][2], s[N], st[N];
bool r[N];
bool nroot(int x) { // 判断节点是否为一个Splay的根（与普通Splay的区别1）
	return c[f[x]][0] == x || c[f[x]][1] == x;
} // 原理很简单，如果连的是轻边，他的父亲的儿子里没有它

// 需要更改的地方
void pushup(int x) { // 上传信息
	s[x] = max(max(s[lc], s[rc]), vw[x]);
	if (s[x] == vw[x]) id[x] = x;
	if (s[x] == s[lc]) id[x] = id[lc];
	if (s[x] == s[rc]) id[x] = id[rc];
}

void pushr(int x) {
	int t = lc;
	lc = rc;
	rc = t;
	r[x] ^= 1;
} // 翻转操作
void pushdown(int x) { // 判断并释放懒标记
	if (r[x]) {
		if (lc) pushr(lc);
		if (rc) pushr(rc);
		r[x] = 0;
	}
}
void rotate(int x) { // 一次旋转
	int y = f[x], z = f[y], k = c[y][1] == x, w = c[x][!k];
	if (nroot(y)) c[z][c[z][1] == y] = x; // 额外注意if(nroot(y))语句，此处不判断会引起致命错误（与普通Splay的区别2）
	c[x][!k] = y;
	c[y][k] = w;
	if (w) f[w] = y;
	f[y] = x;
	f[x] = z;
	pushup(y);
}
void splay(int x) { // 只传了一个参数，因为所有操作的目标都是该Splay的根（与普通Splay的区别3）
	int y = x, z = 0;
	st[++z] = y; // st为栈，暂存当前点到根的整条路径，pushdown时一定要从上往下放标记（与普通Splay的区别4）
	while (nroot(y)) st[++z] = y = f[y];
	while (z) pushdown(st[z--]);
	while (nroot(x)) {
		y = f[x];
		z = f[y];
		if (nroot(y)) rotate((c[y][0] == x) ^ (c[z][0] == y) ? x : y);
		rotate(x);
	}
	pushup(x);
}

void access(int x) { // 访问
	for (int y = 0; x; x = f[y = x])
		splay(x), rc = y, pushup(x);
}
void makeroot(int x) { // 换根
	access(x);
	splay(x);
	pushr(x);
}
int findroot(int x) { // 找根（在真实的树中的）
	access(x);
	splay(x);
	while (lc) pushdown(x), x = lc;
	splay(x);
	return x;
}
void split(int x, int y) { // 提取路径
	makeroot(x);
	access(y);
	splay(y);
}
void link(int x, int y) { // 连边
	makeroot(x);
	if (findroot(y) != x) f[x] = y;
}
void cut(int x, int y) { // 断边
	makeroot(x);
	if (findroot(y) == x && f[y] == x && !c[y][0]) {
		f[y] = c[x][1] = 0;
		pushup(x);
	}
}

struct node
{
	int u, v, a, b;
} e[N];
int cmp(node a, node b) { return a.a < b.a; }

#define pii pair<int, int>
void solve()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		int u, v, a, b;
		cin >> u >> v >> a >> b;
		e[i] = {u, v, a, b};
	}
	sort(e + 1, e + m + 1, cmp);

	// 有权值的点（实际为边）连接的两点
	map<int, pii> mp;

	int num = 1, ans = inf;
	for (int i = 1; i <= m; i++)
	{
		auto [u, v, a, b] = e[i];

		// 联通则在环上找最大权值边删去
		split(u, v);
		if (findroot(u) == findroot(v) && b < s[v])
		{
			int idd = id[v];
			auto [x, y] = mp[idd];
			cut(x, idd), cut(idd, y);
		}

		// 边权转化为点权
		link(u, num + n);
		link(num + n, v);
		vw[num + n] = b;
		mp[num + n] = {u, v};
		num++;

		if (findroot(1) == findroot(n))
		{
			split(1, n);
			ans = min(ans, a + vw[id[n]]);
		}
	}
	if (ans == inf) ans = -1;
	cout << ans << '\n';
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int t = 1; // cin>>t;
	while (t--) solve();
	return 0;
}
