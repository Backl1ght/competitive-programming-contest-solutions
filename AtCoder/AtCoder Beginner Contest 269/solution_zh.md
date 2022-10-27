# AtCoder Beginner Contest 269

咕咕咕咕咕。

## [F - Numbered Checker](https://atcoder.jp/contests/abc269/tasks/abc269_f)

首先矩形容斥，把一个询问拆分成 4 个询问。现在只需要解决：左上角为$(1, 1)$，右下角为 $(x, y)$ 的矩形区域和这一问题。 

把列数为奇数和偶数的分开算，以奇数为例，偶数列同理可得。

第 1 列的上的非零元素可以组成一个首项元素为 $1$ ，公差为 $2m$， 共 $\lfloor \frac{x + 1}{2} \rfloor$ 项的等差数列。

把列数为奇数的列，每列求和后，搞成一个一维数组，这又是一个等差数列，首项为第一列的元素和，公差为 $2 \lfloor \frac{x + 1}{2} \rfloor$ , 共 $\lfloor \frac{y + 1}{2} \rfloor$ 项。

<details>
<summary>AC代码</summary>

```cpp
// Problem: F - Numbered Checker
// Contest: AtCoder - UNICORN Programming Contest 2022(AtCoder Beginner Contest 269)
// URL: https://atcoder.jp/contests/abc269/tasks/abc269_f
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#define ASSERT(x) ;
#define serialize() std::string("")
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

template <typename ValueType, ValueType mod_, typename SupperType>
class Modular {
  static ValueType normalize(ValueType value) {
    if (value >= 0 && value < mod_)
      return value;
    value %= mod_;
    if (value < 0)
      value += mod_;
    return value;
  }

  static ValueType power(ValueType value, int64_t exponent) {
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
  Modular(SupperType value = 0) : value_(normalize(value % mod_)) {}

  ValueType value() const { return value_; }

  Modular inv() const { return Modular(power(value_, mod_ - 2)); }

  Modular power(int64_t exponent) const { return Modular(power(value_, exponent)); }

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

  friend Modular operator-(const Modular& lhs) {
    ValueType result = normalize(-lhs.value() + mod_);
    return result;
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

 private:
  ValueType value_;
};

// using Mint = Modular<int, 1'000'000'007, int64_t>;
using Mint = Modular<int, 998'244'353, int64_t>;

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
  int n, m;
  std::cin >> n >> m;
  int q;
  std::cin >> q;

  auto S1 = [&](Mint a0, Mint k, Mint d) { return k * a0 + d * (k - 1) * (k) / Mint(2); };

  auto S21 = [&](int x, int y) {
    Mint a0 = S1(1, Mint((x + 1) / 2), Mint(2 * m));
    Mint k = Mint((y + 1) / 2);
    Mint d = Mint(2) * Mint((x + 1) / 2);
    return S1(a0, k, d);
  };

  auto S22 = [&](int x, int y) {
    Mint a0 = S1(Mint(m + 2), x / 2, 2 * m);
    Mint k = Mint(y / 2);
    Mint d = Mint(2) * Mint(x / 2);
    return S1(a0, k, d);
  };

  auto Q = [&](int x, int y) { return S21(x, y) + S22(x, y); };

  for (int _ = 1; _ <= q; ++_) {
    int x1, x2, y1, y2;
    std::cin >> x1 >> x2 >> y1 >> y2;

    Mint ans = Q(x2, y2) - Q(x2, y1 - 1) - Q(x1 - 1, y2) + Q(x1 - 1, y1 - 1);
    std::cout << ans.value() << "\n";
  }
}
```

</details>

## [G - Reversible Cards 2](https://atcoder.jp/contests/abc269/tasks/abc269_g)

转化一下，问题变成一个01背包问题：背包初始装了 $s$ 单位重量，价值为 $0$ 的东西，有 $n$ 件物品，每件物品价值为 $1$ ，重量为 $w_i = b_i - a_i$ 单位重量（$w_i$可能小于零），问背包装恰好 $k$ 单位重量的物品的最小代价。

这样直接去 DP 复杂度为$O(nm)$，直接爆炸。

