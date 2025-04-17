#include <bits/stdc++.h>
using namespace std;
// 求解一个数的欧拉函数(比它小且与其互质的数的个数)
void euler()
{
    int n;
    map<int, int> pri;
    for (int i = 1; i * i <= n; i++)
    {
        int k = 0;
        while (n % i == 0)
        {
            k++;
            n /= i;
        }
        pri[i] = k;
    }
}
// 求解多个数的欧拉函数
// 把合数标记为1
const int maxn = 1e6 + 6;
bool isprime[maxn];
// 记录前i个素数，素数个数，每个数的欧拉函数值
int n, pri[maxn], num, phi[maxn];
int main()
{
    cin >> n;
    phi[1] = 1;
    // 求前n个数的欧拉函数
    for (int i = 2; i <= n; i++)
    {
        // 应用性质，素数的欧拉函数等于该素数减一
        if (isprime[i] == 0)
        {
            phi[i] = i - 1;
            pri[++num] = i;
        }
        for (int j = 1; j <= num && i * pri[j] <= n; j++)
        {
            isprime[i * pri[j]] = 1;
            // 应用性质，当n|m时，m*n的欧拉函数=n*（m的欧拉函数）
            if (i % pri[j] == 0)
            {
                phi[i * pri[j]] = pri[j] * phi[i];
                break;
            }
            // 应用性质，欧拉函数是积性函数
            else phi[i * pri[j]] = phi[i] * phi[pri[j]];
        }
    }
}