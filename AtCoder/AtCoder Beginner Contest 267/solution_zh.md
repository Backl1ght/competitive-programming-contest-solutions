# AtCoder Beginner Contest 267

## [E - Erasing Vertices 2](https://atcoder.jp/contests/abc267/tasks/abc267_e)

### 做法1

观察可得：对于某个时刻，贪心删当前代价最小的点肯定是最优的。

但是删一个点会减少相邻接的点的代价。然后就想到了堆，但是这个堆需要支持decrease-key操作。

decrease-key 这个操作`std::priority_queue`并不支持，但是其实二叉堆也能做到 $O(\log n)$。

pbds 里的堆支持decrease-key，接口为 `modify`，然后就完事了。

### 做法2

这个是官方题解给出的做法，大概就是二分答案，然后通过搜索把代价小于等于当前二分的值的点都删掉，如果所有点都能删掉说明当前二分的代价可行。

<details>
<summary>AC代码</summary>

```cpp
// Problem: E - Erasing Vertices 2
// Contest: AtCoder - NEC Programming Contest 2022 (AtCoder Beginner Contest 267)
// URL: https://atcoder.jp/contests/abc267/tasks/abc267_e
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

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

#include <ext/pb_ds/priority_queue.hpp>

template <typename T>
using min_heap = __gnu_pbds::priority_queue<T, std::greater<T>, __gnu_pbds::pairing_heap_tag>;

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  std::vector<std::vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  std::vector<i64> s(n);
  for (int i = 0; i < n; ++i) {
    for (int v : g[i])
      s[v] += a[i];
  }

  min_heap<std::pair<i64, int>> q;
  std::vector<min_heap<std::pair<i64, int>>::point_iterator> p(n);
  for (int i = 0; i < n; ++i) {
    p[i] = q.push({s[i], i});
  }

  i64 ans = 0;
  while (!q.empty()) {
    auto [cost, id] = q.top();
    q.pop();

    ans = std::max(ans, cost);
    p[id] = nullptr;

    for (int v : g[id]) {
      if (p[v] == nullptr)
        continue;

      auto [first, second] = *p[v];
      q.modify(p[v], {first - a[id], second});
    }
  }

  std::cout << ans << "\n";
}

```

</details>

## [F - Exactly K Steps](https://atcoder.jp/contests/abc267/tasks/abc267_f)

有个结论：假设树的直径的两个端点分别为 $a$ 和 $b$，那么对于树中任意一点 $u$ ，$a$ 和 $b$ 中之一必定满足其是树中所有点中离$u$距离最大的点。用反正法可以证明。

由此，对于某个询问$u, k$，要么能在 $u$ 到 $a$ 或 $u$ 到 $b$ 的路径中找到答案，要么无解。

### 做法1

想着把直径端点之一搞成根，此时直径是一条一端为根一端为叶子的链。

对于一个点，往父亲的方向条一定会跳到这条链上。

然后先跳到这条链上，假设此时位于$u$，那么$u$所在的长链一定是直径，这个时候再枚举往父亲的方向跳，还是往长链的方向条，就能枚举到$u$ 到 $a$ 和 $u$ 到 $b$ 的路径。

往父亲的方向跳和往长链的方向条都可以用倍增加速。

### 做法2

这个是官方题解给出的做法，大概就是分别以 $a$ 和 $b$ 作为根，一共跑两次，这样就只需要考虑往父亲的方向跳的情况，也能枚举到$u$ 到 $a$ 和 $u$ 到 $b$ 的路径，而且相对做法1会简单一点。

<details>
<summary>AC代码</summary>

