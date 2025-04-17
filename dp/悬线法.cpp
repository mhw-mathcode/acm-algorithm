#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
const int N = 2e3 + 5;
int A[N][N], l[N][N], r[N][N], u[N][N];
void solve()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> A[i][j];
            
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (A[i][j])
                l[i][j] = l[i][j - 1] + 1;

    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 1; j--)
            if (A[i][j])
                r[i][j] = r[i][j + 1] + 1;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (A[i][j])
            {
                u[i][j] = u[i - 1][j] + 1;
                if (A[i - 1][j])
                    l[i][j] = min(l[i][j], l[i - 1][j]), r[i][j] = min(r[i][j], r[i - 1][j]);
                ans = max(ans, (r[i][j] + l[i][j] - 1) * u[i][j]);
            }
    cout << ans << endl;
}

int a[N][N], b[N][N];
void solve2()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    for (int j = 1; j <= m; j++)
    {
        int ls = 1;
        for (int i = 1; i <= n; i++)
        {
            if (a[i - 1][j] > a[i][j])
            {
                for (int l = i - 1; l >= ls; l--)
                    b[l][j] = (i - 1) - l + 1;
                ls = i;
            }
        }
        for (int l = n; l >= ls; l--)
            b[l][j] = n - l + 1;
    }
    // 区间长度乘区间最小值的max
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        stack<pii> s;
        s.push({0, 0});
        for (int j = 1; j <= m; j++)
        {
            while (s.top().first >= b[i][j])
            {
                int w = s.top().first;
                s.pop();
                ans = max(ans, (j - s.top().second - 1) * w);
            }
            s.push({b[i][j], j});
        }
        while (s.size() != 1)
        {
            int w = s.top().first;
            s.pop();
            ans = max(ans, (m - s.top().second) * w);
        }
    }
}