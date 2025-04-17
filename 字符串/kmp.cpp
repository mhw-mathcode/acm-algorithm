#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 6;
// idx表示匹配的字符串所在的若干起始位置
int pmt[N], idx[N], cnt = 1;
void get_pmt(string big)
{
    for (int i = 1, j = 0; i < big.size(); i++)
    {
        while (j && big[i] != big[j]) j = pmt[j - 1];
        if (big[i] == big[j]) j++;
        pmt[i] = j;
    }
}
void kmp(string big, string sma)
{
    for (int i = 0, j = 0; i < big.size(); i++)
    {
        while (j && big[i] != sma[j]) j = pmt[j - 1];
        if (big[i] == sma[j]) j++;
        if (j == sma.size())
        {
            idx[cnt++] = i - j + 2;
            j = pmt[j - 1];
        }
    }
}
int main()
{
    string a, b;
    cin >> a >> b;
    get_pmt(b);
    kmp(a, b);
    for (int i = 1; i < cnt; i++)
        cout << idx[i] << endl;
    for (int i = 0; i < b.size(); i++)
        cout << pmt[i] << " ";
    cout << endl;
}