// 火车头
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)

#pragma GCC optimize(2) // 手动加o2优化
#include <bits/stdc++.h>
using namespace std;

// 快读快写
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}
void write(int x)
{
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
    return;
}

// 更快读快写
namespace fastIO
{
    static char buf[100000], *h = buf, *d = buf;                                         // 缓存开大可减少读入时间，看题目给的空间
#define gc h == d && (d = (h = buf) + fread(buf, 1, 100000, stdin), h == d) ? EOF : *h++ // 不能用fread则换成getchar
    template <typename T>
    inline void read(T &x)
    {
        int f = 1;
        x = 0;
        register char c(gc);
        while (c > '9' || c < '0')
        {
            if (c == '-') f = -1;
            c = gc;
        }
        while (c <= '9' && c >= '0')
            x = (x << 1) + (x << 3) + (c ^ 48), c = gc;
        x *= f;
    }
    template <typename T>
    void output(T x)
    {
        if (x < 0)
        {
            putchar('-');
            x = ~(x - 1);
        }
        static int s[20], top = 0;
        while (x)
        {
            s[++top] = x % 10;
            x /= 10;
        }
        if (!top) s[++top] = 0;
        while (top) putchar(s[top--] + '0');
    }
}
using namespace fastIO;

// int128读入写出板子，不能关流
template <class T>
inline void read(T &x)
{
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar())
        f ^= (c == '-');
    for (; isdigit(c); c = getchar())
        x = (x << 3) + (x << 1) + (c ^ 48);
    x = f ? -x : x;
}
template <class T>
inline void write(T x)
{
    if (x < 0) putchar('-'), x = -x;
    if (x < 10) putchar(x + 48);
    else write(x / 10), putchar(x % 10 + 48);
}

#include <Windows.h>
int main()
{
    // 测试时间
    DWORD star_time = GetTickCount();
    DWORD end_time = GetTickCount();
    cout << "This program runs: " << (end_time - star_time) << " ms" << endl;

    // 关流
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // 读写文件
    freopen("D:\\3022244240\\vscode\\txt\\in.txt", "r", stdin);   // 输入重定向，输入数据将从D盘根目录下的in.txt文件中读取
    freopen("D:\\3022244240\\vscode\\txt\\out.txt", "w", stdout); // 输出重定向，输出数据将保存在D盘根目录下的out.txt文件中
    fclose(stdin);                                           // 关闭重定向输入
    fclose(stdout);                                          // 关闭重定向输出

    // 随机数
    int seed;
    seed = time(0);
    srand(seed);
    for (int i = 1; i <= 100; i++)
        cout << rand() << "\n";

    // main函数里定义新函数
    auto add = [&](int a, int b) -> int
    {
        return a + b;
    };

    system("pause");
    return 0;
}

// 1. 全排列函数，注意从字典序最小的开始
void cpp()
{
    vector<char> chars = {'a', 'b', 'c'}; 
    do 
    {
        cout << chars[0] << chars[1] << chars[2] << '\n';
    } while (next_permutation(chars.begin(), chars.end()));  
}

// 2. 进制转化
void Decimal_conversion()
{
    // （1）把t进制下的a转化为10进制的ret
    char a[10] = "1a";
    char *b;
    int t = 16;
    long ret = strtol(a, &b, t);

    // （2）把十进制下的c转化为t进制下的s
    int c = 26;
    char s[10];
    itoa(c, s, t);
}

// 3. 二进制
void builtin()
{
    int t;
    // 返回右起第一个‘1’的位置
    int a = __builtin_ffs(t);

    // 返回左起第一个‘1’之前0的个数
    int b = __builtin_clz(t);

    // 返回右起第一个‘1’之后的0的个数
    int c = __builtin_ctz(t);

    // 返回‘1’的个数
    int d = __builtin_popcount(t);
}

// 4. STL
void STL_string()
{
    // （1）字符串与数字相互转化
    int num = 123;
    string s = to_string(num);
    int s_num = atoi(s.c_str());
}
void STL_vector()
{
    vector<int> v;
    // （1）打乱顺序 + 去重 + 翻转
	srand(time(0));
	random_shuffle(v.begin(), v.end()); 

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    reverse(v.begin(), v.end());
}

