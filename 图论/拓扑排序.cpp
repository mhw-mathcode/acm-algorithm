#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
const int N = 2e5 + 5;

struct node
{
    int next, to;
} edge[N];
int hea[N], tot;
void add(int x, int y)
{
    edge[++tot] = {hea[x], y};
    hea[x] = tot;
}

int rudu[N], n;
vector<int> toposort()
{
    vector<int> ret;
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (rudu[i] == 0)
        {
            ret.push_back(i);
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int t = q.front();
        q.pop();
        for (int i = hea[t]; i; i = edge[i].next)
        {
            rudu[edge[i].to]--;
            if (rudu[edge[i].to] == 0)
            {
                ret.push_back(edge[i].to);
                q.push(edge[i].to);
            }
        }
    }
    return ret;
}
