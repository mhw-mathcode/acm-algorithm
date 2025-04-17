#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int block; // 块的大小，记得计算
struct BLOCK
{
    int sum[N], a[N];
    void add(const int &x, const int &u) // 在x的位置加上u
    {
        sum[x / block] += u;
        a[x] += u;
    }
    int ask(const int &l, const int &r) // 询问[l,r]的和
    {
        int ans = 0;
        if (r - l <= block)
        {
            for (int i = l; i <= r; i++) ans += a[i];
            return ans;
        }
        int bl = (l / block + 1) * block;
        int br = r / block * block;
        for (int i = l; i < bl; i++) ans += a[i];
        for (int i = br; i <= r; i++) ans += a[i];
        int blockl = l / block + 1;
        int blockr = r / block - 1;
        for (int i = blockl; i <= blockr; i++) ans += sum[i];
        return ans;
    }
    void clear()
    {
        memset(a, 0, sizeof(a));
        memset(sum, 0, sizeof(sum));
    }
} BL;
signed main()
{
    int n;
    block = sqrt(n);
}