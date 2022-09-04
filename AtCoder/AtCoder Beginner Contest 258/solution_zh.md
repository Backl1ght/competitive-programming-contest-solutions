# AtCoder Beginner Contest 258

咕咕咕咕。

## [E - Packing Potatoes](https://atcoder.jp/contests/abc258/tasks/abc258_e)

<details>
<summary>题意</summary>

有无穷多个土豆，第$i$个土豆的质量为$w_i$，给定$w$的前$n$项，然后$w_{i + n} = w_i$。

有一个打包流程，一个袋子有个参数$x$，不断将土豆放进这个袋子知道袋子中土豆质量和大于等于$x$，然后封袋并使用一个新袋子继续打包。

要求回答$q$个询问，第$i$个询问需要回答第$k_i$个袋子里装了多少个土豆。

其中$1 \le n, q \le 2 \times {10}^5, 1 \le x, w_i \le {10}^9, 1 \le k_i \le {10}^{12}$。

</details>

<details>
<summary>思路</summary>

倍增。

首先，从第$0 \le i < n$个土豆开始打包，所用的袋子中土豆数量以及新袋子从哪一个土豆开始，这个可以二分求。

然后，这个相当于走$1$步结果，通过binary lifting可以处理出走$2^j$步的结果。

最后再将$k$拆分成二进制然后走就可以了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: E - Packing Potatoes
// Contest: AtCoder - AtCoder Beginner Contest 258
// URL: https://atcoder.jp/contests/abc258/tasks/abc258_e
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
  int n, q;
  i64 x;
  std::cin >> n >> q >> x;

  std::vector<i64> w(n), s(n + 1);
  for (int i = 0; i < n; ++i) {
    std::cin >> w[i];
    s[i + 1] = s[i] + w[i];
  }

  auto get = [&](i64 p) { return (p / n) * s[n] + s[p % n]; };

  std::vector<int> c(n);
  i64 lg = 40;
  std::vector<std::vector<int>> f(lg + 1, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    i64 l = i + 1, r = i + x, mid, nxt = i + 1;
    while (l <= r) {
      mid = (l + r) >> 1;
      if (get(mid) - s[i] >= x)
        r = mid - 1, nxt = mid;
      else
        l = mid + 1;
    }

    f[0][i] = nxt % n;
    c[i] = nxt - i;
  }
  logd(c);

  for (int i = 1; i <= lg; ++i) {
    for (int j = 0; j < n; ++j) {
      f[i][j] = f[i - 1][f[i - 1][j]];
    }
  }

  for (int i = 0; i < q; ++i) {
    i64 k;
    std::cin >> k;
    --k;

    int p = 0;
    for (int j = 40; j >= 0; --j) {
      if ((k >> j) & 1) {
        p = f[j][p];
      }
    }

    std::cout << c[p] << "\n";
  }
}

