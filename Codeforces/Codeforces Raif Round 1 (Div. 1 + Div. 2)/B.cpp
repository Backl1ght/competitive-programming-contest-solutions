#include <bits/stdc++.h>
using namespace std;
 
// #include <ext/rope>
// using namespace __gnu_cxx;c
 
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
    inline bool isdowncase(char c) { return (c >= 'a') && (c <= 'z'); }
    inline bool isupcase(char c) { return (c >= 'A') && (c <= 'Z'); }
    inline bool isdigit(char c) { return (c >= '0') && (c <= '9'); }

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

    bool NEOF = 1; //为0表示文件结尾
    const int BUFFER_SIZE = 1 << 20;
    inline char nc() {
        static char buf[BUFFER_SIZE], *p1 = buf, *p2 = buf;
        return p1 == p2 && NEOF && (p2 = (p1 = buf) + fread(buf, 1, BUFFER_SIZE, stdin), p1 == p2) ? (NEOF = 0, EOF) : *p1++;
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

    inline bool need(char c) { return (c == '-') || (c == '>') || (c == '<');}
    // inline bool need(char c) { return isdowncase(c) || isupcase(c) || isdigit(c) || c == '.' || c == '#'; }
    // inline bool need(char c) { return isdowncase(c) || isupcase(c) || isdigit(c); }

    inline bool read_str(char *a) {
        while ((*a = nc()) && need(*a) && NEOF) ++a; *a = '\0';
        return NEOF;
    }

    template<typename T>
    inline void println(T x, bool flag = true) {
        if (x < 0) putchar('-'), x = -x;
        if (x > 9) println(x / 10, false);
        putchar('0' + x % 10);
        if (flag) putchar('\n');
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
    #define debug(...) cerr << "\033[31m"; _dbg(#__VA_ARGS__, __VA_ARGS__); cerr << "\033[0m"; cerr.flush();
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

using namespace Backlight;
const int N = 5e5 + 5;
const int M = 5e5 + 5;
const int V = 5e7 + 5;
const ll MOD = 1e9+ 7 ;              // 998244353 1e9+7
const int INF = 0x3f3f3f3f;             // 1e9+7 0x3f3f3f3f
const ll LLINF = 0x3f3f3f3f3f3f3f3f;    // 1e18+9 0x3f3f3f3f3f3f3f3f
const double eps = 1e-8;

struct Graph {
    struct Edge {
        int u, v;
        Edge(){}
        Edge(int _u, int _v): u(_u), v(_v) {}
    };

    int V;
    vector<vector<Edge>> G;

    Graph() : V(0) {}
    Graph(int _V) : V(_V), G(_V) {}

    inline void addarc(int u, int v) {
        assert(0 <= u && u < V);
        assert(0 <= v && v < V);
        G[u].push_back(Edge(u, v));
    }

    inline void addedge(int u, int v) {
        addarc(u, v);
        addarc(v, u);
    }

    /**************************************************/
    int scc_clock, scc_cnt;
    vector<int> dfn, low, belong, scc_size;
    vector<bool> ins;
    stack<int> stk;

    void tarjan(int u, int fa) {
        dfn[u] = low[u] = ++scc_clock;
        ins[u] = true;
        stk.push(u);

        // bool flag = false;
        for (Edge& e: G[u]) {
            int v = e.v;

            // if (v == fa && !flag) {
                // flag = true;
                // continue;
            // }

            if (!dfn[v]) {
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
            } else if (ins[v]) low[u] = min(low[u], dfn[v]);
        }

        if (dfn[u] == low[u]) {
            ++scc_cnt; scc_size.push_back(0);
            int top;
            do {
                top = stk.top(); stk.pop();
                ins[top] = false;
                belong[top] = scc_cnt;
                ++scc_size[scc_cnt];
            } while(u != top);
        }
    }

    void build_scc() {
        scc_clock = scc_cnt = 0;
        dfn = vector<int>(V);
        low = vector<int>(V);
        belong = vector<int>(V);
        ins = vector<bool>(V);
        scc_size = vector<int>(1);

        for (int i = 0; i < V; ++i) {
            if (!dfn[i]) tarjan(i, i);
        }
    }
};

char s[N];
void solve(int Case) { // printf("Case #%d: ", Case);
    int n;
    read(n); Graph g(n);
    read_str(s);
    REP(i, 0, n) {
        int j = (i + 1) % n;
        if (s[i] == '>') {
            g.addarc(i, j);
        } else if (s[i] == '<') {
            g.addarc(j, i);
        } else {
            g.addarc(i, j);
            g.addarc(j, i);
        }
    }
    g.build_scc();
    // debug(g.belong);
    // debug(g.scc_size);
    int ans = 0;
    FOR(i, 1, g.scc_cnt) if (g.scc_size[i] > 1) ans += g.scc_size[i];
    printf("%d\n", ans);
}

int main() {
#ifdef BACKLIGHT
    freopen("in.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T = 1;
    read(T);
    for (int _ = 1; _ <= T; _++) solve(_);
    return 0;
}