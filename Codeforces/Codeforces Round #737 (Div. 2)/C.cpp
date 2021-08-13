#include <bits/stdc++.h>
using namespace std;
#ifdef BACKLIGHT
#include "debug.h"
#else
#define debug(...)
#endif

const int MOD = 1e9 + 7;  // 998244353 1e9 + 7
const int MAXN = 2e5 + 5;
template <typename T>
inline int mint(T x)
{
    x %= MOD;
    if (x < 0)
        x += MOD;
    return x;
}
inline int add(int x, int y) { return x + y >= MOD ? x + y - MOD : x + y; }
inline int mul(int x, int y) { return 1ll * x * y % MOD; }
inline int sub(int x, int y) { return x < y ? x - y + MOD : x - y; }
inline int qp(int x, int y)
{
    int r = 1;
    for (; y; y >>= 1)
    {
        if (y & 1)
            r = mul(r, x);
        x = mul(x, x);
    }
    return r;
}
inline int inv(int x) { return qp(x, MOD - 2); }
inline int dvd(int x, int y) { return 1ll * x * qp(y, MOD - 2) % MOD; }
inline void inc(int &x, int y)
{
    x += y;
    if (x >= MOD)
        x -= MOD;
}
inline void dec(int &x, int y)
{
    x -= y;
    if (x < 0)
        x += MOD;
}
int f[MAXN], g[MAXN];
inline void initC(int n = MAXN - 1)
{
    assert(n < MAXN);
    f[0] = 1;
    for (int i = 1; i <= n; ++i) f[i] = mul(f[i - 1], i);
    g[n] = inv(f[n]);
    for (int i = n - 1; i >= 0; --i) g[i] = mul(g[i + 1], i + 1);
}
inline int C(int n, int m)
{
    if (m < 0 || m > n)
        return 0;
    return mul(f[n], mul(g[m], g[n - m]));
}

int dp[MAXN][2];
void solve(int Case)
{
    int n, k;
    scanf("%d %d", &n, &k);
    dp[0][0] = 1;
    dp[0][1] = 0;

    int f = n % 2;
    for (int i = 0; i < n; i += 2) f = add(f, C(n, i));
    int g = qp(2, n);

    debug(f, g);

    for (int i = 1; i <= k; ++i)
    {
        dp[i][0] = mul(dp[i - 1][0], f);
        dp[i][1] = (n & 1) ? 0 : dp[i - 1][0];
        dp[i][1] = add(dp[i][1], mul(dp[i - 1][1], g));
        debug(dp[i][0], dp[i][1]);
    }
    int ans = add(dp[k][0], dp[k][1]);
    printf("%d\n", ans);
}

int main()
{
#ifdef BACKLIGHT
    freopen("a.in", "r", stdin);
#endif
    initC();
    int T = 1;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) solve(t);
    return 0;
}