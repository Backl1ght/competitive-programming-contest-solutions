# AtCoder Beginner Contest 240

咕咕咕咕咕。

## [F - Sum Sum Max](https://atcoder.jp/contests/abc240/tasks/abc240_f)

以下标为横座标，值为纵座标，画出图像，则有 $C$ 的图像是多条和横座标平行的线段， $B$ 的图像是折线图， $A$ 的图像就是当 $B_i > 0$ 的时候上升反之下降的图像。如果转成连续函数就是二阶导数，一阶导数，和原函数的图像。

然后易得 $A$ 的最值仅在两端或者 $B$ 的零点出取得，而这些可能的位置至多有 $n+2$ 个。

然后就是模拟了。

<details>
<summary>AC代码</summary>

```cpp
// Problem: F - Sum Sum Max
// Contest: AtCoder - AtCoder Beginner Contest 240
// URL: https://atcoder.jp/contests/abc240/tasks/abc240_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO                       \
  std::ios::sync_with_stdio(false); \
  std::cin.tie(0);                  \
  std::cout.tie(0);

#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#define ASSERT(x) ;
#define serialize() std::string("")
#endif

using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;

void Initialize();
void SolveCase(int Case);

int main(int argc, char* argv[]) {
  CPPIO;

  Initialize();

  int T = 1;
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    SolveCase(t);
  }
  return 0;
}

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;
  logd(n, m);

  auto c2 = [](i64 x) {
    ++x;
    return x * (x - 1) / 2;
  };

  i64 ans = std::numeric_limits<i64>::min();
  i64 a = 0, b = 0;
  for (int i = 0; i < n; ++i) {
    i64 x, y;
    std::cin >> x >> y;

    if (i == 0) {
      ans = std::max(ans, x);
    }

    i64 nb = b + x * y;
    if (b > 0 && nb <= 0) {
      i64 z = b / (-x);
      ans = std::max(ans, a + b * z + c2(z) * x);
    }

    logd(x, y, b, c2(y), b * y + c2(y) * x);
    a = a + b * y + c2(y) * x;
    b = nb;

    ans = std::max(ans, a);
    logd(a, b);
  }

  std::cout << ans << "\n";
}

```

</details>

## [G - Teleporting Takahashi](https://atcoder.jp/contests/abc240/tasks/abc240_g)

不妨先把 $x, y, z$ 换成 $|x|, |y|, |z|$ ，易得这不会影响答案。

考虑依次解决一维，二维和三维的情况。

记 $x^+$ 表示往 $x$ 轴正方向走一步， $x^-$ 表示往 $x$ 轴负方向走一步。另外两个轴类似。

### 一维

$n$ 步从 $0$ 走到 $x$ 的方案数。

易得：当 $x > n$ 或 $n - x$ 是奇数时无解，否则记 $k = \frac{n - x}{2}$，则最终的操作有 $x + k$ 个 $x^+$ 和 $k$ 个 $x^-$ 。记 $f_1(k)$ 表示 $n = x + 2k$ 时的答案，则有 $f_1(k) = \binom{x + 2k}{k}$ ，含义为选从 $x + 2k$ 个位置中选择 $k$ 个放 $x^-$。

### 二维

$n$ 步从 $(0, 0)$ 走到 $(x, y)$ 的方案数。

无解的情况就不再赘述。

类似地，记 $f_2(k)$ 表示 $n = x + y + 2k$ 时的答案，则有
$$
\begin{aligned}
f_2(k)
&= \binom{x + y + 2k}{k} \sum_{i = 0}^{k} \binom{x + y + k}{x + i} \binom{k}{k - i}\\
&= \binom{x + y + 2k}{k} \binom{x + y + 2k}{x + k}
\end{aligned}
$$

