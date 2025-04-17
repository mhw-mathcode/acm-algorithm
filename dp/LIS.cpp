#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const int inf = 0x3f3f3f3f;
int main()
{
	int n;
	vector<double> b(n + 1);
	vector<double> st;
	st.push_back(b[0]);
	for (int i = 1; i < cnt; i++)
	{
		if (ge(b[i], st.back())) st.push_back(b[i]);
		else *lower_bound(st.begin(), st.end(), b[i]) = b[i];
	}
	cout << st.size() << '\n';
}