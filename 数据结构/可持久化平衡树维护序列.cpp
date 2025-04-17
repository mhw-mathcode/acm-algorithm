#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2e5 + 10;
int n, idx;
int dl, dr, temp;
struct node
{
	int l, r;
	int key, val;
	int si;
	bool tag;
	ll sum;
} t[N * 100];
int rt[N];
void push_up(int pos)
{
	t[pos].si = t[t[pos].l].si + t[t[pos].r].si + 1;
	t[pos].sum = t[t[pos].l].sum + t[t[pos].r].sum + t[pos].key;
}
int get_rand(int x)
{
	t[++idx].sum = x;
	t[idx].key = x;
	t[idx].si = 1;
	t[idx].val = rand();
	return idx;
}
void push_down(int &pos)
{
	if (!t[pos].tag) return;
	if (t[pos].l)
	{
		t[++idx] = t[t[pos].l];
		t[pos].l = idx;
		t[t[pos].l].tag ^= 1;
	}
	if (t[pos].r)
	{
		t[++idx] = t[t[pos].r];
		t[pos].r = idx;
		t[t[pos].r].tag ^= 1;
	}
	t[pos].tag = 0;
	swap(t[pos].l, t[pos].r);
}
void split(int pos, int k, int &l, int &r)
{
	if (!pos)
	{
		l = r = 0;
		return;
	}
	push_down(pos);
	int u = t[t[pos].l].si + 1;
	if (u <= k)
	{
		l = ++idx;
		t[l] = t[pos];
		split(t[pos].r, k - u, t[l].r, r);
		push_up(l);
	}
	else
	{
		r = ++idx;
		t[r] = t[pos];
		split(t[pos].l, k, l, t[r].l);
		push_up(r);
	}
}
int merge(int l, int r)
{
	if (!l || !r) return l | r;
	int pos = ++idx;
	if (t[l].val <= t[r].val)
	{
		t[pos] = t[l];
		push_down(pos);
		t[pos].r = merge(t[pos].r, r);
		push_up(pos);
		return pos;
	}
	else
	{
		t[pos] = t[r];
		push_down(pos);
		t[pos].l = merge(l, t[pos].l);
		push_up(pos);
		return pos;
	}
}

void insert(int &pos, int x, int y) // 第x数后面插入y
{
	split(pos, x, dl, dr);
	dl = merge(dl, get_rand(y));
	pos = merge(dl, dr);
}
void delet(int &pos, int x) // 删除第x个数
{
	split(pos, x - 1, dl, dr);
	split(dr, 1, temp, dr);
	pos = merge(dl, dr);
}
void tagerse(int &pos, int l, int r) // 翻转pos版本的l-r区间
{
	split(pos, l - 1, dl, dr);
	split(dr, r - l + 1, temp, dr);
	t[temp].tag ^= 1;
	dr = merge(temp, dr);
	pos = merge(dl, dr);
}
ll query(int &pos, int l, int r) // 求pos版本l-r区间和
{
	split(pos, l - 1, dl, dr);
	split(dr, r - l + 1, temp, dr);
	ll ans = t[temp].sum;
	dr = merge(temp, dr);
	pos = merge(dl, dr);
	return ans;
}
int main()
{
	cin >> n;
	int op, v, xx, yy;
	ll lan = 0;
	for (int t = 1; t <= n; t++)
	{
		scanf("%d %d", &v, &op);
		rt[t] = rt[v];
		if (op == 2)
		{
			scanf("%d", &xx);
			xx ^= lan; // 强制在线
			delet(rt[t], xx);
		}
		else
		{
			scanf("%d %d", &xx, &yy);
			xx ^= lan, yy ^= lan; // 强制在线
			if (op == 1) insert(rt[t], xx, yy);
			else if (op == 3) tagerse(rt[t], xx, yy);
			else
			{
				lan = query(rt[t], xx, yy);
				cout << lan << '\n';
			}
		}
	}
	return 0;
}