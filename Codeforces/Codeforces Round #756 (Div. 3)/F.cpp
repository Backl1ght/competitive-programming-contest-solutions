// Problem: F. ATM and Students
// Contest: Codeforces - Codeforces Round #756 (Div. 3)
// URL: https://codeforces.com/contest/1611/problem/F
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

#define CPPIO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

using i64 = int64_t;
using u64 = uint64_t;

void solve_case(int Case);

int main() {
  CPPIO;
  int T = 1;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

const int N = 2e5 + 5;
int n;
i64 s, a[N], p[N];

i64 mi[N << 2];
void build(int x, int l, int r) {
  if (l == r) {
    mi[x] = p[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(x << 1, l, mid);
  build(x << 1 | 1, mid + 1, r);
  mi[x] = min(mi[x << 1], mi[x << 1 | 1]);
}
i64 getMin(int x, int l, int r, int L, int R) {
  if (l == L && r == R) return mi[x];
  int mid = (l + r) >> 1;
  if (R <= mid)
    return getMin(x << 1, l, mid, L, R);
  else if (L > mid)
    return getMin(x << 1 | 1, mid + 1, r, L, R);
  return min(getMin(x << 1, l, mid, L, mid),
             getMin(x << 1 | 1, mid + 1, r, mid + 1, R));
}

void solve_case(int Case) {
  cin >> n >> s;
  
  for (int i = 1; i <= n; ++i) cin >> a[i], p[i] = p[i - 1] + a[i];

  build(1, 1, n);

  int L = -1, R = -2;
  for (int i = 1; i <= n; ++i) {
    int l = i, r = n, mid, j = i - 1;
    while (l <= r) {
      mid = (l + r) >> 1;
      if (s + getMin(1, 1, n, i, mid) - p[i - 1] >= 0)
        l = mid + 1, j = mid;
      else
        r = mid - 1;
    }
    if (j - i > R - L) {
      L = i;
      R = j;
    }
  }
  if (L == -1)
    cout << "-1\n";
  else
    cout << L << " " << R << "\n";
}