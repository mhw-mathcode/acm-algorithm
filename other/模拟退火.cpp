#include <bits/stdc++.h>
#define inf 2147483647
#define re register
using namespace std;
const double endtime = 0.799;

int n, x, ans = inf, a[1005], val[1005], t[1005];
int cal()
{
    int res = 0, now = x;
    for (int i = 1; i <= n; i++)
    {
        if (now > 0) now -= val[a[i]];
        else if (now < 0) now += val[a[i]];
        else break;
        res += val[a[i]];
    }
    return res;
}
int random(int a, int b) // 得到a-b之间的一个随机数
{
    return rand() % (b - a + 1) + a;
}
void SA()
{
    // 起始温度、终止温度、温度变化量
    double beginT = 5000, endT = 1e-10, changeT = 0.9265;
    for (double T = beginT; T > endT; T *= changeT)
    {

        // 数据量极小时慎用，因为重复概率比较大容易t
        int x, y;
        do
        {
            x = random(1, n);
            y = random(1, n);
        } while (x == y);

        // int x = random(1, n), y = random(1, n);

        swap(a[x], a[y]);
        int sum = cal();

        if (sum < ans)
        {
            ans = sum;
            for (int i = 1; i <= n; i++) t[i] = a[i];
        }
        else if (exp((ans - sum) / T) < (double(rand()) / RAND_MAX))
            swap(a[x], a[y]);

        // 求解最大值
        // if (sum > ans) ans = sum;
        // else if (exp((ans - sum) / T) > (double(rand()) / RAND_MAX))
        //     swap(a[x], a[y]);
    }
}
void solve()
{
    cin >> n >> x;
    for (int i = 1; i <= n; i++)
    {
        cin >> val[i];
        a[i] = n - i + 1;
    }

    // int ctrl = 10000;
    // while (ctrl--) SA();

    // 卡时间（有些无法使用原因未知）
    while ((clock() / (1.0 * CLOCKS_PER_SEC)) <= endtime) SA();
    cout << ans << endl;
    for (int i = 1; i <= n; i++) cout << t[i] << ' ';
    ans = inf;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    srand(time(NULL)); // 随机种子
    srand(rand() + 19491001);
    srand(rand() + 20040405);
    srand(rand());

    int T = 1; // cin >> T;
    while (T--) solve();
    return 0;
}