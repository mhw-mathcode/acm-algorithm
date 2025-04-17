#include <bits/stdc++.h>
using namespace std;
const int N = 3e6 + 5;
// trie存字典树，cnt存以该点为结尾的字符串数
int trie[N * 30][70], cnt[N * 30], id = 1;
// 当需要插入的字符不仅仅是小写字母时
int getnum(char a)
{
    if (a >= 'a' && a <= 'z') return a - 'a';
    else if (a >= 'A' && a <= 'Z') return a - 'A' + 26;
    else return a - '0' + 52;
}
// 初始化，否则可能被memset卡常
void init()
{
    for (int i = 0; i <= id; i++)
        for (int j = 0; j < 70; j++)
            trie[i][j] = 0;
    for (int i = 0; i <= id; i++)
        cnt[i] = 0;
    id = 1;
}
void insert(string a)
{
    int p = 1; // 虚点
    for (int i = 0; i < a.size(); i++)
    {
        int x = getnum(a[i]);
        if (trie[p][x] == 0) trie[p][x] = ++id;
        p = trie[p][x];
        cnt[p]++; // 该语句位置取决于需要查询的是经过该点的字符串数
    }
    // cnt[p]++; //前缀位置
}
int find(string a)
{
    int p = 1; // 虚点
    for (int i = 0; i < a.size() && p; i++)
    {
        int x = getnum(a[i]);
        if (trie[p][x] == 0) return 0;
        p = trie[p][x];
    }
    return cnt[p];
}
int main()
{
    init();
}