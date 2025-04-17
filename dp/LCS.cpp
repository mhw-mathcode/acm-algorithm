#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
const int N = 1e3 + 2;
int dp[N][N];
// 求解LCS的长度
void lcslen(string a, string b)
{
    int lena = a.length(), lenb = b.length();
    for (int i = 1; i <= lena; i++)
    {
        for (int j = 1; j <= lenb; j++)
        {
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    // return dp[lena][lenb];
}
// 求解LCS
string lcs(string a, string b)
{
    int i = a.length(), j = b.length();
    string ret = "";
    while (i != 0 && j != 0)
    {
        if (a[i - 1] == b[j - 1])
        {
            ret += a[--i];
            j--;
        }
        else if (dp[i - 1][j] < dp[i][j - 1]) j--;
        else if (dp[i - 1][j] >= dp[i][j - 1]) i--;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}
// 求解两字符串根据LCS拼接后的字符串
string lcsadd(string a, string b)
{
    int i = a.length(), j = b.length();
    string ret = "";
    while (dp[i][j])
    {
        if (a[i - 1] == b[j - 1])
        {
            ret += a[--i];
            j--;
        }
        else if (dp[i - 1][j] <= dp[i][j - 1]) ret += b[--j];
        else if (dp[i - 1][j] > dp[i][j - 1]) ret += a[--i];
    }
    while (i != 0) ret += a[--i];
    while (j != 0) ret += b[--j];
    reverse(ret.begin(), ret.end());
    return ret;
}
int main()
{
    string a, b;
    while (cin >> a >> b)
    {
        memset(dp, 0, sizeof(dp));
        lcslen(a, b);
        cout << lcsadd(a, b) << endl;
    }
}