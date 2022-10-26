# Codeforces Round #829 (Div. 2)

咕咕咕。

## [C2. Make Nonzero Sum (hard version)](https://codeforces.com/contest/1754/problem/C2)

易得有奇数个非零值时无解。

现在考虑将相邻的两个非零值配对，只要每一个非零值对都搞成和为零，总的和就为零。

由于非零值只有正负一，所以对于一个非零值对，考虑前者符号不变，看情况改变后者符号即可。

<details>
<summary>AC代码</summary>

```cpp
// Problem: C2. Make Nonzero Sum (hard version)
// Contest: Codeforces - Codeforces Round #829 (Div. 2)
// URL: https://codeforces.com/contest/1754/problem/C2
// Memory Limit: 256 MB
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
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  int s = 0;
  for (int i = 0; i < n; ++i)
    s += std::abs(a[i]);

  if (s & 1) {
    std::cout << "-1\n";
    return;
  }

  std::vector<std::pair<int, int>> ans;
  for (int i = 0; i < n; ++i) {
    if (a[i] == 0) {
      ans.push_back({i, i});
      continue;
    }

    std::vector<int> b;
    int j = i;
    while (true) {
      if (a[j] != 0) {
        b.push_back(a[j]);
        if (b.size() == 2)
          break;
      }
      ++j;
    }

    logd(i, j);
    if (b[0] == b[1]) {
      for (int k = i; k <= j - 2; ++k)
        ans.push_back({k, k});
      ans.push_back({j - 1, j});
    } else {
      for (int k = i; k <= j; ++k)
        ans.push_back({k, k});
    }

    i = j;
  }

  std::cout << ans.size() << "\n";
  for (auto [l, r] : ans)
    std::cout << l + 1 << " " << r + 1 << "\n";
}
```

</details>

## [D. Factorial Divisibility](https://codeforces.com/contest/1754/problem/D)

**观察1**：可以用 $n + 1$ 个 $n!$ 来拼出一个 $(n + 1)!$ 。

**观察2**: 当且仅当 $\sum_i a_i! = k(x!)$ 时可行。

记 $c_i$ 表示 $i!$ 的个数，则 $\sum_{i=1}^{n} a_i! = \sum_{j = 1}^{x} c_j (j!)$。

线性扫一边就可以做到尽可能地拼出 $x!$ 。

如果 $\exists i < x, c_i > 0$ 则无解，否则当且仅当 $c_x > 0$ 时有解。

<details>
<summary>AC代码</summary>

```cpp
// Problem: D. Factorial Divisibility
// Contest: Codeforces - Codeforces Round #829 (Div. 2)
// URL: https://codeforces.com/contest/1754/problem/D
// Memory Limit: 256 MB
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
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    SolveCase(t);
  }
  return 0;
}

void Initialize() {}

void SolveCase(int Case) {
  int n, x;
  std::cin >> n >> x;

  std::vector<int> a(n);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i];

  std::vector<int> cnt(x + 1);
  for (int i = 0; i < n; ++i) {
    ++cnt[a[i]];
  }

  for (int i = 1; i <= x - 1; ++i) {
    int d = cnt[i] / (i + 1);
    cnt[i + 1] += d;
    cnt[i] -= d * (i + 1);
  }

  for (int i = 1; i <= x - 1; ++i) {
    if (cnt[i] != 0) {
      std::cout << "No\n";
      return;
    }
  }

  std::cout << (cnt[x] > 0 ? "Yes" : "No") << "\n";
}
```

</details>

## [E. Wish I Knew How to Sort](https://codeforces.com/contest/1754/problem/E)

这题状态的定义蛮巧妙的。

**观察**：假设 $s$ 中包含 $cz$ 个 $0$ ，那么只有交换 $s$ 前 $cz$ 个元素中的 $1$ 和后 $n-cz$ 个元素中的 $0$ 才是有效操作。

定义状态 $x$ 表示此时前 $cz$ 个元素中有 $x$ 个 $1$ ，易得后 $n-cz$ 个元素中有 $x$ 个 $0$。起始状态 $x_0$ 可以通过线性预处理得到。定义 $E(x)$ 表示从初始状态状态 $x_0$ 转移到状态 $x$ 的期望步数。 易得：$E(x_0) = 0$ ，$E(0)$ 即为答案。 

然后，随机到有效操作的概率 $p = \frac{\binom{x}{1}\binom{x}{1}}{\binom{n}{2}}$，此时会从 $x$ 转移到 $x - 1$，否则会从 $x$ 转移到 $x$，由此有：
$$
E(x) = \biggl(pE(x - 1) + (1-p)E(x)\biggr) + 1
$$

移项可得：
$$
E(x - 1) = E(x) + \frac{1}{p} 
$$

<details>
<summary>AC代码</summary>

