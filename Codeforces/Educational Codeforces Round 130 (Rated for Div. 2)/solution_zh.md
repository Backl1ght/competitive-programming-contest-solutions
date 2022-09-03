# Educational Codeforces Round 130 (Rated for Div. 2)

## [A. Parkway Walk](https://codeforces.com/contest/1697/problem/A)

如果能量不足就补充至恰好足够，然后模拟。

## [B. Promo](https://codeforces.com/contest/1697/problem/B)

易得：选最贵的$x$个商品最优。

然后排序加前缀和优化就可以$O(n\log n) \sim O(1)$做。

## [C. awoo's Favorite Problem](https://codeforces.com/contest/1697/problem/C)

从左至右遍历$s$，假设遍历到$i$，如果$s_i \ne t_i$，尝试用给定操作救一下，救不了就无解。

操作1能来救：$s_i$是`b`,$t_i$是`a`，且$s$中当前位置到下一个$a$中间这段全都是`b`的情况。

操作2类似。

对于每种字符拿个`std::set`存字符出现的位置，然后模拟。

## [D. Guess The String](https://codeforces.com/contest/1697/problem/D)

<details>
<summary>题意</summary>

交互题。

有一个长度为$n$的串$s$。

支持两种操作：
1. `1 i`: 返回$s_i$。
2. `2 l r`：返回$s_l\dots s_r$中不同字符的个数。

要求通过不超过$26$次操作1和不超过$6000$次操作2猜出$s$。

其中$1 \le n \le 1000$。

</details>

<details>
<summary>思路</summary>

这题不难其实，就是调代码调了40min，还WA 3了一发。。。

从左至右依次猜每个位置上的字符是什么。

维护每个字符最后出现的位置。将这些位置升序排序，不妨记为$p_i, 1\le i \le k$。对于其中一个位置$p_i$，如果$s_i$没有在$s_{p_i}\dots s_i$中出现过，那么这一段中不同字符的个数为$1 + k - i + 1$，否则为$k - i + 1$。

假设$y$等于满足$s_{p_x}\dots s_i$中不同字符个数等于$k - x + 1$的最大的$x$，那么$s_i = s_y$。

如果没有满足条件的$x$就说明$s_i$之前没有出现过，用操作1确定。

容易看出这个是有单调性的，可以通过二分找$y$或者确定没有满足条件的$x$。

只有$s_i$之前没有出现过才会用操作1确定，所以操作1至多用26次。

对于$s_i$，每个位置$O(\log |\Sigma|) \le 6$次，所以操作2至多用$6n \le 6000$次。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: D. Guess The String
// Contest: Codeforces - Educational Codeforces Round 130 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1697/problem/D
// Memory Limit: 512 MB
// Time Limit: 4000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
#define freep(p) p ? delete p, p = nullptr, void(1) : void(0)

#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#endif

using i64 = int64_t;
using u64 = uint64_t;

void solve_case(int Case);

