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
#define pf printf

const double PI = acos(-1.0);

template<typename T>
T MIN(T a, T b) { return min(a, b); }

template<typename First, typename... Rest>
First MIN(First f, Rest... r) { return min(f, MIN(r...)); }

template<typename T>
T MAX(T a, T b) { return max(a, b); }

template<typename First, typename... Rest>
First MAX(First f, Rest... r) { return max(f, MAX(r...)); }

template<typename T>
inline void umin(T& a, const T& b) { if (a > b) a = b; }

template<typename T>
inline void umax(T& a, const T& b) { if (a < b) a = b; }

ll FIRSTTRUE (ll l, ll r, function<bool(ll)> f) {
    ll res = l - 1, mid;
    while(l <= r) {
        mid = (l + r) >> 1;
        if (f(mid)) r = mid - 1, res = mid;
        else l = mid + 1;
    }
    return res;
}

ll LASTTRUE (ll l, ll r, function<bool(ll)> f) {
    ll res = l - 1, mid;
    while(l <= r) {
        mid = (l + r) >> 1;
        if (f(mid)) l = mid + 1, res = mid;
        else r = mid - 1;
    }
    return res;
}

const int __BUFFER_SIZE__ = 1 << 20;
bool NEOF = 1;
int __top;
char __buf[__BUFFER_SIZE__], *__p1 = __buf, *__p2 = __buf, __stk[996];
inline char nc() {
    return __p1 == __p2 && NEOF && (__p2 = (__p1 = __buf) + fread(__buf, 1, __BUFFER_SIZE__, stdin), __p1 == __p2) ? (NEOF = 0, EOF) : *__p1++;
}

#define rd read
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

#define pr print
#define pln println
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
void println(const vector<T>& V) {
    for(const auto& v: V) print(v), putchar(' ');
    putchar('\n');
}

#ifdef BACKLIGHT
#include "debug.h"
#else
#define debug(...)
#endif

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l, int r) { return l + rng() % (r - l + 1); }

const int N = 5e5 + 5;
const int M = 3e6 + 5;
const int K = 1e7 + 5;
const int MOD = 1e9 + 7;              // 998244353 1e9 + 7
const int INF = 0x3f3f3f3f;             // 1e9 + 7 0x3f3f3f3f
const ll LLINF = 0x3f3f3f3f3f3f3f3f;    // 1e18 + 9 0x3f3f3f3f3f3f3f3f
const double eps = 1e-8;

ll qp(ll a, ll b, ll p = MOD) { ll r = 1; while(b) { if (b & 1) r = r * a % p; a = a * a % p; b>>= 1; } return r; }

class segtree {
public:
    struct node {
        // 声明变量，记得设置初始值
        // ie. 最大值: int mx = INT_MIN;

        ll mi = 0;


        void apply(int l, int r, ll addv) {
            // 更新节点信息
            // ie. 最大值+区间加: mx = mx + addv

            mi += addv;
        }
    };

    friend node operator + (const node& tl, const node& tr) {
        node t;
        // 合并两个区间的信息
        // ie. 区间和: t.sum = t1.sum + t2.sum;

        t.mi = min(tl.mi, tr.mi);

        return t;
    }

    inline void push_down(int x, int l, int r) {
        int lc = x << 1, rc = lc | 1, mid = (l + r) >> 1;
        // 标记下传
        // ie. 区间加法
        // if (tr[x].add != 0) {
        //     tr[lc].apply(l, mid, tr[x].add);
        //     tr[rc].apply(mid + 1, r, tr[x].add);
        //     tr[x].add = 0;
        // }
    }

    /************************************************************************/
    inline void push_up(int x) {
        int lc = x << 1, rc = lc | 1;
        tr[x] = tr[lc] + tr[rc];
    }

    int n;
    vector<node> tr;

    void build(int x, int l, int r) {
        if (l == r) {
            return;
        }
        int lc = x << 1, rc = lc | 1, mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        push_up(x);
    }

    template<class T>
    void build(int x, int l, int r, const vector<T>& arr){
        if (l == r) {
            tr[x].apply(l, r, arr[l]);
            return;
        }
        int lc = x << 1, rc = lc | 1, mid = (l + r) >> 1;
        build(lc, l, mid, arr);
        build(rc, mid + 1, r, arr);
        push_up(x);
    }