```cpp
// Problem: F - Exactly K Steps
// Contest: AtCoder - NEC Programming Contest 2022 (AtCoder Beginner Contest 267)
// URL: https://atcoder.jp/contests/abc267/tasks/abc267_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

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
  int n, m = 20;
  std::cin >> n;

  std::vector<std::vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  // make one end of diameter the root.
  std::vector<int> dep(n), f(n);
  int rt = 0;
  std::function<void(int, int, int)> dfs1 = [&](int u, int fa, int depth) {
    dep[u] = depth;
    f[u] = fa;
    if (dep[u] > dep[rt])
      rt = u;

    for (int v : g[u]) {
      if (v == fa)
        continue;

      dfs1(v, u, depth + 1);
    }
  };
  dfs1(0, 0, 0);
  int temp = rt;
  dfs1(rt, rt, 0);
  rt = temp;
  logd(rt);
  logd(dep);

  // binary lifting for k-th ancester.
  std::vector<std::vector<int>> up(n, std::vector<int>(m));
  std::function<void(int, int)> dfs2 = [&](int u, int fa) {
    if (u == rt) {
      std::fill(up[u].begin(), up[u].end(), rt);
    } else {
      up[u][0] = fa;
      for (int i = 1; i < m; ++i) {
        up[u][i] = up[up[u][i - 1]][i - 1];
      }
    }

    for (int v : g[u]) {
      if (v == fa)
        continue;

      dfs2(v, u);
    }
  };
  dfs2(rt, rt);
  logd(up);

  // binary lifting for longest chain in subtree.
  std::vector<int> len(n), son(n);
  std::vector<std::vector<int>> down(n, std::vector<int>(m));
  std::function<void(int, int)> dfs3 = [&](int u, int fa) {
    son[u] = -1;
    len[u] = 0;

    for (int v : g[u]) {
      if (v == fa)
        continue;

      dfs3(v, u);
      if (son[u] == -1 || len[v] > len[son[u]]) {
        son[u] = v;
        len[u] = len[v] + 1;
      }
    }

    if (son[u] == -1) {
      std::fill(down[u].begin(), down[u].end(), u);
    } else {
      down[u][0] = son[u];
      for (int i = 1; i < m; ++i) {
        down[u][i] = down[down[u][i - 1]][i - 1];
      }
    }
  };
  dfs3(rt, rt);

  std::vector<int> in_diameter(n, false);
  {
    int x = rt;
    while (x != -1) {
      in_diameter[x] = true;
      x = son[x];
    }
  }

  // return v whose distance from u is k by:
  // - jump up in the path to root.
  // - jump down in the longest chain in subtree whose root is u.
  auto Q = [&](int u, int k) {
    if (dep[u] >= k) {
      int x = u;
      for (int i = m - 1; i >= 0; --i) {
        if ((k >> i) & 1)
          x = up[x][i];
      }
      return x + 1;
    }

    if (len[u] >= k) {
      int x = u;
      for (int i = m - 1; i >= 0; --i) {
        if ((k >> i) & 1)
          x = down[x][i];
      }
      return x + 1;
    }

    return -1;
  };

  int q;
  std::cin >> q;
  for (int _ = 0; _ < q; ++_) {
    int u, k, r;
    std::cin >> u >> k;
    --u;

    r = Q(u, k);
    if (r != -1) {
      std::cout << r << "\n";
      continue;
    }

    if (in_diameter[u]) {
      std::cout << "-1\n";
      continue;
    }

    int y = u;
    for (int i = m - 1; i >= 0; --i) {
      if (not in_diameter[up[y][i]])
        y = up[y][i];
    }
    y = f[y];
    k -= dep[u] - dep[y];
    u = y;

    std::cout << Q(u, k) << "\n";
  }
}

```

</details>

## [G - Increasing K Times](https://atcoder.jp/contests/abc267/tasks/abc267_g)

问题转换成 $a$ 有多少个排列 $A$ 满足恰好有 $k$ 个 $i$ 满足$A_i < A_{i + 1}$。

考虑从小到大把 $a$ 中的元素加入 $A$ ，从而构成一个 $a$ 的排列 $A$ 。为了防止边界条件的讨论，不妨令初始时 $A = [0, 0]$，然后再加入元素。这样相比原本的情况中会多算一个满足$A_i < A_{i + 1}$ 的 $i$，因为 $A_n$ 一定大于 $0$ ，此时改成求恰好有 $k + 1$ 个满足条件的$i$即可。

然后考虑动态规划，令 $dp_{i, j}$ 表示插入前 $i$ 个元素，恰好有 $j$ 个 $x$ 满足 $A_x < A_{x + 1}$。

假设现在要插入$y$，这个操作要么令满足条件的 $x$ 的数量保持不变，要么令满足条件的 $x$ 的数量增加一。

什么时候会增加呢，只有将 $y$ 插到满足 $A_{x} \ge A_{x + 1}$ 的 $A_x$ 之后才会令满足条件的 $x$ 的数量增加。假设之前已经插入了 $i$ 个元素，有 $j$ 个满足条件的 $x$，然后插入了 $z$ 个 $y$，那么一共有 $i - j - z$ 个位置，将 $y$ 插到这个位置会使满足条件的 $x$ 数量增加一，剩余 $j + z$ 个位置会使满足条件的 $x$ 数量保持不变。

<details>
<summary>AC代码</summary>

