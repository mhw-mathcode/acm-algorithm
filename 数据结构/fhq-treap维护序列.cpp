#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
struct node
{
    int l, r;
    int key, val;
    int siz;
    int tag;
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
void push_down(int pos)
{
    if (t[pos].tag) // 下传懒标记实现左右子树翻转
    {
        t[t[pos].l].tag ^= 1;
        t[t[pos].r].tag ^= 1;
        swap(t[pos].l, t[pos].r);
        t[pos].tag = 0;
    }
}
// 分离一颗fhq-treap，左树每个节点key值小于等于x，右树每个节点key值大于x
void split(int pos, int k, int &l, int &r)
{
    if (!pos)
    {
        l = r = 0;
        return;
    }
    push_down(pos);
    int u = t[t[pos].l].siz + 1;
    if (u <= k)
    {
        l = pos;
        split(t[pos].r, k - u, t[pos].r, r);
        push_up(l);
    }
    else
    {
        r = pos;
        split(t[pos].l, k, l, t[pos].l);
        push_up(r);
    }
}
// 合并两颗fhq-treap
int merge(int l, int r) // 传入左右子树的根节点
{
    if (!l || !r) return l | r; // 如果有空树，直接返回非空树
    push_down(l);
    push_down(r);
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
void reverse(int l, int r) // 翻转区间l-r
{
    int p1 = 0, p2 = 0, p3 = 0, p4 = 0;
    split(rt, l - 1, p1, p2);
    split(p2, (r - l + 1), p3, p4);
    t[p3].tag ^= 1;
    p2 = merge(p3, p4);
    rt = merge(p1, p2);
}
void print_res(int pos) // 中序输出
{
    push_down(pos);
    if (t[pos].l) print_res(t[pos].l);
    cout << t[pos].key << " ";
    if (t[pos].r) print_res(t[pos].r);
}

void solve()
{
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) insert(i);
    while (k--)
    {
        int l, r;
        cin >> l >> r;
        reverse(l, r);
    }
    print_res(rt);
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1; // cin>>T;
    while (T--) solve();
    return 0;
}