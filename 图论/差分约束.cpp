#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 2147483647
#define pii pair<int, int>
const int N = 1e5 + 5;

// n点数，m边数，s出发点
int tot = 0, n, m, s = 0;
// d数组表示出发点到该点的最短距离，v数组表示是否访问过
int hea[N], d[N], v[N], num[N];

struct edge
{
    int next, to, dis;
} edge[N << 1];               // 链式前向星
void add(int x, int y, int w) // 起点，终点，权值
{
    edge[++tot] = {hea[x], y, w}; // 新加的这条边的上一条边的序号
    hea[x] = tot;                 // 此时以x为一端的最后一条边的序号
}

// 判断是否存在负环
bool SPFA()
{
    queue<int> q;
    memset(d, -0x3f, sizeof d);
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
            // 确定是最长路还是最短路
            if (d[y] < d[x] + edge[i].dis)
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
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    // 满足方程式 x1-x2<=y
    for (int i = 1; i <= m; i++)
    {
        int x1, x2, y;
        cin >> x1 >> x2 >> y;
        add(x1, x2, -y);
    }
    // 超级源点0
    for (int i = 1; i <= n; i++) add(0, i, 0);
    bool f = SPFA();
    if (f) cout << "NO" << endl;
    else
        for (int i = 1; i <= n; i++)
            cout << d[i] << " ";
}
