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
typedef double db;
typedef pair<int,int> PI;
typedef vector<int> VI;

#define rep(i,_,__) for (int i=_;i<=__;++i)
#define per(i,_,__) for (int i=_;i>= __;--i)
#define fore(u) for (int i=head[u];i;i=e[i].nxt)

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define x1 _x
#define x2 __x
#define y1 _y
#define y2 __y
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define endl '\n'
  
const double pi=acos(-1.0);
  
namespace IO{
    bool REOF = 1; //为0表示文件结尾
    inline char nc() {
        static char buf[100000], *p1 = buf, *p2 = buf;
        return p1 == p2 && REOF && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? (REOF = 0, EOF) : *p1++;
    }
  
    template<class T>
    inline bool read(T &x) {
        char c = nc();bool f = 0; x = 0;
        while (c<'0' || c>'9')c == '-' && (f = 1), c = nc();
        while (c >= '0'&&c <= '9')x = (x << 3) + (x << 1) + (c ^ 48), c = nc();
        if(f)x=-x;
        return REOF;
    }

    template<class T>
    inline void write(T x){
        while(x){
            putchar('0'+x%10);
            x/=10;
        }
    }
  
    template<typename T, typename... T2>
    inline bool read(T &x, T2 &... rest) {
        read(x);
        return read(rest...);
    }
  
  
    inline bool need(char &c) { return ((c >= 'a') && (c <= 'z')) || ((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'Z')); }
    // inline bool need(char &c) { return ((c >= 'a') && (c <= 'z')) || ((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'Z')) || c==' '; }
  
    inline bool read_str(char *a) {
        while ((*a = nc()) && need(*a) && REOF)++a; *a = '\0';
        return REOF;
    }
  
    inline bool read_dbl(double &x){
        bool f = 0; char ch = nc(); x = 0;
        while(ch<'0'||ch>'9')  {f|=(ch=='-');ch=nc();}
        while(ch>='0'&&ch<='9'){x=x*10.0+(ch^48);ch=nc();}
        if(ch == '.') {
            double tmp = 1; ch = nc();
            while(ch>='0'&&ch<='9'){tmp=tmp/10.0;x=x+tmp*(ch^48);ch=nc();}
        }
        if(f)x=-x;
        return REOF;
    }
  
    template<class TH> void _dbg(const char *sdbg, TH h){ cerr<<sdbg<<'='<<h<<endl; }
  
    template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
        while(*sdbg!=',')cerr<<*sdbg++;
        cerr<<'='<<h<<','<<' '; _dbg(sdbg+1, a...);
    }
     
    template<class T> ostream &operator<<(ostream& os, vector<T> V) {
        os << "["; for (auto vv : V) os << vv << ","; return os << "]";
    }
  
    template<class T> ostream &operator<<(ostream& os, set<T> V) {
        os << "["; for (auto vv : V) os << vv << ","; return os << "]";
    }

    template<class T> ostream &operator<<(ostream& os, map<T,T> V) {
        os << "["; for (auto vv : V) os << vv << ","; return os << "]";
    }
 
    template<class L, class R> ostream &operator<<(ostream &os, pair<L,R> P) {
        return os << "(" << P.x << "," << P.y << ")";
    }
     
    #define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
}

using namespace IO;
const int maxn = 1e5 + 5;
const int maxv = 1e6 + 5;
const int mod = 1e9+7;  // 998244353 1e9+7
const int INF = 0x3f3f3f3f; // 1e9+7 0x3f3f3f3f
const ll LLINF = 0x3f3f3f3f3f3f3f3f; // 1e18+9 0x3f3f3f3f3f3f3f3f
const double eps = 1e-12;

int dx[4] = { 0, 1, 0, -1 };
// int dx[8] = { 1, 0, -1, 1, -1, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };
// int dy[8] = { 1, 1, 1, 0, 0, -1, -1, -1 };

// ll qp(ll a, ll b) { 
//     ll res = 1;
//     a %= mod;
//     assert(b >= 0);
//     while(b){
//         if(b&1)
//             res = res * a % mod;
//         a = a * a % mod;
//         b >>= 1;
//     }
//     return res;
// }

// #define ls (x<<1)
// #define rs (x<<1|1)
// #define mid ((l+r)>>1)
// #define lson ls,l,mid
// #define rson rs,mid+1,r

// int tot = 1, head[maxv];
// struct Edge{
// 	int v,nxt;
//     Edge(){}
//     Edge(int _v,int _nxt):v(_v),nxt(_nxt){}
// } e[maxv << 1];
// void init(){
//     tot = 1;
//     memset(head, 0, sizeof(head));
// }
// inline void addarc(int u,int v){
//     e[tot] = Edge(v, head[u]);
//     head[u] = tot++;
// }
// inline void addedge(int u,int v){
//     addarc(u, v);
//     addarc(v, u);
// }
  
/**
 * **********     Backlight     **********
 * 仔细读题
 * 注意边界条件
 * 记得注释输入流重定向
 * 没有思路就试试逆向思维
 * 加油，奥利给
 */

int n, a[maxn], b;

void solve(int Case) {
    int ans=0;

    read(n, b);
    rep(i, 1, n) read(a[i]);
    sort(a+1, a+1+n);

    rep(i, 1, n) {
        if(b>=a[i]) {
            b-=a[i];
            ans++;
        }
    }

    printf("Case #%d: %d\n", Case, ans);
}
 
int main()
{
    // freopen("in.txt", "r", stdin);
    // ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int _T; read(_T); for (int _ = 1; _ <= _T; _++) solve(_);
    // int _T=1; while(read(n)) solve(_T), _T++;
    // solve(1);
    return 0;
}