```cpp
// Problem: E. Wish I Knew How to Sort
// Contest: Codeforces - Codeforces Round #829 (Div. 2)
// URL: https://codeforces.com/contest/1754/problem/E
// Memory Limit: 256 MB
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
} binom(2e5 + 5);

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i];

  int count_zero = 0;
  for (int i = 0; i < n; ++i) {
    if (a[i] == 0) {
      ++count_zero;
    }
  }

  int x = 0;
  for (int i = 0; i < count_zero; ++i) {
    if (a[i] == 1)
      ++x;
  }

  Mint E(0);
  for (int i = x; i >= 1; --i) {
    Mint p = binom(i, 1) * binom(i, 1) / binom(n, 2);
    E = E + Mint(1) / p;
  }

  std::cout << E.value() << "\n";
}
```

</details>

## [F. The Beach](https://codeforces.com/contest/1754/problem/F)

01:05 过的 E 题，然后开始罚坐。

先搞个棋盘染色，那么最终的床一定是覆盖一个白格和一个黑格。

把移动床转看成移动空位，大概就是对于一个位置 $(i, j)$ ，如果与它共用一条边的相邻位置 $(ni, nj)$ 上有床，这张床的另一个位置为 $(mi, mj)$ ，那么可以把这个 $(i, j)$ 上的空位以 $p$ 或 $q$ 的代价移动到 $(mi, mj)$。观察易得通过这样的移动，空位的颜色不会改变。

对于满足条件的移动，从 $(i, j)$ 向 $(mi, mj)$ 连一条边权为移动代价的边，这样建出来的图，黑点和白点之间不连通。此外，以所有空位为源点集跑最短路，则从源点集到位置 $(i, j)$ 的距离 $dis(i, j)$ 就是通过给定操作把 $(i, j)$ 空出来的最小代价。

然后枚举所有位置 $(i, j)$ ，再枚举相邻位置 $(ni, nj)$ ， $dis(i, j) + dis(ni, nj)$ 就是把床放在 $(i, j)$ 和 $(ni, nj)$ 上的最小代价。

<details>
<summary>AC代码</summary>

```cpp
// Problem: F. The Beach
// Contest: Codeforces - Codeforces Round #829 (Div. 2)
// URL: https://codeforces.com/contest/1754/problem/F
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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

template <typename DistanceType,
          typename Comp = std::greater<>,
          typename Edge = std::pair<DistanceType, int>,
          typename Node = std::pair<DistanceType, int>>
std::vector<DistanceType> Dijkstra(const std::vector<std::vector<Edge>>& g,
                                   const std::vector<int>& s) {
  const DistanceType INF = std::numeric_limits<DistanceType>::max();
  const int n = g.size();
  const Comp comp;

  std::vector<DistanceType> dis(n, INF);
  std::vector<bool> vis(n, false);

  std::priority_queue<Node, std::vector<Node>, Comp> q;
  for (int u : s) {
    dis[u] = 0;
    q.push(Node(dis[u], u));
  }
  while (!q.empty()) {
    auto [c, u] = q.top();
    q.pop();

    if (vis[u])
      continue;
    vis[u] = true;

    for (auto [w, v] : g[u]) {
      if (comp(dis[v], c + w)) {
        dis[v] = c + w;
        q.push(Node(dis[v], v));
      }
    }
  }

  return dis;
}

void SolveCase(int Case) {
  const int dx[] = {0, 0, 1, -1};
  const int dy[] = {1, -1, 0, 0};

  int n, m;
  std::cin >> n >> m;

  int p, q;
  std::cin >> p >> q;

  std::vector<std::string> s(n);
  for (int i = 0; i < n; ++i)
    std::cin >> s[i];

  std::vector<int> sources;
  std::vector<std::vector<std::pair<i64, int>>> g(n * m);
  auto addedge = [&](int u, int v, i64 w) { g[u].push_back({w, v}); };
  auto id = [&](int i, int j) { return i * m + j; };
  auto getpair = [&](int i, int j) -> std::pair<int, int> {
    if (s[i][j] == 'L')
      return {i, j + 1};
    else if (s[i][j] == 'R')
      return {i, j - 1};
    else if (s[i][j] == 'U')
      return {i + 1, j};
    else if (s[i][j] == 'D')
      return {i - 1, j};
    else
      assert(false);
  };

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (s[i][j] == '#')
        continue;

      if (s[i][j] == '.')
        sources.push_back(id(i, j));

      for (int d = 0; d < 4; ++d) {
        int ni = i + dx[d];
        int nj = j + dy[d];
        if (ni < 0 || ni >= n || nj < 0 || nj >= m || s[ni][nj] == '#' ||
            s[ni][nj] == '.')
          continue;

        auto [mi, mj] = getpair(ni, nj);
        addedge(id(i, j), id(mi, mj), (i == mi || j == mj) ? q : p);
      }
    }
  }

  auto dis = Dijkstra<i64>(g, sources);
  const i64 INF = std::numeric_limits<i64>::max();

  i64 ans = INF;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (dis[id(i, j)] == INF)
        continue;

      for (int d = 0; d < 4; ++d) {
        int ni = i + dx[d];
        int nj = j + dy[d];
        if (ni < 0 || ni >= n || nj < 0 || nj >= m || dis[id(ni, nj)] == INF)
          continue;
        ans = std::min(ans, dis[id(i, j)] + dis[id(ni, nj)]);
      }
    }
  }
  if (ans == INF)
    ans = -1;
  std::cout << ans << "\n";
}

```

</details>