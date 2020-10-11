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
const int V = 5e7 + 5;
const ll MOD = 998244353;              // 998244353 1e9+7
const int INF = 0x3f3f3f3f;             // 1e9+7 0x3f3f3f3f
const ll LLINF = 0x3f3f3f3f3f3f3f3f;    // 1e18+9 0x3f3f3f3f3f3f3f3f
const double eps = 1e-8;

void exgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1; y = 0;
        return;
    }
    ll x1, y1;
    exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
}

vector<tuple<ll, char, ll>> ans;

void solve(int Case) { // printf("Case #%d: ", Case);
    ll x; read(x);

    auto add = [] (ll a, ll b) {
        ans.PB(make_tuple(a, '+', b));
    };

    auto xr = [] (ll a, ll b) {
        ans.PB(make_tuple(a, '^', b));
    };

    auto mul = [add] (ll a, ll n) {
        ll base = a, res = 0;
        while(n) {
            if (n & 1) {
                add(res, base); res += base;
            }
            add(base, base); base *= 2;
            n >>= 1;
        }
    };

    // Step 0: Make 0 for Multiplication.
    xr(x, x);

    // Step 1: Write on the blackboard a number y coprime with x.
    // let e be the largest integer satisfying 2^e \le x.
    // y = (2^ex) ^ x = (2^e + 1)x - 2^{e + 1}, gcd(x, y) = gcd(x, 2^{e + 1}) = 1.
        ll e = 0, ee = 1, y = x;
        while(ee <= x) {
            ++e; ee *= 2;
        }
        FOR(i, 1, e - 1) {
            add(y, y);
            y *= 2;
        }
        xr(y, x); y = y ^ x;
        assert(__gcd(x, y) == 1);

    // Step 2: Write 1 = gcd(x, y) on the blackboard.
    // Bezout's theorem: There exist a,b \ge 0 and b is even, such that ax - by = 1.
    // use ex_gcd to get a and b, and then write ax ^ by = 1

        ll a, b;
        exgcd(x, y, a, b);
        a = (a % y + y) % y;
        b = (a * x - 1) / y;

        if (b & 1) {
            a += y;
            b += x;
        }

        debug(a, x, b, y, a * x, b * y);
        assert(a * x - b * y == 1);

        mul(x, a);
        mul(y, b);

        xr(a * x, b * y);

    println(SZ(ans));
    for (tuple<ll, char, ll> t: ans) {
        printf("%lld %c %lld\n", get<0>(t), get<1>(t), get<2>(t));
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