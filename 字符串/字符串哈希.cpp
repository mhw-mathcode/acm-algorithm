#include <bits/stdc++.h>
using namespace std;
using i64=long long;
#define int long long
#define pii pair<int,int>

const int N = 1 << 21; // 范围1e6
const i64 P1 = 1590318979, b1 = 127; // 模数自己写程序跑一个大于1e9的质数
const i64 P2 = 1333333399, b2 = 131;
vector<i64> bs1, bs2;
void init (int n = N) { //使用结构体之前必须init
	bs1.resize(n + 1), bs2.resize(n + 1);
	bs1[0] = 1, bs2[0] = 1;
	for (int i = 1; i <= n; i++) {
		bs1[i] = bs1[i - 1] * b1 % P1;
		bs2[i] = bs2[i - 1] * b2 % P2;
	}
}
struct Hash {
	string s;
	vector<i64>h1, h2;
 
	Hash(string s_) : s(s_), h1{0}, h2{0}{ // 声明 Hash hash(s);
		for (auto it : s) {
			h1.push_back((h1.back() * b1 % P1 + it) % P1);
			h2.push_back((h2.back() * b2 % P2 + it) % P2);
		}
	}
	pair<i64, i64> get() { // 返回用来声明的字符串的整个哈希值
		return {h1.back(), h2.back()};
	}
	pair<i64, i64> get(int l, int r) { // 子串哈希值， 对于abba， get(0, 2)就是abb的哈希值
		i64 ans1 = ((h1[r + 1] - h1[l] * bs1[r - l + 1] % P1) % P1 + P1) % P1;
		i64 ans2 = ((h2[r + 1] - h2[l] * bs2[r - l + 1] % P2) % P2 + P2) % P2;
		return {ans1, ans2};
	}
	pair<i64, i64> get(string s) { 
        //查随便一个字符串的哈希值，和子串不一样，线性复杂度，不会对声明时的数据有任何影响当个函数就好
		i64 ans1 = 0, ans2 = 0;
		for (auto it : s) {
			ans1 = (ans1 * b1 % P1 + it) % P1;
			ans2 = (ans2 * b2 % P2 + it) % P2;
		}
		return {ans1, ans2};
	}
	pair<i64, i64> modify(int idx, char x) { //修改一位的哈希值，不会对声明时的数据有任何影响
		int n = s.size() - 1;
		i64 ans1 = (h1.back() + bs1[n - idx] * (x - s[idx]) % P1) % P1;
		i64 ans2 = (h2.back() + bs2[n - idx] * (x - s[idx]) % P2) % P2;
		return {ans1, ans2};
	}
};

// 想随机化就用这个，种子是找jiangly抄的，尽量不要乱换，听说伪随机数种子简单也能被卡
/*
bool isprime(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}
int findPrime(int n) {
    while (!isprime(n)) n++;
    return n;
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
P1 = findPrime(rng() % 900000000 + 100000000);
*/

void solve()
{
    string a,b;cin>>a>>b;
    map<pii,int>mp;
    Hash ha(a);
    Hash hb(b); 
}
signed main()
{
    int t;cin>>t;
    init(); // 注意初始化
    while(t--) solve();
    return 0;
}