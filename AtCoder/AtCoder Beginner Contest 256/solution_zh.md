# AtCoder Beginner Contest 256

咕咕咕咕。

## [E - Takahashi's Anguish](https://atcoder.jp/contests/abc256/tasks/abc256_e)

<details>
<summary>题意</summary>

有$n$个人，第$i$个人不想第$x_i$个人排在他前面，如果第$x_i$个人排在第$i$个人前面第$i$个人就会有$c_i$的不满值，否则第$i$个人的不满值就是$0$。

要求给出排列$p$使得所有人的不满值之和最小。

其中$2 \le n \le 2 \times {10}^5, 1 \le x_i \le n, x_i \ne i, 1 \le c_i \le {10}^9$。

</details>

<details>
<summary>思路</summary>

转化成图论模型，对与$1\ le i \le n$，添加一条$i$到$x_i$的单向边。

首先，如果一个点的入度为0，那么这个点可以不增加不满值的排好，所以一遍拓扑排序搞定所有的这些点。

然后因为每个点的出度都为1，所以此时图中只剩一堆简单环。一个简单环需要花费的代价是所有环中的点的不满值的最小值，因为断掉一条边就是一条链，又可以白嫖了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: E - Takahashi's Anguish
// Contest: AtCoder - Tokio Marine & Nichido Fire Insurance Programming Contest 2022（AtCoder
// Beginner Contest 256) URL: https://atcoder.jp/contests/abc256/tasks/abc256_e Memory Limit: 1024
// MB Time Limit: 2000 ms
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

void solve_case(int Case) {
  int n;
  std::cin >> n;

  std::vector<int> x(n);
  for (int i = 0; i < n; ++i)
    std::cin >> x[i], --x[i];

  std::vector<int> c(n);
  for (int i = 0; i < n; ++i)
    std::cin >> c[i];

  std::vector<std::vector<int>> g(n);
  std::vector<int> indeg(n, 0);
  for (int i = 0; i < n; ++i) {
    g[i].push_back(x[i]);
    ++indeg[x[i]];
  }

  std::vector<bool> vis(n);
  std::queue<int> q;
  for (int i = 0; i < n; ++i)
    if (indeg[i] == 0)
      q.push(i);

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    vis[u] = true;

    for (int v : g[u]) {
      --indeg[v];
      if (indeg[v] == 0) {
        q.push(v);
      }
    }
  }

  i64 ans = 0;
  for (int i = 0; i < n; ++i) {
    if (!vis[i]) {
      int mi = INT_MAX, j = i;
      do {
        vis[j] = true;
        mi = std::min(mi, c[j]);
        j = x[j];
      } while (!vis[j]);
      ans += mi;
    }
  }

  std::cout << ans << "\n";
}

