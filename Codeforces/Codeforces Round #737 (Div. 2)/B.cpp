#include <bits/stdc++.h>
using namespace std;
#ifdef BACKLIGHT
#include "debug.h"
#else
#define debug(...)
#endif

const int N = 1e5 + 5;

int n, k, a[N], b[N];
void solve(int Case)
{
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i) b[i] = a[i];
    sort(b + 1, b + 1 + n);

    for (int i = 1; i <= n; ++i) a[i] = lower_bound(b + 1, b + 1 + n, a[i]) - b;

    int sz = 0;
    for (int i = 1; i <= n; ++i)
    {
        int j = i;
        while (j + 1 <= n && a[j + 1] == a[j] + 1) ++j;
        ++sz;
        i = j;
    }

    puts(sz <= k ? "Yes" : "No");
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