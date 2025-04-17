#include <bits/stdc++.h>
using namespace std;
const int N = 2000005;

// rt为根节点编号
// tot为叶子节点个数
// fa[i]为i的父亲
// ch[i][0/1]为左右儿子编号
// val[i]表示i节点的权值
// cnt[i]表示权值出现的次数
// sz[i]表示i子树大小
int rt, tot, fa[N], ch[N][2], val[N], cnt[N], sz[N];
struct Splay
{

    /*
    maintain(x)：在改变节点位置后，将节点 x 的 size 更新。
    get(x)：判断节点 x 是父亲节点的左儿子还是右儿子。
    clear(x)：销毁节点 x。
    */
    void maintain(int x) { sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x]; }
    bool get(int x) { return x == ch[fa[x]][1]; }
    void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = val[x] = sz[x] = cnt[x] = 0; }

    // 左旋/右旋
    void rotate(int x)
    {
        int y = fa[x], z = fa[y], chk = get(x);
        ch[y][chk] = ch[x][chk ^ 1];
        if (ch[x][chk ^ 1]) fa[ch[x][chk ^ 1]] = y;
        ch[x][chk ^ 1] = y;
        fa[y] = x;
        fa[x] = z;
        if (z) ch[z][y == ch[z][1]] = x;
        maintain(y);
        maintain(x);
    }

    // 每访问一个节点都要强制将其旋转到根节点
    void splay(int x)
    {
        for (int f = fa[x]; f = fa[x], f; rotate(x))
            if (fa[f]) rotate(get(x) == get(f) ? f : x);
        rt = x;
    }

    // 插入节点
    void ins(int k)
    {
        if (!rt)
        {
            val[++tot] = k;
            cnt[tot]++;
            rt = tot;
            maintain(rt);
            return;
        }
        int cur = rt, f = 0;
        while (1)
        {
            if (val[cur] == k)
            {
                cnt[cur]++;
                maintain(cur);
                maintain(f);
                splay(cur);
                break;
            }
            f = cur;
            cur = ch[cur][val[cur] < k];
            if (!cur)
            {
                val[++tot] = k;
                cnt[tot]++;
                fa[tot] = f;
                ch[f][val[f] < k] = tot;
                maintain(tot);
                maintain(f);
                splay(tot);
                break;
            }
        }
    }

    // 查询一个数的排名
    int rk(int k)
    {
        int res = 0, cur = rt;
        while (1)
        {
            if (k < val[cur]) cur = ch[cur][0];
            else
            {
                res += sz[ch[cur][0]];
                if (!cur) return res + 1;
                if (k == val[cur])
                {
                    splay(cur);
                    return res + 1;
                }
                res += cnt[cur];
                cur = ch[cur][1];
            }
        }
    }

    // 查询排名为k的数
    int kth(int k)
    {
        int cur = rt;
        while (1)
        {
            if (ch[cur][0] && k <= sz[ch[cur][0]])
                cur = ch[cur][0];
            else
            {
                k -= cnt[cur] + sz[ch[cur][0]];
                if (k <= 0)
                {
                    splay(cur);
                    return val[cur];
                }
                cur = ch[cur][1];
            }
        }
    }

    // 查询一个数的前驱
    int pre()
    {
        int cur = ch[rt][0];
        if (!cur) return cur;
        while (ch[cur][1]) cur = ch[cur][1];
        splay(cur);
        return cur;
    }

    // 查询一个数的后继
    int nxt()
    {
        int cur = ch[rt][1];
        if (!cur) return cur;
        while (ch[cur][0]) cur = ch[cur][0];
        splay(cur);
        return cur;
    }

    // 删除一个数
    void del(int k)
    {
        rk(k);
        if (cnt[rt] > 1)
        {
            cnt[rt]--;
            maintain(rt);
            return;
        }
        if (!ch[rt][0] && !ch[rt][1])
        {
            clear(rt);
            rt = 0;
            return;
        }
        if (!ch[rt][0])
        {
            int cur = rt;
            rt = ch[rt][1];
            fa[rt] = 0;
            clear(cur);
            return;
        }
        if (!ch[rt][1])
        {
            int cur = rt;
            rt = ch[rt][0];
            fa[rt] = 0;
            clear(cur);
            return;
        }
        int cur = rt;
        int x = pre();
        fa[ch[cur][1]] = x;
        ch[x][1] = ch[cur][1];
        clear(cur);
        maintain(rt);
    }
} tree;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, op;
    cin >> n >> op;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        tree.ins(x);
    }
    int las = 0, ans = 0;
    while (op--)
    {
        int opt, x;
        cin >> opt >> x;
        x ^= las;
        if (opt == 1) tree.ins(x);
        else if (opt == 2) tree.del(x);
        else
        {
            if (opt == 3) las = tree.rk(x);
            else if (opt == 4) las = tree.kth(x);
            else if (opt == 5) tree.ins(x), las = val[tree.pre()], tree.del(x);
            else tree.ins(x), las = val[tree.nxt()], tree.del(x);
            ans ^= las;
        }
    }
    cout << ans << '\n';
    return 0;
}