```

</details>

## [F - Cumulative Cumulative Cumulative Sum](https://atcoder.jp/contests/abc256/tasks/abc256_f)

<details>
<summary>题意</summary>

有一个长度为$n$的数组$a$，要求回答$q$个询问，询问共有两种类型：
1. `1 x v`： 令$a_x$的值等于$v$。
2. `2 x`： 询问$a$的3阶前缀和的第$x$个元素，答案对$998244353$取模。

其中$1 \le n, q \le 2 \times {10}^5, 0 \le a_i, v \le {10}^9$。

</details>

<details>
<summary>思路</summary>

手推$n=4$的例子然后找规律，发现有

$$
\begin{align*}
D_x &= \sum_{i = 1}^{x} \frac{(x - i + 2)(x - i + 1)}{2} a_i\\
    &= \frac{1}{2} \sum_{i = 1}^{x} i^2a_i - \frac{2x + 3}{2} \sum_{i = 1}^{x} ia_i + \frac{(x + 1)(x + 1)}{2} \sum_{i = 1}^{x} a_i
\end{align*}
$$

然后就是用数据结构分别维护$a_i, ia_i, i^2a_i$的前缀和就行了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: F - Cumulative Cumulative Cumulative Sum
// Contest: AtCoder - Tokio Marine & Nichido Fire Insurance Programming Contest 2022（AtCoder
// Beginner Contest 256) URL: https://atcoder.jp/contests/abc256/tasks/abc256_f Memory Limit: 1024
// MB Time Limit: 2000 ms
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

template <typename T>
struct FenwickTree {
  int n;
  std::vector<T> c;
  FenwickTree(int _n) : n(_n), c(n + 1) {}
  inline int lb(int x) { return x & -x; }
  void add(int x, T d) {
    for (; x <= n; x += lb(x))
      c[x] = c[x] + d;
  }
  T getsum(int x) {
    T r = 0;
    for (; x; x -= lb(x))
      r = r + c[x];
    return r;
  }
  T getsum(int l, int r) { return getsum(r) - getsum(l - 1); }
};

void solve_case(int Case) {
  int n, q;
  std::cin >> n >> q;

  FenwickTree<Mint> a0(n), a1(n), a2(n);

  std::vector<Mint> a(n + 1);
  for (int i = 1; i <= n; ++i) {
    int x;
    std::cin >> x;
    a[i] = Mint(x);
    a0.add(i, a[i]);
    a1.add(i, Mint(i) * a[i]);
    a2.add(i, Mint(i) * Mint(i) * a[i]);
  }

  for (int i = 1; i <= q; ++i) {
    int op;
    std::cin >> op;
    if (op == 1) {
      int x, v;
      std::cin >> x >> v;
      Mint d = Mint(v) - Mint(a[x]);
      a0.add(x, d);
      d = d * Mint(x);
      a1.add(x, d);
      d = d * Mint(x);
      a2.add(x, d);
      a[x] = Mint(v);
    } else {
      int x;
      std::cin >> x;
      Mint ans = Mint(1) / Mint(2) * a2.getsum(x) -
                 (Mint(2) * Mint(x) + Mint(3)) / Mint(2) * a1.getsum(x) +
                 Mint(x + 1) * Mint(x + 2) / Mint(2) * a0.getsum(x);

      std::cout << ans.value() << "\n";
    }
  }
}

```

</details>

## [G - Black and White Stones](https://atcoder.jp/contests/abc256/tasks/abc256_g)

<details>
<summary>题意</summary>

有一个正$n$边形，它每个顶点上都有1个石头，每条边上（不包含顶点）有$d - 1$个石头，总共$nd$个石头。

石头可以染成黑色或者白色。

问有多少种方法使得每条边（包含顶点）上白色石头的数量相等，答案对$998244353$取模。

其中$3 \le n \le {10}^{12}, 1 \le d \le {10}^4$。

</details>

<details>
<summary>思路</summary>

枚举白色石头的数量，算这种情况下的方案数，然后累加。

假设要使每条边上的白色石头数量为$k$，这个可以DP结合矩阵快速幂来算。

首先，环的DP不好搞，按照惯例拆成链。就是把环的顶点拆成两个不相连的点分别连接两条边，然后就可以把环拆成$n$条链了。

令$dp_{s, t}$表示按上述方法生成的某条链，起点颜色为$s$，终点颜色为$t$对应的方案数，因为两端颜色确定了中间的应该有的白色石头数量也就确定了，方案数就是再算一次组合数的事情。

然后任意两条链的答案合并可以看成矩阵乘，就是一条链的结尾和另外一条链的开头颜色相同就可以把两者合并成一个点，也就是把两条链合并成一条链。然后这个过程是可以用矩阵快速幂加速计算的。

这样最后会得到一条$nd + 1$个节点的链的答案，链的答案算出来之后就可以映射回环了，具体就是链首尾节点颜色要一样。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: G - Black and White Stones
// Contest: AtCoder - Tokio Marine & Nichido Fire Insurance Programming Contest 2022（AtCoder
// Beginner Contest 256) URL: https://atcoder.jp/contests/abc256/tasks/abc256_g Memory Limit: 1024
// MB Time Limit: 2000 ms
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

template <typename ValueType>
class Matrix {
 private:
  using MatrixDataType = std::vector<std::vector<ValueType>>;
  using RowDataType = std::vector<ValueType>;

  size_t n_;
  size_t m_;
  MatrixDataType a_;

 public:
  static Matrix zero(size_t n, size_t m) {
    MatrixDataType data(n, RowDataType(m, 0));
    return Matrix(move(data));
  }

