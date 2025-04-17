#include <bits/stdc++.h>
using namespace std;
const int N = 2e5;
// hw[i]-1表示以第i个字母为中心最大回文串的长度
int n, hw[N], ans;
char a[N], s[N << 1];
void manacher()
{
	s[0] = s[1] = '#';
	for (int i = 0; i < n; i++) s[i * 2 + 2] = a[i], s[i * 2 + 3] = '#';
	n = n * 2 + 2;
	s[n] = 0;
	int mr = 0, mid;
	for (int i = 1; i < n; i++)
	{
		if (i < mr) hw[i] = min(hw[(mid << 1) - i], hw[mid] + mid - i);
		else hw[i] = 1;
		for (; s[i + hw[i]] == s[i - hw[i]]; hw[i]++) ;
		if (hw[i] + i > mr) mr = hw[i] + i, mid = i;
	}
}
int main()
{
	scanf("%s", a);
	n = strlen(a);
	manacher();
	ans = 1;
	for (int i = 0; i < n; i++)
	{
		printf("%d\n", hw[i] - 1);
		ans = max(ans, hw[i]);
	}
	printf("%d\n", ans - 1);
}