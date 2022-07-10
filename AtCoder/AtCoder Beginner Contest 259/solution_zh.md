# AtCoder Beginner Contest 259

咕咕咕。

## [D - Circumferences](https://atcoder.jp/contests/abc259/tasks/abc259_d)

<details>
<summary>题意</summary>

给定$n$个园$(x_i, y_i, r_i)$以及起点$(sx, sy)$和终点$(tx, ty)$。

问只在给定圆的圆周上移动，能否从起点移动至终点。

其中$1 \le n \le 3000, -{10}^9 \le x_i, y_i \le {10}^9, 1 \le r_i \le {10}^9$。

</details>

<details>
<summary>思路</summary>

转换成图论问题，一个圆对应一个节点，如果两个圆之间有交点就在两个节点之间连边，表示可以从一个圆走到另一个圆。

两圆是否有交点就是高中数学。然后这里的可达关系是传递的，所以可以用并查集维护。

如果起点和终点在同一连通块中则可行，反之则无解。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: D - Circumferences
// Contest: AtCoder - AtCoder Beginner Contest 259
// URL: https://atcoder.jp/contests/abc259/tasks/abc259_d
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
  auto dist2 = [](int sx, int sy, int tx, int ty) {
    return i64(1) * (tx - sx) * (tx - sx) + i64(1) * (ty - sy) * (ty - sy);
  };

  auto square = [](int x) { return i64(1) * x * x; };

  auto intersect = [&dist2, &square](const std::array<int, 3>& lhs, const std::array<int, 3>& rhs) {
    auto [x1, y1, r1] = lhs;
    auto [x2, y2, r2] = rhs;
    return dist2(x1, y1, x2, y2) <= square(r1 + r2) &&
           dist2(x1, y1, x2, y2) >= square(std::abs(r1 - r2));
  };

  int n;
  std::cin >> n;

  int sx, sy, tx, ty;
  std::cin >> sx >> sy >> tx >> ty;

  std::vector<int> f(n);
  std::iota(f.begin(), f.end(), 0);
  std::function<int(int)> find = [&](int x) { return x == f[x] ? x : f[x] = find(f[x]); };
  auto merge = [&](int x, int y) {
    x = find(x), y = find(y);
    if (x == y)
      return;
    f[x] = y;
  };

  std::vector<std::array<int, 3>> a(n);
  for (int i = 0; i < n; ++i) {
    int x, y, r;
    std::cin >> x >> y >> r;
    a[i] = {x, y, r};
  }

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (intersect(a[i], a[j])) {
        merge(i, j);
      }
    }
  }

  auto belong = [&](int sx, int sy) {
    int z = -1;
    for (int i = 0; i < n; ++i) {
      auto [x, y, r] = a[i];
      if (dist2(sx, sy, x, y) == square(r)) {
        z = find(i);
        break;
      }
    }
    return z;
  };

  int sid = belong(sx, sy), tid = belong(tx, ty);
  std::cout << (sid != -1 && sid == tid ? "Yes" : "No") << "\n";
}

```

</details>


## [E - LCM on Whiteboard](https://atcoder.jp/contests/abc259/tasks/abc259_e)

<details>
<summary>题意</summary>

给定$n$个数字的质因数分解形式，要求将其中某一个数置成1，问操作过后这$n$个数可能的LCM有多少个。

其中$1 \le n \le 2 \times {10}^{5}$。

</details>

<details>
<summary>思路</summary>

假设操作之前，$n$个数字的LCM等于$lcm$。

根据
$$
\operatorname{LCM} = \prod_i p_i^{\max_j(e_j)}
$$

可以得出，如果将某个数字置成1之后，某个$\max_j(e_j)$发生变化，则这个数字对和一个新的LCM一一对应。

还有一种可能是将某个数字置成1之后，$\max_j(e_j)$均未发生变化，这一部分的数字均对应$lcm$。

两部分之和即为答案。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: E - LCM on Whiteboard
// Contest: AtCoder - AtCoder Beginner Contest 259
// URL: https://atcoder.jp/contests/abc259/tasks/abc259_e
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
  int n;
  std::cin >> n;

  std::map<int, std::pair<int, int>> mp;
  std::vector<std::vector<std::pair<int, int>>> a(n);
  for (int i = 0; i < n; ++i) {
    int m;
    std::cin >> m;
    for (int j = 0; j < m; ++j) {
      int p, e;
      std::cin >> p >> e;

      a[i].push_back({p, e});

      if (!mp.count(p)) {
        mp[p] = {e, 1};
      } else {
        if (e > mp[p].first) {
          mp[p] = {e, 1};
        } else if (e == mp[p].first) {
          ++mp[p].second;
        }
      }
    }
  }

  int ans = 0, delta = 0;
  for (int i = 0; i < n; ++i) {
    bool flag = false;
    for (auto [p, e] : a[i]) {
      if (e == mp[p].first && mp[p].second == 1) {
        flag = true;
      }
    }
    if (flag)
      ++ans;
    else
      delta = 1;
  }

  std::cout << ans + delta << "\n";
}

```