int main(int argc, char* argv[]) {
  CPPIO;
  int T = 1;
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

std::mt19937 rng(time(0));

void solve_case(int Case) {
  int n;

#ifdef BACKLIGHT
  n = 1000;
  std::string t(n + 1, '?');
  for (int i = 1; i <= n; ++i) {
    t[i] = rng() % 26 + 'a';
  }
  logd(t);

  auto Q1 = [&t](int x) -> char {
    ++x;
    return t[x];
  };

  auto Q2 = [&t](int l, int r) -> int {
    ++l, ++r;
    std::set<char> st;
    for (int i = l; i <= r; ++i) {
      st.insert(t[i]);
    }
    return st.size();
  };

#else
  auto Q1 = [](int x) -> char {
    ++x;
    std::cout << "? 1 " << x << std::endl;
    char r;
    std::cin >> r;
    return r;
  };

  auto Q2 = [](int l, int r) -> int {
    ++l, ++r;
    std::cout << "? 2 " << l << " " << r << std::endl;
    int t;
    std::cin >> t;
    return t;
  };

  std::cin >> n;
#endif

  std::string s(n, '?');
  std::vector<int> p(26, -1);

  s[0] = Q1(0);
  p[s[0] - 'a'] = 0;
  for (int i = 1; i < n; ++i) {
    std::vector<int> q;
    for (int i = 0; i < 26; ++i) {
      if (p[i] != -1) {
        q.push_back(p[i]);
      }
    }
    std::sort(q.begin(), q.end());

    int z = -1;
    {
      // logd(q);
      int l = 0, r = q.size() - 1, mid;
      while (l <= r) {
        mid = (l + r) >> 1;

        int x = q.size() - mid + 1;
        int y = Q2(q[mid], i);
        // logd(mid, x, y);
        if (y == x)
          r = mid - 1;
        else
          l = mid + 1, z = q[mid];
      }
    }
    if (z == -1) {
      s[i] = Q1(i);
    } else {
      s[i] = s[z];
    }
    // logd(i, s[i], z);
    p[s[i] - 'a'] = i;
  }
  std::cout << "! " << s << "\n";

#ifdef BACKLIGHT
  logd(s, t);
  for (int i = 0; i < n; ++i) {
    if (s[i] != t[i + 1]) {
      logd(i, s[i], t[i + 1]);
    }
  }
  assert(s == t.substr(1));
#endif
}
```

</details>

## [E. Coloring](https://codeforces.com/contest/1697/problem/E)

<details>
<summary>题意</summary>

二维空间中有$n$个点，点与点之间的距离定义为曼哈顿距离。要用$n$种颜色给点染色。

令$d(i, j)$表示$i, j$两点间距离，有以下两个限制：
1. 如果点$a, b, c$同色，那么有$d(a, b) = d(b, c) = d(c, a)$。
2. 如果点$a, b$同色，$c$与$a, b$异色，那么有$d(a, b) < d(a, c)$且$d(a, b) < d(b, c)$。

问染色方案数，答案对$998244353$取模。

其中$2 \le n \le 100$。

</details>

<details>
<summary>思路</summary>

如果点$i$能够与点$j$同色，那么根据题意一定没有$k$使得$d(i, k) < d(i, j)$或者$d(j, k) < d(i, j)$成立。

如果在能够同色的点对间连一条边，这样建出的图会是由多个极大团组成的，且一个极大团中的点要么全部同色，要么全部异色。

根据这一点就可以DP算答案了，感觉不复杂。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: E. Coloring
// Contest: Codeforces - Educational Codeforces Round 130 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1697/problem/E
// Memory Limit: 512 MB
// Time Limit: 3000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
#define freep(p) p ? delete p, p = nullptr, void(1) : void(0)

#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#endif

using i64 = int64_t;
using u64 = uint64_t;

void solve_case(int Case);

int main(int argc, char* argv[]) {
  CPPIO;
  int T = 1;
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

const int MOD = 998244353;
int add(int x, int y) {
  return x + y >= MOD ? x + y - MOD : x + y;
}
int mul(int x, int y) {
  return i64(1) * x * y % MOD;
}
int sub(int x, int y) {
  return x - y < 0 ? x - y + MOD : x - y;
}
int qp(int x, int y) {
  int r = 1;
  while (y) {
    if (y & 1)
      r = mul(r, x);
    x = mul(x, x);
    y >>= 1;
  }
  return r;
}
int inv(int x) {
  return qp(x, MOD - 2);
}
int dvd(int x, int y) {
  return mul(x, inv(y));
}

const int N = 105;
int f[N], g[N];
void init(int n) {
  f[0] = 1;
  for (int i = 1; i <= n; ++i)
    f[i] = mul(f[i - 1], i);
  g[n] = inv(f[n]);
  for (int i = n - 1; i >= 0; --i)
    g[i] = mul(g[i + 1], i + 1);
}
int C(int n, int m) {
  return mul(f[n], mul(g[m], g[n - m]));
}

void solve_case(int Case) {
  int n;
  std::cin >> n;
  init(n);

  std::vector<int> x(n), y(n);
  for (int i = 0; i < n; ++i)
    std::cin >> x[i] >> y[i];

  auto manhattan = [&](int a, int b) -> int {
    return std::abs(x[a] - x[b]) + std::abs(y[a] - y[b]);
  };

  std::vector<int> min_dist(n, INT_MAX);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (j == i)
        continue;
      min_dist[i] = std::min(min_dist[i], manhattan(i, j));
    }
  }

  std::vector<std::vector<int>> a(n);
  for (int i = 0; i < n; ++i) {
    a[i].push_back(i);
    for (int j = 0; j < n; ++j) {
      if (j == i)
        continue;
      if (manhattan(i, j) == min_dist[i])
        a[i].push_back(j);
    }
    std::sort(a[i].begin(), a[i].end());
  }
  std::sort(a.begin(), a.end());

  // dp_i means the number of ways that coloring these n points with exatly i different colors
  std::vector<int> dp(n + 1, 0);
  dp[0] = 1;
  for (int i = 0; i < n; ++i) {
    int j = i;
    while (j + 1 < n && a[i] == a[j + 1])
      ++j;

    std::vector<int> next(n + 1, 0);

    // find a maximal clique of size m
    int m = j - i + 1;
    if ((int)a[i].size() != j - i + 1)
      m = 1;

    // m points with the same color
    for (int i = 0; i + 1 <= n; ++i) {
      // there are n - i ways to choose one color
      next[i + 1] = add(next[i + 1], mul(dp[i], n - i));
    }

    // or every pair of points with different colors
    if (m > 1) {
      for (int i = 0; i + m <= n; ++i) {
        // there are \binom{n - i}{m} ways to choose m colors
        // and there are m! ways to distribute these color to points
        next[i + m] = add(next[i + m], mul(dp[i], mul(C(n - i, m), f[m])));
      }
    }

    dp = next;
    i = i + m - 1;
  }

  int ans = 0;
  for (int i = 1; i <= n; ++i)
    ans = add(ans, dp[i]);

  std::cout << ans << "\n";
}

```

</details>

## [F. Too Many Constraints](https://codeforces.com/contest/1697/problem/F)

<details>
<summary>题意</summary>

给定一个长度为 $n$ 的数组$a$，有两个基本的限制：
1. $a_i \in [1, k]$。
2. $\forall i \in [1, n - 1], a_i \le a_{i+1}$。

再给出 $m$ 个额外的限制，有三种类型：
1. $a_i \ne x$。
2. $a_i + a_j \le x$。
3. $a_i + a_j \ge x$。

给出一种满足所有类型的方案，或者说明无解。

其中 $2 \le n \le 2 \times {10}^4,  0 \le m \le 2 \times {10}^4, 2 \le k \le 10$。 

</details>

<details>
<summary>思路</summary>

只判断是否有解的话可以用 2-SAT ，就 $a_i = x$ 和 $a_i \ne x$ 要满足一个。

但是这样子没办法输出方案，因为这样子可能会有多选一，但是 2-SAT 只能支持二选一。

可以把条件改成 $a_i \le x$ 和 $a_i > x$ ，然后因为 $a_i \le x$ 可以推出 $a_i \le x + 1$，所以随着 $x$ 的增加， $a_i \le x$ 会是一段不成立，接一段成立。然后输出方案的时候选择第一个成立的那个 $x$ 即可。

为了减少边界讨论，扩展 $a_i$ 的值域到 $[0, k]$，然后通过建图限制 $a_i > 0$ 。

然后就是 2-SAT 板子了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: F. Too Many Constraints
// Contest: Codeforces - Educational Codeforces Round 130 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1697/problem/F
// Memory Limit: 512 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
#define freep(p) p ? delete p, p = nullptr, void(1) : void(0)

#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#define ASSERT(x) ;
#endif

using i64 = int64_t;
using u64 = uint64_t;

void solve_case(int Case);

int main(int argc, char* argv[]) {
  CPPIO;
  int T = 1;
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

class TwoSAT {
 private:
 public:
  TwoSAT(int n) : n_(n), g_(2 * n_), r_(2 * n_) {}

  int ID(int x, int y) {
    ASSERT(0 <= x && x < n_);
    ASSERT(y == 0 || y == 1);

    return 2 * x + y;
  }

  void Either(int x, int y) {
    g_[x ^ 1].push_back(y);
    r_[y].push_back(x ^ 1);

    g_[y ^ 1].push_back(x);
    r_[x].push_back(y ^ 1);
  }

  void Implies(int x, int y) { Either(x ^ 1, y); }

  void Must(int x) { Either(x, x); }

  std::pair<bool, std::vector<int>> Solve() {
    int dfs_clock = 0;
    std::vector<bool> vis(2 * n_, false);
    std::vector<int> dfn(2 * n_, -1);
    std::function<void(int)> dfs1 = [&](int u) {
      vis[u] = true;
      for (int v : g_[u]) {
        if (vis[v] == false) {
          dfs1(v);
        }
      }
      dfn[dfs_clock++] = u;
    };
    for (int i = 0; i < 2 * n_; ++i) {
      if (!vis[i]) {
        dfs1(i);
      }
    }

    int c = 0;
    std::vector<int> color(2 * n_, -1);
    std::function<void(int)> dfs2 = [&](int u) {
      color[u] = c;
      for (int v : r_[u]) {
        if (color[v] == -1) {
          dfs2(v);
        }
      }
    };
    for (int i = 2 * n_ - 1; i >= 0; --i) {
      int u = dfn[i];
      if (color[u] == -1) {
        dfs2(u);
        c++;
      }
    }

    for (int i = 0; i < n_; ++i) {
      if (color[2 * i] == color[2 * i + 1]) {
        return {false, {}};
      }
    }

    std::vector<int> values(n_, false);
    for (int i = 0; i < n_; ++i) {
      values[i] = color[2 * i] < color[2 * i + 1];
    }

    return {true, values};
  }

 private:
  int n_;
  std::vector<std::vector<int>> g_, r_;
};

void solve_case(int Case) {
  int n, m, k;
  std::cin >> n >> m >> k;

  // represent a_p <= v.
  auto id = [&](int p, int v) {
    ASSERT(0 <= p && p < n);
    ASSERT(0 <= v && v <= k);

    return p * (k + 1) + v;
  };

  TwoSAT sat(n * (k + 1));

  // basic constraints
  {
    // a_i > 0 must be true.
    for (int i = 0; i < n; ++i)
      sat.Must(sat.ID(id(i, 0), 0));

    // a_i <= k must be true.
    for (int i = 0; i < n; ++i)
      sat.Must(sat.ID(id(i, k), 1));

    // a_i <= x --> a_i <= x + 1.
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j <= k - 1; ++j)
        sat.Implies(sat.ID(id(i, j), 1), sat.ID(id(i, j + 1), 1));
    }

    // a should be non-decreasing. That is, a_i > x --> a_{i+1} > x.
    for (int i = 0; i + 1 < n; ++i) {
      for (int j = 0; j <= k; ++j) {
        sat.Implies(sat.ID(id(i, j), 0), sat.ID(id(i + 1, j), 0));
      }
    }
  }

  // additional constraints
  for (int _ = 0; _ < m; ++_) {
    int tp;
    std::cin >> tp;
    if (tp == 1) {
      int i, x;
      std::cin >> i >> x;
      --i;

      // a_i != x --> a_i <= x - 1 or a_i > x
      sat.Either(sat.ID(id(i, x - 1), 1), sat.ID(id(i, x), 0));
    } else if (tp == 2) {
      int i, j, x;
      std::cin >> i >> j >> x;
      --i, --j;

      // a_i + a_j <= x, a_i > y --> a_j < x - y --> a_j <= x - y - 1.
      for (int y = 0; y <= k; ++y) {
        int z = x - y - 1;
        if (z >= 0 && z <= k) {
          sat.Implies(sat.ID(id(i, y), 0), sat.ID(id(j, z), 1));
        }
      }
    } else if (tp == 3) {
      int i, j, x;
      std::cin >> i >> j >> x;
      --i, --j;

      // a_i + a_j >= x, a_i <= y --> a_j >= x - y --> a_j > x - y - 1
      for (int y = 1; y <= k; ++y) {
        int z = x - y - 1;
        if (z >= 0 && z <= k)
          sat.Implies(sat.ID(id(i, y), 1), sat.ID(id(j, z), 0));
      }
    }
  }

  auto [valid, values] = sat.Solve();
  if (!valid) {
    std::cout << "-1\n";
  } else {
    std::vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 1; j <= k; ++j) {
        if (values[id(i, j)]) {
          ans[i] = j;
          break;
        }
      }
    }
    for (int i = 0; i < n; ++i)
      std::cout << ans[i] << " \n"[i + 1 == n];
  }
}
```

</details>