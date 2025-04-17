// O(n)求解一数组中长度为m的任一区间的最值
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
int main()
{
    int n, m, V[N];
    deque<int> Q; // 存储的是编号，区间长为m的最大值
    for (int i = 0; i < n; i++)
    {
        if (!Q.empty() && i - Q.front() >= m) Q.pop_front();
        while (!Q.empty() && V[Q.back()] < V[i]) Q.pop_back();
        Q.push_back(i); // 新生入队
        if (i >= m - 1) cout << V[Q.front()] << " ";
    }
}