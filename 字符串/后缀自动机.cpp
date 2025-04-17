#include <bits/stdc++.h>
using namespace std;
const int N=5e5+5;

struct SAM {
	//root是1
	int size, last, len[N << 1], fa[N << 1], tr[N << 1][31];
	int nxt[N << 1], head[N << 1], to[N << 1], ecnt = 1;
	int cnt[N << 1], first_pos[N << 1], is_clone[N << 1];

#define sfor(x, i) for(int i = 0; i <= 30; ++i) if(tr[x][i])
	SAM() {
		size = last = ecnt = 1;
	}
	int extend(int x) {
		int cur = ++ size,u;
		cnt[cur] = 1, first_pos[cur] = len[cur] = len[last] + 1;
		for(u = last; u && !tr[u][x]; u = fa[u]) tr[u][x] = cur;
		if(!u) fa[cur] = 1;
		else {
			int v = tr[u][x];
			if(len[v] == len[u] + 1) fa[cur] = v;
			else {
				int clone = ++ size;
				len[clone] = len[u] + 1, fa[clone] = fa[v], first_pos[clone] = first_pos[v], is_clone[clone] = 1;
				memcpy(tr[clone], tr[v], sizeof(tr[v]));//时间复杂度在这个地方
				for(; u && tr[u][x] == v; u = fa[u]) tr[u][x] = clone;
				fa[cur] = fa[v] = clone;
			}
		}
		return last = cur;
	}
	//cnt数组表示endpos的大小，默认是真实大小
	//d数组表示下面可以走多少路径，默认和endpos集合大小有关
	//每个结点的endpos集合起始就是终点结点的endpos的集合
//=========================================建树=========================================
	void add(int x, int y) {
		nxt[++ecnt] = head[x], to[ecnt] = y, head[x] = ecnt;
	}
	void build_tree() {
		for(int i = 2; i <= size; ++i) add(fa[i], i);
	}

//===========================================求occ=========================================
	int pos[N << 1], f[N << 1][20];//pos代表s[1...r]对应的结点
	//调用的时候pos[r] = extend(s[r] - 'a' + 1);
	//调用时先建树 并求得cnt
	void get_f(int x = 1){//遍历后缀链接树
		f[x][0] = fa[x];
		for(int i = 1; i <= 19; ++i) f[x][i] = f[f[x][i - 1]][i - 1];
		for(int i = head[x]; i; i = nxt[i]) if(fa[x] != to[i]) {
			get_f(to[i]);
		}
	}
	int node(int l, int r){
		int now = pos[r];
		for(int i = 19; i >= 0; --i) if(len[f[now][i]] >= r-l+1) now = f[now][i];
		return now;//找到l...r所在的结点 并映射到cnt
	}
	int occ(int l, int r){
		return cnt[node(l, r)];
	}
//==========================================求结点的cnt=======================================
	void Get_cnt(int x) {
		for(int i = head[x]; i; i = nxt[i]) Get_cnt(to[i]), cnt[x] += cnt[to[i]];
	}
	//调用时先建树
	void get_cnt(int type = 1) {
		if(type == 0) for(int i = 1; i <= size; ++i) cnt[i] = 1;    //不同位置的子串算作一个 强制每个子串只出现一次
		else Get_cnt(1);
	}
	vector<int> endpos(int x) {
		queue<int> q;
		vector<int> ep;
		q.push(x);
		while(!q.empty()) {
			int now = q.front();
			q.pop();
			if(!is_clone[now])  //是终点结点
				ep.push_back(first_pos[now]);
			for(int i = head[now]; i; i = nxt[i])
				q.push(to[i]);
		}
		return ep;
	}
	//遍历后缀树：用图那一套 从1开始 //遍历后缀自动机：从1开始用tr转移
	int d[N], ans[N];//d记录了从x开始往下有几条路径 ans记录了从x开始，往下所有路径上不同子串的总长度。
	void get_d(int x = 1) {
		if(d[x]) return ;
		d[x] = cnt[x];
		sfor(x, i) get_d(tr[x][i]), d[x] += d[tr[x][i]];
	}
	void debug() {
		puts("--------Debug_SAM--------");
		for(int i = 1; i <= size; ++i)
			cout << "i = " << i << ", endpos_size = " << cnt[i] << ", fa = " << fa[i] << ", len = " << len[i] << ", d = " << d[i] << endl;
		for(int i = 1; i <= size; ++i) {
			cout << "i = " << i << " can trans to " << endl;
			sfor(i, j)  cout << tr[i][j] << " by " << char(j + 'a' - 1) << endl;
		}
		puts("--------End_Debug--------");
	}
} sam;

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    
	string s;cin>>s;
	for(int i=0;i<(int)s.size();i++) 
		sam.extend(s[i]-'a');

	sam.build_tree();
	sam.get_cnt();

	int q;cin>>q;
	while(q--)
	{
		string t;cin>>t;
		int now=1;
		for(int i=0;i<(int)t.size();i++)
		{
			int pos=sam.tr[now][t[i]-'a'];
			if(pos) now=pos;
			else 
			{
				now=-1;
				break;
			}
		}
		if(now==-1) cout<<0<<"\n";
		else cout<<sam.cnt[now]<<"\n";
	}
}