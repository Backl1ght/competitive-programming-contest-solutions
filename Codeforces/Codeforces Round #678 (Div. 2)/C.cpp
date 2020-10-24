#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<ll> VL;
typedef vector<vector<int>> VVI;
typedef vector<vector<ll>> VVL;
 
#define REP(i, _, __) for (int i = (_); i < (__); ++i)
#define PER(i, _, __) for (int i = (_-1); i >= (__); --i)
#define FOR(i, _, __) for (int i = (_); i <= (__); ++i)
#define ROF(i, _, __) for (int i = (_); i >= (__); --i)
#define FE(v, V) for (auto& v: V)

#define EB emplace_back
#define PB push_back
#define MP make_pair
#define FI first
#define SE second
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(),(x).end()
#define LLA(x) (x).rbegin(),(x).rend()

const double PI = acos(-1.0);
   
namespace Backlight {
    const int __BUFFER_SIZE__ = 1 << 20;
    bool NEOF = 1; //为0表示文件结尾
    int __top;
    char __buf[__BUFFER_SIZE__], *__p1 = __buf, *__p2 = __buf, __stk[996];

    template<typename T>
    T MIN(T a, T b) { return min(a, b); }

    template<typename First, typename... Rest>
    First MIN(First f, Rest... r) { return min(f, MIN(r...)); }

    template<typename T>
    T MAX(T a, T b) { return max(a, b); }

    template<typename First, typename... Rest>
    First MAX(First f, Rest... r) { return max(f, MAX(r...)); }

    template<typename T>
    void updMin(T& a, T b) { if (a > b) a = b; }

    template<typename T>
    void updMax(T& a, T b) { if (a < b) a = b; }

    inline char nc() {
        return __p1 == __p2 && NEOF && (__p2 = (__p1 = __buf) + fread(__buf, 1, __BUFFER_SIZE__, stdin), __p1 == __p2) ? (NEOF = 0, EOF) : *__p1++;
    }
   
    template<typename T>
    inline bool read(T &x) {
        char c = nc();
        bool f = 0; x = 0;
        while (!isdigit(c)) c == '-' && (f = 1), c = nc();
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = nc();
        if (f) x = -x;
        return NEOF;
    }

    inline bool read_db(double &x){
        bool f = 0; char c = nc(); x = 0;
        while (!isdigit(c))  { f |= (c == '-'); c = nc(); }
        while (isdigit(c)) { x = x * 10.0 + (c ^ 48); c = nc(); }
        if (c == '.') {
            double temp = 1; c = nc();
            while (isdigit(c)) { temp = temp / 10.0; x = x + temp * (c ^ 48); c = nc(); }
        }
        if (f) x = -x;
        return NEOF;
    }

    template<typename T, typename... T2>
    inline bool read(T &x, T2 &... rest) {
        read(x);
        return read(rest...);
    }

    // inline bool need(char c) { return (c == '-') || (c == '>') || (c == '<');}
    // inline bool need(char c) { return islower(c) || isupper(c) || isdigit(c) || c == '.' || c == '#'; }
    inline bool need(char c) { return islower(c) || isupper(c) || isdigit(c); }

    inline bool read_str(char *a) {
        while ((*a = nc()) && need(*a) && NEOF) ++a; *a = '\0';
        return NEOF;
    }

    template<typename T>
    inline void print(T x) {
        if (x < 0) putchar('-'), x = -x;
        if (x == 0) { putchar('0'); return; }
        __top = 0;
        while(x) {
            __stk[++__top] = x % 10 + '0';
            x /= 10;
        }
        while(__top) {
            putchar(__stk[__top]);
            --__top;
        }
    }

    template<typename First, typename... Rest>
    inline void print(First f, Rest... r) {
        print(f); putchar(' ');
        print(r...);
    }

    template<typename T>
    inline void println(T x) {
        print(x); 
        putchar('\n');
    }

    template<typename First, typename... Rest>
    inline void println(First f, Rest... r) {
        print(f); putchar(' ');
        println(r...);
    }


   
    template<typename T>
    inline void _dbg(const char *format, T value) { cerr << format << '=' << value << endl; }
   
    template<typename First, typename... Rest>
    inline void _dbg(const char *format, First f, Rest... r) {
        while(*format != ',') cerr << *format++;
        cerr << '=' << f << ", ";
        _dbg(format + 1, r...);
    }
      
    template<typename T>
    ostream &operator<<(ostream& os, vector<T> V) {
        os << "[ "; for (auto v : V) os << v << ","; return os << " ]";
    }
   
    template<typename T>
    ostream &operator<<(ostream& os, set<T> V) {
        os << "[ "; for (auto v : V) os << v << ","; return os << " ]";
    }

    template<typename T>
    ostream &operator<<(ostream& os, multiset<T> V) {
        os << "[ "; for (auto v : V) os << v << ","; return os << " ]";
    }
 
