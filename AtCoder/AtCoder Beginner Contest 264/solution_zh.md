# AtCoder Beginner Contest 264

## [E - Blackout 2](https://atcoder.jp/contests/abc264/tasks/abc264_e)

离线+并查集。

注意到只有删边操作，而删边操作其实不是很好维护。由于没有强制在线，所以可以离线一下然后逆序考虑，这样删边就变成了加边，用并查集就足以维护了。

<details>
<summary>AC代码</summary>

```cpp
// Problem: E - Blackout 2
// Contest: AtCoder - freee Programming Contest 2022（AtCoder Beginner Contest 264）
// URL: https://atcoder.jp/contests/abc264/tasks/abc264_e
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

void solve_case(int Case) {
  int n, m, e;
  std::cin >> n >> m >> e;

  std::vector<std::array<int, 3>> E(e);
  for (int i = 0; i < e; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    E[i] = {u, v, 0};
  }

  int q;
  std::cin >> q;
  std::vector<int> x(q);
  for (int i = 0; i < q; ++i) {
    std::cin >> x[i];
    --x[i];
    E[x[i]][2] = 1;
  }
  logd(E);

  int cnt = 0;
  std::vector<int> f(n + m), sz(n + m), w(n + m);
  for (int i = 0; i < n + m; ++i) {
    f[i] = i;
    sz[i] = i < n ? 1 : 0;
    w[i] = i >= n ? 1 : 0;
  }

  std::function<int(int)> find = [&](int x) { return x == f[x] ? x : f[x] = find(f[x]); };

  auto merge = [&](int x, int y) {
    x = find(x), y = find(y);
    if (x == y)
      return;

    if (w[x])
      cnt -= sz[x];
    if (w[y])
      cnt -= sz[y];

    f[x] = y;
    sz[y] += sz[x];
    w[y] |= w[x];

    if (w[y])
      cnt += sz[y];
  };

  for (auto [u, v, f] : E) {
    if (f == 0) {
      merge(u, v);
    }
  }

  std::vector<int> ans(q);
  for (int i = q - 1; i >= 0; --i) {
    ans[i] = cnt;

    auto [u, v, f] = E[x[i]];
    merge(u, v);
  }

  for (int i = 0; i < q; ++i)
    std::cout << ans[i] << "\n";
}

```

</details>

## [F - Monochromatic Path](https://atcoder.jp/contests/abc264/tasks/abc264_f)

DP。

注意到只能往右或者往下走，这样其实前$i - 1$行的操作不会影响到$i$行以及之后，列的话类似，所以这个满足无后效性，可以DP搞。

每一行和每一列都有翻转了和未翻转两个状态。

令$dp_{i, j, x, y}$表示从$(1, 1)$走到$(i, j)$，第$i$行状态为$x$，第$j$列状态为$y$的最小代价。

这样$dp_{i, j, x, y}$就可以转移到$dp_{i + 1, j, nx, ny}$和$dp_{i, j + 1, nx, ny}$。

然后就是$O(n^2)$DP一下完事。

注意，是先把所有翻转操作都做了，然后再看能不能走，所以$(i, j)$走到$(i + 1, j)$时是无法改变第$j$列的状态的，例如$dp_{i, j, x, 0}$是不能更新$dp_{i, j, x, 1}$的。$(i, j)$走到$(i, j + 1)$类似。

<details>
<summary>AC代码</summary>

