#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef uint64_t u64;
typedef __uint128_t u128;
const int N = 105; 
const int mod = 1e9 + 7;
// 计算模意义下的行列式，O(n^3)
struct fastmod 
{
    int m; 
    u64 b;
    fastmod() {}
    fastmod(int m): m(m), b(((u128)1 << 64) / m) {}
    int reduce(u64 a) 
    {
        int r = a - ((u128)a * b >> 64) * m;
        return r < m ? r : r - m;
    }
}z;
struct mat 
{
    int n, a[N][N];
    auto & operator [] (int x) {return a[x];}
    mat(int n = 0): n(n) {}
    int det() 
    {   
        mat a = (*this); int ans = 1;
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
            {
                a[i][j] = (a[i][j] % mod + mod) % mod;
                a[i][j] = z.reduce(a[i][j]);
            }
        for(int j = 1; j <= n; j++) 
        {
            for(int i = j + 1; i <= n; i++) 
            {
                while(a[i][j]) 
                {
                    if(a[i][j] <= a[j][j]) 
                    {
                        int v = a[j][j] / a[i][j];
                        for(int k = j; k <= n; k++) a[j][k] = z.reduce(a[j][k] + (u64)(mod - v) * a[i][k]);
                    }
                    for(int k = j; k <= n; k++) swap(a[j][k], a[i][k]); 
                    ans = (mod - ans);
                }
            }
            ans = z.reduce((u64)ans * a[j][j]);
        }
        return ans;
    }
};
void solve()
{
    int n;
    mat jz(n); z = mod;
    for(int i = 1; i <= n; i++) 
        for(int j = 1; j <= n; j++)
            cin >> jz.a[i][j];
}
