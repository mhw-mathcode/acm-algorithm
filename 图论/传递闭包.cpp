#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 5;
int a[N][N];
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        memset(a, 0, sizeof a);
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= m; i++)
        {
            int x, y;
            cin >> x >> y;
            a[x][y] = 1;
        }

        // floyd写法
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (a[i][k] && a[k][j])
                        a[i][j] = 1;

        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            int from = 0, to = 0;
            for (int j = 1; j <= n; j++)
            {
                if (a[i][j]) to++;
                if (a[j][i]) from++;
            }
            if (to > n / 2 || from > n / 2) ans++;
        }
        cout << ans << "\n";
    }
    return 0;
}