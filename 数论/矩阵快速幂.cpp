#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const i64 P = 1e9 + 7;
const int SIZE = 100;
struct Matrix {
    i64 M[SIZE + 2][2 * SIZE + 2];
	Matrix () { memset(M, 0, sizeof(M)); }
    void clear() { memset(M, 0, sizeof(M)); }
    void reset() { //初始化
        clear();
        for (int i = 1; i <= SIZE; ++i) M[i][i] = 1;
    }
    Matrix friend operator*(const Matrix &A, const Matrix &B) {
        Matrix Ans;
        Ans.clear();
        for (int i = 1; i <= SIZE; ++i)
            for (int j = 1; j <= SIZE; ++j)
                for (int k = 1; k <= SIZE; ++k)
                    Ans.M[i][j] = (Ans.M[i][j] + A.M[i][k] * B.M[k][j] % P + P) % P;
        return Ans;
    }
    Matrix friend operator+(const Matrix &A, const Matrix &B) {
        Matrix Ans;
        Ans.clear();
        for (int i = 1; i <= SIZE; ++i)
            for (int j = 1; j <= SIZE; ++j)
                Ans.M[i][j] = (A.M[i][j] + B.M[i][j]) % P;
        return Ans;
    }
	void debug() {
		for (int i = 1; i <= SIZE; i++) {
			for (int j = 1; j <= SIZE; j++) {
				cout << M[i][j] << " \n"[j == SIZE];
			}
		}
		cout << '\n';
	}
};
Matrix qpow(Matrix base, i64 b) {
    Matrix ans;
    ans.reset();
    while (b) {
        if (b & 1) ans = ans * base;
        base = base * base;
        b >>= 1;
    }
    return ans;
}
i64 qpow(i64 x, i64 y, i64 p = P) {
    i64 res = 1;
    while (y) {
        if (y & 1) res = res * x % p;
        x = x * x % p;
        y >>= 1;
    }
    return res;
}
bool ok = 1;
Matrix getinv(Matrix a, int siz) { //矩阵求逆
	ok = 1;
    Matrix res;
    res.clear();
    int n = siz, m = siz * 2;
    for (int i = 1; i <= n; i++) a.M[i][i + n] = 1;
    for (int i = 1; i <= n; i++) {
        int pos = i;
        for (int j = i + 1; j <= n; j++)
            if (abs(a.M[j][i]) > abs(a.M[pos][i])) pos = j;
        if (i != pos) swap(a.M[i], a.M[pos]);
        if (!a.M[i][i]) {
            puts("No Solution");
            ok = 0;
			return res;
        }
        i64 inv = qpow(a.M[i][i], P - 2);
        for (int j = 1; j <= n; j++)
            if (j != i) {
                i64 mul = a.M[j][i] * inv % P;
                for (int k = i; k <= m; k++)
                    a.M[j][k] = ((a.M[j][k] - a.M[i][k] * mul) % P + P) % P;
            }
        for (int j = 1; j <= m; j++) a.M[i][j] = a.M[i][j] * inv % P;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) 
            res.M[i][j] = a.M[i][n + j];
    return res;
}
void solve() {
	i64 n, k;
	cin >> n >> k;
	Matrix a;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a.M[i][j];
		}
	}
	// a = getinv(a, n); // 矩阵逆元
    a = qpow(a, k); // 矩阵快速幂
	if (!ok) return;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << a.M[i][j] << " \n"[j == n];
		}
	}
}
int main() {
	// ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);
	int t = 1; 
	// cin >> t;
	while(t--) solve();
	return 0;
}