#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 2;

const double eps = 1e-6;
// 增广矩阵
int n;
double a[N][N];
int guass()
{
    int c, r = 0;
    for (c = 1, r = 1; c <= n; c++)
    {
        int t = r;
        for (int i = r + 1; i <= n; i++)
            if (fabs(a[i][c]) > fabs(a[t][c])) t = i;
        if (fabs(a[t][c]) < eps) continue;
        for (int i = c; i <= n + 1; i++)
            swap(a[t][i], a[r][i]);
        for (int i = n + 1; i >= c; i--)
            a[r][i] /= a[r][c];
        for (int i = r + 1; i <= n; i++)
            if (fabs(a[i][c]) > eps)
                for (int j = n + 1; j >= c; j--)
                    a[i][j] -= a[r][j] * a[i][c];
        r++;
    }
    if (r <= n)
    {
        for (int i = r; i <= n; i++)
            if (fabs(a[i][n + 1]) > eps) return 2; // 非0无解
        return 1;         // 无穷多组解
    }
    for (int i = n; i >= 1; i--)
        for (int j = i + 1; j <= n + 1; j++)
            a[i][n + 1] -= a[j][n + 1] * a[i][j];
    return 0;
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++)
            cin >> a[i][j];
    int t = guass();
    if (t == 0)
    {
        for (int i = 1; i <= n; i++)
            cout << fixed << setprecision(2) << a[i][n + 1] << endl;
    }
    else if (t == 1)
        cout << "Infinite group solutions" << endl; // 无穷多组解
    else
        cout << "No Solution" << endl; // 无解
    return 0;
}