# AtCoder Beginner Contest 266

咕咕咕咕。

## [E - Throwing the Die](https://atcoder.jp/contests/abc266/tasks/abc266_e)

注意到如果对当前的结果不满意然后重开的话，后面的结果和当前结果是没有关系的。

假设已经算出了有 $n$ 次机会时的期望得分 $E_n$。

那么还剩 $n + 1$ 次机会的时候，摇了一次结果为 $X$，还剩下 $n$ 次机会。如果 $E_n > X$，那么就继续玩；反之则直接结束游戏。

然后 $E_0 = 0$，这样子就可以直接递推算了。

<details>
<summary>AC代码</summary>

```cpp
// Problem: E - Throwing the Die
// Contest: AtCoder - AtCoder Beginner Contest 266
// URL: https://atcoder.jp/contests/abc266/tasks/abc266_e
// Memory Limit: 1024 MB
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
#define serialize() ""
#endif

using i64 = int64_t;
using u64 = uint64_t;

void Initialize();
void SolveCase(int Case);

int main(int argc, char* argv[]) {
  CPPIO;
  int T = 1;
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    SolveCase(t);
  }
  return 0;
}

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  double e = 0;
  for (int i = 1; i <= n; ++i) {
    double ne = 0;
    for (int j = 1; j <= 6; ++j) {
      if (j < e) {
        ne = ne + e / 6.0;
      } else {
        ne = ne + j / 6.0;
      }
    }
    e = ne;
  }
  std::cout << std::fixed << std::setprecision(12) << e << "\n";
}

```

</details>

## [F - Well-defined Path Queries on a Namori](https://atcoder.jp/contests/abc266/tasks/abc266_f)

询问相当于只能走桥边时两点是否连通，然后tarjan跑出桥边，再并查集维护连通性即可。

<details>
<summary>AC代码</summary>

```cpp
// Problem: F - Well-defined Path Queries on a Namori
// Contest: AtCoder - AtCoder Beginner Contest 266
// URL: https://atcoder.jp/contests/abc266/tasks/abc266_f
// Memory Limit: 1024 MB
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
#define ASSERT(x) ;
#define serialize() ""
#endif

using i64 = int64_t;
using u64 = uint64_t;

void Initialize();
void SolveCase(int Case);

int main(int argc, char* argv[]) {
  CPPIO;
  int T = 1;
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    SolveCase(t);
  }
  return 0;
}

void Initialize() {}

std::vector<std::pair<int, int>> EdgeBCC(const std::vector<std::vector<int>>& g) {
  int n = g.size();

  std::vector<std::pair<int, int>> bridges;

  int dfs_clock = 0;
  std::vector<int> dfn(n, -1), low(n);
  std::function<void(int, int)> tarjan = [&](int u, int fa) {
    dfn[u] = low[u] = dfs_clock++;
    for (int v : g[u]) {
      if (v == fa)
        continue;

      if (dfn[v] == -1) {
        tarjan(v, u);

        low[u] = std::min(low[u], low[v]);

        if (dfn[u] < low[v]) {
          bridges.push_back({u, v});
        }
      } else if (dfn[v] < dfn[u]) {
        low[u] = std::min(low[u], dfn[v]);
      }
    }
  };
  for (int i = 0; i < n; ++i) {
    if (dfn[i] == -1) {
      tarjan(i, i);
    }
  }

  return bridges;
}

void SolveCase(int Case) {
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> g(n);
  std::vector<std::pair<int, int>> E;
  for (int i = 0; i < n; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;

    g[u].push_back(v);
    g[v].push_back(u);

    E.push_back({u, v});
  }

  auto bridges = EdgeBCC(g);
  logd(bridges);

  std::vector<int> f(n);
  std::iota(f.begin(), f.end(), 0);
  std::function<int(int)> find = [&](int x) { return x == f[x] ? x : f[x] = find(f[x]); };

  for (auto [u, v] : bridges) {
    u = find(u), v = find(v);
    if (u != v)
      f[u] = v;
  }

  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;

    u = find(u), v = find(v);
    std::cout << (u == v ? "Yes" : "No") << "\n";
  }
}

```

</details>

## [G - Yet Another RGB Sequence](https://atcoder.jp/contests/abc266/tasks/abc266_g)

先放 `G` 和 `B` ，此时没有任何约束，共 $\binom{G + B}{G}$ 种方案。

然后，选择 $K$ 个 `G`，对于选中的每一个 `G` ，在前面插一个 `R` ，共 $\binom{G}{K}$ 种方案。

