#include <bits/stdc++.h>
using namespace std;
 
using ll = int64_t;
using ull = uint64_t;
using uint = uint32_t;
using VI = vector<int>;
using VL = vector<ll>;
using VVI = vector<vector<int>>;
using VVL = vector<vector<ll>>;
using PII = pair<int,int>;
using PLL = pair<ll, ll>;
 
#define REP(i, _, __) for (int i = (_); i < (__); ++i)
#define PER(i, _, __) for (int i = (_-1); i >= (__); --i)
#define FOR(i, _, __) for (int i = (_); i <= (__); ++i)
#define ROF(i, _, __) for (int i = (_); i >= (__); --i)
#define FC(v, V) for (const auto& v: V)
#define FE(v, V) for (auto& v: V)

#define EB emplace_back
#define PB push_back
#define MP make_pair
#define FI first
#define SE second
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(),(x).end()
#define LLA(x) (x).rbegin(),(x).rend()

const double PI = acos(-1.0);
   
namespace Backlight {
    const int __BUFFER_SIZE__ = 1 << 20;
    bool NEOF = 1;
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

    inline bool need(char c) { return (c != '\n') && (c != ' '); }

    inline bool read(char& a) {
        while ((a = nc()) && need(a) && NEOF) ;
        return NEOF;
    }

    inline bool read(char *a) {
        while ((*a = nc()) && need(*a) && NEOF) ++a; 
        *a = '\0';
        return NEOF;
    }

    inline bool read(double &x) {
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

    template<typename First, typename... Rest>
    inline bool read(First &f, Rest &... r) {
        read(f);
        return read(r...);
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
    #define debug(...) cerr << "\033[31m" << "[" << __LINE__ << "] : "; _dbg(#__VA_ARGS__, __VA_ARGS__); cerr << "\033[0m";
    // #define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__); 
    #else
    #define debug(...)
    #endif
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l, int r) { return l + rng() % (r - l + 1); }

using namespace Backlight;
const int N = 5e5 + 5;
const int M = 3e6 + 5;
const int K = 1e7 + 5;
const int MOD = 1e9 + 7;              // 998244353 1e9 + 7
const int INF = 0x3f3f3f3f;             // 1e9 + 7 0x3f3f3f3f
const ll LLINF = 0x3f3f3f3f3f3f3f3f;    // 1e18 + 9 0x3f3f3f3f3f3f3f3f
const double eps = 1e-8;

#define ls (x << 1)
#define rs (x << 1 | 1)
#define mid ((l + r) >> 1)
#define lson ls, l, mid
#define rson rs, mid+1, r

ll sum[N << 2], tag[N << 2];
void change(int x, int l, int r, ll val) {
    sum[x] += val * (r - l + 1);
    tag[x] += val;
}

void push_up(int x) {
    sum[x] = sum[ls] + sum[rs];
}

void push_down(int x, int l, int r) {
    if (tag[x] != 0) {
        change(lson, tag[x]);
        change(rson, tag[x]);
        tag[x] = 0;
    }
}

void build(int x, int l, int r) {
    tag[x] = 0;
    if (l == r) {
        sum[x] = 0;
        return;
    }
    build(lson); build(rson);
    push_up(x);
}

ll queryPoint(int x, int l, int r, int p) {
    if (l == r) return sum[x];
    push_down(x, l, r);
    ll res = 0;
    if (p <= mid) res = queryPoint(lson, p);
    else res = queryPoint(rson, p);
    push_up(x);
    return res;
}

ll querySegment(int x, int l, int r, int L, int R) {
    if (l == L && r == R) return sum[x];
    push_down(x, l, r);
    ll res = 0;
    if (R <= mid) res = querySegment(lson, L, R);
    else if (L > mid) res =  querySegment(rson, L, R);
    else res =  querySegment(lson, L, mid) + querySegment(rson, mid + 1, R);
    push_up(x);
    return res;
}

void changePoint(int x, int l, int r, int p, ll val) {
    if (l == r) {
        sum[x] += val;
        return;
    }
    push_down(x, l, r);
    if (p <= mid) changePoint(lson, p, val);
    else changePoint(rson, p, val);
    push_up(x);
}

void changeSegment(int x, int l, int r, int L, int R, ll val) {
    if (l == L && r == R) {
        change(x, l, r, val);
        return;
    }
    push_down(x, l, r);
    if (R <= mid) changeSegment(lson, L, R, val);
    else if (L > mid) changeSegment(rson, L, R, val);
    else {
        changeSegment(lson, L, mid, val);
        changeSegment(rson, mid + 1, R, val);
    }
    push_up(x);
}

int queryFirstPosition(int x, int l, int r, ll k) {
    if (sum[x] < k) return -1;
    if (l == r) return l;
    push_down(x, l, r);
    if (sum[ls] >= k) return queryFirstPosition(lson, k);
    return queryFirstPosition(rson, k - sum[ls]);
}

void add(int pos, ll val) {
    changeSegment(1, 0, N - 1, pos, pos, val);
}

void add(int l, int r, ll val) {
    changeSegment(1, 0, N - 1, l, r, val);
}

ll get(int pos) {
    return querySegment(1, 0, N - 1, pos, pos);
}

ll get(int l, int r) {
    return querySegment(1, 0, N - 1, l, r);
}

ll qry(int k) {
    return queryFirstPosition(1, 0, N - 1, k);
}

int n, k, l[N];
void solve(int Case) { // printf("Case #%d: ", Case);
    read(n, k);
    FOR(i, 1, n) read(l[i]);

    sort(l + 1, l + 1 + n, [] (int x, int y) {
        return x > y;
    });

    build(1, 0, N - 1);

    int first_white = 0, ans = -1;
    add(first_white, 1);
    FOR(i, 1, n) {
        while(get(first_white) == 0) ++first_white;

        add(first_white, -1);
        int l1 = (l[i] - 1) / 2, l2 = l[i] - l1 - 1;

        add(first_white + 2, first_white + l1 + 1, 1);
        add(first_white + 2, first_white + l2 + 1, 1);

        int cur = qry(k);
        if (cur != -1 && (ans == -1 || ans > cur)) ans = cur;
    }

    println(ans);
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
    cerr << "\033[32mTime Elasped: " << duration.count() << " ms\033[0m" << endl;
#endif
    return 0;
}