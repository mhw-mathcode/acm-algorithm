#include <bits/stdc++.h>
using namespace std;
const int M = 5e5 + 5;
struct node
{
    int s, ls, rs, ms;
    int lis, ris, mis;
} tree[M << 2];
int a[M];
void pushup(int bh)
{
    int lson = bh << 1;
    int rson = bh << 1 | 1;
    tree[bh].s = tree[lson].s + tree[rson].s;

    tree[bh].ls = max(tree[lson].ls, tree[lson].s + tree[rson].ls);
    tree[bh].rs = max(tree[rson].rs, tree[rson].s + tree[lson].rs);
    tree[bh].ms = max(max(tree[lson].ms, tree[rson].ms), tree[lson].rs + tree[rson].ls);

    tree[bh].lis = min(tree[lson].lis, tree[lson].s + tree[rson].lis);
    tree[bh].ris = min(tree[rson].ris, tree[rson].s + tree[lson].ris);
    tree[bh].mis = min(min(tree[lson].mis, tree[rson].mis), tree[lson].ris + tree[rson].lis);
}

void build(int bh, int L, int R)
{
    if (L == R)
    {
        tree[bh].s = a[L];
        tree[bh].ls = tree[bh].rs = tree[bh].ms = tree[bh].s;
        tree[bh].lis = tree[bh].ris = tree[bh].mis = tree[bh].s;
        return;
    }
    int mid = (L + R) >> 1;
    build(bh << 1, L, mid);
    build(bh << 1 | 1, mid + 1, R);
    pushup(bh);
}

node askans(int bh, int L, int R, int x, int y)
{
    if (x <= L && y >= R)
        return tree[bh];
    int mid = (L + R) >> 1;
    node f1, f2, T;
    T.s = 0;
    if (y <= mid) T = askans(bh << 1, L, mid, x, y);
    if (x > mid) T = askans(bh << 1 | 1, mid + 1, R, x, y);
    if (x <= mid && y > mid)
    {
        f1 = askans(bh << 1, L, mid, x, y);
        f2 = askans(bh << 1 | 1, mid + 1, R, x, y);

        T.s = f1.s + f2.s;
        T.ls = max(f1.ls, f1.s + f2.ls);
        T.rs = max(f2.rs, f2.s + f1.rs);
        T.ms = max(max(f1.ms, f2.ms), f1.rs + f2.ls);

        T.lis = min(f1.lis, f1.s + f2.lis);
        T.ris = min(f2.ris, f2.s + f1.ris);
        T.mis = min(min(f1.mis, f2.mis), f1.ris + f2.lis);
    }
    return T;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, m; cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, n, 1);
    cin >> m;
    while (m--)
    {
        int l, r;
        cin >> l >> r;
        node ans = askans(l, r, 1, n, 1);
        cout << max(abs(ans.mis), ans.ms) << endl;
    }
    return 0;
}
