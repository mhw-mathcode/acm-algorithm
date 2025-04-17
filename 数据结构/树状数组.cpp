#include <bits/stdc++.h>
using namespace std;

struct BIT {
    vector<int> v;
    int len;
    int lowbit(int x) { return x & (-x); }
    BIT(int n) {
        len = n;
        v.resize(n + 10);
    }
    void update(int i, int x) {
        i++;
        for (int pos = i; pos <= len; pos += lowbit(pos))
            v[pos] += x;
    }
    int ask(int i) {
        i++;
        int res = 0;
        for (int pos = i; pos; pos -= lowbit(pos))
            res += v[pos];
        return res;
    }
};

const int N = 2e5 + 5;
int n, t[N];
int lowbit(int x) { return x & (-x); }
void update(int pos, int k)
{
    for (int i = pos; i <= n; i += lowbit(i))
        t[i] += k;
}
int ask(int pos)
{
    int ans = 0;
    for (int i = pos; i; i -= lowbit(i))
        ans += t[i];
    return ans;
}

// 树状数组求逆序对
struct node
{
    int val, ind;
    bool operator<(node &W) const
    {
        if (val == W.val) return ind < W.ind;
        else return val < W.val;
    }
} stu[N];
int ra[N];
int reord()
{
    int ans = 0;
    sort(stu + 1, stu + n + 1);
    for (int i = 1; i <= n; i++) ra[stu[i].ind] = i;
    for (int i = 1; i <= n; i++)
    {
        int pos = ra[i];
        ans += ask(n) - ask(pos);
        update(pos, 1);
    }
    return ans;
}

// 区间最值求解
int n, tmax[N], tmin[N], a[N], m;
int lowbit(int x) { return x & (-x); }
void update(int pos, int k)
{
    for (int i = pos; i <= n; i += lowbit(i))
    {
        tmax[i] = max(tmax[i], k);
        tmin[i] = min(tmin[i], k);
    }
}
int ask(int l, int r)
{
    int maxx = 0, minn = 1e6;
    while (1)
    {
        maxx = max(maxx, a[r]), minn = min(minn, a[r]);
        if (l == r) break;
        for (r -= 1; r - l >= lowbit(r); r -= lowbit(r))
            maxx = max(maxx, tmax[r]), minn = min(minn, tmin[r]);
    }
    return maxx - minn;
}

int main()
{
    int l, r, k;
    update(l, k);
    update(r + 1, k); // 区间修改
    // 注意多次使用需要对t数组清0
    for (int i = 1; i <= n; i++)
    {
        cin >> stu[i].val; // 要求逆序对的数组
        stu[i].ind = i;
    }
}