```cpp
// Problem: G - Increasing K Times
// Contest: AtCoder - NEC Programming Contest 2022 (AtCoder Beginner Contest 267)
// URL: https://atcoder.jp/contests/abc267/tasks/abc267_g
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

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
};
template <typename StreamType, typename ValueType, ValueType mod, typename SupperType = int64_t>
StreamType& operator<<(StreamType& out, const Modular<ValueType, mod, SupperType>& modular) {
  return out << modular.value();
}
template <typename StreamType, typename ValueType, ValueType mod, typename SupperType = int64_t>
StreamType& operator>>(StreamType& in, Modular<ValueType, mod, SupperType>& modular) {
  ValueType value;
  in >> value;
  modular = Modular<ValueType, mod, SupperType>(value);
  return in;
}
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
};

void SolveCase(int Case) {
  int n, k;
  std::cin >> n >> k;
  ++k;

  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i)
    std::cin >> a[i];
  std::sort(a.begin() + 1, a.end());

  std::vector<int> same(n + 1);
  for (int i = 1; i <= n; ++i) {
    if (a[i] != a[i - 1])
      same[i] = 0;
    else
      same[i] = same[i - 1] + 1;
  }

  std::vector<Mint> dp(k + 1, Mint(0));
  dp[0] = Mint(1);
  for (int i = 1; i <= n; ++i) {
    std::vector<Mint> temp(k + 1, Mint(0));
    for (int j = 0; j <= k; ++j) {
      temp[j] = temp[j] + Mint(j + same[i]) * dp[j];
      if (j + 1 <= k)
        temp[j + 1] = temp[j + 1] + Mint(i - j - same[i]) * dp[j];
    }
    dp = temp;
  }

  std::cout << dp[k].value() << "\n";
}

```

</details>

## [Ex - Odd Sum](https://atcoder.jp/contests/abc267/tasks/abc267_h)

考虑动态规划，令 $dp_{i, 0/1}$ 表示选奇数或者偶数个元素且所选元素之和为 $i$ 的方案数，然后类似背包的DP就能求，但是复杂度爆炸。

考虑 $f_{0}(x) = \sum_i a_i x^i$ ，$[x^i]f_0 (x)$表示选偶数个元素且元素和为 $i$ 的方案数，类似可得$f_{1}(x)$。

假设现在有两个数组，对应的多项式分别为$f_{0/1}$和$g_{0/1}$，那么对于两个数组的并集对应的多项式$h$有：
$$
h_0 = f_0 * g_0 + f_1 * g_1\\
h_1 = f_0 * g_1 + f_1 * g_0\\
$$

把每个 $a_i$ 都看成独立的数组，不断两两合并的到 $a$，对应的多项式也两两合并，得到 $a$ 对应的多项式$f_{0/1}$，答案即为$[x^m]f_1$。

用类似分治FFT的过程跑能做到$O(m \log m \log n)$的时间复杂度。

<details>
<summary>AC代码</summary>

