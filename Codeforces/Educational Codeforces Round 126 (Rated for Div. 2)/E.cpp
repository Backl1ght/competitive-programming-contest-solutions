// Problem: E. Narrow Components
// Contest: Codeforces - Educational Codeforces Round 126 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1661/problem/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO \
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#endif

#ifdef BACKLIGHT
#define debug(a, l, r)                            \
  {                                               \
    std::string res = "[";                        \
    for (size_t i = l; i <= r; ++i)               \
      res += std::to_string(a[i]) + ",]"[i == r]; \
    std::cerr << res << std::endl;                \
  }

#else
#define debug(...) ;
#endif

using i64 = int64_t;
using u64 = uint64_t;

void solve_case(int Case);

int main() {
  CPPIO;
  int T = 1;
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

const int N = 5e5 + 5;
const int M = 4;
int n, m = 3, q, a[M][N];

int f[N * M];
int leader(int x) {
  if (x == -1)
    return -1;
  return x == f[x] ? x : (f[x] = leader(f[x]));
}
bool merge(int x, int y) {
  x = leader(x), y = leader(y);
  if (x == y)
    return false;
  f[x] = y;
  return true;
}

struct node {
  int ans;

  int lmask[M];
  int rmask[M];

  node() {}

  node(int p) {
    for (int i = 1; i <= m; ++i) {
      lmask[i] = a[i][p];
    }
    if (lmask[2] != -1) {
      ans = 1;
      if (lmask[1] != -1)
        lmask[1] = lmask[2];
      if (lmask[3] != -1)
        lmask[3] = lmask[2];
    } else {
      ans = (lmask[1] != -1) + (lmask[3] != -1);
    }
    for (int i = 1; i <= m; ++i)
      rmask[i] = lmask[i];
  }

  friend node operator+(const node& a, const node& b) {
    node c;
    c.ans = a.ans + b.ans;

    logd(a.ans, b.ans, c.ans);
    debug(a.lmask, 1, 3);
    debug(a.rmask, 1, 3);
    debug(b.lmask, 1, 3);
    debug(b.rmask, 1, 3);

    for (int i = 1; i <= m; ++i) {
      f[a.lmask[i]] = a.lmask[i];
      f[a.rmask[i]] = a.rmask[i];
      f[b.lmask[i]] = b.lmask[i];
      f[b.rmask[i]] = b.rmask[i];
    }
    for (int i = 1; i <= m; ++i) {
      if (a.rmask[i] == -1 || b.lmask[i] == -1)
        continue;
      if (merge(a.rmask[i], b.lmask[i])) {
        --c.ans;
      }
    }
    for (int i = 1; i <= m; ++i) {
      c.lmask[i] = leader(a.lmask[i]);
      c.rmask[i] = leader(b.rmask[i]);
    }

    logd(a.ans, b.ans, c.ans);
    debug(c.lmask, 1, 3);
    debug(c.rmask, 1, 3);

    return c;
  }
};

node t[N << 2];
void build(int x, int l, int r) {
  if (l == r) {
    t[x] = node(l);
    return;
  }
  int mid = (l + r) >> 1;
  build(x << 1, l, mid);
  build(x << 1 | 1, mid + 1, r);
  t[x] = t[x << 1] + t[x << 1 | 1];
}

node query(int x, int l, int r, int L, int R) {
  if (l == L && r == R)
    return t[x];
  int mid = (l + r) >> 1;
  if (R <= mid)
    return query(x << 1, l, mid, L, R);
  else if (L > mid)
    return query(x << 1 | 1, mid + 1, r, L, R);
  return query(x << 1, l, mid, L, mid) +
         query(x << 1 | 1, mid + 1, r, mid + 1, R);
}

void solve_case(int Case) {
  std::cin >> n;

  std::string s;
  for (int i = 1; i <= m; ++i) {
    std::cin >> s;
    for (int j = 0; j < n; ++j) {
      if (s[j] == '0') {
        a[i][j + 1] = -1;
      } else {
        a[i][j + 1] = (i - 1) * n + j + 1;
      }
    }
  }

  build(1, 1, n);

  std::cin >> q;
  for (int _ = 1; _ <= q; ++_) {
    int l, r;
    std::cin >> l >> r;
    logd(l, r);
    node nd = query(1, 1, n, l, r);
    std::cout << nd.ans << "\n";
  }
}