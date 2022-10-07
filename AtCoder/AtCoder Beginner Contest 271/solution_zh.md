# AtCoder Beginner Contest 271

## [E - Subsequence Path](https://atcoder.jp/contests/abc271/tasks/abc271_e)

最短路问题变种， Dijkstra 最短路改改就行了。

<details>
<summary>AC代码</summary>

```cpp
// Problem: E - Subsequence Path
// Contest: AtCoder - KYOCERA Programming Contest 2022（AtCoder Beginner Contest
// 271） URL: https://atcoder.jp/contests/abc271/tasks/abc271_e Memory Limit:
// 1024 MB Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO \
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

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

template <typename T>
using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

void SolveCase(int Case) {
  int n, m, k;
  std::cin >> n >> m >> k;

  std::vector<std::vector<std::array<int, 3>>> g(n);
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    std::cin >> a >> b >> c;
    --a, --b;
    g[a].push_back({c, i, b});
  }

  std::vector<std::vector<int>> p(m);
  for (int i = 0; i < k; ++i) {
    int x;
    std::cin >> x;
    --x;
    p[x].push_back(i);
  }

  const i64 INF = INT64_C(0x3f3f3f3f3f3f3f3f);
  min_heap<std::array<i64, 3>> q;
  std::vector<std::map<int, i64>> dis(n);
  std::vector<std::set<int>> vis(n);

  dis[0][-1] = 0;
  q.push({0, -1, 0});
  while (!q.empty()) {
    auto [c, last, u] = q.top();
    q.pop();

    if (vis[u].count(last))
      continue;
    vis[u].insert(last);

    if (u == n - 1) {
      std::cout << c << "\n";
      return;
    }

    for (auto [w, e, v] : g[u]) {
      auto it = std::upper_bound(p[e].begin(), p[e].end(), last);
      if (it == p[e].end())
        continue;
      int next = *it;

      if (!dis[v].count(next) || c + w < dis[v][next]) {
        dis[v][next] = c + w;
        q.push({dis[v][next], next, v});
      }
    }
  }

  std::cout << "-1\n";
}

```

</details>

## [F - XOR on Grid Path](https://atcoder.jp/contests/abc271/tasks/abc271_f)

虽然 $n$ 较小，但 $(1, 1) \to (n, n)$ 不同的路径数量 $\binom{2n - 1}{n - 1}$ 还是比较大的，没办法直接爆搜，考虑使用 meet in the middle 来优化爆搜复杂度。

把 $(1, 1) \to (n, n)$ 的路径拆分成 $(1, 1) \to (x, y)$ 和 $(x, y) \to (n, n)$ 两段，其中 $(x, y)$ 位于副对角线上。两部分的不同的路径数量为 $\sum_{x = 1}^{n} \binom{x + y - 1}{x - 1} = O(2^{n - 1})$ 。

最后枚举一下 $(x, y)$ 合并两段的答案即可。

<details>
<summary>AC代码</summary>

```cpp
// Problem: F - XOR on Grid Path
// Contest: AtCoder - KYOCERA Programming Contest 2022（AtCoder Beginner Contest
// 271） URL: https://atcoder.jp/contests/abc271/tasks/abc271_f Memory Limit:
// 1024 MB Time Limit: 3000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO \
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

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
  auto merge = [](std::map<int, i64>& a, std::map<int, i64>& b, int v) {
    std::map<int, i64> c;
    for (auto [x, y] : a) {
      i64& z = c[x ^ v];
      z = z + y;
    }
    for (auto [x, y] : b) {
      i64& z = c[x ^ v];
      z = z + y;
    }
    return c;
  };

  auto calc = [](std::map<int, i64>& a, std::map<int, i64>& b, int v) {
    i64 r(0);
    for (auto& [x, y] : a) {
      if (!b.count(x ^ v))
        continue;
      r = r + y * b[x ^ v];
    }
    return r;
  };

  int n;
  std::cin >> n;

  std::vector<std::vector<int>> a(n + 1, std::vector<int>(n + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      std::cin >> a[i][j];
    }
  }

  std::vector<std::vector<std::map<int, i64>>> dp1(
      n + 2, std::vector<std::map<int, i64>>(n + 2));

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (i + j > n + 1)
        continue;

      if (i == 1 && j == 1) {
        dp1[i][j][a[i][j]] = 1;
      } else {
        dp1[i][j] = merge(dp1[i - 1][j], dp1[i][j - 1], a[i][j]);
      }
      // logd(i, j, dp1[i][j]);
    }
  }

  std::vector<std::vector<std::map<int, i64>>> dp2(
      n + 2, std::vector<std::map<int, i64>>(n + 2));
  for (int i = n; i >= 1; --i) {
    for (int j = n; j >= 1; --j) {
      if (i + j < n + 1)
        continue;

      if (i == n && j == n) {
        dp2[i][j][a[i][j]] = 1;
      } else {
        dp2[i][j] = merge(dp2[i + 1][j], dp2[i][j + 1], a[i][j]);
      }
      // logd(i, j, dp2[i][j]);
    }
  }

  i64 ans(0);
  for (int i = 1; i <= n; ++i) {
    int j = n + 1 - i;

    auto& x = dp1[i][j];
    auto& y = dp2[i][j];
    if (x.size() < y.size()) {
      ans = ans + calc(x, y, a[i][j]);
    } else {
      ans = ans + calc(y, x, a[i][j]);
    }
  }

  std::cout << ans << "\n";
}

```

