#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
int tr[N * 4];
inline void pushup(int x)
{
    tr[x] = tr[x * 2] + tr[x * 2 + 1];
}
void insert(int x, int l, int r, int k, int p)
{
    // 插入一个数k
    if (l == r)
    {
        tr[x] += p;
        return;
    }
    int mid = (l + r) / 2;
    if (k <= mid) insert(x * 2, l, mid, k, p);
    else insert(x * 2 + 1, mid + 1, r, k, p);
    pushup(x);
}
void del(int x, int l, int r, int k)
{
    // 删除一个数k
    if (l == r)
    {
        tr[x]--;
        return;
    }
    int mid = (l + r) / 2;
    if (k <= mid) del(x * 2, l, mid, k);
    else del(x * 2 + 1, mid + 1, r, k);
    pushup(x);
}
int query(int x, int l, int r, int ql, int qr)
{
    // 查询值在ql，qr之间一共有多少个数
    if (l >= ql && r <= qr) return tr[x];
    int mid = (l + r) / 2, sum = 0;
    if (ql <= mid) sum = query(x * 2, l, mid, ql, qr);
    if (qr > mid) sum += query(x * 2 + 1, mid + 1, r, ql, qr);
    return sum;
}
// 查询整个数组第k大
int kth(int x, int l, int r, int k)
{
    if (l == r) return l; // 查到了，返回即可
    int mid = (l + r) / 2;
    if (k <= tr[x * 2]) return kth(x * 2, l, mid, k);
    return kth(x * 2 + 1, mid + 1, r, k - tr[x * 2]);
}
// 查询x的排名
int rnk(int x, int l, int r, int k)
{
    if (l == r) return 1;
    int mid = (l + r) / 2;
    if (k <= mid) return rnk(x * 2, l, mid, k);
    return rnk(x * 2 + 1, mid + 1, r, k) + tr[x * 2];
}

int main()
{
    int n, k;
    cin >> n >> k;
    while (k--)
    {
        char op;
        cin >> op;
        int m, p;
        if (op == 'A')
        {
            cin >> m;
            cout << query(1, 1, n, 1, m) << endl;
        }
        if (op == 'B')
        {
            cin >> m >> p;
            insert(1, 1, n, m, p);
        }
        if (op == 'C')
        {
            cin >> m >> p;
            insert(1, 1, n, m, -p);
        }
    }
}