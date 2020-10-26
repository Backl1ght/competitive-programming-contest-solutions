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
const int N = 3e5 + 5;
const int M = 5e5 + 5;
const int V = 5e7 + 5;
const ll MOD = 1e9+ 7 ;              // 998244353 1e9+7
const int INF = 0x3f3f3f3f;             // 1e9+7 0x3f3f3f3f
const ll LLINF = 0x3f3f3f3f3f3f3f3f;    // 1e18+9 0x3f3f3f3f3f3f3f3f
const double eps = 1e-8;

#define mid ((l + r) >> 1)
#define lson x << 1, l, mid
#define rson x << 1 | 1, mid + 1, r
#define ls x << 1
#define rs x << 1 | 1

int mi[N << 1];

void push_up(int x) {
    mi[x] = min(mi[ls], mi[rs]);
}

void update(int x, int l, int r, int p, int v) {
    if (l == r) {
        mi[x] = v;
        return;
    }
    if (p <= mid) update(lson, p, v);
    else update(rson, p, v);
    push_up(x);
}

int query(int x, int l, int r, int L, int R) {
    if (l > r || L > R) return -INF;
    if (l == L && r == R) return mi[x];
    if (R <= mid) return query(lson, L, R);
    else if (L > mid) return query(rson, L, R);
    return min(query(lson, L, mid), query(rson, mid + 1, R));
}

int n, a[N], lst[N], can[N];
void solve(int Case) { //printf("Case #%d: ", Case);
    read(n);
    FOR(i, 1, n) read(a[i]);

    FOR(i, 1, n) if (a[i] != 1) can[1] = 1;
    FOR(i, 1, n) if (a[i] == 1) can[2] = 1;

    FOR(i, 1, n) {
        update(1, 1, n, a[i], i);
        int left = query(1, 1, n, 1, a[i] - 1);
        if (left > lst[a[i]]) can[a[i]] = 1;
        lst[a[i]] = i;
    }

    FOR(i, 2, n + 2) {
        int left = query(1, 1, n, 1, i - 1);
        // debug(i, lst[i], left);
        if (left > lst[i]) can[i] = 1;
    }

    int ans = 1; while(can[ans]) ++ans; 
    println(ans);
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
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    cerr << "\033[32mTime Elasped: " << (double) (duration.count()) << " ms\033[0m" << endl;
#endif
    return 0;
}