</details>

## [G - Access Counter](https://atcoder.jp/contests/abc271/tasks/abc271_g)

记 $p_i$ 为 $i$ 点发生了一次访问的概率， $q$ 表示连续一天都不发生访问的概率，即 $q = \prod_{i = 0}^{23} p_i$。

令 $dp_{i, j}$ 表示上一次访问发生在 $i$ 点，当前访问发生在 $j$ 点的概率。中间可能间隔多天，枚举间隔的天数，则有
$$
\begin{aligned}
dp_{i, j}
&= \sum_{x = 0}^{+\infin} q^x \prod_{k = i + 1}^{j - 1} (1 - p_k) p_j\\
&=\frac{\prod_{k = i + 1}^{j - 1} (1 - p_k) p_j}{1 - q}
\end{aligned}
$$

由于是从 $0$ 点开始计时的，所以 $dp_{23, i}$ 还等价于第一次访问发生在 $i$ 点的概率。

记 $dp^{2}_{i, j} = \sum_{k = 0}^{23} dp_{i, k} dp_{k, j}$ ，则 $dp^{2}_{i, j}$ 表示上上次访问发生在 $i$ 点，当前访问发生在 $j$ 点的概率。$dp^{2}_{23, i}$ 表示第二次访问发生在 $i$ 点的概率。

以此类推有 $dp^{n}_{23, i}$ 表示第 $n$ 次访问发生在 $i$ 点的概率，根据这个就可以算出第 $n$ 次访问由 Aoki 操作的概率。

然后矩阵快速幂求 $dp^{n}_{i, j}$ 就完事了。

<details>
<summary>AC代码</summary>

```cpp
// Problem: G - Access Counter
// Contest: AtCoder - KYOCERA Programming Contest 2022（AtCoder Beginner Contest
// 271） URL: https://atcoder.jp/contests/abc271/tasks/abc271_g Memory Limit:
// 1024 MB Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO \
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

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

template <typename T, typename... Args>
auto n_vector(size_t n, Args&&... args) {
  if constexpr (sizeof...(args) == 1) {
    return std::vector<T>(n, args...);
  } else {
    return std::vector(n, n_vector<T>(args...));
  }
}

void SolveCase(int Case) {
  i64 n;
  int x100, y100;
  std::cin >> n >> x100 >> y100;

  std::string s;
  std::cin >> s;

  Mint x = Mint(x100) / 100;
  Mint y = Mint(y100) / 100;

  std::vector<Mint> p(24);
  for (int i = 0; i < 24; ++i) {
    p[i] = s[i] == 'T' ? x : y;
  }

  Mint q = 1;
  for (int i = 0; i < 24; ++i) {
    q = q * (1 - p[i]);
  }

  auto a = Matrix<Mint>(n_vector<Mint>(24, 24, Mint(0)));
  for (int i = 0; i < 24; ++i) {
    for (int j = 0; j < 24; ++j) {
      Mint temp = p[i];
      for (int k = (j + 1) % 24; k != i; k = (k + 1) % 24) {
        temp = temp * (1 - p[k]);
      }
      a[j][i] = a[j][i] + temp / (1 - q);
    }
  }
  a = a ^ n;

  Mint ans = 0;
  for (int i = 0; i < 24; ++i) {
    if (s[i] == 'A') {
      ans = ans + a[23][i];
    }
  }
  std::cout << ans.value() << "\n";
}

```

</details>

## [Ex - General General](https://atcoder.jp/contests/abc271/tasks/abc271_h)

为了减少讨论，可以通过转换座标系来使 $a$ 和 $b$ 均大于等于 $0$。

