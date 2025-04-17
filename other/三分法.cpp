#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int cal(int x)
{

}
void solve()
{
    int l = 1, r = 100;
    int lans, rans;
    while (l < r)
    {
        int lmid = l + (r - l) / 3;
        int rmid = r - (r - l) / 3;
        lans = cal(lmid), rans = cal(rmid);

        // 求凹函数的极小值
        if (lans <= rans) r = rmid - 1;
        else l = lmid + 1;

        // 求凸函数的极大值
        if (lans >= rans) l = lmid + 1;
        else r = rmid - 1;
    }

    // 求凹函数的极小值
    cout << min(lans, rans) << endl;
    // 求凸函数的极大值
    cout << max(lans, rans) << endl;

    const double EPS = 1e-9;
    while (r - l > EPS)
    {
        double lmid = l + (r - l) / 3;
        double rmid = r - (r - l) / 3;
        lans = cal(lmid), rans = cal(rmid);

        // 求凹函数的极小值
        if (lans <= rans) r = rmid;
        else l = lmid;

        // 求凸函数的极大值
        if (lans >= rans) l = lmid;
        else r = rmid;
    }
    // 输出 l 或 r 都可
    cout << l << endl;
}