```

</details>

## [F - Main Street](https://atcoder.jp/contests/abc258/tasks/abc258_f)

<details>
<summary>题意</summary>

二维平面上有多条路，对于任意整数$n$，$x = n$是一条路，$y = n$是一条路。

然后，在这些路中$x = bn$和$y = bn$是主路。

支持往上下左右4个方向移动一步，在主路上耗时为1秒，在其他路上耗时为$k$秒。

问从点$(sx, sy)$移动到点$(tx, ty)$的最小耗时。

其中$1 \le b, k \le {10}^9, 0 \le sx, sy, tx, ty \le {10}^9$。

</details>

<details>
<summary>思路</summary>

答案最差不会超过两点manhattan距离的$k$倍。

然后可能可以借助主路来降低耗时，这个需要先走到主路上。

易得只需要考虑直线走到主路上的路线，所以起点和终点可以对应到4个主路上的点，分别记为$S$和$T$。

为了方便计算，可以将路径拆分成3段：从起点走到$S$中的点，在主路上从$S$中的点走到$T$中的点，最后从$T$中的点走到终点。

然后分别枚举$S$和$T$中的点，计算代价取最小值即可。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: F - Main Street
// Contest: AtCoder - AtCoder Beginner Contest 258
// URL: https://atcoder.jp/contests/abc258/tasks/abc258_f
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

void solve_case(int Case) {
  auto manhattan = [](const std::array<i64, 2>& p1, const std::array<i64, 2>& p2) -> i64 {
    return std::abs(p2[0] - p1[0]) + std::abs(p2[1] - p1[1]);
  };

  i64 B, K;
  i64 sx, sy, tx, ty;
  std::cin >> B >> K;
  std::cin >> sx >> sy >> tx >> ty;

  auto get1 = [&B, &K, &manhattan](i64 x, i64 y) -> std::vector<std::array<i64, 3>> {
    std::vector<i64> X = {x / B * B, (x / B * B) + B};
    std::vector<i64> Y = {y / B * B, (y / B * B) + B};

    std::vector<std::array<i64, 3>> result;
    for (i64 nx : X) {
      result.push_back({nx, y, K * manhattan({x, y}, {nx, y})});
    }
    for (i64 ny : Y) {
      result.push_back({x, ny, K * manhattan({x, y}, {x, ny})});
    }

    return result;
  };

  auto get2 = [&B, &K, &manhattan](i64 x1, i64 y1, i64 x2, i64 y2) -> i64 {
    i64 cost;
    if (x1 % B == 0 && x2 % B == 0 && y1 / B == y2 / B) {
      cost = std::min(K * std::abs(x2 - x1) + std::abs(y2 - y1),
                      std::abs(x2 - x1) + std::min(y1 % B + y2 % B, 2 * B - y1 % B - y2 % B));
    } else if (y1 % B == 0 && y2 % B == 0 && x1 / B == x2 / B) {
      cost = std::min(std::abs(x2 - x1) + K * std::abs(y2 - y1),
                      std::abs(y2 - y1) + std::min(x1 % B + x2 % B, 2 * B - x1 % B - x2 % B));
    } else {
      cost = manhattan({x1, y1}, {x2, y2});
    }
    return cost;
  };

  i64 ans = K * manhattan({sx, sy}, {tx, ty});
  auto S = get1(sx, sy);
  auto T = get1(tx, ty);
  for (const auto& [x1, y1, c1] : S) {
    for (const auto& [x2, y2, c2] : T) {
      ans = std::min(ans, c1 + c2 + get2(x1, y1, x2, y2));
    }
  }

  std::cout << ans << "\n";
}

```

</details>

## [G - Triangle](https://atcoder.jp/contests/abc258/tasks/abc258_g)

靠`std::bitset`加速能暴力水过去。

## [Ex - Odd Steps](https://atcoder.jp/contests/abc258/tasks/abc258_h)

记 $T = \{0, 1, \dots , S \} \setminus \{A_1, A_2, \dots, A_n\}$，则题目可以转化成从 $T$ 中选择多个整数并满足以下两个条件的方案数：
-  $0$ 和 $S$ 被选中。
-  若将所选的数升序排序，则相邻整数奇偶性不同。

考虑这样一个 DP ，从小到大选择整数，令 $dp_{i, 0/1}$ 表示考虑了 $T$ 中小于等于 $i$ 的整数，且已选择的最大数奇偶性和$i$不同/相同。

若$i \in \{A_1, A_2, \dots, A_n\}$，则有

$$
\left[
\begin{matrix}
dp_{i, 0} & dp_{i, 1}\\
\end{matrix}
\right]=
\left[
\begin{matrix}
dp_{i - 1, 0} & dp_{i - 1, 1}\\
\end{matrix}
\right]
*
\left[
\begin{matrix}
0 & 1\\
1 & 0\\
\end{matrix}
\right]
$$

若$i \notin \{A_1, A_2, \dots, A_n\}$，则有

