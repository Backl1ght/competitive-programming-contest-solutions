# AtCoder Beginner Contest 270

咕咕咕。

## [D - Stones](https://atcoder.jp/contests/abc270/tasks/abc270_d)

冲了发贪心，然后 WA 。

然后想了个 DP，就令 $dp_{n, 0/1}$ 表示石头总数为 $n$ 时，先手/后手最多能拿多少个石头，然后跑个 $O(nk)$ 的DP就完事了。

<details>
<summary>AC代码</summary>

```cpp
// Problem: D - Stones
// Contest: AtCoder - TOYOTA MOTOR CORPORATION Programming Contest 2022(AtCoder Beginner Contest
// 270) URL: https://atcoder.jp/contests/abc270/tasks/abc270_d Memory Limit: 1024 MB Time Limit:
// 2000 ms
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
  int n, k;
  std::cin >> n >> k;

  std::vector<int> a(k);
  for (int i = 0; i < k; ++i)
    std::cin >> a[i];

  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(2, 0));
  dp[0][0] = 0;
  dp[0][1] = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = k - 1; j >= 0; --j) {
      if (i >= a[j]) {
        dp[i][0] = std::max(dp[i][0], dp[i - a[j]][1] + a[j]);
        dp[i][1] = i - dp[i][0];
      }
    }
  }
  logd(dp);

  std::cout << dp[n][0] << "\n";
}

```

</details>

## [E - Apple Baskets on Circle](https://atcoder.jp/contests/abc270/tasks/abc270_e)

记走一圈为一轮，可以把结果相同的轮的贡献合并到一起算，从而加速模拟。

假设 $a$ 按大小排序后的数组为 $b$，那么原过程等价于在 $b$ 上从左往右走的过程，假设走到了 $b_i$ ，则现在的一轮一轮等价于 $[i, n]$ 区间减 $1$ 。假设 $b_i$ 之前已经走了了 $d$ 轮，那么接下来 $\min(\lfloor \frac{k}{n - i} \rfloor, b_i - d)$ 轮的结果相同，这几轮的贡献可以 $O(1)$ 计算。

现在 $k$ 可能还有剩余但不足以走完一轮，模拟一下即可。

时间复杂度 $O(n \log n)$，瓶颈在于排序，模拟的部分复杂度为 $O(n)$。

<details>
<summary>AC代码</summary>

```cpp
// Problem: E - Apple Baskets on Circle
// Contest: AtCoder - TOYOTA MOTOR CORPORATION Programming Contest 2022(AtCoder Beginner Contest
// 270) URL: https://atcoder.jp/contests/abc270/tasks/abc270_e Memory Limit: 1024 MB Time Limit:
// 2000 ms
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
  int n;
  i64 k;
  std::cin >> n >> k;

  std::vector<i64> a(n);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i];

  auto b = a;
  std::sort(b.begin(), b.end());

  i64 d = 0;
  for (int i = 0; i < n; ++i) {
    i64 r = n - i;
    if (k < n - i)
      break;

    i64 x = std::min(k / (n - i), b[i] - d);
    logd(i, x);
    d += x;
    k -= x * r;
  }

  for (int i = 0; i < n; ++i)
    a[i] = std::max(i64(0), a[i] - d);
  logd(a);

  for (int i = 0; i < n; ++i) {
    if (a[i] > 0 && k > 0) {
      --a[i];
      --k;
    }
  }
  ASSERT(k == 0);

  for (int i = 0; i < n; ++i)
    std::cout << a[i] << " \n"[i + 1 == n];
}

```

</details>

## [F - Transportation](https://atcoder.jp/contests/abc270/tasks/abc270_f)

把机场和港口也看成节点的话，问题就转化成了的最小生成树问题。

然后可能会有不使用机场和港口的情况，机场和港口都可用可不用，一共 $4$ 种情况，那就跑 $4$ 次 Kruskal 最小生成树算法。

<details>
<summary>AC代码</summary>

