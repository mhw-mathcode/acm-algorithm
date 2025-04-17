#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 6;
// trie存字典树，cnt存以该点为结尾的字符串数
int trie[N * 30][2], cnt[N * 30], id = 1;
void insert(int a)
{
    int p = 1;
    for (int i = 29; i >= 0; i--)
    {
        int x = ((a >> i) & 1);
        if (trie[p][x] == 0) trie[p][x] = ++id;
        p = trie[p][x];
    }
    cnt[p]++;
}
int find(int a)
{
    int p = 1, ret = 0;
    for (int i = 29; i >= 0 && p; i--)
    {
        int x = ((a >> i) & 1);
        if (x)
        {
            if (trie[p][0]) p = trie[p][0], ret += (1 << i);
            else p = trie[p][1];
        }
        else
        {
            if (trie[p][1]) p = trie[p][1], ret += (1 << i);
            else p = trie[p][0];
        }
    }
    return ret;
}