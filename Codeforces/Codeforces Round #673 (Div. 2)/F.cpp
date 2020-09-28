#include <bits/stdc++.h>
using namespace std;
 
// #include <ext/rope>
// using namespace __gnu_cxx;
 
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
 
// typedef ll key_type;
// typedef null_mapped_type value_type;
// typedef tree<key_type, value_type, less<key_type>, rb_tree_tag, tree_order_statistics_node_update> rbtree;
 
// typedef __gnu_pbds::priority_queue<pi,greater<pi>,pairing_heap_tag > heap;
 
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int rnd(int l,int r){return l+rng()%(r-l+1);}
 
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<vector<int>> VVI;
 
#define REP(i,_,__) for (int i = (_); i < (__); ++i)
#define PER(i,_,__) for (int i = (_-1); i >= (__); --i)
#define FOR(i,_,__) for (int i = (_); i <= (__); ++i)
#define ROF(i,_,__) for (int i = (_); i >= (__); --i)

#define eb emplace_back
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define x1 _x
#define x2 __x
#define y1 _y
#define y2 __y
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(),(x).end()
#define RALL(x) (x).rbegin(),(x).rend()

const double pi = acos(-1.0);
   
namespace IO {
    bool REOF = 1; //为0表示文件结尾
    inline char nc() {
        static char buf[1 << 20], *p1 = buf, *p2 = buf;
        return p1 == p2 && REOF && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? (REOF = 0, EOF) : *p1++;
    }
   
    template<typename T>
    inline bool read(T &x) {
        char c = nc();
        bool f = 0; x = 0;
        while (c < '0' || c > '9') c == '-' && (f = 1), c = nc();
        while (c >= '0'&&c <= '9')x = (x << 3) + (x << 1) + (c ^ 48), c = nc();
        if (f)x=-x;
        return REOF;
    }
 
    template<typename T>
    inline void write(T x){
        if(x > 9) write(x / 10);
        putchar('0' + x%10);
    }
   
    template<typename T, typename... T2>
    inline bool read(T &x, T2 &... rest) {
        read(x);
        return read(rest...);
    }
   
   inline bool isdowncase(char c) { return (c >= 'a') && (c <= 'z'); }
   inline bool isupcase(char c) { return (c >= 'A') && (c <= 'Z'); }
   inline bool isdigit(char c) { return (c >= '0') && (c <= '9'); }

    // inline bool need(char &c) { return (c == '.') || (c == 'x') || (c=='o');}
    // inline bool need(char &c) { return isdowncase(c) || isupcase(c) || isdigit(c) || c == '.' || c == '#'; }
    inline bool need(char &c) { return isdowncase(c) || isupcase(c) || isdigit(c); }

    inline bool read_str(char *a) {
        while ((*a = nc()) && need(*a) && REOF) ++a; *a = '\0';
        return REOF;
    }
   
    inline bool read_db(double &x){
        bool f = 0; char ch = nc(); x = 0;
        while(ch < '0' || ch > '9')  { f |= (ch == '-'); ch = nc(); }
        while(ch >= '0' && ch <= '9') { x = x * 10.0 + (ch^48); ch = nc(); }
        if(ch == '.') {
            double temp = 1; ch = nc();
            while(ch >= '0' && ch <= '9') { temp = temp / 10.0; x = x + temp * (ch^48); ch = nc(); }
        }
        if(f) x = -x;
        return REOF;
    }
   
    template<typename TH>
    inline void _dbg(const char *sdbg, TH h){ cerr << sdbg << '=' << h << endl; }
   
    template<typename TH, typename... TA>
    inline void _dbg(const char *sdbg, TH h, TA... a) {
        while(*sdbg != ',') cerr << *sdbg++;
        cerr << '=' << h << ',' << ' ';
        _dbg(sdbg+1, a...);
    }
      
    template<typename T>
    ostream &operator<<(ostream& os, vector<T> V) {
        os << "[ "; for (auto vv : V) os << vv << ","; return os << " ]";
    }
   
    template<typename T>
    ostream &operator<<(ostream& os, set<T> V) {
        os << "[ "; for (auto vv : V) os << vv << ","; return os << " ]";
    }

    template<typename T>
    ostream &operator<<(ostream& os, multiset<T> V) {
        os << "[ "; for (auto vv : V) os << vv << ","; return os << " ]";
    }
 
    template<typename T>
    ostream &operator<<(ostream& os, map<T,T> V) {
        os << "[ "; for (auto vv : V) os << vv << ","; return os << " ]";
    }
  