  static Matrix one(size_t n, size_t m) {
    assert(n == m);
    MatrixDataType data(n, RowDataType(m, 0));
    for (size_t i = 0; i < n; ++i) {
      data[i][i] = 1;
    }
    return Matrix(move(data));
  }

 public:
  Matrix() : n_(0), m_(0) {}

  Matrix(const MatrixDataType& a) : n_(a.size()), m_(a[0].size()), a_(a) {}

  Matrix(const Matrix& matrix) : n_(matrix.n_), m_(matrix.m_), a_(matrix.a_) {}

  size_t n() const { return n_; }

  size_t m() const { return m_; }

  RowDataType& operator[](size_t row) { return a_[row]; }

  const ValueType& at(size_t row, size_t col) const { return a_[row][col]; }

  friend Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
    assert(lhs.m() == rhs.n());

    Matrix result = zero(lhs.n(), rhs.m());
    for (size_t i = 0; i < lhs.n(); ++i) {
      for (size_t j = 0; j < lhs.m(); ++j) {
        for (size_t k = 0; k < rhs.m(); ++k) {
          result[i][k] = result.at(i, k) + lhs.at(i, j) * rhs.at(j, k);
        }
      }
    }
    return result;
  }

  void operator=(const Matrix& rhs) {
    n_ = rhs.n_;
    m_ = rhs.m_;
    a_ = rhs.a_;
  }

  friend Matrix operator^(const Matrix& lhs, size_t exponent) {
    assert(lhs.n() == lhs.m());

    Matrix result = one(lhs.n(), lhs.m());
    Matrix base = lhs;
    while (exponent) {
      if (exponent & 1)
        result = result * base;
      base = base * base;
      exponent >>= 1;
    }
    return result;
  }
};
template <typename ValueType>
std::string to_string(const Matrix<ValueType>& matrix) {
  std::stringstream ss;
  ss << "[";
  for (size_t i = 0; i < matrix.n(); ++i) {
    ss << "[";
    for (size_t j = 0; j < matrix.m(); ++j) {
      ss << matrix.at(i, j).value() << ",]"[j == matrix.m() - 1];
    }
    ss << ",]"[i == matrix.n() - 1];
  }
  return ss.str();
}

void solve_case(int Case) {
  i64 n, d;
  std::cin >> n >> d;

  std::vector<Mint> f(d + 1, Mint(0)), g(d + 1, Mint(0));
  f[0] = Mint(1);
  for (int i = 1; i <= d; ++i)
    f[i] = f[i - 1] * Mint(i);
  g[d] = f[d].inv();
  for (int i = d - 1; i >= 0; --i)
    g[i] = g[i + 1] * Mint(i + 1);
  auto C = [&](int n, int m) -> Mint {
    if (n < 0 || m < 0 || m > n)
      return Mint(0);
    return f[n] * g[m] * g[n - m];
  };

  Mint ans = 0;
  for (int k = 0; k <= d + 1; ++k) {
    Matrix<Mint> dp = std::vector<std::vector<Mint>>(
        {{C(d - 1, k), C(d - 1, k - 1)}, {C(d - 1, k - 1), C(d - 1, k - 2)}});
    dp = dp ^ n;
    ans = ans + dp[0][0] + dp[1][1];
  }

  std::cout << ans.value() << "\n";
}

