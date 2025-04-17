#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
// prime数组存储素数，tot记录素数的个数
// mbus数组记录每个数对应的莫比乌斯函数值，vis[i]数组表示i是否为素数
int prime[N], tot, mbus[N], vis[N];
void mobius()
{
    mbus[1] = 1;
    for (int i = 2; i < N; i++)
    {
        if (!vis[i]) // 如果i是素数vis[i]=0
        {
            prime[tot++] = i; // 把素数存入prime数组
            mbus[i] = -1;     // 素数莫比乌斯函数值为-1
        }
        for (int j = 0; j < tot && i * prime[j] < N; j++)
        {
            vis[i * prime[j]] = 1; // 把合数标记出来
            // 如果不是整除，多乘一个素数就改变符号
            if (i % prime[j]) mbus[i * prime[j]] = -mbus[i];
            // 如果整除，说明含有平方因子
            else
            {
                mbus[i * prime[j]] = 0;
                break;
            }
        }
    }
}