    template<typename L, typename R>
    ostream &operator<<(ostream &os, pair<L,R> P) {
        return os << "(" << P.first << "," << P.second << ")";
    }


    template<typename TH>
    TH MIN(TH a, TH b) { return min(a, b); }
    template<typename TH, typename... TA>
    TH MIN(TH a, TA... c) { return min(a, MIN(c...)); }

    template<typename TH>
    TH MAX(TH a, TH b) { return max(a, b); }
    template<typename TH, typename... TA>
    TH MAX(TH a, TA... c) { return max(a, MIN(c...)); }

    template<typename T>
    void updMin(T& a, T b) { if (a > b) a = b; }

    template<typename T>
    void updMax(T& a, T b) { if (a < b) a = b; }
 
    #ifdef BACKLIGHT
    #define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
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

using namespace IO;
const int N = 5e5 + 5;
const int M = 5e5 + 5;
const int V = 5e7 + 5;
const ll MOD = 998244353;              // 998244353 1e9+7
const int INF = 0x3f3f3f3f;             // 1e9+7 0x3f3f3f3f
const ll LLINF = 0x3f3f3f3f3f3f3f3f;    // 1e18+9 0x3f3f3f3f3f3f3f3f
const double eps = 1e-8;



VI G[N];
int n, m, q, p[N], is[N];
PII query[N], e[N];

// Disjoint Set Union
int fa[N];
int find(int x) { return x == fa[x] ? x : (fa[x] = find(fa[x])); }
void merge(int x, int y) {
    x = find(x); y = find(y);

    if (x == y) return;

    ++n; fa[n] = n;
    fa[x] = n; fa[y] = n;
    G[n].pb(x); G[n].pb(y);
}









// Segment Tree
PII ma[N << 2];
PII queryMax(int x, int l, int r, int L, int R) {
    // debug("Q", l, r, L, R);
    if (L > R || l > R || r < L) return PII(0, 0);
    if (l == L && r == R) return ma[x];
    int mid = (l + r) >> 1;
    if (R <= mid) return queryMax(x << 1, l, mid, L, R);
    else if (L > mid) return queryMax(x << 1 | 1, mid + 1, r, L, R);
    return max(queryMax(x << 1, l, mid, L, mid), queryMax(x << 1 | 1, mid + 1, r, mid + 1, R));
}

void updatePosition(int x, int l, int r, int pos, PII val) {
    // debug("U", l, r, pos, val);
    if (l == r) {
        ma[x] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) updatePosition(x << 1, l, mid, pos, val);
    else updatePosition(x << 1 | 1, mid + 1, r, pos, val);
    ma[x] = max(ma[x << 1], ma[x << 1 | 1]);
}







// euler sequence
int dfs_clock, st[N], ed[N];
void dfs(int u) {
    st[u] = ++dfs_clock;
    for(int v: G[u]) {
        dfs(v);
    }
    ed[u] = dfs_clock;
}







void solve(int Case) { // printf("Case #%d: ", Case);
    // prework
    read(n, m, q);

    FOR(i, 1, n) read(p[i]);
    
    int u, v;
    FOR(i, 1, m) {
        read(u, v);
        e[i] = PII(u, v);
    }

    int op;
    FOR(i, 1, q) {
        read(op, v);
        query[i] = PII(op, v);
        if (op == 2) is[v] = 1;
    }


    // mainwork
    FOR(i, 1, n) fa[i] = i;

    FOR(i, 1, m) if (!is[i]) {
        merge(e[i].fi, e[i].se);
    }

    ROF(i, q, 1) {
        if (query[i].fi == 1) {
            query[i].se = find(query[i].se);
        } else {
            int eid = query[i].se;
            merge(e[eid].fi, e[eid].se);
        }
    }

    FOR(i, 1, n) if (find(i) == i) {
        dfs(i);
    }

    FOR(i, 1, n) {
        updatePosition(1, 1, n, st[i], PII(p[i], st[i]));
    }

    FOR(i, 1, q) if (query[i].fi == 1) {
        int id = query[i].se;
        PII ans = queryMax(1, 1, n, st[id], ed[id]);
        printf("%d\n", ans.fi);
        if (ans.fi != 0) updatePosition(1, 1, n, ans.se, PII(0, 0));
    }
}

int main()
{
#ifdef BACKLIGHT
    freopen("in.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T = 1;
    // read(T);
    for (int _ = 1; _ <= T; _++) solve(_);
    return 0;
}