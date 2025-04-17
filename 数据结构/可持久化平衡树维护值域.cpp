#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define inf 0x3f3f3f3f
#define endl '\n'
const int N = 5e5 + 5;
const int mod = 998244353;
struct node
{
    int l, r;
    int key, val;
    int siz;
} t[N * 60];
int idx, dl, dr, temp;

// 不同版本对应的根节点
int rt[N * 60];
int get_rand(int x) // 新建一个节点
{
    t[++idx].key = x;
    t[idx].val = rand();
    t[idx].siz = 1;
    return idx;
}
void push_up(int pos)
{
    // 左右儿子大小加上自己的大小
    t[pos].siz = t[t[pos].l].siz + t[t[pos].r].siz + 1;
}

// 分离一颗fhq-treap，左树每个节点key值小于等于x，右树每个节点key值大于x
void split(int pos, int x, int &l, int &r)
{
    if (!pos)
    {
        l = r = 0;
        return;
    }
    if (t[pos].key <= x)
    {
        l = ++idx;
        t[l] = t[pos];
        split(t[l].r, x, t[l].r, r);
        push_up(l);
    }
    else
    {
        r = ++idx;
        t[r] = t[pos];
        split(t[pos].l, x, l, t[r].l);
        push_up(r);
    }
}

// 合并两颗fhq-treap
int merge(int l, int r) // 传入左右子树的根节点
{
    if (!l || !r) return l | r; // 如果有空树，直接返回非空树
    int pos = ++idx;
    if (t[l].val <= t[r].val)
    {
        t[pos] = t[l];
        t[pos].r = merge(t[pos].r, r);
    }
    else
    {
        t[pos] = t[r];
        t[pos].l = merge(l, t[pos].l);
    }
    push_up(pos);
    return pos;
}

void insert(int &pos, int x) // 插入一个key为x的点
{
    split(pos, x - 1, dl, dr);
    pos = merge(merge(dl, get_rand(x)), dr);
}
void del(int &pos, int x) // 删除一个key为x的点
{
    split(pos, x - 1, dl, dr);
    split(dr, x, temp, dr);
    temp = merge(t[temp].l, t[temp].r);
    pos = merge(dl, merge(temp, dr));
}
int get_rk(int &pos, int x) // 得到key为x的rank
{
    split(pos, x - 1, dl, dr);
    int rnk = t[dl].siz + 1;
    pos = merge(dl, dr);
    return rnk;
}
int get_num(int pos, int x) // 得到排名为x的key值
{
    int u = t[t[pos].l].siz + 1;
    if (u == x) return t[pos].key;
    if (u > x) return get_num(t[pos].l, x);
    else return get_num(t[pos].r, x - u);
}

int pre(int &pos, int x) // 前驱
{
    split(pos, x - 1, dl, dr);
    int res = get_num(dl, t[dl].siz);
    pos = merge(dl, dr);
    return res;
}
int nex(int &pos, int x) // 后继
{
    split(pos, x, dl, dr);
    int res = get_num(dr, 1);
    pos = merge(dl, dr);
    return res;
}

void solve()
{
    int n;
    cin >> n;
    int cnt = 0, t, op, x;
    while (n--)
    {
        cin >> t >> op >> x;
        cnt++;
        rt[cnt] = rt[t];
        if (op == 1) insert(rt[cnt], x);
        else if (op == 2) del(rt[cnt], x);
        else if (op == 3) cout << get_rk(rt[cnt], x) << endl;
        else if (op == 4) cout << get_num(rt[cnt], x) << endl;
        else if (op == 5) cout << pre(rt[cnt], x) << endl;
        else cout << nex(rt[cnt], x) << endl;
    }
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
