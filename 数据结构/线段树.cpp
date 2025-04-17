#include <bits/stdc++.h>
using namespace std;

#define ls k << 1
#define rs k << 1 | 1

const int N = 2e5 + 5;
int a[N];
struct node
{
    int sum, lazy;
} t[N << 2];
void bulid(int k, int l, int r)
{
    if (l == r)
    {
        t[k].sum = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    bulid(ls, l, mid);
    bulid(rs, mid + 1, r);
    t[k].sum = t[ls].sum + t[rs].sum;
}
void pushdown(int k, int l, int r)
{
    if (t[k].lazy)
    {
        int mid = (l + r) >> 1;
        t[ls].sum += (mid - l + 1) * t[k].lazy;
        t[rs].sum += (r - mid) * t[k].lazy;
        t[ls].lazy += t[k].lazy;
        t[rs].lazy += t[k].lazy;
        t[k].lazy = 0;
    }
}
void modify(int k, int l, int r, int p, int q, int val)
{
    // 非永久化懒标记
    if (p == l && q == r)
    {
        t[k].sum += 1ll * (r - l + 1) * val;
        t[k].lazy += val;
        return;
    }
    pushdown(k, l, r);

    // 永久化懒标记
    t[k].sum += val * (q - p + 1);
    if (p == l && q == r)
    {
        t[k].lazy += val;
        return;
    }

    int mid = (l + r) >> 1;
    if (q <= mid) modify(ls, l, mid, p, q, val);
    else if (p > mid) modify(rs, mid + 1, r, p, q, val);
    else modify(ls, l, mid, p, mid, val), modify(rs, mid + 1, r, mid + 1, q, val);
    t[k].sum = t[ls].sum + t[rs].sum;
}

// 非永久化懒标记
int query(int k, int l, int r, int p, int q)
{
    if(p == l && q == r) return t[k].sum;
    pushdown(k, l, r);
    int mid = (l + r) >> 1;
    if(q <= mid) return query(ls, l, mid, p, q);
    else if(p > mid) return query(rs, mid + 1, r, p, q);
    else return query(ls, l, mid, p, mid) + query(rs, mid + 1, r, mid + 1, q);
}

// 永久化懒标记
int query(int k, int l, int r, int p, int q, int lz)
{
    if (p == l && q == r) return t[k].sum + lz * (r - l + 1);
    int mid = (l + r) >> 1;
    if (q <= mid) return query(ls, l, mid, p, q, lz + t[k].lazy);
    else if (p > mid) return query(rs, mid + 1, r, p, q, lz + t[k].lazy);
    else return query(ls, l, mid, p, mid, lz + t[k].lazy) + query(rs, mid + 1, r, mid + 1, q, lz + t[k].lazy);
}

// 区间最值查询，相应上面也要改动
int ask(int k, int l, int r, int p, int q)
{
    if (p == l && q == r) return t[k].sum;
    pushdown(k, l, r);
    int mid = (l + r) >> 1;
    if (q <= mid) return ask(ls, l, mid, p, q);
    else if (p > mid) return ask(rs, mid + 1, r, p, q);
    else return max(ask(ls, l, mid, p, mid), ask(rs, mid + 1, r, mid + 1, q));
}