```cpp
// Problem: Ex - Odd Sum
// Contest: AtCoder - NEC Programming Contest 2022 (AtCoder Beginner Contest 267)
// URL: https://atcoder.jp/contests/abc267/tasks/abc267_h
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

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

namespace Polynomial {

constexpr int P = 998244353, G = 3;
std::vector<int> rev, roots{0, 1};

int power(int a, int b) {
  int r = 1;
  while (b) {
    if (b & 1)
      r = 1ll * r * a % P;
    a = 1ll * a * a % P;
    b >>= 1;
  }
  return r;
}

void dft(std::vector<int>& a) {
  int n = a.size();
  if (int(rev.size()) != n) {
    int k = __builtin_ctz(n) - 1;
    rev.resize(n);
    for (int i = 0; i < n; ++i)
      rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
  }
  for (int i = 0; i < n; ++i)
    if (rev[i] < i)
      std::swap(a[i], a[rev[i]]);
  if (int(roots.size()) < n) {
    int k = __builtin_ctz(roots.size());
    roots.resize(n);
    while ((1 << k) < n) {
      int e = power(G, (P - 1) >> (k + 1));
      for (int i = 1 << (k - 1); i < (1 << k); ++i) {
        roots[2 * i] = roots[i];
        roots[2 * i + 1] = 1ll * roots[i] * e % P;
      }
      ++k;
    }
  }
  for (int k = 1; k < n; k *= 2) {
    for (int i = 0; i < n; i += 2 * k) {
      for (int j = 0; j < k; ++j) {
        int u = a[i + j];
        int v = 1ll * a[i + j + k] * roots[k + j] % P;
        int x = u + v;
        if (x >= P)
          x -= P;
        a[i + j] = x;
        x = u - v;
        if (x < 0)
          x += P;
        a[i + j + k] = x;
      }
    }
  }
}

void idft(std::vector<int>& a) {
  int n = a.size();
  std::reverse(a.begin() + 1, a.end());
  dft(a);
  int inv = power(n, P - 2);
  for (int i = 0; i < n; ++i)
    a[i] = 1ll * a[i] * inv % P;
}

struct poly {
  std::vector<int> a;

  poly() {}
  poly(int f0) { a = {f0}; }
  poly(const std::vector<int>& f) : a(f) {
    while (!a.empty() && !a.back())
      a.pop_back();
  }
  poly(const std::vector<int>& f, int n) : a(f) { a.resize(n); }
  int size() const { return a.size(); }
  int deg() const { return a.size() - 1; }
  int operator[](int idx) const {
    if (idx < 0 || idx >= size())
      return 0;
    return a[idx];
  }
  std::string to_string() const {
    std::stringstream ss;
    ss << "poly: ";
    for (int v : a)
      ss << v << " ";
    return ss.str();
  }
  poly mulxk(int k) const {
    auto b = a;
    b.insert(b.begin(), k, 0);
    return poly(b);
  }
  poly modxk(int k) const {
    k = std::min(k, size());
    return poly(std::vector<int>(a.begin(), a.begin() + k));
  }
  poly alignxk(int k) const { return poly(a, k); }
  poly divxk(int k) const {
    if (size() <= k)
      return poly();
    return poly(std::vector<int>(a.begin() + k, a.end()));
  }
  friend poly operator+(const poly& f, const poly& g) {
    int k = std::max(f.size(), g.size());
    std::vector<int> res(k);
    for (int i = 0; i < k; ++i) {
      res[i] = f[i] + g[i];
      if (res[i] >= P)
        res[i] -= P;
    }
    return poly(res);
  }
  friend poly operator-(const poly& f, const poly& g) {
    int k = std::max(f.size(), g.size());
    std::vector<int> res(k);
    for (int i = 0; i < k; ++i) {
      res[i] = f[i] - g[i];
      if (res[i] < 0)
        res[i] += P;
    }
    return poly(res);
  }
  friend poly operator*(const poly& f, const poly& g) {
    int sz = 1, k = f.size() + g.size() - 1;
    while (sz < k)
      sz *= 2;
    std::vector<int> p = f.a, q = g.a;
    p.resize(sz);
    q.resize(sz);
    dft(p);
    dft(q);
    for (int i = 0; i < sz; ++i)
      p[i] = 1ll * p[i] * q[i] % P;
    idft(p);
    return poly(p);
  }
  friend poly operator/(const poly& f, const poly& g) { return f.divide(g).first; }
  friend poly operator%(const poly& f, const poly& g) { return f.divide(g).second; }
  poly& operator+=(const poly& f) { return (*this) = (*this) + f; }
  poly& operator-=(const poly& f) { return (*this) = (*this) - f; }
  poly& operator*=(const poly& f) { return (*this) = (*this) * f; }
  poly& operator/=(const poly& f) { return (*this) = divide(f).first; }
  poly& operator%=(const poly& f) { return (*this) = divide(f).second; }
  poly derivative() const {
    if (a.empty())
      return poly();
    int n = a.size();
    std::vector<int> res(n - 1);
    for (int i = 0; i < n - 1; ++i)
      res[i] = 1ll * (i + 1) * a[i + 1] % P;
    return poly(res);
  }
  poly integral() const {
    if (a.empty())
      return poly();
    int n = a.size();
    std::vector<int> res(n + 1);
    for (int i = 0; i < n; ++i)
      res[i + 1] = 1ll * a[i] * power(i + 1, P - 2) % P;
    return poly(res);
  }
  poly rev() const { return poly(std::vector<int>(a.rbegin(), a.rend())); }
  poly inv(int m) const {
    poly x(power(a[0], P - 2));
    int k = 1;
    while (k < m) {
      k *= 2;
      x = (x * (2 - modxk(k) * x)).modxk(k);
    }
    return x.modxk(m);
  }
  poly log(int m) const { return (derivative() * inv(m)).integral().modxk(m); }
  poly exp(int m) const {
    poly x(1);
    int k = 1;
    while (k < m) {
      k *= 2;
      x = (x * (1 - x.log(k) + modxk(k))).modxk(k);
    }
    return x.modxk(m);
  }
  poly sqrt(int m) const {
    poly x(1);
    int k = 1;
    while (k < m) {
      k *= 2;
      x = (x + (modxk(k) * x.inv(k)).modxk(k)) * ((P + 1) / 2);
    }
    return x.modxk(m);
  }
  poly sin() const {
    int i = power(G, (P - 1) / 4);
    poly p = i * (*this);
    p = p.exp(p.size());

    poly q = (P - i) * (*this);
    q = q.exp(q.size());

    poly r = (p - q) * power(2 * i % P, P - 2);
    return r;
  }
  poly cos() const {
    int i = power(G, (P - 1) / 4);
    poly p = i * (*this);
    p = p.exp(p.size());

    poly q = (P - i) * (*this);
    q = q.exp(q.size());

    poly r = (p + q) * power(2, P - 2);
    return r;
  }
  poly tan() const { return sin() / cos(); }
  poly cot() const { return cos() / sin(); }
  poly arcsin() {
    poly sq = (*this) * (*this).modxk(size());
    for (int i = 0; i < size(); ++i)
      sq.a[i] = sq.a[i] ? P - sq.a[i] : 0;
    sq.a[0] = 1 + sq.a[0];
    if (sq.a[0] >= P)
      sq.a[0] -= P;
    poly r = (derivative() * sq.sqrt(size()).inv(size())).integral();
    return r;
  }
  poly arccos() {
    poly r = arcsin();
    for (int i = 0; i < size(); ++i)
      r.a[i] = r.a[i] ? P - r.a[i] : 0;
    return r;
  }
  poly arctan() {
    poly sq = (*this) * (*this).modxk(size());
    sq.a[0] = 1 + sq.a[0];
    if (sq.a[0] >= P)
      sq.a[0] -= P;
    poly r = (derivative() * sq.inv(size())).integral();
    return r;
  }
  poly arccot() {
    poly r = arctan();
    for (int i = 0; i < size(); ++i)
      r.a[i] = r.a[i] ? P - r.a[i] : 0;
    return r;
  }
  poly mulT(const poly& b) const {
    if (b.size() == 0)
      return poly();
    int n = b.size();
    return ((*this) * b.rev()).divxk(n - 1);
  }
  std::pair<poly, poly> divide(const poly& g) const {
    int n = a.size(), m = g.size();
    if (n < m)
      return make_pair(poly(), a);

    poly fR = rev();
    poly gR = g.rev().alignxk(n - m + 1);
    poly gRI = gR.inv(gR.size());

    poly qR = (fR * gRI).modxk(n - m + 1);

    poly q = qR.rev();

    poly r = ((*this) - g * q).modxk(m - 1);

    return std::make_pair(q, r);
  }
  std::vector<int> eval(std::vector<int> x) const {
    if (size() == 0)
      return std::vector<int>(x.size(), 0);
    const int n = std::max(int(x.size()), size());
    std::vector<poly> q(4 * n);
    std::vector<int> ans(x.size());
    x.resize(n);
    std::function<void(int, int, int)> build = [&](int p, int l, int r) {
      if (r - l == 1) {
        q[p] = std::vector<int>{1, (P - x[l]) % P};
      } else {
        int m = (l + r) / 2;
        build(2 * p, l, m);
        build(2 * p + 1, m, r);
        q[p] = q[2 * p] * q[2 * p + 1];
      }
    };
    build(1, 0, n);
    std::function<void(int, int, int, const poly&)> work = [&](int p, int l, int r,
                                                               const poly& num) {
      if (r - l == 1) {
        if (l < int(ans.size()))
          ans[l] = num[0];
      } else {
        int m = (l + r) / 2;
        work(2 * p, l, m, num.mulT(q[2 * p + 1]).modxk(m - l));
        work(2 * p + 1, m, r, num.mulT(q[2 * p]).modxk(r - m));
      }
    };
    work(1, 0, n, mulT(q[1].inv(n)));
    return ans;
  }
};

}  // namespace Polynomial
using Polynomial::poly;

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(n);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i];

  std::vector<std::pair<poly, poly>> all(n);
  std::vector<int> temp(11);
  for (int i = 0; i < n; ++i) {
    temp[0] = 1;
    poly f(temp);
    temp[0] = 0;

    temp[a[i]] = 1;
    poly g(temp);
    temp[a[i]] = 0;

    all[i] = std::make_pair(f, g);
  }

  while (all.size() > 1) {
    std::vector<std::pair<poly, poly>> next;

    for (int i = 0; i < all.size(); i += 2) {
      if (i == all.size() - 1) {
        next.push_back(all[i]);
      } else {
        next.push_back({
            all[i].first * all[i + 1].first + all[i].second * all[i + 1].second,
            all[i].first * all[i + 1].second + all[i].second * all[i + 1].first,
        });
      }
    }

    all = std::move(next);
  }

  poly f = all[0].second;
  std::cout << f[m] << "\n";
}

```

</details>