</details>

## [F - Select Edges](https://atcoder.jp/contests/abc259/tasks/abc259_f)

<details>
<summary>题意</summary>

给定一棵$n$个节点的树，边带权。

考虑选出一些边，要求至多选择$d_i$条一端为节点$i$的边。

问选出来的边的最大边权和。

其中$2 \le n \le 3 \times {10}^5$。

</details>

<details>
<summary>思路</summary>

一开始猜了个假结论，即一个类似Kruscal的贪心，然后WA了。

然后就想到了DP，不妨令节点$1$为根，记$dp_{i, 0/1}$表示以$i$为根的子树中，是否还有余量选择指向$i$父亲的边，的最大边权和。易得$\max(dp_{1, 0}, dp_{1, 1})$即为答案。

对于节点$u$，记其子节点的集合为$V$，则$dp_{u,0/1}$可以只从$V$转移得到。

然后这里的转移可以贪心搞。

具体就是对于$v \in V$，节点$v$可以提供两种方案：收益为$dp_{v, 0}$代价为0以及收益为$w + dp_{v, 1}$代价为1。

$dp_{u, 0}$可以看成至多花费$d_u$的代价的最大收益，$dp_{u, 1}$可以看成至多花费$d_u - 1$的代价的最大收益。

当$d_u = 0$时令$dp_{u, 1}$为$-\infin$。

可以先将所有$dp_{v, 0}$累加起来，问题转化成可以花费1的代价额外增加$w + dp_{v, 1} - dp_{v, 0}$的收益，然后排个序贪心搞就可以了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: F - Select Edges
// Contest: AtCoder - AtCoder Beginner Contest 259
// URL: https://atcoder.jp/contests/abc259/tasks/abc259_f
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

struct Edge {
  int v, w;
  Edge() {}
  Edge(int _v, int _w) : v(_v), w(_w) {}
  bool operator<(const Edge& e) const { return w > e.w; }
};

void solve_case(int Case) {
  int n;
  std::cin >> n;

  std::vector<int> d(n);
  for (int i = 0; i < n; ++i)
    std::cin >> d[i];

  std::vector<std::vector<Edge>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    --u, --v;
    g[u].push_back(Edge(v, w));
    g[v].push_back(Edge(u, w));
  }

  std::vector<std::vector<i64>> dp(n, std::vector<i64>(2, 0));
  std::function<void(int, int)> dfs = [&](int u, int f) {
    std::vector<i64> W;

    i64 x = 0;
    for (auto [v, w] : g[u]) {
      if (v == f)
        continue;
      dfs(v, u);

      x += dp[v][0];

      if (w > 0 && d[u] > 0 && d[v] > 0) {
        W.push_back(w + dp[v][1] - dp[v][0]);
      }
    }

    if (d[u] == 0) {
      dp[u][0] = x;
      dp[u][1] = -0x3f3f3f3f3f3f3f3f;
      return;
    }

    std::sort(W.begin(), W.end(), std::greater<int>());

    dp[u][0] = dp[u][1] = x;

    for (int i = 0; i < std::min(d[u], (int)W.size()); ++i)
      if (W[i] > 0)
        dp[u][0] += W[i];

    for (int i = 0; i < std::min(d[u] - 1, (int)W.size()); ++i)
      if (W[i] > 0)
        dp[u][1] += W[i];
  };
  dfs(1, 1);

  std::cout << dp[1][0] << "\n";
}

