#include <bits/stdc++.h>
using namespace std;
#ifdef BACKLIGHT
#include "debug.h"
#else
#define debug(...)
#endif

const int N = 1e5 + 5;

int n, a[N];
void solve(int Case)
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    sort(a + 1, a + 1 + n);
    int64_t sum = 0;
    for (int i = 1; i <= n; ++i) sum += a[i];
    double ans = 1.0 * (sum - a[n]) / (n - 1) + a[n];
    printf("%.10f\n", ans);
}

int main()
{
#ifdef BACKLIGHT
    freopen("a.in", "r", stdin);
#endif
    int T = 1;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) solve(t);
    return 0;
}