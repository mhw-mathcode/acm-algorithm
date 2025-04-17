#include<bits/stdc++.h>
using namespace std;
// 辗转相除法
int gcd(int a, int b)  
{  
    return b ? gcd(b, a % b) : a;  
} 
// 更相减损术(当a>>b时)
int stein(int a, int b)  
{  
    if (a < b) swap(a, b);  
    if (b == 0) return a;  
    if ((!(a & 1)) && (!(b & 1))) return stein(a >> 1, b >> 1) << 1; 
    else if ((a & 1) && !(b & 1)) return stein(a, b >> 1);  
    else if (!(a & 1) && (b & 1)) return stein(a >> 1, b);  
    else return stein(a - b, b);  
}