$$
\left[
\begin{matrix}
dp_{i, 0} & dp_{i, 1}\\
\end{matrix}
\right]=
\left[
\begin{matrix}
dp_{i - 1, 0} & dp_{i - 1, 1}\\
\end{matrix}
\right]
*
\left[
\begin{matrix}
1 & 1\\
1 & 0\\
\end{matrix}
\right]
$$

$S$ 很大，直接 DP 时间复杂度爆炸。但是注意到 $N$ 其实不大，所以有很多连续的位置都是连着用第二种方式转移。用 $\{A_1, A_2, \dots, A_n\}$ 将 $\{0, 1, \dots, S\}$ 分割成多段，前面说的连续的位置可以用矩阵快速幂加速，这样就做到了 $O(N \log S)$ 的时间复杂度。

<details>
<summary>AC代码</summary>

```cpp
// Problem: Ex - Odd Steps
// Contest: AtCoder - AtCoder Beginner Contest 258
// URL: https://atcoder.jp/contests/abc258/tasks/abc258_h
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
  Modular(ValueType value = 0) : value_(normalize(value)) {}

  Modular(SupperType value) : value_(normalize(value % mod_)) {}

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

  std::string to_string() const { return std::string(value_); }

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

template <typename ValueType>
class Matrix {
 private:
  using MatrixDataType = std::vector<std::vector<ValueType>>;
  using RowDataType = std::vector<ValueType>;

  int n_;
  int m_;
  MatrixDataType a_;

 public:
  static Matrix zero(int n, int m) {
    MatrixDataType data(n, RowDataType(m, 0));
    return Matrix(move(data));
  }

  static Matrix one(int n, int m) {
    assert(n == m);
    MatrixDataType data(n, RowDataType(m, 0));
    for (int i = 0; i < n; ++i) {
      data[i][i] = 1;
    }
    return Matrix(move(data));
  }

 public:
  Matrix() : n_(0), m_(0) {}

  Matrix(const MatrixDataType& a) : n_(a.size()), m_(a[0].size()), a_(a) {}

  Matrix(const Matrix& matrix) : n_(matrix.n_), m_(matrix.m_), a_(matrix.a_) {}

  int n() const { return n_; }

  int m() const { return m_; }

  RowDataType& operator[](int row) { return a_[row]; }

  const ValueType& at(int row, int col) const { return a_[row][col]; }

  friend Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
    assert(lhs.m() == rhs.n());

    Matrix result = zero(lhs.n(), rhs.m());
    for (int i = 0; i < lhs.n(); ++i) {
      for (int j = 0; j < lhs.m(); ++j) {
        for (int k = 0; k < rhs.m(); ++k) {
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

  friend Matrix operator^(const Matrix& lhs, int64_t exponent) {
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

  std::string to_string() const {
    std::stringstream ss;
    ss << "[";
    for (int i = 0; i < n_; ++i) {
      ss << "[";
      for (int j = 0; j < m_; ++j) {
        ss << a_[i][j].value() << ",]"[j == m_ - 1];
      }
      ss << ",]"[i == n_ - 1];
    }
    return ss.str();
  }
};

void solve_case(int Case) {
  int n;
  std::cin >> n;

  i64 s;
  std::cin >> s;

  std::vector<i64> a(n + 1);
  a[0] = 0;
  for (int i = 1; i <= n; ++i)
    std::cin >> a[i];

  Matrix<Mint> T1({{Mint(1), Mint(1)}, {Mint(1), Mint(0)}});
  Matrix<Mint> T2({{Mint(0), Mint(1)}, {Mint(1), Mint(0)}});

  Matrix<Mint> r({{Mint(1), Mint(0)}});
  for (int i = 0; i < n; ++i) {
    i64 d = a[i + 1] - 1 - a[i];
    r = r * (T1 ^ d);
    r = r * T2;
  }
  r = r * (T1 ^ (s - a[n]));

  std::cout << r[0][1].value() << "\n";
}

```

</details>