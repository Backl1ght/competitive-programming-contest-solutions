# AtCoder Beginner Contest 257

咕咕咕咕咕。

## [F - Teleporter Setting](https://atcoder.jp/contests/abc257/tasks/abc257_f)

<details>
<summary>题意</summary>

给一个有$n$个节点$m$条边的无向图，边集中有一部分边只确定了一端，记这部分边的集合为$S$。

对于$i = 1, 2, \dots, n$，问当$S$中的边的不确定的那一端均为$i$时，从点$1$到点$n$的最短路长度。

其中，$2 \le n \le 3 \times {10}^5, 1 \le m \le 3 \times {10}^5$。

</details>

<details>
<summary>思路</summary>

新增一个虚拟节点$n + 1$，将$S$中的边的不确定的那一段都看成是$n + 1$。

在询问$i$时，可以看成是在$i$和$n + 1$之间连一条长度为$0$的边。

此时的最短路，要么不包含$S$中的边，要么是$1 \to n + 1 \to i \to n$或$1 \to i \to n + 1 \to n$。

然后就是dijkstra板子了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: F - Teleporter Setting
// Contest: AtCoder - NS Solutions Corporation Programming Contest 2022（AtCoder Beginner Contest
// 257）
// URL: https://atcoder.jp/contests/abc257/tasks/abc257_f
// Memory Limit: 1024 MB Time Limit: 2000 ms
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

template <typename DistanceType>
struct Edge {
  int v_;
  DistanceType w_;
  Edge() {}
  Edge(int v, DistanceType w) : v_(v), w_(w) {}
};

template <typename DistanceType>
std::vector<DistanceType> Dijkstra(const std::vector<std::vector<Edge<DistanceType>>>& g, int s) {
  using Node = std::pair<DistanceType, int>;
  const DistanceType INF = std::numeric_limits<DistanceType>::max();
  const int n = g.size();

  std::vector<DistanceType> dis(n, INF);
  std::vector<bool> vis(n, false);

  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> q;
  dis[s] = 0;
  q.push(Node(dis[s], s));
  while (!q.empty()) {
    auto [c, u] = q.top();
    q.pop();

    if (vis[u])
      continue;
    vis[u] = true;

    for (auto [v, w] : g[u]) {
      if (dis[v] > c + w) {
        dis[v] = c + w;
        q.push(Node(dis[v], v));
      }
    }
  }
  return dis;
}

void solve_case(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<Edge<int>>> g(n + 1);
  for (int i = 1; i <= m; ++i) {
    int u, v;
    std::cin >> u >> v;
    if (u == 0) {
      u = n + 1;
    }
    --u, --v;
    g[u].push_back(Edge(v, 1));
    g[v].push_back(Edge(u, 1));
  }

  std::vector<int> ds = Dijkstra(g, 0);
  std::vector<int> dt = Dijkstra(g, n - 1);
  const int INF = std::numeric_limits<int>::max();

  for (int i = 0; i < n; ++i) {
    int mi = ds[n - 1];
    if (ds[n] != INF && dt[i] != INF)
      mi = std::min(mi, ds[n] + dt[i]);
    if (ds[i] != INF && dt[n] != INF)
      mi = std::min(mi, ds[i] + dt[n]);

    if (mi == INF)
      mi = -1;
    std::cout << mi << " ";
  }
}


