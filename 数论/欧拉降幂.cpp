#include<bits/stdc++.h>
using namespace std;
typedef long long ll;  
ll a, b, m, phi = 1, mm;  
bool flag;  
ll ksm(ll a, ll b)  
{  
    ll ans = 1;  
    for (;b;b >>= 1, a = a * a % m)  
        if (b & 1) ans = ans * a % m;  
    return ans;  
}  
int main()  
{  
    //求解a的b次方%m(当a，b值十分大时，应用欧拉降幂)
    cin >> a >> m;mm = m, a %= m;  
    for (int i = 2;i * i <= mm;i++)  
    {  
        if (mm % i == 0)  
        {  
            phi *= (i - 1), mm /= i;  
            while (mm % i == 0) { phi *= i, mm /= i; };  
        }  
    }  
    if (mm > 1) phi *= (mm - 1);  
    char ch = getchar();  
    while (ch < '0' || ch>'9') ch = getchar();  
    while (ch >= '0' && ch <= '9')  
    {  
        b = (b << 3) + (b << 1) + (ch & 15);  
        ch = getchar();  
        if (b >= phi) flag = 1, b %= phi;  
    }  
    if (flag) b += phi;  
    cout << ksm(a, b) << endl;  
}