#include<bits/stdc++.h>
#define ll long long

using namespace std;

// 寻找一段区间小于某数的数个数
const int N = 1e5 + 7;
struct ZX_TREE {
    ll lsh[N], tot, n, node[N];
    struct seg {
        int v, ls, rs;
    } t[N << 5];
    int rt[N << 2],cnt;
    void pushup(int o) {
        t[o].v = t[t[o].ls].v + t[t[o].rs].v;
    }
    void change(int lsto, int &o, int l, int r, int q, int v) {
        if(!o) o = ++cnt;
        if(l == r) {
            t[o].v += v;
            return ;
        }
        int mid = (l + r) >> 1;
        if(q <= mid) { //如果加入的位置在左边
            t[o].rs = t[lsto].rs;//右子树直接copy
            t[o].ls = ++ cnt;
            t[t[o].ls] = t[t[lsto].ls];//左子树copy结构体，然后更改
            change(t[lsto].ls, t[o].ls, l, mid, q, v);
        } else {
            t[o].ls = t[lsto].ls;
            t[o].rs = ++cnt;
            t[t[o].rs] = t[t[lsto].rs];
            change(t[lsto].rs, t[o].rs, mid + 1, r, q, v);
        }
        pushup(o);
    }
    void init(int *a, int _n) {
        n = _n;
        cnt = 0;
        for(int i = 1; i <= n; ++i)
            lsh[i] = node[i] = a[i];
        sort(lsh + 1, lsh + n + 1);
        tot = unique(lsh + 1, lsh + 1 + n) - lsh - 1;
        for(int i = 1; i <= n; i++) {
            node[i] = lower_bound(lsh + 1, lsh + tot + 1, node[i]) - lsh;
            change(rt[i-1], rt[i], 1, tot, node[i], 1);
        }
    }
    int ask_kth(int o1, int o2, int l, int r, int q) {
        if(l == r) {
            return l;
        }
        int mid = (l + r) >> 1, tmp = t[t[o2].ls].v - t[t[o1].ls].v;
        if(tmp >= q) return ask_kth(t[o1].ls, t[o2].ls, l, mid, q);
        else return ask_kth(t[o1].rs, t[o2].rs, mid + 1, r, q - tmp);
    }
    int ask_rnk(int o1, int o2, int l, int r, int ql, int qr) { //区间求和 //待定
        if(ql > qr) return 0;
        if(ql <= l && r <= qr) {
            return t[o2].v - t[o1].v;
        }
        int mid = (l + r) >> 1, ans = 0;
        if(ql <= mid) ans += ask_rnk(t[o1].ls, t[o2].ls, l, mid, ql, qr);
        if(qr > mid) ans += ask_rnk(t[o1].rs, t[o2].rs, mid + 1, r, ql, qr);
        return ans;
    }

    ll get_kth(int x, int y, ll q) { // x...y中第q小的数
        if(q > y - x + 1) return -1;
        return lsh[ask_kth(rt[x - 1], rt[y], 1, tot, q)];
    }
    ll get_tot_min(int x, int y, ll q) { // 找x...y中严格小于q的个数
        q = lower_bound(lsh + 1, lsh + tot + 1, q) - lsh;
        return q == 1 ? 0 : ask_rnk(rt[x - 1], rt[y], 1, tot, 1, q - 1);
    }

    ll get_tot_max(int x, int y, ll q) { // 找x...y中严格大于q的个数
        return (y - x + 1) - get_tot_min(x, y, q + 1);
    }

    ll get_pre(int x, int y, ll q) { // 找到x...y中q的前驱
        ll pre_rnk = get_tot_min(x, y, q); // 多少个严格小的
        return get_kth(x, y, pre_rnk);
    }
    ll get_nxt(int x, int y, ll q) { // 找到x...y中q的后继
        ll nxt_rnk = get_tot_min(x, y, q + 1) + 1; // 多少个严格小于等于的 + 1
        return get_kth(x, y, nxt_rnk);
    }
    void cls(){
        for(int i = 0; i <= cnt; ++i)
            t[i].v = t[i].ls = t[i].rs = rt[i] = 0;
    }
} zxt;

// 寻找一段区间内数的种类数
// a为指定序列
int n, m, a[N];
struct interval_weights
{
	int root[N], tot, last[N];
	struct Node
	{
		int l, r;
		int cnt;
	} tr[N * 40];
	int build(int l, int r)
	{
		int p = ++tot;
		if (l == r) return p;
		int mid = (l + r) >> 1;
		tr[p].l = build(l, mid), tr[p].r = build(mid + 1, r);
		return p;
	}
	int insert(int p, int idx, int l, int r, int x)
	{
		int q = ++tot;
		tr[q] = tr[p], tr[q].cnt += x;
		if (l < r)
		{
			int mid = (l + r) >> 1;
			if (idx <= mid) tr[q].l = insert(tr[p].l, idx, l, mid, x);
			else tr[q].r = insert(tr[p].r, idx, mid + 1, r, x);
		}
		return q;
	}
	int query(int idx, int q, int l, int r)
	{
		if (l == r) return tr[q].cnt;
		int mid = (l + r) >> 1;
		if (idx <= mid) return query(idx, tr[q].l, l, mid) + tr[tr[q].r].cnt;
		else return query(idx, tr[q].r, mid + 1, r);
	}
	int ask(int l, int r) // 直接调用该函数即可
	{
		return query(l, s.root[r], 1, n);
	}
	void init(int n)
	{
		root[0] = build(1, n);
		for (int i = 1; i <= n; i++)
		{
			if (!last[a[i]]) 
				root[i] = insert(root[i - 1], i, 1, n, 1);
			else
			{
				int t = insert(root[i - 1], last[a[i]], 1, n, -1);
				root[i] = insert(t, i, 1, n, 1);
			}
			last[a[i]] = i;
		}
	}
	void clear(int n)
	{
		for (int i = 1; i <= n; i++) 
		{
			root[i] = 0;
			last[a[i]] = 0;
		}
		for (int i = 0; i <= tot; i++) tr[i] = {0, 0, 0};
		tot = 0;
	}
}s;


int main() {
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int n, m; cin >> n >> m;
        for(int i = 1; i <= n; ++i) cin >> a[i];
        zxt.init(a, n);

        zxt.cls();
    }
    return 0;
}