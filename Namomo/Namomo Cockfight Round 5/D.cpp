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
typedef double db;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<vector<int> > VVI;
 
#define REP(i,_,__) for (int i=(_); i<(__); ++i)
#define PER(i,_,__) for (int i=(_-1); i>=(__); --i)
#define FOR(i,_,__) for (int i=(_); i<=(__); ++i)
#define ROF(i,_,__) for (int i=(_); i>=(__); --i)

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
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define endl '\n'
   
const double pi = acos(-1.0);
   
namespace IO {
    bool REOF = 1; //为0表示文件结尾
    inline char nc() {
        static char buf[1 << 20], *p1 = buf, *p2 = buf;
        return p1 == p2 && REOF && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? (REOF = 0, EOF) : *p1++;
    }
   
    template<typename T>
    inline bool read(T &x) {
        char c = nc();bool f = 0; x = 0;
        while (c<'0' || c>'9') c == '-' && (f = 1), c = nc();
        while (c >= '0'&&c <= '9')x = (x << 3) + (x << 1) + (c ^ 48), c = nc();
        if (f)x=-x;
        return REOF;
    }
 
    template<typename T>
    inline void write(T x){
        if(x > 9) write(x / 10);
        putchar('0'+x%10);
    }
   
    template<typename T, typename... T2>
    inline bool read(T &x, T2 &... rest) {
        read(x);
        return read(rest...);
    }
   
    // inline bool need(char &c) { return (c == '.') || (c == '#');}
    // inline bool need(char &c) { return ((c >= 'a') && (c <= 'z')) || ((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'Z')); }
    inline bool need(char &c) { return ((c >= 'a') && (c <= 'z')) || ((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'Z')) || c == '.' || c == '#'; }

    inline bool read_str(char *a) {
        while ((*a = nc()) && need(*a) && REOF)++a; *a = '\0';
        return REOF;
    }
   
    inline bool read_db(double &x){
        bool f = 0; char ch = nc(); x = 0;
        while(ch<'0'||ch>'9')  {f|=(ch=='-');ch=nc();}
        while(ch>='0'&&ch<='9'){x=x*10.0+(ch^48);ch=nc();}
        if(ch == '.') {
            double temp = 1; ch = nc();
            while(ch>='0'&&ch<='9'){temp=temp/10.0;x=x+temp*(ch^48);ch=nc();}
        }
        if(f)x=-x;
        return REOF;
    }
   
    template<typename TH>
    inline void _dbg(const char *sdbg, TH h){ cerr<<sdbg<<'='<<h<<endl; }
   
