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
 
#define REP(i, _, __) for (int i = (_); i < (__); ++i)
#define PER(i, _, __) for (int i = (_-1); i >= (__); --i)
#define FOR(i, _, __) for (int i = (_); i <= (__); ++i)
#define ROF(i, _, __) for (int i = (_); i >= (__); --i)

#define EB emplace_back
#define PB push_back
#define MP make_pair
#define FI first
#define SE second
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(),(x).end()
#define LLA(x) (x).rbegin(),(x).rend()

const double pi = acos(-1.0);
   
namespace Backlight {
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
        while (c >= '0'&&c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = nc();
        if (f) x = -x;
        return REOF;
    }
 
    template<typename T>
    inline void println(T x, bool flag = true) {
        if (x < 0) putchar('-'), x = -x;
        if(x > 9) println(x / 10, false);
        putchar('0' + x % 10);
        if (flag) putchar('\n');
    }

    #define YES puts("YES");
    #define NO puts("NO");
    #define Yes puts("Yes");
    #define No puts("No");
    #define yes puts("yes");
    #define no puts("no");
   
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
        while (ch < '0' || ch > '9')  { f |= (ch == '-'); ch = nc(); }
        while (ch >= '0' && ch <= '9') { x = x * 10.0 + (ch^48); ch = nc(); }
        if(ch == '.') {
            double temp = 1; ch = nc();
            while (ch >= '0' && ch <= '9') { temp = temp / 10.0; x = x + temp * (ch^48); ch = nc(); }
        }
        if(f) x = -x;
        return REOF;
    }
   
    template<typename TH>
    inline void _dbg(const char *sdbg, TH h){ cerr << sdbg << '=' << h << endl; }
   
    template<typename TH, typename... TA>
    inline void _dbg(const char *sdbg, TH h, TA... a) {
        while(*sdbg != ',') cerr << *sdbg++;
        cerr << '=' << h << ", ";
        _dbg(sdbg+1, a...);
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

using namespace Backlight;
const int N = 5e5 + 5;
const int M = 5e5 + 5;
const int V = 1e6 + 5;
const ll MOD = 998244353;              // 998244353 1e9+7
const int INF = 0x3f3f3f3f;             // 1e9+7 0x3f3f3f3f
const ll LLINF = 0x3f3f3f3f3f3f3f3f;    // 1e18+9 0x3f3f3f3f3f3f3f3f
const double eps = 1e-8;

int n, r, t[N], x[N], y[N], dp[N];

// 这里前缀最大值就可以了，我比赛的时候脑子短路写复杂了。
int ma[N << 2];
void update(int x, int l, int r, int p, int v) {
    if (l == r) {
        if (l == p) ma[x] = v;
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) update(x << 1, l, mid, p, v);
    else update(x << 1 | 1, mid + 1, r, p, v);
    ma[x] = max(ma[x << 1], ma[x << 1 | 1]);
}

int get(int x, int l, int r, int L, int R) {
    if (l == L && r == R) return ma[x];
    int mid = (l + r) >> 1;
    if (R <= mid) return get(x << 1, l, mid, L, R);
    else if (L > mid) return get(x << 1 | 1, mid + 1, r, L, R);
    return max(get(x << 1, l, mid, L, mid), get(x << 1 | 1, mid + 1, r, mid + 1, R));
}

void solve(int Case) { // printf("Case #%d: ", Case);
    read(r, n); x[0] = y[0] = 1; dp[0] = 0;

    FOR(i, 1, n) read(t[i], x[i], y[i]);

    FOR(i, 1, n) {
        dp[i] = -INF;
        ROF(j, i - 1, 0) {
            if (t[j] + 2 * r < t[i]) {
                dp[i] = max(dp[i], get(1, 0, n, 0, j) + 1);
                break;
            }

            if (abs(x[i] - x[j]) + abs(y[i] - y[j]) <= t[i] - t[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        } 
        update(1, 0, n, i, dp[i]);
    }

    int ans = *max_element(dp, dp + 1 + n);
    println(ans);
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