此时，有 $K$ 个 `RG` 的约束已经满足了，为了满足第一个约束，还需要再插入 $R - K$ 个 `R` ，且没有新增的 `RG` 。这样子的话，一个 `R` 只能插入到某个 `RG` 前面，或者某个 `B` 前面，或者结尾，共 $K + B + 1$ 个可能的插入位置。

**注意**：字符是不带标号的，所以不能直接 ${(K + B + 1)}^{R - K}$，这样子会重复计数。

其实问题转换一下就是，有 $x$ 个带标号的容器，有 $y$ 个不带标号的小球，一个容器可以放任意个小球，问有几种不同的放法？这个其实是个挺经典的问题，用隔板法可以得出有 $\binom{x + y - 1}{x - 1}$ 种放法（用 $x - 1$ 个隔板把 $y$ 个小球分成 $x$ 份）。

<details>
<summary>AC代码</summary>

```cpp
// Problem: G - Yet Another RGB Sequence
// Contest: AtCoder - AtCoder Beginner Contest 266
// URL: https://atcoder.jp/contests/abc266/tasks/abc266_g
// Memory Limit: 1024 MB
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
#define serialize() ""
#endif

using i64 = int64_t;
using u64 = uint64_t;

void Initialize();
void SolveCase(int Case);

int main(int argc, char* argv[]) {
  CPPIO;
  int T = 1;
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    SolveCase(t);
  }
  return 0;
}

void Initialize() {}

template <typename ValueType, ValueType mod_, typename SupperType = int64_t>
class Modular {
 private:
  ValueType value_;

  ValueType normalize(ValueType value) const {
    if (value >= 0 && value < mod_)
      return value;
    value %= mod_;
    if (value < 0)
      value += mod_;
    return value;
  }

  ValueType power(ValueType value, size_t exponent) const {
    ValueType result = 1;
    ValueType base = value;
    while (exponent) {
      if (exponent & 1)
        result = SupperType(result) * base % mod_;
      base = SupperType(base) * base % mod_;
      exponent >>= 1;
    }
    return result;
  }

 public:
  Modular() : value_(0) {}

  Modular(const ValueType& value) : value_(normalize(value)) {}

  ValueType value() const { return value_; }

  Modular inv() const { return Modular(power(value_, mod_ - 2)); }

  Modular power(size_t exponent) const { return Modular(power(value_, exponent)); }

  friend Modular operator+(const Modular& lhs, const Modular& rhs) {
    ValueType result = lhs.value() + rhs.value() >= mod_ ? lhs.value() + rhs.value() - mod_
                                                         : lhs.value() + rhs.value();
    return Modular(result);
  }

  friend Modular operator-(const Modular& lhs, const Modular& rhs) {
    ValueType result = lhs.value() - rhs.value() < 0 ? lhs.value() - rhs.value() + mod_
                                                     : lhs.value() - rhs.value();
    return Modular(result);
  }

  friend Modular operator*(const Modular& lhs, const Modular& rhs) {
    ValueType result = SupperType(1) * lhs.value() * rhs.value() % mod_;
    return Modular(result);
  }

  friend Modular operator/(const Modular& lhs, const Modular& rhs) {
    ValueType result = SupperType(1) * lhs.value() * rhs.inv().value() % mod_;
    return Modular(result);
  }

  std::string to_string() const { return std::to_string(value_); }
};
// using Mint = Modular<int, 1'000'000'007>;
using Mint = Modular<int, 998'244'353>;

class Binom {
 private:
  std::vector<Mint> f, g;

 public:
  Binom(int n) {
    f.resize(n + 1);
    g.resize(n + 1);

    f[0] = Mint(1);
    for (int i = 1; i <= n; ++i)
      f[i] = f[i - 1] * Mint(i);
    g[n] = f[n].inv();
    for (int i = n - 1; i >= 0; --i)
      g[i] = g[i + 1] * Mint(i + 1);
  }
  Mint operator()(int n, int m) {
    if (n < 0 || m < 0 || m > n)
      return Mint(0);
    return f[n] * g[m] * g[n - m];
  }
} binom(3e6 + 5);

void SolveCase(int Case) {
  auto fast = [&binom](int r, int g, int b, int k) {
    Mint ans = Mint(1);
    ans = ans * binom(b + g, b);
    // logd(ans);
    ans = ans * binom(g, k);
    // logd(ans);
    ans = ans * binom(k + b + r - k, k + b);
    // logd(k + b + r - k, k + b, ans);
    return ans.value();
  };

  int r, g, b, k;
  std::cin >> r >> g >> b >> k;

  std::cout << fast(r, g, b, k) << "\n";
}

```