```cpp
// Problem: F - Monochromatic Path
// Contest: AtCoder - freee Programming Contest 2022（AtCoder Beginner Contest 264）
// URL: https://atcoder.jp/contests/abc264/tasks/abc264_f
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

template <typename T, T init>
std::vector<T> Vector(size_t n) {
  return std::vector<T>(n, init);
}

template <typename T, T init>
std::vector<std::vector<T>> Vector(size_t n, size_t m) {
  using value_type = decltype(Vector<T, init>(0));
  return std::vector<value_type>(n, Vector<T, init>(m));
}

template <typename T, T init>
std::vector<std::vector<std::vector<T>>> Vector(size_t n, size_t m, size_t k) {
  using value_type = decltype(Vector<T, init>(0, 0));
  return std::vector<value_type>(n, Vector<T, init>(m, k));
}

template <typename T, T init>
std::vector<std::vector<std::vector<std::vector<T>>>> Vector(size_t n,
                                                             size_t m,
                                                             size_t k,
                                                             size_t l) {
  using value_type = decltype(Vector<T, init>(0, 0, 0));
  return std::vector<value_type>(n, Vector<T, init>(m, k, l));
}

void solve_case(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<int> r(n + 1);
  for (int i = 1; i <= n; ++i)
    std::cin >> r[i];

  std::vector<int> c(m + 1);
  for (int i = 1; i <= m; ++i)
    std::cin >> c[i];

  auto a = Vector<int, 0>(n + 1, m + 1);
  std::string s;
  for (int i = 1; i <= n; ++i) {
    std::cin >> s;
    for (int j = 1; j <= m; ++j) {
      a[i][j] = s[j - 1] - '0';
    }
  }

  const i64 INF = INT64_C(0x3f3f3f3f3f3f3f3f);
  auto dp = Vector<i64, INF>(n + 1, m + 1, 2, 2);
  dp[1][1][0][0] = 0;
  dp[1][1][0][1] = c[1];
  dp[1][1][1][0] = r[1];
  dp[1][1][1][1] = c[1] + r[1];
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      for (int x : {0, 1}) {
        for (int y : {0, 1}) {
          for (int nx : {0, 1}) {
            for (int ny : {0, 1}) {
              // down
              if (i + 1 <= n && a[i][j] ^ x ^ y == a[i + 1][j] ^ nx ^ ny) {
                dp[i + 1][j][nx][ny] =
                    std::min(dp[i + 1][j][nx][ny],
                             dp[i][j][x][y] + (nx ? r[i + 1] : 0) + (y == ny ? 0 : INF));
              }

              // right
              if (j + 1 <= m && a[i][j] ^ x ^ y == a[i][j + 1] ^ nx ^ ny) {
                dp[i][j + 1][nx][ny] =
                    std::min(dp[i][j + 1][nx][ny],
                             dp[i][j][x][y] + (x == nx ? 0 : INF) + (ny ? c[j + 1] : 0));
              }
            }
          }
        }
      }
    }
  }

  i64 ans = INF;
  for (int x : {0, 1}) {
    for (int y : {0, 1}) {
      ans = std::min(ans, dp[n][m][x][y]);
    }
  }

  std::cout << ans << "\n";
}


```

</details>

## [G - String Fair](https://atcoder.jp/contests/abc264/tasks/abc264_g)

由于$|T_i| \le 3$，所以对于字符串$S$，在其后面添加一个新的字符，增加的收益只和新字符以及$S$最后两个字符有关。这里为了方便处理，令初始$S$为`$$`。

如果用$S$最后两个字符表示$S$的状态，在$S$后面新增一个字符可以看成状态之间的转移。把转移关系的图建出来，字符串$S$就可以看成从`$$`开始的一条路径，原问题的答案就是从`$$`开始的最长路。

注意到这个图可能有正环可能有负权，但是一共只有$27 * 27 = 729$个点，所以直接BellmanFord搞就够了。

<details>
<summary>AC代码</summary>