    template<typename T1, typename T2>
    ostream &operator<<(ostream& os, map<T1,T2> V) {
        os << "[ "; for (auto v : V) os << v << ","; return os << " ]";
    }
  
    template<typename L, typename R>
    ostream &operator<<(ostream &os, pair<L,R> P) {
        return os << "(" << P.first << "," << P.second << ")";
    }
 
    #ifdef BACKLIGHT
    #define debug(...) cerr << "\033[31m"; _dbg(#__VA_ARGS__, __VA_ARGS__); cerr << "\033[0m";
    // #define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__); 
    #else
    #define debug(...)
    #endif
}

/************     Backlight     **********
 * 一发入魂
 * 仔细读题，注意边界条件
 * 没有思路就试试逆向思维
 * wdnmd!我柜子动了不打了
 * 能不能把我掉的分还给我
 ************     Backlight     **********/

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int rnd(int l, int r) { return l + rng() % (r - l + 1); }

using namespace Backlight;
const int N = 1e6 + 5;
const int M = 5e5 + 5;
const int V = 5e7 + 5;
const ll MOD = 1e9+ 7 ;              // 998244353 1e9+7
const int INF = 0x3f3f3f3f;             // 1e9+7 0x3f3f3f3f
const ll LLINF = 0x3f3f3f3f3f3f3f3f;    // 1e18+9 0x3f3f3f3f3f3f3f3f
const double eps = 1e-8;

template<int MD>
struct Modular {
    ll value, md;

    Modular() : value(0), md(MD) {}

    Modular(ll value) : value((value % MD + MD) % MD), md(MD) {}

    Modular& norm() { value = (value % MD + MD) % MD; return *this; }

    Modular operator - () const { return Modular(0) - *this; }

    Modular operator ~ () const { return Modular(1) / *this; }

    Modular operator ^ (const Modular& a) const { return pow(*this, a); }

    Modular& operator += (const Modular& a) { value += a.value; if(value >= MD) value -= MD; return *this; }

    Modular& operator -= (const Modular& a) { value += MD - a.value; if(value >= MD) value -= MD; return *this; }
  
    Modular& operator *= (const Modular& a) { (value *= a.value) %= MD; return *this; }
  
    Modular& operator /= (const Modular& a) { (value *= a.pow(MD - 2).value) %= MD; return *this; }
    
    Modular operator + (const Modular& a) const { return Modular(this->value) += a; }
    
    Modular operator - (const Modular& a) const { return Modular(this->value) -= a; }
    
    Modular operator * (const Modular& a) const { return Modular(this->value) *= a; }
    
    Modular operator / (const Modular& a) const { return Modular(this->value) /= a; }

    bool operator < (const Modular& a) const { return value < a.value; }

    bool operator == (const Modular& a) const { return value == a.value; }

    bool operator != (const Modular& a) const { return value != a.value; }
    
    Modular pow(ll b) const {
        Modular a = value, res = 1;
        while(b) {
            if (b & 1) res *= a;
            a *= a;
            b >>= 1;
        }
        return res;
    }

    Modular inv() const { return this->pow(MD - 2); }
};
using Mint = Modular<MOD>;
istream& operator >> (istream& is, Mint& a) { return is >> a.value; }
ostream& operator << (ostream& os, const Mint& a) { return os << a.value; }


struct Combination {
    int N;
    vector<Mint> f, g;

    Combination() : N(0) {}
    Combination(int _n) : N(_n), f(N + 1), g(N + 1) {
        f[0] = 1;
        for (int i = 1; i <= N; ++i) f[i] = f[i - 1] * i;
        g[N] = f[N].inv();
        for (int i = N - 1; i >= 0; --i) g[i] = g[i + 1] * (i + 1);
    }

    Mint get(int n, int m) {
        if (n < 0 || m < 0 || n < m) return 0;
        return f[n] * g[m] * g[n - m];
    }
} C(1005);

void solve(int Case) { // printf("Case #%d: ", Case);
    int n, x, pos;
    read(n, x, pos);

    int l = 0, g = 0;
    int left = 0, right = n, middle;
    while(left < right) {
        middle = (left + right) / 2;
        if (middle <= pos) {
            left = middle + 1;
            ++l;
        } else {
            right = middle;
            ++g;
        }
    }
    --l;
    Mint ans = C.get(x - 1, l) * C.f[l] * C.get(n - x, g) * C.f[g] * C.f[n - l - g - 1];
    println(ans.value);
}

int main() {
#ifdef BACKLIGHT
    freopen("in.txt", "r", stdin);
    auto begin = std::chrono::steady_clock::now();
#endif

    // ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T = 1;
    // read(T);
    for (int _ = 1; _ <= T; _++) solve(_);

#ifdef BACKLIGHT
    freopen("in.txt", "r", stdin);
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    cerr << "\033[32mTime Elapsed: " << (double) (duration.count()) << " ms\033[0m" << endl;
#endif
    return 0;
}