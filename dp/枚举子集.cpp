#include <bits/stdc++.h>
using namespace std;
void solve()
{
    int n;
    // 降序遍历 m 的非空子集
    for (int m = 0; m < (1 << n); ++m)
    {
        // s 是 m 的一个非空子集
        for (int s = m; s; s = (s - 1) & m)
        {

        }
    }
}