```

</details>

## [G - Prefix Concatenation](https://atcoder.jp/contests/abc257/tasks/abc257_g)

<details>
<summary>题意</summary>

给两个字符串$s$和$t$，问最少用多个$s$的前缀能拼出$t$。

其中$1 \le |s|, |t| \le 5 \times {10}^5$。

</details>

<details>
<summary>思路</summary>

记$dp_i$表示最少用多少个$s$的前缀能够拼出$t$长度为$i$的前缀。

然后猜了个结论，就是把令$z = s + \# + t$，然后跑kmp求出$z$每个位置的最长border长度记为数组$p$，则$dp_i$只从$dp_{i - p_i}$处转移即可。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: G - Prefix Concatenation
// Contest: AtCoder - NS Solutions Corporation Programming Contest 2022（AtCoder Beginner Contest
// 257）
// URL: https://atcoder.jp/contests/abc257/tasks/abc257_g
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

std::vector<int> kmp(const std::string& s) {
  int n = s.size();
  std::vector<int> p(n);

  p[0] = 0;
  for (int i = 1; i < n; ++i) {
    int j = p[i - 1];
    while (j > 0 && s[j] != s[i])
      j = p[j - 1];
    if (s[i] == s[j])
      ++j;
    p[i] = j;
  }

  return p;
}

void solve_case(int Case) {
  std::string s;
  std::string t;
  std::cin >> s;
  std::cin >> t;
  int n = s.size(), m = t.size();

  s = s + "#" + t;
  auto p = kmp(s);

  std::vector<int> dp(m + 1, 0x3f3f3f3f);
  dp[0] = 0;
  for (int i = 1; i <= m; ++i) {
    int l = p[n + i];
    dp[i] = std::min(dp[i], dp[i - l] + 1);
  }
  if (dp[m] == 0x3f3f3f3f)
    dp[m] = -1;
  std::cout << dp[m] << "\n";
}

```

</details>

## [Ex - Dice Sum 2](https://atcoder.jp/contests/abc257/tasks/abc257_h)

<details>
<summary>题意</summary>

给定 $n$ 个六面骰子，第 $i$ 个骰子的第 $j$ 面上面的数字为 $a_{i, j}$，第 $i$ 个骰子值 $c_i$ 块钱。

要从这 $n$ 个骰子中选择 $k$ 个使得 $A^2 - B$ 取值的期望最大，其中 $A$ 为所选骰子每个骰子摇一次，显示数字之和的平方， $B$ 为所选骰子的价值之和。

其中 $1 \le n \le 1000$ 。

</details>

<details>
<summary>思路</summary>

**问题转化**

假设所选的骰子集合为$D = \{i_1, \dots , i_k \}$，根据期望的定义，有

$$
\begin{aligned}
E_D
&= \frac{1}{6^k} \sum_{\substack{i \in D\\ 1\le j_1, \dots, j_k \le 6}} (a_{i_1, j_1} + \dots + a_{i_k, j_k})^2 - \sum_{i \in D} c_i\\
&= \frac{1}{6^k} (\sum_{\substack{i \in D \\ 1 \le j \le 6}} 6^{k-1} a_{i, j}^2 - 2\sum_{\substack{i, j \in D, i \ne j\\ 1 \le l, h \le 6}} 6^{k-2} a_{i, h} a_{j, l}) - 
\sum_{i \in D} c_i\\
&= \frac{1}{6} \sum_{\substack{i \in D \\ 1 \le j \le 6}} a_{i, j}^2 - \frac{1}{18} \sum_{\substack{i, j \in D, i \ne j\\ 1 \le l, h \le 6}} a_{i, h} a_{j, l} - \sum_{i \in D} c_i\\
\end{aligned}
$$

令$S_i = \sum_{j = 1}^6 a_{i, j}, Q_i = \sum_{j = 1}^6 a_{i, j}^2$，则有
$$
\begin{aligned}
E_D = \frac{1}{6} \sum_{i \in D} Q_i + \frac{1}{36} (\sum_{i \in D} S_i)^2 - \frac{1}{36} \sum_{i \in D} S_i^2 - \sum_{i \in D} c_i
\end{aligned}
$$

令$A_i= S_i, B_i = 6Q_i - S_i^2 - 36c_i, X_D = \sum_{i \in D} A_i, Y_D = \sum_{i \in D} B_i$，则有
$$
E_D = X_D^2 + Y_D
$$

把一个选择方案 $D$ 看成二位平面上的一个点 $(X_D, Y_D)$ ，现在问题转化为给定点集，要求最大化$x^2 + y$。

**问题求解**

对于最优的选择方案 $D$ ，一定存在某个实数 $z$ 使得$\forall i \in D, \forall j \notin D, zA_i + B_i \ge zA_j + B_j$。

**证明**