```

</details>

## [Ex - I like Query Problem](https://atcoder.jp/contests/abc256/tasks/abc256_h)

<details>
<summary>题意</summary>

有一个长度为$n$的数组$a$，要求回答$q$个询问，询问共有3中类型：
1. `1 l r x`：区间整除
2. `2 l r x`：区间置数
3. `3 l r`：区间和

其中$1 \le n \le 5 \times {10}^5, 1 \le q \le {10}^5$。

</details>

<details>
<summary>思路</summary>

先不考虑操作1，就是简单线段树。

然后操作1的话，如果一个区间内元素相同的话，可以看成是区间置数，不然就继续拆分区间。

有点像segment tree beats，复杂度$O(\text{能过})$。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: Ex - I like Query Problem
// Contest: AtCoder - Tokio Marine & Nichido Fire Insurance Programming Contest 2022（AtCoder
// Beginner Contest 256) URL: https://atcoder.jp/contests/abc256/tasks/abc256_h Memory Limit: 1024
// MB Time Limit: 8000 ms
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

struct Node {
  i64 sum;
  int sz, mx, mn;
  int fset;
};
Node merge(Node a, Node b) {
  Node c;
  c.sum = a.sum + b.sum;
  c.sz = a.sz + b.sz;
  c.mx = std::max(a.mx, b.mx);
  c.mn = std::min(a.mn, b.mn);
  return c;
}

const int N = 5e5 + 5;
Node nd[N << 2];
int a[N];

void push_up(int x) {
  nd[x].sum = nd[x << 1].sum + nd[x << 1 | 1].sum;
  nd[x].mx = std::max(nd[x << 1].mx, nd[x << 1 | 1].mx);
  nd[x].mn = std::min(nd[x << 1].mn, nd[x << 1 | 1].mn);
}

void change_set(int x, int v) {
  nd[x].sum = i64(1) * nd[x].sz * v;
  nd[x].fset = nd[x].mx = nd[x].mn = v;
}

void change_div(int x, int v) {
  if (nd[x].mx == nd[x].mn) {
    change_set(x, nd[x].mx / v);
  } else {
    change_div(x << 1, v);
    change_div(x << 1 | 1, v);
    push_up(x);
  }
}

void push_down(int x) {
  if (nd[x].fset != -1) {
    change_set(x << 1, nd[x].fset);
    change_set(x << 1 | 1, nd[x].fset);
    nd[x].fset = -1;
  }
}

void build(int x, int l, int r) {
  nd[x].fset = -1;
  nd[x].sz = r - l + 1;
  if (l == r) {
    nd[x].sum = nd[x].mx = nd[x].mn = a[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(x << 1, l, mid);
  build(x << 1 | 1, mid + 1, r);
  push_up(x);
}

void update_div(int x, int l, int r, int L, int R, int v) {
  if (l == L && r == R) {
    change_div(x, v);
    return;
  }
  push_down(x);
  int mid = (l + r) >> 1;
  if (R <= mid)
    update_div(x << 1, l, mid, L, R, v);
  else if (L > mid)
    update_div(x << 1 | 1, mid + 1, r, L, R, v);
  else {
    update_div(x << 1, l, mid, L, mid, v);
    update_div(x << 1 | 1, mid + 1, r, mid + 1, R, v);
  }
  push_up(x);
}

void update_set(int x, int l, int r, int L, int R, int v) {
  if (l == L && r == R) {
    change_set(x, v);
    return;
  }
  push_down(x);
  int mid = (l + r) >> 1;
  if (R <= mid)
    update_set(x << 1, l, mid, L, R, v);
  else if (L > mid)
    update_set(x << 1 | 1, mid + 1, r, L, R, v);
  else {
    update_set(x << 1, l, mid, L, mid, v);
    update_set(x << 1 | 1, mid + 1, r, mid + 1, R, v);
  }
  push_up(x);
}

Node query(int x, int l, int r, int L, int R) {
  if (l == L && r == R)
    return nd[x];
  push_down(x);
  int mid = (l + r) >> 1;
  if (R <= mid)
    return query(x << 1, l, mid, L, R);
  else if (L > mid)
    return query(x << 1 | 1, mid + 1, r, L, R);
  return merge(query(x << 1, l, mid, L, mid), query(x << 1 | 1, mid + 1, r, mid + 1, R));
}

void solve_case(int Case) {
  int n, q;
  std::cin >> n >> q;

  for (int i = 1; i <= n; ++i)
    std::cin >> a[i];
  build(1, 1, n);

  for (int i = 1; i <= q; ++i) {
    int op;
    std::cin >> op;
    if (op == 1) {
      int l, r, x;
      std::cin >> l >> r >> x;
      update_div(1, 1, n, l, r, x);
    } else if (op == 2) {
      int l, r, x;
      std::cin >> l >> r >> x;
      update_set(1, 1, n, l, r, x);
    } else if (op == 3) {
      int l, r;
      std::cin >> l >> r;
      std::cout << query(1, 1, n, l, r).sum << "\n";
    }
  }
}

```

</details>