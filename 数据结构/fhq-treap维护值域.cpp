#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
struct node
{
    int l, r;
    int key, val;
    int siz;
} t[N << 1];
int idx, dl, dr, rt, temp;
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
        l = pos;
        split(t[l].r, x, t[l].r, r);
    }
    else
    {
        r = pos;
        split(t[r].l, x, l, t[r].l);
    }
    push_up(pos);
}

// 合并两颗fhq-treap
int merge(int l, int r) // 传入左右子树的根节点
{
    if (!l || !r) return l | r; // 如果有空树，直接返回非空树
    if (t[l].val <= t[r].val)
    {
        t[l].r = merge(t[l].r, r);
        push_up(l);
        return l;
    }
    else
    {
        t[r].l = merge(l, t[r].l);
        push_up(r);
        return r;
    }
}

void insert(int x) // 插入一个key为x的点
{
    split(rt, x - 1, dl, dr);
    rt = merge(merge(dl, get_rand(x)), dr);
}
void del(int x) // 删除一个key为x的点
{
    split(rt, x - 1, dl, dr);
    split(dr, x, temp, dr);
    temp = merge(t[temp].l, t[temp].r);
    rt = merge(dl, merge(temp, dr));
}
int get_rk(int x) // 得到key为x的rank
{
    split(rt, x - 1, dl, dr);
    int rnk = t[dl].siz + 1;
    rt = merge(dl, dr);
    return rnk;
}
int get_num(int pos, int x) // 得到排名为x的key值
{
    int u = t[t[pos].l].siz + 1;
    // cout<<u<<endl;
    if (u == x) return t[pos].key;
    if (u > x) return get_num(t[pos].l, x);
    else return get_num(t[pos].r, x - u);
}
int pre(int x) // 前驱
{
    split(rt, x - 1, dl, dr);
    int res = get_num(dl, t[dl].siz);
    merge(dl, dr);
    return res;
}
int nex(int x) // 后继
{
    split(rt, x, dl, dr);
    int res = get_num(dr, 1);
    merge(dl, dr);
    return res;
}

void solve()
{
    int n;
    cin >> n;
    while (n--)
    {
        int op, x;
        cin >> op >> x;
        if (op == 1) insert(x);
        else if (op == 2) del(x);
        else if (op == 3) cout << get_rk(x) << endl;
        else if (op == 4) cout << get_num(rt, x) << endl;
        else if (op == 5) cout << pre(x) << endl;
        else cout << nex(x) << endl;
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