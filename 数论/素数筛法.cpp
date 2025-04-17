#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 6;
int n;           // 所求素数范围
bool isprime[N]; // 把合数标记为1
vector<int> isp; // 存储所有素数
int num = 0;     // 记录素数的个数

// 线性筛
void xian()
{
    for (int i = 2; i <= n; i++)
    {
        if (isprime[i] == 0)
        {
            isp.push_back(i);
            num++;
        }
        for (int j = 0; j < num && i * isp[j] <= n; j++)
        {
            isprime[i * isp[j]] = 1;
            if (i % isp[j] == 0) break;
        }
    }
}