```cpp
// Problem: F - Transportation
// Contest: AtCoder - TOYOTA MOTOR CORPORATION Programming Contest 2022(AtCoder Beginner Contest
// 270) URL: https://atcoder.jp/contests/abc270/tasks/abc270_f Memory Limit: 1024 MB Time Limit:
// 4000 ms
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
  auto kruskal = [](int n, std::vector<std::array<int, 4>> E) {
    std::sort(E.begin(), E.end());

    std::vector<int> f(n + 2);
    std::iota(f.begin(), f.end(), 0);

    std::function<int(int)> find = [&](int x) { return x == f[x] ? x : f[x] = find(f[x]); };

    i64 ans = 0;
    for (auto [w, _, u, v] : E) {
      int fu = find(u), fv = find(v);
      if (fu == fv)
        continue;

      f[fu] = fv;

      ans += w;
    }

    for (int i = 0; i < n; ++i)
      if (find(i) != find(0))
        return std::numeric_limits<i64>::max();

    return ans;
  };

  int n, m;
  std::cin >> n >> m;

  std::vector<std::array<int, 4>> E;

  int airport = n, harbor = n + 1;
  std::vector<int> x(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> x[i];
  }
  std::vector<int> y(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> y[i];
  }
  std::vector<int> a(m), b(m), z(m);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    --u, --v;
    a[i] = u, b[i] = v, z[i] = w;
  }

  i64 ans = std::numeric_limits<i64>::max();
  {
    std::vector<std::array<int, 4>> E;
    for (int i = 0; i < n; ++i) {
      E.push_back({x[i], 1, i, airport});
    }
    for (int i = 0; i < n; ++i) {
      E.push_back({y[i], 1, i, harbor});
    }
    for (int i = 0; i < m; ++i) {
      E.push_back({z[i], 0, a[i], b[i]});
    }
    ans = std::min(ans, kruskal(n, E));
  }
  {
    std::vector<std::array<int, 4>> E;
    for (int i = 0; i < n; ++i) {
      E.push_back({y[i], 1, i, harbor});
    }
    for (int i = 0; i < m; ++i) {
      E.push_back({z[i], 0, a[i], b[i]});
    }
    ans = std::min(ans, kruskal(n, E));
  }
  {
    std::vector<std::array<int, 4>> E;
    for (int i = 0; i < n; ++i) {
      E.push_back({x[i], 1, i, airport});
    }
    for (int i = 0; i < m; ++i) {
      E.push_back({z[i], 0, a[i], b[i]});
    }
    ans = std::min(ans, kruskal(n, E));
  }
  {
    std::vector<std::array<int, 4>> E;
    for (int i = 0; i < m; ++i) {
      E.push_back({z[i], 0, a[i], b[i]});
    }
    ans = std::min(ans, kruskal(n, E));
  }

  std::cout << ans << "\n";
}

```

</details>

## [G - Sequence in mod P](https://atcoder.jp/contests/abc270/tasks/abc270_g)

令 $f(x) = Ax +  B$，则可以算出 $f^{-1}(x) = Cx + D$ 。

$X_n = G$ 等价于 $f^x(S) = G$ ，这个式子和离散对数的式子很相似，考虑类似求解离散对数问题的大步小步算法(BSGS, baby-step giant-step)。

令 $M = \sqrt{p}$，则对于所有 $x$ 都存在 $0 \le A, B \le \sqrt{p}$ 使得 $x = AM + B$ 成立，然后就有 $f^x(S) = G$ 等价于 $f^{AM}(S) = f^{-B}(G)$。

由于 $0 \le A, B \le \sqrt{p}$，所以可以先枚举等式的一边，记录结果取值以及对应步数；然后再枚举等式的另一边，看是否有结果取值相等的记录，若有则两边的步数相加就是一个可行的 $x$ 。

<details>
<summary>AC代码</summary>

```cpp
// Problem: G - Sequence in mod P
// Contest: AtCoder - TOYOTA MOTOR CORPORATION Programming Contest 2022(AtCoder Beginner Contest
// 270) URL: https://atcoder.jp/contests/abc270/tasks/abc270_g Memory Limit: 1024 MB Time Limit:
// 4000 ms
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
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    SolveCase(t);
  }
  return 0;
}

void Initialize() {}

int mod_;
template <typename ValueType, typename SupperType>
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

  std::string to_string() const { return std::to_string(value_); }

 private:
  ValueType value_;
};
using Mint = Modular<int, int64_t>;

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

using Mint = Modular<int, int64_t>;

void SolveCase(int Case) {
  int p, a, b, s, g;
  std::cin >> p >> a >> b >> s >> g;
  mod_ = p;

  if (s == g) {
    std::cout << "0\n";
    return;
  }

  if (a == 0) {
    std::cout << (b == g ? 1 : -1) << "\n";
    return;
  }

  int M = std::sqrt(p);

  std::map<int, int> mp;
  Mint X(g);
  Mint c = Mint(a).inv(), d = Mint(a).inv() * Mint(-b);
  for (int i = 0; i < M; ++i) {
    if (!mp.count(X.value()))
      mp[X.value()] = i;

    X = X * c + d;
  }

  Mint Y(s);
  Mint A(1), B(0);
  for (int i = 0; i < M; ++i) {
    A = A * Mint(a);
    B = B * Mint(a) + Mint(b);
  }
  for (int i = 0; i <= p / M + 1; ++i) {
    if (mp.count(Y.value())) {
      int ans = i * M + mp[Y.value()];
      std::cout << ans << "\n";
      return;
    }

    Y = Y * A + B;
  }

  std::cout << "-1\n";
}

```

