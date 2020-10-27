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

    // inline bool need(char c) { return (c == '-') || (c == '>') || (c == '<');}
    // inline bool need(char c) { return islower(c) || isupper(c) || isdigit(c) || c == '.' || c == '#'; }
    inline bool need(char c) { return islower(c) || isupper(c) || isdigit(c); }

    inline bool read(char& a) {
        while ((a = nc()) && need(a) && NEOF) ;
        return NEOF;
    }

    inline bool read(char *a) {
        while ((*a = nc()) && need(*a) && NEOF) ++a; *a = '\0';
        return NEOF;
    }

    inline bool read(double &x){
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
    ostream &operator<<(ostream& os, map<T1, T2> V) {
        os << "[ "; for (auto v : V) os << v << ","; return os << " ]";
    }
  
    template<typename L, typename R>
    ostream &operator<<(ostream &os, pair<L, R> P) {
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
const int N = 1e5 + 5;
const int M = 1e5 + 5;
const int V = 1e6 + 5;
const ll MOD = 1e9+ 7 ;              // 998244353 1e9+7
const int INF = 0x3f3f3f3f;             // 1e9+7 0x3f3f3f3f
const ll LLINF = 0x3f3f3f3f3f3f3f3f;    // 1e18+9 0x3f3f3f3f3f3f3f3f
const double eps = 1e-8;



// Treap
namespace Treap {
    using T = int;
    const int S = N << 5;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    int tot, sz[S], L[S], R[S], rnd[S];

    T v[S];

    inline void init() {
        tot = 0;
    }

    inline int newnode(T val) {
        ++tot;
        sz[tot] = 1;
        L[tot] = R[tot] = 0;
        rnd[tot] = rng();
        v[tot] = val;
        return tot;
    }

    inline void push_up(int x) {
        sz[x] = sz[L[x]] + 1 + sz[R[x]];
    }

    void split(int u, T k, int &x, int &y) {
        if (!u) x = y = 0;
        else {
            if (v[u] <= k) {
                x = u;
                split(R[x], k, R[x], y);
                push_up(x);
            } else {
                y = u;
                split(L[y], k, x, L[y]);
                push_up(y);
            }
        }
    }

    int merge(int x, int y) {
        if (!x || !y) return x | y;
        if (rnd[x] < rnd[y]) {
            R[x] = merge(R[x], y);
            push_up(x);
            return x;
        } else {
            L[y] = merge(x, L[y]);
            push_up(y);
            return y;
        }
    }

    void __DEBUG(int rt) {
        if (!rt) return;
        __DEBUG(L[rt]);
        cerr << v[rt] << " ";
        __DEBUG(R[rt]);
    }

    void DEBUG(int rt) {
        cerr << "Treap: ";
        __DEBUG(rt);
        cerr << endl;
    }






    void insert(int& rt, T val) {
        if (!rt) {
            rt = newnode(val);
            return;
        }
        int x, y;
        split(rt, val, x, y);
        x = merge(x, newnode(val));
        rt = merge(x, y);
    }

    int query(int rt, int val) {
        int x, y;
        split(rt, val, x, y);
        int res = sz[x];
        rt = merge(x, y);
        return res;
    }
} // namespace Treap











VI g[N];
int n, a[N];


// Segment Tree
int rt[N << 2];
void insert(int x, int l, int r, int p, int val) {
    Treap::insert(rt[x], val);
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (p <= mid) insert(x << 1, l, mid, p, val);
    else insert(x << 1 | 1, mid + 1, r, p, val);
}

int query(int x, int l, int r, int L, int R, int val) {
    if (l == L && r == R) return Treap::query(rt[x], val);
    int mid = (l + r) >> 1;
    if (R <= mid) return query(x << 1, l, mid, L, R, val);
    if (L > mid) return query(x << 1 | 1, mid + 1, r, L, R, val);
    return query(x << 1, l, mid, L, mid, val) + query(x << 1 | 1, mid + 1, r, mid + 1, R, val);
}

int query(int l, int r) {
    if (l > r) return -1;
    return query(1, 1, n, l, r, l - 1);
}













void solve(int Case) { // printf("Case #%d: ", Case);
    read(n);
    FOR(i, 1, n) read(a[i]), g[a[i]].PB(i);

    FOR(i, 1, n + 1) {
        g[i].PB(n + 1);

        bool flag = false;
        int lst = 0;
        for (int pos: g[i]) {
            int cnt = query(lst + 1, pos - 1);
            if (cnt == i - 1) {
                flag = true;
                break;
            }
            lst = pos;
        }

        if (!flag) {
            println(i);
            return;
        }

        lst = 0;
        for (int pos: g[i]) {
            if (pos <= n) {
                insert(1, 1, n, pos, lst);
            }
            lst = pos;
        }
    }
    println(n + 2);
}

int main() {
#ifdef BACKLIGHT
    freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
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