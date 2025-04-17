#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define inf 0x3f3f3f3f
#define pii pair<int, int>
const int N = 3e3 + 5;

// n点数，m边数，s出发点
int tot = 0, n, m, s = 1;
int hea[N], d[N], v[N], num[N]; // 初始化0, inf, 0, 0

struct edge
{
    int next, to, dis;
} edge[N << 1];               
void add(int x, int y, int w) 
{
    edge[++tot] = {hea[x], y, w}; 
    hea[x] = tot; 
}

// 判断是否存在负环
bool SPFA()
{
    queue<int> q;
    d[s] = 0;
    q.push(s);
    num[s]++;
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        v[x] = 0;
        for (int i = hea[x]; i; i = edge[i].next) // 链式前向星遍历一点所有边
        {
            int y = edge[i].to;
            if (d[y] > d[x] + edge[i].dis)
            {
                d[y] = d[x] + edge[i].dis;
                if (v[y] == 0)
                {
                    v[y] = 1;
                    q.push(y);
                    num[y]++;
                    if (num[y] >= n) return 1;
                }
            }
        }
    }
    return 0;
}

// 优化spfa
const int N = 2e5 + 5;
vector<pii> g[N];
int n, m;
int dis[N], cnt[N], vis[N]; // 初始化 inf, 0, 0
bool spfa_slf_lll(int s)
{
    deque<int> q;
    dis[s] = 0;
    q.push_back(s);
    int sum = dis[s], num = 1, flag = 0, temp; 
    cnt[s]++, vis[s] = 1; 
    while (!q.empty())
    {
        temp = q.front();
        while (dis[temp] * num > sum)
        {
            // lll优化
            q.pop_front();
            q.push_back(temp);
            temp = q.front();
        }
        q.pop_front();
        sum -= dis[temp], num--, vis[temp] = 0; 
        for (auto [v, w]: g[temp])
        {
            if (dis[v] > dis[temp] + w)
            {
                dis[v] = dis[temp] + w; // 更新最短路径
                if (!vis[v])
                {
                    if (!q.empty() && dis[v] > dis[q.front()]) q.push_back(v); // 大于入队尾
                    else q.push_front(v); // 小于入队头
                    sum += dis[v], num++, cnt[v]++;
                    if (cnt[v] > n)
                    {
                        flag = 1;
                        return flag;
                    }
                    vis[v] = true;
                }
            }
        }
    }
    return flag;
}