```

</details>

## [G - Grid Card Game](https://atcoder.jp/contests/abc259/tasks/abc259_g)

<details>
<summary>题意</summary>

给定一个$n$行$m$列的矩阵，可以选择其中些行和列，收益计算方式如下:
- 若存在$a_{i, j} < 0$且同时选择了第$i$行和第$j$列，则收益为$- \infin$。
- 否则，收益为被至少选中一次的元素之和。

问最大收益。

其中$1 \le n, m \le 100$。

</details>

<details>
<summary>思路</summary>

统计行元素和，记为$r_i$；统计列元素和，记为$c_j$。

由于可以全部不选从而使得收益为$0$，如果$r_i < 0$则不可能会选择这一行，列同理。

先不考虑重复部分，此时的最佳方案就是将所有收益为正的行和列都选择。但是由于所选行和列之间存在交集，还需要扣去一些重复计算的值。现在问题转化成让扣去的值最小。

根据以下规则建图：
- 若$r_i$大于$0$则从$S$向第$i$行连边，容量为$r_i$，表示选第$i$行。
- 若$c_j$大于$0$则从第$j$列向$T$连边，容量为$c_j$，表示选第$j$列。
- 若$a_{i, j}$大于等于$0$则从第$i$行向第$j$列连边，容量为$a_{i, j}$，表示同时选择第$i$行和第$j$列。
- 若$a_{i, j}$小于$0$则从第$i$行向第$j$列连边，容量为$+\infin$，表示同时选择第$i$行和第$j$列。

如果同时选了第$i$行和第$j$列，那么收益就应当扣去$a_{i, j}$，相当于割掉图中的一条边；如果没有选某一行，那么收益就应当扣去$r_i$，相当于割掉图中的一条边；列同理。问题转化为在图中删去一些边使得$S$和$T$不连通且割掉的边权和最小，这个就是最小割。

然后根据最大流最小割定理，Dinic跑个最大流完事。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: G - Grid Card Game
// Contest: AtCoder - AtCoder Beginner Contest 259
// URL: https://atcoder.jp/contests/abc259/tasks/abc259_g
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

template <typename CapacityType>
class MaxFlowGraph {
  struct Edge {
    int from, to;
    CapacityType capacity, flow;
    Edge() {}
    Edge(int _from, int _to, CapacityType _capacity, CapacityType _flow)
        : from(_from), to(_to), capacity(_capacity), flow(_flow) {}
  };

  int n_;
  int m_;
  std::vector<Edge> edges_;
  std::vector<std::vector<int>> adjacent_;

 public:
  explicit MaxFlowGraph(int n) : n_(n), m_(0), edges_(0), adjacent_(n) {}

  void AddEdge(int from, int to, CapacityType capacity) {
    assert(0 <= from and from < n_);
    assert(0 <= to and to < n_);

    edges_.emplace_back(from, to, capacity, 0);
    adjacent_[from].push_back(m_);
    ++m_;

    edges_.emplace_back(to, from, 0, 0);
    adjacent_[to].push_back(m_);
    ++m_;
  }

  CapacityType Dinic(int src, int dst) {
    const static CapacityType INF = std::numeric_limits<CapacityType>::max();
    std::vector<int> level(n_);
    std::vector<int> start_index(n_);

    std::function<bool()> bfs = [&]() -> bool {
      std::fill(level.begin(), level.end(), -1);

      std::queue<int> q;
      q.push(src);
      level[src] = 0;

      while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int edge_id : adjacent_[u]) {
          auto [from, to, capacity, flow] = edges_[edge_id];
          CapacityType residual_capacity = capacity - flow;
          if (residual_capacity > 0 && level[to] == -1) {
            level[to] = level[u] + 1;
            if (to == dst)
              break;
            q.push(to);
          }
        }
      }

      return level[dst] != -1;
    };

    std::function<CapacityType(int, CapacityType)> dfs =
        [&](int u, CapacityType max_augment) -> CapacityType {
      if (u == dst)
        return max_augment;

      if (max_augment == 0)
        return 0;

      CapacityType total_augment = 0;
      int i = start_index[u];
      for (; i < (int)adjacent_[u].size(); ++i) {
        int edge_id = adjacent_[u][i];
        auto [from, to, capacity, flow] = edges_[edge_id];
        if (level[to] == level[u] + 1) {
          CapacityType residual_capacity = capacity - flow;
          CapacityType new_augment = dfs(to, std::min(max_augment, residual_capacity));
          if (new_augment <= 0)
            continue;

          max_augment -= new_augment;
          total_augment += new_augment;
          edges_[edge_id].flow += new_augment;
          edges_[edge_id ^ 1].flow -= new_augment;

          if (max_augment == 0)
            break;
        }
      }
      start_index[u] = i;

      if (total_augment == 0)
        level[u] = -1;

      return total_augment;
    };

    CapacityType max_flow = 0;
    while (bfs()) {
      std::fill(start_index.begin(), start_index.end(), 0);
      CapacityType new_flow = dfs(src, INF);
      logd(new_flow);
      max_flow += new_flow;
    }

    return max_flow;
  }
};

void solve_case(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> a(n, std::vector<int>(m));
  std::vector<i64> r(n), c(m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> a[i][j];
      r[i] += a[i][j];
      c[j] += a[i][j];
    }
  }

  MaxFlowGraph<i64> g(n + m + 2);
  int s = n + m, t = s + 1;

  i64 sum = 0;
  for (int i = 0; i < n; ++i) {
    if (r[i] > 0) {
      g.AddEdge(s, i, r[i]);
      sum += r[i];
    }
  }
  for (int i = 0; i < m; ++i) {
    if (c[i] > 0) {
      g.AddEdge(n + i, t, c[i]);
      sum += c[i];
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (a[i][j] >= 0) {
        g.AddEdge(i, n + j, a[i][j]);
      } else {
        g.AddEdge(i, n + j, 1e18);
      }
    }
  }

  std::cout << sum - g.Dinic(s, t) << "\n";
}

```

