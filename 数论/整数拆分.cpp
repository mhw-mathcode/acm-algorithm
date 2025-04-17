#include <bits/stdc++.h>
#define times 10
#define N 6081
#define ll long long
#define int long long
using namespace std;

#define MYDATA long long
const int MOD = 1000000007;
struct Integer_splitting
{
#define AMS 100005 // 整数拆分范围
    int pp[AMS], asist[2 * AMS];
    void myinit()
    {
        for (int i = 0; i < AMS; i++)
        {
            asist[2 * i] = i * (i * 3 - 1) / 2;
            asist[2 * i + 1] = i * (i * 3 + 1) / 2;
        }
    }
    void mymethod()
    {
        pp[0] = 1, pp[1] = 1, pp[2] = 2;
        for (int i = 3; i < AMS; i++)
        {
            int k = 0, flags;
            pp[i] = 0;
            for (int j = 2; asist[j] <= i; j++)
            {
                flags = k & 2;
                if (!flags) pp[i] = (pp[i] + pp[i - asist[j]] + MOD) % MOD;
                else pp[i] = (pp[i] - pp[i - asist[j]] + MOD) % MOD;
                k++;
                k %= 8;
            }
        }
    }
};
signed main()
{
    Integer_splitting p;
    // 使用之前先计算
    p.myinit();
    p.mymethod();

    int n; cin >> n;
    while (n--)
    {
        int t;
        cin >> t;
        cout << p.pp[t] << endl;
    }
    return 0;
}