    template<class T>
    void build(int x, int l, int r, T* arr){
        if (l == r) {
            tr[x].apply(l, r, arr[l]);
            return;
        }
        int lc = x << 1, rc = lc | 1, mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        push_up(x);
    }

    node get(int x, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            return tr[x];
        }
        push_down(x, l, r);
        int lc = x << 1, rc = lc | 1, mid = (l + r) >> 1;
        node res;
        if (R <= mid) res = get(lc, l, mid, L, R);
        else if (L > mid) res = get(rc, mid + 1, r, L, R);
        else res = get(lc, l, mid, L, mid) + get(rc, mid + 1, r, mid + 1, R);
        push_up(x);
        return res;
    }

    template<class... T>
    void upd(int x, int l, int r, int L, int R, const T&... v) {
        if (L <= l && r <= R) {
            tr[x].apply(l, r, v...);
            return;
        }
        push_down(x, l, r);
        int lc = x << 1, rc = lc | 1, mid = (l + r) >> 1;
        node res;
        if (L <= mid) upd(lc, l, mid, L, R, v...);
        if (R > mid) upd(rc, mid + 1, r, L, R, v...);
        push_up(x);
    }

    int __get_first(int x, int l, int r, const function<bool(const node&)> &f) {
        if (l == r) {
            return l;
        }
        int lc = x << 1, rc = lc | 1, mid = (l + r) >> 1;
        push_down(x, l, r);
        int res;
        if (f(tr[lc])) res = __get_first(lc, l, mid, f);
        else res = __get_first(rc, mid + 1, r, f);
        push_up(x);
        return res;
    }

    int get_first(int x, int l, int r, int L, int R, const function<bool(const node&)> &f) {
        if (L <= l && r <= R) {
            if (!f(tr[x])) {
                return -1;
            }
            return __get_first(x, l, r, f);
        }
        push_down(x, l, r);
        int lc = x << 1, rc = lc | 1, mid = (l + r) >> 1;
        int res;
        if (L <= mid) res = get_first(lc, l, mid, L, R, f);
        if (res == -1 && R > mid) res = get_first(rc, mid + 1, r, L, R, f);
        push_up(x);
        return res;
    }

    int __get_last(int x, int l, int r, const function<bool(const node&)> &f) {
        if (l == r) {
            return l;
        }
        int lc = x << 1, rc = lc | 1, mid = (l + r) >> 1;
        push_down(x, l, r);
        int res;
        if (f(tr[lc])) res = __get_first(rc, mid + 1, r, f);
        else res = __get_first(lc, l, mid, f);
        push_up(x);
        return res;
    }

    int get_last(int x, int l, int r, int L, int R, const function<bool(const node&)> &f) {
        if (L <= l && r <= R) {
            if (!f(tr[x])) {
                return -1;
            }
            return __get_first(x, l, r, f);
        }
        push_down(x, l, r);
        int lc = x << 1, rc = lc | 1, mid = (l + r) >> 1;
        int res;
        if (R > mid) res = get_last(rc, mid + 1, r, L, R, f);
        if (res == -1 && L <= mid) res = get_last(lc, l, mid, L, R, f);
        push_up(x);
        return res;
    }

    int find_first(int l, int r, const function<bool(const node&)> &f) {
        int L = l, R = r, mid, res = -1;
        while(L <= R) {
            mid = (L + R) >> 1;
            if (f(get(l, mid))) R = mid - 1, res = mid;
            else L = mid + 1;
        }
        return res;
    }
 
    int find_last(int l, int r, const function<bool(const node&)> &f) {
        int L = l, R = r, mid, res = -1;
        while(L <= R) {
            mid = (L + R) >> 1;
            if (f(get(l, mid))) L = mid + 1, res = mid;
            else R = mid - 1;
        }
        return res;
    }

    segtree(int _n) : n(_n) {
        assert(n > 0);
        tr.resize((n << 2) + 5);
        build(1, 1, n);
    }

    template<class T>
    segtree(const vector<T>& arr) {
        n = arr.size() - 1;
        assert(n > 0);
        tr.resize((n << 2) + 5);
        build(1, 1, n, arr);
    }

    template<class T>
    segtree(int _n, T* arr) {
        n = _n;
        assert(n > 0);
        tr.resize((n << 2) + 5);
        build(1, 1, n, arr);
    }

    node get(int l, int r) {
        assert(l >= 1 && l <= r && r <= n);
        return get(1, 1, n, l, r);
    }

    node get(int p) {
        assert(1 <= p && p <= n);
        return get(1, 1, n, p, p);
    }
    
    template <class... T> 
    void upd(int l, int r, const T&... v) {
        assert(l >= 1 && l <= r && r <= n);
        upd(1, 1, n, l, r, v...);
    }

    template <class... T> 
    void upd1(int p, const T&... v) {
        assert(p >= 1 && p <= n);
        upd(1, 1, n, p, p, v...);
    }

    int get_first(int l, int r, const function<bool(const node&)> &f) {
        assert(l >= 1 && l <= r && r <= n);
        return get_first(1, 1, n, l, r, f);
    }

    
    int get_last(int l, int r, const function<bool(const node&)> &f) {
        assert(l >= 1 && l <= r && r <= n);
        return get_last(1, 1, n, l, r, f);
    }

    void print(int x, int l, int r) {
        if (l == r) {
            cerr << tr[x].mi << " ";
            return;
        }
        push_down(x, l, r);
        int lc = x << 1, rc = lc | 1, mid = (l + r) >> 1;
        print(lc, l, mid);
        print(rc, mid + 1, r);
    }

    void print() {
        #ifdef BACKLIGHT
        cerr << "SEGTREE: " << endl;
        print(1, 1, n);
        cerr << "\n-----------------------------" << endl;
        #endif
    }
};