```cpp
// Problem: G - String Fair
// Contest: AtCoder - freee Programming Contest 2022（AtCoder Beginner Contest 264）
// URL: https://atcoder.jp/contests/abc264/tasks/abc264_g
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

template <typename T>
std::pair<bool, std::vector<T>> BellmanFord(const std::vector<std::vector<std::pair<int, T>>>& g,
                                            int S) {
  int n = g.size();
  std::vector<T> dis(n, std::numeric_limits<T>::min());
  dis[S] = 0;

  bool flag;
  for (int r = 1; r <= n; ++r) {
    flag = false;
    for (int u = 0; u < n; ++u) {
      if (dis[u] == std::numeric_limits<T>::min())
        continue;

      for (auto [v, w] : g[u]) {
        if (dis[v] < dis[u] + w) {
          dis[v] = dis[u] + w;
          flag = true;
        }
      }
    }
  }

  return {flag, dis};
}

void solve_case(int Case) {
  const int N = 27 * 27;

  int n;
  std::cin >> n;

  std::vector<i64> a(27 * 27 * 27, 0);
  auto id = [&](const std::string& s) {
    int r = 0;
    for (char ch : s) {
      int c = ch == '$' ? 0 : ch - 'a' + 1;
      r = r * 27 + c;
    }
    return r;
  };

  auto cost = [&](const std::string& s) {
    i64 w = 0;
    w += a[id(s.substr(2, 1))];
    if (s[1] != '$')
      w += a[id(s.substr(1, 2))];
    if (s[0] != '$')
      w += a[id(s.substr(0, 3))];
    return w;
  };

  std::string t, u, v;
  int p;
  for (int i = 0; i < n; ++i) {
    std::cin >> t >> p;
    a[id(t)] = p;
  }

  std::vector<std::vector<std::pair<int, i64>>> g(N);

  std::queue<std::string> q;
  std::vector<bool> visited(N, 0);
  q.push("$$");
  visited[id("$$")] = true;
  while (!q.empty()) {
    u = q.front();
    q.pop();

    int ndu = id(u);
    for (int i = 0; i < 26; ++i) {
      v = u + char('a' + i);
      int ndv = id(v.substr(1, 2));

      g[ndu].push_back({ndv, cost(v)});

      if (!visited[ndv]) {
        visited[ndv] = true;
        q.push(v.substr(1));
      }
    }
  }

  auto [flag, dis] = BellmanFord(g, id("$$"));
  if (flag) {
    std::cout << "Infinity\n";
  } else {
    std::cout << *std::max_element(dis.begin() + 1, dis.end()) << "\n";
  }
}

```

</details>

## [Ex - Perfect Binary Tree](https://atcoder.jp/contests/abc264/tasks/abc264_h)

树高为$d$的完美二叉树有$2^d - 1$个节点，所以只有深度不超过$20$的点才会对答案有贡献。

然后就可以开始类似树形DP了。

<details>
<summary>AC代码</summary>

```cpp
// Problem: Ex - Perfect Binary Tree
// Contest: AtCoder - freee Programming Contest 2022（AtCoder Beginner Contest 264）
// URL: https://atcoder.jp/contests/abc264/tasks/abc264_h
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

void solve_case(int Case) {
  int n;
  std::cin >> n;

  std::vector<int> p(n + 1), d(n + 1);
  p[1] = 0, d[1] = 0;
  for (int i = 2; i <= n; ++i) {
    std::cin >> p[i];
  }

  std::vector<std::vector<Mint>> f(n + 1, std::vector<Mint>(20, Mint(0)));
  std::vector<std::vector<Mint>> g(n + 1, std::vector<Mint>(20, Mint(0)));

  f[1][0] = Mint(1);
  g[0][0] = Mint(1);
  std::cout << "1\n";

  for (int i = 2; i <= n; ++i) {
    d[i] = d[p[i]] + 1;

    if (d[i] < 20) {
      int v = i, curd = 0;
      Mint val(1);
      while (v != 0) {
        int u = p[v];
        Mint next_val = val * (g[u][curd] - f[v][curd]);

        g[u][curd] = g[u][curd] + val;
        f[v][curd] = f[v][curd] + val;

        v = u;
        curd += 1;
        val = next_val;
      }
    }

    Mint ans(0);
    for (int i = 0; i < 20; ++i)
      ans = ans + g[0][i];
    std::cout << ans.value() << "\n";
  }
}

```

</details>