</details>

## [Ex - Yet Another Path Counting](https://atcoder.jp/contests/abc259/tasks/abc259_h)

<details>
<summary>题意</summary>

给定一个$n$行$n$列的矩阵，每个格子带有一种颜色。可以从任意格子出发，但是只能往右或者往下走，可以在任意格子停止。记过程中经过的格子为一条路径，包括开头和结尾。

问满足开头和结尾颜色相同的路径有多少条。

其中$1 \le n \le 400$。

</details>

<details>
<summary>思路</summary>

**方法1**：对于某个颜色$c$，记颜色为$c$的格子的集合为$S(c)$，则分别枚举起点和终点，从起点走到终点的路径数其实就是经典组合数，累加起来就可以得到颜色$c$对答案的贡献。单词时间复杂度$O(|S(c)|^2)$，在格子颜色全部相同时总的复杂度为$O(n^4)$。

**方法2**：对于某个颜色$c$，令$dp_{i, j}$表示从某个颜色为$c$的起点开始走到格子$(i, j)$（颜色不必为$c$）的路径数，颜色为$c$的格子的$dp$之和即为颜色$c$对答案的贡献。那么通过一个$O(n^2)$的DP就可以计算出颜色$c$对答案的贡献。单次时间复杂度$O(n^2)$，在格子颜色两两相异时总的时间复杂度为$O(n^4)$。

两个方法单独工作均可能被卡超时，但是两者结合起来就可以将时间复杂度控制在$O(n^3)$。具体做法就是当$|S(c)| \le n$时用方法1，否则用方法2。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: Ex - Yet Another Path Counting
// Contest: AtCoder - AtCoder Beginner Contest 259
// URL: https://atcoder.jp/contests/abc259/tasks/abc259_h
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
} binom(400 * 2 + 5);

void solve_case(int Case) {
  int n;
  std::cin >> n;

  std::vector<std::vector<int>> a(n + 1, std::vector<int>(n + 1));
  std::vector<std::vector<std::pair<int, int>>> C(n * n + 1);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      std::cin >> a[i][j];
      C[a[i][j]].push_back(std::make_pair(i, j));
    }
  }

  auto solve1 = [&](int c) {
    Mint result(0);
    int n = C[c].size();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        int dx = C[c][j].first - C[c][i].first;
        int dy = C[c][j].second - C[c][i].second;
        if (dx >= 0 && dy >= 0) {
          logd(C[c][i], C[c][j]);
          result = result + binom(dx + dy, dy);
        }
      }
    }
    return result;
  };

  auto solve2 = [&](int c) {
    Mint result(0);
    std::vector<std::vector<Mint>> dp(n + 1, std::vector<Mint>(n + 1, Mint(0)));
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        if (a[i][j] == c) {
          dp[i][j] = dp[i][j] + Mint(1);
          result = result + dp[i][j];
        }
      }
    }
    return result;
  };

  Mint ans(0);
  for (int c = 1; c <= n * n; ++c) {
    if (C[c].size() <= n) {
      ans = ans + solve1(c);
      logd(c, 1, ans.value());
    } else {
      ans = ans + solve2(c);
      logd(c, 2, ans.value());
    }
  }

  std::cout << ans.value() << "\n";
}

```

</details>