int n;
ll a[N], d[N];
void solve(int Case) { // printf("Case #%d: ", Case);
    rd(n);
    FOR(i, 1, n) rd(a[i]);
    
    // if possible, it always can remove all stones if you remove from left to right.
    // that is, let d_i = a_i - d_{i - 1}
    // it is possible if and only if d_i \ge 0 and d_n = 0
    FOR(i, 1, n) d[i] = a[i] - d[i - 1];

    segtree t[2] = {segtree(n), segtree(n)};

    FOR(i, 2, n) {
        t[i & 1].upd(i, i, d[i]);
        t[!(i & 1)].upd(i, i, LLINF);
    }


    bool flag = false;

    // do nothing
    if (t[0].get(1, n).mi >= 0 && t[1].get(1, n).mi >= 0 && d[n] == 0) flag = true;

    // swap a_i, a_{i + 1}
    FOR(i, 1, n - 1) {
        bool f = true;

        if (i > 1 && t[(i - 1) & 1].get(1, i - 1).mi < 0) f = false;
        if (i > 2 && t[(i - 2) & 1].get(1, i - 2).mi < 0) f = false;

        if (d[i] - a[i] + a[i + 1] < 0) f = false;

        if (i + 1 <= n && t[(i + 1) & 1].get(i + 1, n).mi - 2 * a[i + 1] + 2 * a[i] < 0) f = false;
        if (i + 2 <= n && t[(i + 2) & 1].get(i + 2, n).mi + 2 * a[i + 1] - 2 * a[i] < 0) f = false;

        if ((i & 1) == (n & 1) && d[n] + 2 * a[i + 1] - 2 * a[i] != 0) f = false;
        if ((i & 1) != (n & 1) && d[n] - 2 * a[i + 1] + 2 * a[i] != 0) f = false;

        if (f) flag = true;
    }

    puts(flag ? "YES" : "NO");
}

int main() {
#ifdef BACKLIGHT
    freopen("a.in", "r", stdin);
    // freopen("a.out", "w", stdout);
    auto begin = std::chrono::steady_clock::now();
#endif

    // ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T = 1;
    read(T);
    for (int _ = 1; _ <= T; _++) solve(_);

#ifdef BACKLIGHT
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    cerr << "\033[32mTime Elasped: " << duration.count() << " ms\033[0m" << endl;
#endif
    return 0;
}