> **观察1**：所有物品重量的绝对值之和小于等于 $m$ 。
> **证明**：
> $$
> \sum_i |w_i| = \sum_i |b_i - a_i| \le \sum_i |b_i| + |-a_i| = m
> $$

> **观察2**： 如果把重量相同的物品视为一类，则至多有 $2 \lceil \sqrt{m} \rceil$ 种物品。或者说至多有$2\sqrt{m}$中物品数量大于等于1。
> **证明**： 考虑反证法。假设有$2 \lceil \sqrt{m} \rceil + 1$种物品，考虑构造出一种方案使得$\sum_i |w_i|$尽可能小，则应该是每种物品数量都为1，然后物品重量值域为$[-\lceil \sqrt{m} \rceil, \lceil \sqrt{m} \rceil]$。此时有$\sum_i |w_i| = 0 + 2 \sum_{i = 1}^{\lceil \sqrt{m} \rceil} i = m + \lceil \sqrt{m} \rceil$，与观察1相悖。


> **观察3**： 至多有 $2 \lceil \frac{\sqrt{m}}{2^t} \rceil$ 种物品数量大于等于$2^t$。
> **证明**：类似观察2的证明。

现在问题转化成多重背包问题，可以二进制分组优化搞，假设有$c$种物品，第$i$种物品有$k_i$个，则复杂度为$O(n + m \sum_{i = 1}^{c} \log k_i)$。又有

$$
\sum_{i = 1} ^ c \log k_i = \sum_{x=0}^{+\infin} \sum_{i=1}^{c} [k_i \ge 2^x] = \sum_{x=0}^{+\infin} 2 \lceil \frac{\sqrt{m}}{2^t} \rceil = O(\sqrt{m})
$$

所以总的时间复杂度为$O(n + m\sqrt m)$。

<details>
<summary>AC代码</summary>

```cpp
// Problem: G - Reversible Cards 2
// Contest: AtCoder - UNICORN Programming Contest 2022(AtCoder Beginner Contest 269)
// URL: https://atcoder.jp/contests/abc269/tasks/abc269_g
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#define ASSERT(x) ;
#define serialize() std::string("")
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
  int n, m;
  std::cin >> n >> m;

  std::map<int, int> mp;
  int s = 0;
  for (int i = 0; i < n; ++i) {
    int a, b;
    std::cin >> a >> b;
    ++mp[b - a];
    s += a;
  }

  const int INF = 0x3f3f3f3f;
  std::vector<int> dp(m + 1, INF);
  dp[s] = 0;
  for (auto [d, c] : mp) {
    if (d == 0)
      continue;

    int x = 1;
    while (c) {
      x = std::min(x, c);

      if (d > 0) {
        for (int i = m; i >= x * d; --i)
          dp[i] = std::min(dp[i], dp[i - x * d] + x);
      } else {
        for (int i = 0; i - x * d <= m; ++i)
          dp[i] = std::min(dp[i], dp[i - x * d] + x);
      }

      c = c - x;
      x = x * 2;
    }
  }

  for (int i = 0; i <= m; ++i) {
    if (dp[i] == INF)
      dp[i] = -1;
    std::cout << dp[i] << "\n";
  }
}

```

</details>

## [Ex - Antichain](https://atcoder.jp/contests/abc269/tasks/abc269_h)

很容易能得到一个 $O(n^2)$ 的 DP ，但是复杂度过高。考虑使用 FFT 来优化。

假设 $f_u(x) = \sum_i a_i x^i$ 表示以 $u$ 为根的子树的答案的生成函数，即以 $u$ 为根的子树中有 $a_i$ 种方案构造出 $|S| = i$ 的$S$ 。

首先，对树进行轻重剖分，跑出重儿子和轻儿子。对于一棵树，考虑从根开始的重链，假设链上的节点自顶向下依次为 $c_i, i = 1, 2, ..., k$。

令
$$
g_u(x) = \prod_{\substack{v \text{ is light child of } u}} f_v(x)
$$

那么对于每一个 $c_i$， 递归计算出其轻儿子的$f$，然后通过分治 FFT 计算出 $g_{c_i}(x)$。

考虑通过合并重链计算出整棵树的答案 $f_{c_1}(x)$ 。

