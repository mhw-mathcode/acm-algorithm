#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
const int N = 2e5 + 5;
int maxx[N][21], lg[N];
int ask(int l, int r)
{
    int k = lg[r - l + 1];
    return max(maxx[l][k], maxx[r - (1 << k) + 1][k]);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> maxx[i][0];
    lg[1] = 0;
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    for (int j = 1; j <= lg[n]; j++)
        for (int i = 1; i <= n - (1 << j) + 1; i++)
            maxx[i][j] = max(maxx[i][j - 1], maxx[i + (1 << (j - 1))][j - 1]);
    while (m--)
    {
        int l, r;
        cin >> l >> r;
        cout << ask(l, r) << "\n";
    }
    return 0;
}