</details>

## [Ex - Snuke Panic (2D)](https://atcoder.jp/contests/abc266/tasks/abc266_h)

官方题解写得听清楚的，就座标转换一下变成 1D/1D DP，然后这类DP的转移可以用 CDQ 分治从 $O(n^2)$ 优化到 $O(n \log^2 n)$。

<details>
<summary>AC代码</summary>

```cpp
// Problem: Ex - Snuke Panic (2D)
// Contest: AtCoder - AtCoder Beginner Contest 266
// URL: https://atcoder.jp/contests/abc266/tasks/abc266_h
// Memory Limit: 1024 MB
// Time Limit: 5000 ms
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
#define serialize() ""
#endif

using i64 = int64_t;
using u64 = uint64_t;

void Initialize();
void SolveCase(int Case);

int main(int argc, char* argv[]) {
  CPPIO;
  int T = 1;
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    SolveCase(t);
  }
  return 0;
}

void Initialize() {}

const i64 INF = INT64_C(0x3f3f3f3f3f3f3f3f);

template <typename T>
class FenwickTree {
 public:
  using Operator = std::function<T(const T&, const T&)>;

 private:
  inline int lb(int x) { return x & -x; }

 public:
  FenwickTree(int n, T init, Operator op = std::plus<T>())
      : n_(n), init_(init), c_(n_ + 1, init_), op_(op), t_(n_ + 1, -1), tag_(0) {}

  void Update(int x, T d) {
    for (; x <= n_; x += lb(x)) {
      if (t_[x] != tag_)
        c_[x] = init_;
      c_[x] = op_(c_[x], d);
      t_[x] = tag_;
    }
  }

  T Query(int x) {
    T r = init_;
    for (; x; x -= lb(x)) {
      if (t_[x] == tag_)
        r = op_(r, c_[x]);
    }
    return r;
  }

  void Reset() { ++tag_; }

  T Query(int l, int r) { return Query(r) - Query(l - 1); }

  T Kth(int k) {
    T ans = 0, cnt = 0;
    for (int i = std::__lg(n_) + 1; i >= 0; --i) {
      ans += (1LL << i);
      if (ans >= n_ || cnt + c_[ans] >= k)
        ans -= (1LL << i);
      else
        cnt += c_[ans];
    }
    return ans + 1;
  }

 private:
  int n_;

  T init_;
  std::vector<T> c_;
  const Operator op_;

  std::vector<int> t_;
  int tag_;
};

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<std::array<i64, 4>> p;
  p.push_back({0, 0, 0, 0});
  for (int i = 1; i <= n; ++i) {
    i64 t, x, y, a;
    std::cin >> t >> x >> y >> a;

    p.push_back({y, t - x - y, t + x - y, a});
  }

  std::vector<i64> dp(n + 1, -INF);

  std::function<void(int, int)> CDQ = [&](int l, int r) {
    if (l == r)
      return;

    int mid = (l + r) >> 1;
    CDQ(l, mid);

    {
      std::vector<std::array<i64, 4>> temp;
      temp.reserve(r - l + 1);
      for (int i = l; i <= r; ++i) {
        temp.push_back({p[i][1], p[i][2], i, p[i][3]});
      }

      std::vector<i64> b, c;
      b.reserve(temp.size());
      c.reserve(temp.size());
      for (auto [x, y, id, a] : temp) {
        b.push_back(x);
        c.push_back(y);
      }
      std::sort(b.begin(), b.end());
      b.erase(std::unique(b.begin(), b.end()), b.end());
      std::sort(c.begin(), c.end());
      c.erase(std::unique(c.begin(), c.end()), c.end());
      for (auto& [x, y, id, a] : temp) {
        x = std::lower_bound(b.begin(), b.end(), x) - b.begin() + 1;
        y = std::lower_bound(c.begin(), c.end(), y) - c.begin() + 1;
      }

      std::sort(temp.begin(), temp.end());

      FenwickTree<i64> bit(c.size(), -INF,
                           [](const i64& x, const i64& y) -> i64 { return std::max(x, y); });
      for (auto [x, y, id, a] : temp) {
        if (id <= mid) {
          bit.Update(y, dp[id]);
        } else {
          dp[id] = std::max(dp[id], bit.Query(y) + a);
        }
      }
    }

    CDQ(mid + 1, r);
  };

  std::sort(p.begin(), p.end());
  dp[0] = 0;
  CDQ(0, p.size() - 1);

  i64 ans = *std::max_element(dp.begin(), dp.end());
  std::cout << ans << "\n";
}

```

</details>