假设选择了 $c_i$，那么重链上其余点都不能选了， $j \ge i$ 的 $g_{c_j}(x)$ 也不能选，而 $j < i$ 的 $g_{c_j}(x)$ 可以随便选；当然也可以重链上的点一个都不选。由此有 

$$
f_{c_1}(x) = \sum_{i = 1}^{k} x \prod_{j = 1}^{i - 1} g_{c_j}(x) + \prod_{i = 1}^{k} g_{c_j}(x)
$$

这个过程可以通过分治来搞，就把一段区间分成两半，前一半的生成函数为 $L_1$ ， $g_{c_j}(x)$ 的积为 $R_1$ ；后一半的生成函数为 $L_2$ ， $g_{c_j}(x)$ 的积为 $R_2$ 。则整个区间的生成函数为 $L_1R_2 + L2$，$g_{c_j}(x)$ 的积为 $R_1R_2$。

然后就是递归去搞就完事了，时间复杂度为 $O(n \log^3n)$。（复杂度证明待补）

<details>
<summary>AC代码</summary>

```cpp
// Problem: Ex - Antichain
// Contest: AtCoder - UNICORN Programming Contest 2022(AtCoder Beginner Contest 269)
// URL: https://atcoder.jp/contests/abc269/tasks/abc269_h
// Memory Limit: 1024 MB
// Time Limit: 8000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#define ASSERT(x) ;
#define serialize() std::string("")
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
  int n;
  std::cin >> n;

  std::vector<int> p(n);
  std::vector<std::vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    std::cin >> p[i];
    --p[i];
    g[p[i]].push_back(i);
  }

  std::vector<int> sz(n), heavy_son(n);
  std::function<void(int)> dfs1 = [&](int u) {
    sz[u] = 1;
    heavy_son[u] = -1;

    for (int v : g[u]) {
      dfs1(v);
      sz[u] += sz[v];
      if (heavy_son[u] == -1 || sz[v] > sz[heavy_son[u]])
        heavy_son[u] = v;
    }
  };
  dfs1(0);

  std::vector<int> top(n);
  std::function<void(int, int)> dfs2 = [&](int u, int k) {
    top[u] = k;
    if (heavy_son[u] != -1)
      dfs2(heavy_son[u], k);
    for (int v : g[u]) {
      if (v == heavy_son[u])
        continue;
      dfs2(v, v);
    }
  };
  dfs2(0, 0);

  std::function<poly(const std::vector<poly>&, int, int)> merge_light =
      [&](const std::vector<poly>& a, int l, int r) {
        if (l == r)
          return a[l];

        int m = (l + r) >> 1;
        auto L = merge_light(a, l, m);
        auto R = merge_light(a, m + 1, r);
        return L * R;
      };

  std::function<std::pair<poly, poly>(const std::vector<poly>&, int, int)> merge_heavy =
      [&](const std::vector<poly>& a, int l, int r) {
        if (l == r)
          return std::make_pair(poly{1}, a[l]);

        int m = (l + r) >> 1;
        auto [L1, R1] = merge_heavy(a, l, m);
        auto [L2, R2] = merge_heavy(a, m + 1, r);
        auto res = std::make_pair(L1 * R2 + L2, R1 * R2);
        return res;
      };

  std::function<poly(int)> dfs3 = [&](int u) {
    std::vector<poly> heavy_chain;

    int p = u;
    while (p != -1) {
      std::vector<poly> light_children;
      light_children.push_back({1});
      for (int v : g[p]) {
        if (v == heavy_son[p])
          continue;

        light_children.push_back(dfs3(v));
      }
      auto gp = merge_light(light_children, 0, light_children.size() - 1);
      heavy_chain.push_back(gp);

      p = heavy_son[p];
    }
    std::reverse(heavy_chain.begin(), heavy_chain.end());

    auto [fi, se] = merge_heavy(heavy_chain, 0, heavy_chain.size() - 1);
    auto r = fi * poly({0, 1}) + se;
    return r;
  };
  auto ans = dfs3(0).a;
  ans.resize(n + 1);

  for (int i = 1; i <= n; ++i)
    std::cout << ans[i] << "\n";
}

```

</details>