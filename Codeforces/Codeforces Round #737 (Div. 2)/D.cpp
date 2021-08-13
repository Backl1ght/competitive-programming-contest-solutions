#include <bits/stdc++.h>
using namespace std;
#ifdef BACKLIGHT
#include "debug.h"
#else
#define debug(...)
#endif

const int N = 3e5 + 5;

using PII = pair<int, int>;

PII PII_MIN = PII(INT_MIN, INT_MIN);
PII ma[N << 3], tag[N << 3];
void change(int x, PII v)
{
    ma[x] = max(ma[x], v);
    tag[x] = max(tag[x], v);
}
void push_down(int x)
{
    if (tag[x] != PII_MIN)
    {
        change(x << 1, tag[x]);
        change(x << 1 | 1, tag[x]);
        tag[x] = PII_MIN;
    }
}
void push_up(int x) { ma[x] = max(ma[x << 1], ma[x << 1 | 1]); }
void build(int x, int l, int r)
{
    tag[x] = PII_MIN;
    if (l == r)
    {
        ma[x] = PII(0, 0);
        return;
    }
    int mid = (l + r) >> 1;
    build(x << 1, l, mid);
    build(x << 1 | 1, mid + 1, r);
    push_up(x);
}
void update(int x, int l, int r, int L, int R, PII v)
{
    if (l == L && r == R)
    {
        change(x, v);
        return;
    }
    push_down(x);
    int mid = (l + r) >> 1;
    if (R <= mid)
        update(x << 1, l, mid, L, R, v);
    else if (L > mid)
        update(x << 1 | 1, mid + 1, r, L, R, v);
    else
    {
        update(x << 1, l, mid, L, mid, v);
        update(x << 1 | 1, mid + 1, r, mid + 1, R, v);
    }
    push_up(x);
}
PII query(int x, int l, int r, int L, int R)
{
    if (l == L && r == R)
        return ma[x];
    push_down(x);
    int mid = (l + r) >> 1;
    if (R <= mid)
        return query(x << 1, l, mid, L, R);
    else if (L > mid)
        return query(x << 1 | 1, mid + 1, r, L, R);
    return max(query(x << 1, l, mid, L, mid),
               query(x << 1 | 1, mid + 1, r, mid + 1, R));
}

int n, m;
int nt, t[N << 1], pre[N];
bool vis[N];
vector<PII> s[N];
void solve(int Case)
{
    scanf("%d %d", &n, &m);
    int x, l, r;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d %d %d", &x, &l, &r);
        s[x].push_back(PII(l, r));
        t[++nt] = l;
        t[++nt] = r;
    }
    sort(t + 1, t + 1 + nt);
    nt = unique(t + 1, t + 1 + nt) - (t + 1);

    for (int i = 1; i <= n; ++i)
    {
        for (PII &p : s[i])
        {
            debug(p);
            p.first = lower_bound(t + 1, t + 1 + nt, p.first) - t;
            p.second = lower_bound(t + 1, t + 1 + nt, p.second) - t;
            debug(p);
        }
    }

    build(1, 1, n);
    for (int i = 1; i <= n; ++i)
    {
        PII mx = PII_MIN;
        for (PII p : s[i]) mx = max(mx, query(1, 1, nt, p.first, p.second));

        pre[i] = mx.second;
        debug(i, mx);
        mx = PII(mx.first + 1, i);
        debug(i, mx);

        for (PII p : s[i]) update(1, 1, nt, p.first, p.second, mx);
    }
    PII mx = ma[1];
    debug(mx);

    int p = mx.second;
    while (p) vis[p] = true, p = pre[p];

    printf("%d\n", n - mx.first);
    for (int i = 1; i <= n; ++i)
        if (!vis[i])
            printf("%d ", i);
}

int main()
{
#ifdef BACKLIGHT
    freopen("a.in", "r", stdin);
#endif
    int T = 1;
    // scanf("%d", &T);
    for (int t = 1; t <= T; ++t) solve(t);
    return 0;
}