假设最优操作时，操作 $i$ 使用了 $c_i$ 次，则 $c_i$ 可以拆分成多个 $2^x$ 相加。

记题目给定的操作为基本操作，基本操作叠加可以构成高级操作，例如操作1和操作2叠加可以构成 $(+2, +1)$。记叠加时每个操作至多可以使用一次，这样构造出新的操作集合 $S = {(dx, dy, z)}$，其中$dx, dy, z$ 分别表示两个轴上的移动量，以及这个操作使用的基本操作数量。 $(dx, dy)$ 可能会有重复，保留 $z$ 最小的即可。此后只需要考虑 $S$ 中的操作即可。

现在最优操作就可以分解为 $2^0$ 个操作$op_0$， $2^1$ 个操作 $op_1$，$\dots$，$2^{31}$ 个操作$op_{31}$，其中 $op_i \in S$。 $S$ 中的操作在单个轴上的便宜量至多为$3$，考虑从低位到高位跑DP。

记 $dp_{i, j, k}$ 表示第 $i$ 位上，横座标的取值为 $j$，纵座标的取值为 $k$的最小操作数。其中 $j, k$的取值范围为 $[-3, 3]$ 。

转移的时候就枚举 $S$ 中的操作转移，转移过程中需要保证每个座标轴上当前位取值和目标位置相同，再模拟一下进位和借位就可以了。

<details>
<summary>AC代码</summary>

```cpp
// Problem: Ex - General General
// Contest: AtCoder - KYOCERA Programming Contest 2022（AtCoder Beginner Contest
// 271） URL: https://atcoder.jp/contests/abc271/tasks/abc271_h Memory Limit:
// 1024 MB Time Limit: 5000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO \
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

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
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    SolveCase(t);
  }
  return 0;
}

void Initialize() {}

const int d[8][2] = {{1, 0},  {1, 1},   {0, 1},  {-1, 1},
                     {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

void SolveCase(int Case) {
  int a, b;
  std::cin >> a >> b;
  std::string s;
  std::cin >> s;

  // make sure that a and b greater than or equal to 0
  if (a < 0) {
    a = -a;
    std::swap(s[0], s[4]);
    std::swap(s[1], s[3]);
    std::swap(s[5], s[7]);
  }
  if (b < 0) {
    b = -b;
    std::swap(s[1], s[7]);
    std::swap(s[2], s[6]);
    std::swap(s[3], s[5]);
  }

  std::map<std::pair<int, int>, int> trans_map;
  for (int mask = 0; mask < (1 << 8); ++mask) {
    bool ok = true;
    int dx = 0, dy = 0, z = 0;
    for (int i = 0; i < 8; ++i) {
      if (mask >> i & 1) {
        if (s[i] == '0') {
          ok = false;
          break;
        }

        dx += d[i][0];
        dy += d[i][1];
        z += 1;
      }
    }

    if (not ok)
      continue;

    if (!trans_map.count({dx, dy}))
      trans_map[{dx, dy}] = z;
    else
      trans_map[{dx, dy}] = std::min(trans_map[{dx, dy}], z);
  }

  std::vector<std::array<int, 3>> trans;
  for (auto [dxy, z] : trans_map) {
    auto [dx, dy] = dxy;
    trans.push_back({dx, dy, z});
  }

  const i64 INF = INT64_C(0x3f3f3f3f3f3f3f3f);
  const int offset = 4;
  std::vector<std::vector<i64>> dp(8, std::vector<i64>(8, INF));
  dp[offset][offset] = 0;

  for (int digit = 0; digit < 32; ++digit) {
    std::vector<std::vector<i64>> next(8, std::vector<i64>(8, INF));

    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        for (auto [dx, dy, z] : trans) {
          int ni = i - offset + dx;
          int nj = j - offset + dy;

          // make sure that each bit is same with a or b
          if ((ni % 2 + a % 2) % 2 != 0)
            continue;
          if ((nj % 2 + b % 2) % 2 != 0)
            continue;

          // borrows and carries
          ni = ((ni - (std::abs(ni) % 2)) / 2) + offset;
          nj = ((nj - (std::abs(nj) % 2)) / 2) + offset;

          next[ni][nj] = std::min(next[ni][nj], dp[i][j] + (i64(z) << digit));
        }
      }
    }

    dp = std::move(next);
    a >>= 1;
    b >>= 1;
  }

  i64 ans = dp[offset][offset] == INF ? -1 : dp[offset][offset];
  std::cout << ans << "\n";
}

```

</details>