大概含义是从 $x + y + 2k$ 个位置中选 $k$ 个放 $x^-$ 或者 $y^-$ ，然后枚举把 $k$ 个中的 $i$ 个往负方向走的操作分配给 $x$ 轴。然后求和这一项可以用 [Vandermonde's identity](https://en.wikipedia.org/wiki/Vandermonde%27s_identity) 化简。

$O(n)$ 预处理完组合数之后就可以 $O(1)$ 计算 $f_2(k)$ 了。

### 三维

继续枚举看把 $k$ 个中的 $i$ 分配给其中一个轴，然后问题就化简成二维的了。

$$
f_3(k) = \sum_{i = 0}^{k} \binom{n}{x + 2i} \binom{x + 2i}{i} f_2(k - i)
$$

大概含义是枚举分配 $i$ 次往负方向走的操作给 $x$ 轴，选 $x + 2i$ 个位置给 $x$ 轴， 这 $x + 2i$ 个位置中有 $i$ 个 $x^-$ ，剩余位置有二维子问题解决。

$f_3(\frac{n - x - y - z}{2})$ 即为答案。

<details>
<summary>AC代码</summary>

```cpp
// Problem: G - Teleporting Takahashi
// Contest: AtCoder - AtCoder Beginner Contest 240
// URL: https://atcoder.jp/contests/abc240/tasks/abc240_g
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO                       \
  std::ios::sync_with_stdio(false); \
  std::cin.tie(0);                  \
  std::cout.tie(0);

#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#define ASSERT(x) ;
#define serialize() std::string("")
#endif

using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;

void Initialize();
void SolveCase(int Case);

int main(int argc, char* argv[]) {
  CPPIO;

  Initialize();

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

  template <typename ExponentType>
  static ValueType power(ValueType value, ExponentType exponent) {
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

  Modular(ValueType value) : value_(normalize(value)) {}

  Modular(SupperType value) : value_(normalize(value % mod_)) {}

  ValueType value() const { return value_; }

  Modular inv() const { return Modular(power(value_, mod_ - 2)); }

  template <typename ExponentType>
  Modular power(ExponentType exponent) const {
    return Modular(power(value_, exponent));
  }

  friend Modular operator+(const Modular& lhs, const Modular& rhs) {
    ValueType result = lhs.value() + rhs.value() >= mod_
                           ? lhs.value() + rhs.value() - mod_
                           : lhs.value() + rhs.value();
    return Modular(result);
  }

  friend Modular operator-(const Modular& lhs, const Modular& rhs) {
    ValueType result = lhs.value() - rhs.value() < 0
                           ? lhs.value() - rhs.value() + mod_
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

  Mint gf(int n) { return f[n]; }
} binom(2e7 + 5);

void SolveCase(int Case) {
  int n, x, y, z;
  std::cin >> n >> x >> y >> z;

  x = std::abs(x);
  y = std::abs(y);
  z = std::abs(z);

  int w = n - x - y - z;
  if (w < 0 || w & 1) {
    std::cout << "0\n";
    return;
  }

  w = w / 2;
  Mint ans(0);
  for (int k = 0; k <= w; ++k) {
    ans = ans + binom(x + y + 2 * k, k) * binom(x + y + 2 * k, x + k) *
                    binom(n, z + 2 * (w - k)) * binom(z + 2 * (w - k), w - k);
  }

  std::cout << ans.value() << "\n";
}

```

</details>

## [Ex - Sequence of Substrings](https://atcoder.jp/contests/abc240/tasks/abc240_h)

令 $B = \sqrt{n}$，考虑长度小于等于 $B$ 的字符串即可。

> **证明**： 假设最终选出来的字符串长度依次为$a_1, \dots, a_m$，根据字典序严格递增有 $a_i \le a_{i + 1}$。如果 $a_{i + 1} > a_{i} + 1$ 其实可以把 $a_{i + 1}$ 砍成 $a_{i} + 1$，并保持答案不变。在这种情况下，尽可能去使 $a_m$ 大，最差情况下就是 $a_i$ 两两互不相等，然后就可以得出 $a_m \le O(\sqrt{n})$。

考虑这么一个 DP ， $dp_i$ 表示 $s(1, i)$ 的答案。把需要考虑的字符串字典序排序，从小到大遍历，假设遍历到 $s(l, r)$，那么就可以用 $1 + \max_{i = 1}^{l - 1} dp_i$ 来更新 $dp_r$。

字符串排序的话可以类似倍增后缀数组整个每次长度加一的版本，更新的话可以借助树状数组或者线段树加速。

复杂度大概是 $O(n \sqrt{n} \log n)$。

<details>
<summary>AC代码</summary>

```cpp
// Problem: Ex - Sequence of Substrings
// Contest: AtCoder - AtCoder Beginner Contest 240
// URL: https://atcoder.jp/contests/abc240/tasks/abc240_h
// Memory Limit: 1024 MB
// Time Limit: 5000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO                       \
  std::ios::sync_with_stdio(false); \
  std::cin.tie(0);                  \
  std::cout.tie(0);

#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#define ASSERT(x) ;
#define serialize() std::string("")
#endif

using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;

void Initialize();
void SolveCase(int Case);

int main(int argc, char* argv[]) {
  CPPIO;

  Initialize();

  int T = 1;
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    SolveCase(t);
  }
  return 0;
}

void Initialize() {}

template <typename T>
class FenwickTree {
 public:
  using Operator = std::function<T(const T&, const T&)>;

 private:
  inline int lb(int x) { return x & -x; }

 public:
  FenwickTree(int n, const T& init, const Operator& op = std::plus<T>())
      : n_(n),
        init_(init),
        c_(n_ + 1, init_),
        op_(op),
        t_(n_ + 1, -1),
        tag_(0) {}

  void Update(int x, T d) {
    for (; x <= n_; x += lb(x)) {
      if (t_[x] != tag_)
        c_[x] = init_;
      c_[x] = op_(c_[x], d);
      t_[x] = tag_;
    }
  }

  const T Query(int x) {
    T r = init_;
    for (; x; x -= lb(x)) {
      if (t_[x] == tag_)
        r = op_(r, c_[x]);
    }
    return r;
  }

  // TODO(backlight): add something to ensure that this can only be called when
  // op_ is inversable.
  const T Query(int l, int r) { return Query(r) - Query(l - 1); }

  // TODO(backlight): similar to range query.
  const T Kth(int k) {
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

  void Reset() { ++tag_; }

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

  std::string s;
  std::cin >> s;

  int B = std::sqrt(2 * n);

  std::vector<std::vector<int>> sa(B), rk(B);

  sa[0].reserve(n);
  for (char c : {'0', '1'}) {
    for (int i = 0; i < n; ++i) {
      if (s[i] == c)
        sa[0].push_back(i);
    }
  }
  rk[0].resize(n);
  for (int i = 0; i < n; ++i)
    rk[0][i] = s[i] - '0';

  for (int l = 1; l < B; ++l) {
    sa[l].reserve(n - l);
    for (char c : {'0', '1'}) {
      for (int i : sa[l - 1]) {
        if (i - 1 >= 0 && s[i - 1] == c)
          sa[l].push_back(i - 1);
      }
    }

    rk[l].resize(n - l);
    rk[l][0] = 0;
    for (int i = 1; i < n - l; ++i) {
      int j0 = sa[l][i - 1];
      int j1 = sa[l][i];

      if (s[j0] == s[j1] && rk[l - 1][j0 + 1] == rk[l - 1][j1 + 1])
        rk[l][j1] = rk[l][j0];
      else
        rk[l][j1] = rk[l][j0] + 1;
    }
  }

  std::vector<std::pair<int, int>> candidate;
  candidate.reserve(n * B);
  for (int i = 0; i < n; ++i)
    for (int l = 0; l < B && i + l < n; ++l)
      candidate.push_back({i, l});

  std::sort(candidate.begin(), candidate.end(),
            [&rk](const auto& lhs, const auto& rhs) -> bool {
              auto [li, llen] = lhs;
              auto [ri, rlen] = rhs;

              int l = std::min(llen, rlen);

              if (rk[l][li] != rk[l][ri])
                return rk[l][li] < rk[l][ri];
              else if (llen != rlen)
                return llen < rlen;
              else
                return li > ri;
            });

  FenwickTree<int> t(n, 0, [](int x, int y) { return std::max(x, y); });
  for (auto [i, l] : candidate) {
    ++i, ++l;
    t.Update(i + l - 1, t.Query(i - 1) + 1);
  }

  std::cout << t.Query(n) << "\n";
}

```

</details>