考虑在某条线段上恒速运动的点$(x, y)$，$x^2 + y$的图像是关于 $x$ 的一个开口向上的抛物线，由此其极值点必定在两个端点之一。拓展到多个点时，则有极值点必定位于点集的凸包的顶点。

对于每一个顶点，都有某一个 $z$ ，使得 $zx + y$ 最大化。

对于某一个 $z$，也可以找到对应的一个顶点使得 $zx + y$ 最大化，这个顶点对应的选择方案为选择 $zA_i + B_i$ 前 $k$ 大的点。

**求解**

考虑从小到大搜索 $z$ 的值，复杂度爆炸。

上述过程可以分成多段结果相同的段。特别地，如果把 $(A_i, B_i)$ 按 $zA_i + B_i$ 排序，只有在 $z$ 在 $zA_i + B_i = zA_j + B_j$ 时，或者说$z = \frac{B_i - B_j}{A_j - A_i}$时，结果会发生改变，改变为 $(A_i, B_i)$ 和 $(A_j, B_j)$ 交换位置，原本位于 $i, j$ 中间的点保持不变。

易得只有$O(n^2)$个使结果发生变化的 $z$ ，每对点也至多交换一次。

不妨先令 $z = +\infin$，然后再不断降低 $z$ 的取值，从而搜索所有可能的交换，单次交换至多交换两个点。

时间复杂度为 $O(n^2 \log n)$，瓶颈在于快排。

**补充**

求解部分[kmjp's blog](https://kmjp.hatenablog.jp/entry/2022/06/26/0930)这个博客讲的比官方题解具体。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: Ex - Dice Sum 2
// Contest: AtCoder - NS Solutions Corporation Programming Contest 2022（AtCoder Beginner Contest
// 257） URL: https://atcoder.jp/contests/abc257/tasks/abc257_h Memory Limit: 1024 MB Time Limit:
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

  static ValueType power(ValueType value, size_t exponent) {
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

void SolveCase(int Case) {
  int n, k;
  std::cin >> n >> k;

  std::vector<i64> a(n), b(n), c(n);
  for (int i = 0; i < n; ++i)
    std::cin >> c[i];

  for (int i = 0; i < n; ++i) {
    i64 s = 0, s2 = 0;
    for (int j = 0; j < 6; ++j) {
      i64 x;
      std::cin >> x;

      s += x;
      s2 += x * x;
    }

    a[i] = s;
    b[i] = 6 * s2 - s * s - 36 * c[i];
  }

  // let z = +\inf first, and then decrease z gradually.
  std::vector<std::pair<i64, i64>> p(n);
  for (int i = 0; i < n; ++i)
    p[i] = {a[i], b[i]};
  std::sort(p.begin(), p.end(), std::greater<>());

  std::vector<int> selected(n, false);
  i64 X = 0, Y = 0;
  for (int i = 0; i < k; ++i) {
    X += p[i].first;
    Y += p[i].second;
    selected[i] = true;
  }
  i64 ans = X * X + Y;

  // decrease z gradually.
  std::vector<std::array<i64, 4>> swaps;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      auto [xi, yi] = p[i];
      auto [xj, yj] = p[j];

      // pi can replace pj only if xi < xj and yi > yj since we are maximizing cx + y.
      if (xi < xj && yi > yj) {
        swaps.push_back({xi - xj, yi - yj, i, j});
      }
    }
  }
  std::sort(swaps.begin(), swaps.end(),
            [&](const std::array<i64, 4>& lhs, const std::array<i64, 4>& rhs) -> bool {
              auto [dx1, dy1, _1, _2] = lhs;
              auto [dx2, dy2, _3, _4] = rhs;

              return dx1 * dy2 > dx2 * dy1;
            });
  for (auto [_1, _2, i, j] : swaps) {
    if (!selected[i] && selected[j]) {
      X += p[i].first - p[j].first;
      Y += p[i].second - p[j].second;
      ans = std::max(ans, X * X + Y);

      selected[i] = true;
      selected[j] = false;
    }
  }
  std::cout << (Mint(ans) / Mint(36)).value() << "\n";
}

```

</details>