    template<typename TH, typename... TA>
    inline void _dbg(const char *sdbg, TH h, TA... a) {
        while(*sdbg!=',')cerr<<*sdbg++;
        cerr<<'='<<h<<','<<' '; _dbg(sdbg+1, a...);
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
 
    #ifdef BACKLIGHT
    #define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
    #else
    #define debug(...)
    #endif
}

// int dx[4] = { 0, 1, 0, -1 };
// int dy[4] = { 1, 0, -1, 0 };
// int dx[8] = { 1, 0, -1, 1, -1, 1, 0, -1 };
// int dy[8] = { 1, 1, 1, 0, 0, -1, -1, -1 };

    
/************     Backlight     **********
 * 一发入魂
 * 仔细读题，注意边界条件
 * 没有思路就试试逆向思维
 * wdnmd!我柜子动了不打了
 * 能不能把我掉的分还给我
 ************     Backlight     **********/

// using namespace IO;
const int N = 1e6 + 5;
const int M = 5e5 + 5;
const int V = 3e7 + 5;
const int MOD = 1e9 + 7;              // 998244353 1e9+7
const int INF = 0x3f3f3f3f;             // 1e9+7 0x3f3f3f3f
const ll LLINF = 0x3f3f3f3f3f3f3f3f;    // 1e18+9 0x3f3f3f3f3f3f3f3f
const double eps = 1e-8;

int tot, ch[N][2], fa[N], sz[N], ed[N];
ll sum1[N], sum2[N];

void I(char* s, ll v) {
    // debug("I", s, v);
    int n = strlen(s);
    int p = 0;
    REP(i, 0, n) {
        int c = s[i] - '0';
        if (!ch[p][c]) {
            ch[p][c] = ++tot;
            fa[tot] = p;
            ch[tot][0] = ch[tot][1] = sum1[tot] = sum2[tot] = sz[tot] = ed[tot] = 0;
        }
        p = ch[p][c];
        sum1[p] += v; ++sz[p];
    }
    sum2[p] += v;
    ++ed[p];
}

void D(char* s) {
    // debug("D", s);
    int n = strlen(s);
    int p = 0;
    REP(i, 0, n) {
        int c = s[i] - '0';
        if (!ch[p][c]) {
            puts("Not Exist");
            return;
        }
        p = ch[p][c];
    }

    if (ed[p] == 0) {
        puts("Not Exist");
        return;
    }

    int tp = p;
    ll v1 = sum2[p];
    int v2 = ed[p];
    while(p != 0) {
        sum1[p] -= v1;
        sz[p] -= v2;
        p = fa[p];
    }
    sum2[tp] = ed[tp] = 0;
}

ll Q(char* s) {
    // debug("Q", s);
    int n = strlen(s);
    int p = 0;
    REP(i, 0, n) {
        int c = s[i] - '0';
        if (!ch[p][c]) {
            return 0;
        }
        p = ch[p][c];
    }
    return sum1[p];
}

void __U(int x, int y) {
    sz[y] += sz[x];
    sum1[y] += sum1[x];
    sum2[y] += sum2[x];
    ed[y] += ed[x];

    if(ch[x][0] && ch[y][0]) __U(ch[x][0], ch[y][0]);
    else if(ch[x][0]) fa[ch[y][0] = ch[x][0]] = y;

    if(ch[x][1] && ch[y][1]) __U(ch[x][1], ch[y][1]);
    else if(ch[x][1]) fa[ch[y][1] = ch[x][1]] = y;
}

void U(char* s, char* t) {
    int n = strlen(s);
    int p = 0;
    REP(i, 0, n) {
        int c = s[i] - '0';
        if (!ch[p][c]) {
            puts("Not Exist");
            return;
        }
        p = ch[p][c];
    }

    if (sz[p] == 0) {
        puts("Not Exist");
        return;
    }

    int q = 0;
    int m = strlen(t);
    REP(i, 0, m) {
        int c = t[i] - '0';
        if (!ch[q][c]) {
            ch[q][c] = ++tot;
            fa[tot] = q;
            ch[tot][0] = ch[tot][1] = sum1[tot] = sum2[tot] = sz[tot] = ed[tot] = 0;
        }
        q = ch[q][c];
    }

    ll v1 = sum1[p];
    int v2 = sz[p];

    int tp = p, tq = q;

    p = fa[p];
    while(p != 0) {
        sum1[p] -= v1;
        sz[p] -= v2;
        p = fa[p];
    }
    ch[fa[tp]][s[n - 1] - '0'] = 0;

    fa[tp] = fa[tq];

    q = fa[tp];
    while(q != 0) {
        sum1[q] += v1;
        sz[q] += v2;
        q = fa[q];
    }

    __U(tp, tq);
}

char op[5], s[N], t[N];
int n;
ll v;
void solve(int Case) { // printf("Case #%d: ", Case);
    printf("Case %d\n", Case);

    tot = ch[0][0] = ch[0][1] = sum1[0] = sum2[0] = sz[0] = ed[0] = 0;

    scanf("%d", &n);
    REP(i, 0, n) {
        scanf("%s", op);
        scanf("%s", s);
        
        if (op[0] == 'I') {
            scanf("%lld", &v);
            I(s, v);
        } else if (op[0] == 'D') {
            D(s);
        } else if (op[0] == 'Q') {
            printf("%lld\n", Q(s));
        } else if (op[0] == 'U') {
            scanf("%s", t);
            U(s, t);
        }
    }
}
 
int main()
{
#ifdef BACKLIGHT
    freopen("in.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T = 1;
    cin >> T;
    for (int _ = 1; _ <= T; _++) solve(_);
    return 0;
}