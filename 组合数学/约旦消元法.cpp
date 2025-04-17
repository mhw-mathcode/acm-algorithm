#include<bits/stdc++.h>
using namespace std;
const int N = 5007;
const double eps = 1e-6;
int n, m;
double a[N][N];
int guass() 
{
    //枚举列
    for(int i = 1; i <= n; ++ i) 
    {
        int maxx = i;
        //1.找
        for(int j = i + 1; j <= n; ++ j)
//第i列以前的未知量除了第i行的所有行都已经消成0了，不能再动了
            if(fabs(a[j][i]) > fabs(a[maxx][i]))
                maxx = j;
        //2.换
        for(int j = 1; j <= n + 1; ++ j)//找到的最大一行跟第i行换
            swap(a[i][j], a[maxx][j]);
        if(fabs(a[i][i]) < eps) return -1;
        //3.减
        for(int j = 1; j <= n; ++ j)
//把该未知量除第i行以外全部减成0（普通的高斯是第i行以下减为0，但是需要回代）
            if(j != i)
            {
                double tmp = a[j][i] / a[i][i];
                for(int k = i + 1; k <= n +1; ++ k) //只需要减第i列右边就行了，因为左边全为0
                    a[j][k] -= a[i][k] * tmp;
            }                               //约旦消元法
    }                                       //最后会得到这样的矩阵
    for(int i = 1; i <= n; ++ i)            // k1*a=e1
        a[i][n + 1] /= a[i][i];             // k2*b=e2
    //所以最后要除以该项的系数     <--        // k3*c=e3
    return 1;                               // k4*d=e4
}
int main()
{
    cin>>n;
    for(int i = 1; i <= n; ++ i)
        for(int j = 1; j <= n + 1; ++ j)
            cin>>a[i][j];
    int ans = guass();
    if(ans == -1) cout<<"No Solution"<<endl;
    else 
        for(int i = 1; i <= n; ++ i)
            cout<<fixed<<setprecision(2)<<a[i][n + 1]<<endl;
    return 0;
}