</details>

## [Ex - add 1](https://atcoder.jp/contests/abc270/tasks/abc270_h)

记计数器的取值分别为 $c_i$，定义当前状态为 $k = \max_i(a_i - c_i)$ 。

易得，存在 $r$ 使得 $a_r < k \le a_{r + 1}$ 。如果下一步选择的 $i$ 满足 $1 \le i \le r$ ，则状态会从 $k$ 变为 $k - 1$ ；如果 $r + 1 \le i \le n$ ，则有状态会从 $k$ 变为 $a_i$ 。

现在状态转移有了，就可以写出转移方程，假设 $E_k$ 表示状态从 $k$ 变为 $0$ 的期望步数，则 $E_{0} = 0$ ， $E_{a_n}$ 即为答案。
$$
E_{k - 1} = \frac{1}{n}(rE_{k} + \sum_{j = r + 1}^{n} E_{A_j}) + 1
\tag{1}
$$

现在有个问题， $E_k$ 可以从 $E_x, x > k$ 推导得出，但是已知是 $E_0 = 0$ ，方向对不上。记 $F_k = E_{A_n} - E_k$ ，则有 $F_{a_n} = 0$ ， $F_0$ 即为答案。式(1)等式两边同乘 $-1$ 再加上 $E_{a_n}$ 可得
$$
rF_{k - 1} = nF_k + n - \sum_{j = r + 1}^{n} F_{a_j}
\tag{2}
$$

依次计算 $F_x, x = a_n, a_n - 1, \dots, 0$ 即可得到答案，但是 $a_n \le {10}^{18}$，复杂度爆炸。

注意到对于 $a_r \le x < a_{r + 1}$ ， $\sum_{j = r + 1}^{n} F_{a_j}$ 不变，记为 $s_{r + 1}$ ，所以考虑将$s_{r + 1}$视为常数，然后把这一段的转移合并到一起。

需要凑出一个 $F_k$ 相关的 $G_k$ ， $G_k$ 这个式子已知某一项，可以快速地转移，例如 $G_k$ 等比或者等差，但是由于 $F_k$ 和 $F_{k - 1}$ 前的系数不同，所以等差不行。现在只剩等比的情况，然后式(2)中除了 $F_x$ 相关的还有 $n - s_{r + 1}$ ， $G_k$ 和这个应该也有关系，然后就待定系数法有
$$
G_k = F_{k} + d(n - s_{r + 1})\\
r(F_{k-1} + d(n - s_{r + 1})) = n(F_k + d(n - s_{r + 1}))
\tag{3}
$$

结合式(2)和(3)求出 $d$，再带入(3)可得
$$
G_k = F_k + \frac{n - s_{r+1}}{n - r}\\
G_{k - 1} = \frac{n}{r} G_{k}
$$

即
$$
F_{a_r} = (\frac{n}{r})^{a_{r + 1} - a_r} (F_{a_{r + 1}} + \frac{n - s_{r + 1}}{n - r}) - \frac{n - s_{r + 1}}{n - r}
$$

现在就可以依次求出 $F_x, x = a_n, a_{n - 1}, \dots, a_1$，其中 $F_{a_1} = F_0$ 即为答案。

<details>
<summary>AC代码</summary>

```cpp
// Problem: Ex - add 1
// Contest: AtCoder - TOYOTA MOTOR CORPORATION Programming Contest 2022(AtCoder Beginner Contest
// 270) URL: https://atcoder.jp/contests/abc270/tasks/abc270_h Memory Limit: 1024 MB Time Limit:
// 3000 ms
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
  int n;
  std::cin >> n;

  std::vector<i64> a(n + 1);
  for (int i = 1; i <= n; ++i)
    std::cin >> a[i];

  Mint sr(0);
  Mint Fk(0);
  for (int i = n - 1; i >= 1; --i) {
    int r = i;

    Mint A = (Mint(n) / Mint(r)).power(a[i + 1] - a[i]);
    Mint B = (Mint(n) - Mint(sr)) / (Mint(n) - Mint(r));

    Fk = A * (Fk + B) - B;
    sr = sr + Fk;
  }

  std::cout << Fk.value() << "\n";
}

```

</details>