# AtCoder Beginner Contest 250

A，B，C过于简单跳过。

## [D - 250-like Number](https://atcoder.jp/contests/abc250/tasks/abc250_d)

<details>
<summary>题意</summary>

给定$n$，问有多少个二元组$<p, q>$满足：

- $p$和$q$都是素数。
- $p < q$。
- $pq^3 \le n$。

其中$n \le 10^{18}$。

</details>

<details>
<summary>思路</summary>

易得$q \le 10^6$，又$p < q$，所以所有的$q$和$q$都在$10^6$内。

线性筛筛出所有候选，然后枚举$q$，再算出$t = \lfloor \dfrac{n}{q^3} \rfloor$，则小于等于$t$的素数都可以是$p$，这个再二分一下就能得到了。

代码里算$t$算复杂了，用了二分，实际上直接除就可以了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: D - 250-like Number
// Contest: AtCoder - AtCoder Beginner Contest 250
// URL: https://atcoder.jp/contests/abc250/tasks/abc250_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO \
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#endif

using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;

void solve_case(int Case);

int main() {
  CPPIO;
  int T = 1;
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

std::vector<int> seive(int n) {
  std::vector<int> primes;
  std::vector<bool> is(n + 1, true);
  is[1] = false;
  for (int i = 2; i <= n; ++i) {
    if (is[i]) {
      primes.push_back(i);
    }
    for (int j = 0; j < (int)primes.size(); ++j) {
      i64 nxt = i64(1) * i * primes[j];
      if (nxt > n)
        break;
      is[nxt] = false;
      if (i % primes[j] == 0)
        break;
    }
  }
  return primes;
}

void solve_case(int Case) {
  i64 n;
  std::cin >> n;

  i64 ans = 0;
  std::vector<int> primes = seive(1e6);
  logd(primes.size());
  for (int i = 0; i < (int)primes.size(); ++i) {
    int p = primes[i];
    i128 q3 = i128(1) * p * p * p;

    int l = 2, r = p - 1, mid, t = 0;
    while (l <= r) {
      mid = (l + r) >> 1;
      if (q3 * mid <= n)
        l = mid + 1, t = mid;
      else
        r = mid - 1;
    }
    if (t == 0)
      continue;
    int c = std::upper_bound(primes.begin(), primes.end(), t) - primes.begin();
    ans += c;
  }

  std::cout << ans << "\n";
}
```

</details>


## [E - Prefix Equality](https://atcoder.jp/contests/abc250/tasks/abc250_e)

<details>
<summary>题意</summary>

给定两个长度为$n$的数组$a$和$b$，以及$q$个询问$(x_i, y_i)$，每个询问需要回答：$a$中前$x_i$个元素构成的集合，$b$中前$y_i$个元素构成的集合，这两个集合是否相等。

其中，$1 \le n, q \le 2 \times 10^5$，$1 \le a_i, b_i \le 10^9$。

</details>

<details>
<summary>思路</summary>

直接hash搞定。

对于$a$维护一个前缀hash值数组$ha$，$ha_i$表示$a$前$i$个元素构成的集合的hash值，集合$S$的hash值$hash(S) = \sum_{v \in S} p^{v}$。

这里写了自然溢出，$p = 998244353$。

类似地对$b$维护一个$hb$。

然后就可以$O(1)$回答一个询问了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: E - Prefix Equality
// Contest: AtCoder - AtCoder Beginner Contest 250
// URL: https://atcoder.jp/contests/abc250/tasks/abc250_e
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO \
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#endif

using i64 = int64_t;
using u64 = uint64_t;

void solve_case(int Case);

int main() {
  CPPIO;
  int T = 1;
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

const int p = 998244353;
u64 qp(int a, int b) {
  u64 r = 1;
  while (b) {
    if (b & 1)
      r = r * a;
    a = a * a;
    b >>= 1;
  }
  return r;
}
std::vector<u64> h(const std::vector<int>& a) {
  int n = a.size();
  u64 h = 0;
  std::vector<u64> ha(n);
  std::set<u64> sa;
  for (int i = 0; i < n; ++i) {
    if (!sa.count(a[i])) {
      sa.insert(a[i]);
      h += qp(p, a[i]);
    }
    ha[i] = h;
  }
  return ha;
}

void solve_case(int Case) {
  int n;
  std::cin >> n;

  std::vector<int> a(n), b(n);
  for (int& v : a)
    std::cin >> v;
  for (int& v : b)
    std::cin >> v;

  auto ha = h(a);
  auto hb = h(b);

  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    int x, y;
    std::cin >> x >> y;
    --x, --y;
    std::cout << (ha[x] == hb[y] ? "Yes" : "No") << "\n";
  }
}
```

</details>

## [F - One Fourth](https://atcoder.jp/contests/abc250/tasks/abc250_f)

<details>
<summary>题意</summary>

给一个凸包，问连接凸包上两个顶点，将凸包划分成两部分，要求其中一部分的面积尽可能接近凸包面积的$\frac{1}{4}$，问最小的面积差。

凸包顶点个数小于等于$10^5$。

</details>

<details>
<summary>思路</summary>

假设凸包面积的四分之一为$s$。

假设现在连接$p_l$和$p_r$，编号$l$到$r$之间的点构成的凸包面积为$t$，注意到增加$l$相当于$t$减去三角形$(l, l + 1, r)$的面积，增加$r$相当于加上三角形$(l, r, r + 1)$的面积，枚举$l$和$r$就可以$O(n^2)$做。

注意到固定$l$，当$t>s$之后，再增加$r$就没有意义了。

枚举$l$，类似双指针维护一个$r$使得$t$恰好大于$s$，答案必定在其中，时间复杂度为$O(n)$。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: F - One Fourth
// Contest: AtCoder - AtCoder Beginner Contest 250
// URL: https://atcoder.jp/contests/abc250/tasks/abc250_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO \
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#endif

using i64 = int64_t;
using u64 = uint64_t;

void solve_case(int Case);

int main() {
  CPPIO;
  int T = 1;
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

i64 abs(i64 x) {
  return x > 0 ? x : -x;
}

struct point {
  i64 x, y;
  point() {}
  point(i64 x, i64 y) {
    this->x = x;
    this->y = y;
  }
  friend point operator-(const point& a, const point& b) {
    return point(a.x - b.x, a.y - b.y);
  }
};

inline i64 det4(const point& a, const point& b) {
  return 4 * (a.x * b.y - a.y * b.x);
}

i64 area(const point& a, const point& b, const point& c) {
  return abs(det4(b - a, c - a));
}

void solve_case(int Case) {
  int n;
  std::cin >> n;

  std::vector<point> p(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> p[i].x >> p[i].y;
  }

  // s = 1/4 x 8 x area
  i64 s = 0;
  for (int i = 0; i < n; ++i) {
    s += det4(p[i], p[(i + 1) % n]);
  }
  s = abs(s) / 4;
  logd(s);

  i64 t = 0, ans = INT64_MAX;
  int l = 0, r = 1;
  for (int i = 0; i < n; ++i) {
    while (t < s) {
      t += area(p[(r + 1) % n], p[r], p[l]);
      ans = std::min(ans, abs(t - s));
      r = (r + 1) % n;
    }
    t -= area(p[r], p[l], p[(l + 1) % n]);
    ans = std::min(ans, abs(t - s));
    l = (l + 1) % n;
  }

  std::cout << ans << "\n";
}
```

</details>

## [G - Stonks](https://atcoder.jp/contests/abc250/tasks/abc250_g)

<details>
<summary>题意</summary>

有一支股票，接下来$n$天，第$i$天股票的价格为每股$p_i$。

你每天可以做以下3个操作之一：

1. 买入一股。
2. 卖出已拥有的一股。
3. 啥也不做。

问最大收益。

其中，$n \le 2 \times 10^5, 1 \le p_i \le 10^9$。

</details>

<details>
<summary>思路</summary>

带悔贪心板子。可以看[贪心 - OI Wiki](https://oi-wiki.org/basic/greedy/)。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: G - Stonks
// Contest: AtCoder - AtCoder Beginner Contest 250
// URL: https://atcoder.jp/contests/abc250/tasks/abc250_g
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO \
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#endif

using i64 = int64_t;
using u64 = uint64_t;

void solve_case(int Case);

int main() {
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
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i];

  std::priority_queue<int, std::vector<int>, std::greater<int>> q;
  i64 ans = 0;
  q.push(a[0]);
  for (int i = 1; i < n; ++i) {
    if (q.top() < a[i]) {
      ans += a[i] - q.top();
      q.pop();
      q.push(a[i]);
    }
    q.push(a[i]);
  }
  std::cout << ans << "\n";
}
```

</details>

## [Ex - Trespassing Takahashi](https://atcoder.jp/contests/abc250/tasks/abc250_h)

<details>
<summary>题意</summary>

给一张$n$个点的无向图，图连通，没有自环，没有重边。前$k$个点上有房子。图中的边$(a_i, b_i, c_i)$连接了点$a_i$和点$b_i$，且走完这条边需要$c_i$分钟。

给$q$个询问$(x_i, y_i, t_i)$，每个询问需要回答：你可以在房子里休息，休息完之后最多可以行动$t_i$分钟，超过了之后就无法再行动，问是否能从$x_i$到达$y_i$。

$1 \le n, q \le 2 \times 10^5$。

</details>

<details>
<summary>思路</summary>

先dijkstra跑一遍多源最短路，对于每个点$i$求出离点最近的房子$ch_i$。这样按照$ch_i$划分就可以将原图分成多块，块的中心为$ch_i$。

对于两个邻接的块，两个块的中心可以通过横跨两个块的边$(u, v, w)$连通，代价为$w + dis_u + dis_v$。

对于两个不邻接的块，可以证明必定是通过上一个过程中新增的边跳转最优。

然后问题就变成了给定边集，只能使用权重小于等于$t_i$的边，问$x_i$和$y_i$是否连通。这个就是经典kruskal最小生成树的应用了。

**证明**：TBA。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: Ex - Trespassing Takahashi
// Contest: AtCoder - AtCoder Beginner Contest 250
// URL: https://atcoder.jp/contests/abc250/tasks/abc250_h
// Memory Limit: 1024 MB
// Time Limit: 7000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO \
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#endif

using i64 = int64_t;
using u64 = uint64_t;

void solve_case(int Case);

int main() {
  CPPIO;
  int T = 1;
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

struct Edge {
  int v;
  i64 w;
  Edge() {}
  Edge(int _v, i64 _w) : v(_v), w(_w) {}
};

struct Node {
  int u;
  i64 c;
  Node() {}
  Node(int _u, i64 _c) : u(_u), c(_c) {}
  bool operator<(const Node& nd) const { return c > nd.c; }
};

struct Edge2 {
  int u, v;
  i64 w;
  Edge2() {}
  Edge2(int _u, int _v, i64 _w) : u(_u), v(_v), w(_w) {}
  bool operator<(const Edge2& e) const { return w < e.w; }
};

void solve_case(int Case) {
  int n, m, k;
  std::cin >> n >> m >> k;

  std::vector<std::vector<Edge>> g(n);
  std::vector<Edge2> e;
  for (int i = 0; i < m; ++i) {
    int u, v;
    i64 w;
    std::cin >> u >> v >> w;
    --u, --v;
    e.push_back(Edge2(u, v, w));
    g[u].push_back(Edge(v, w));
    g[v].push_back(Edge(u, w));
  }

  std::vector<int> closest_house(n, -1);
  std::vector<i64> dis(n);
  std::vector<bool> vis(n);
  {
    for (int i = 0; i < n; ++i) {
      dis[i] = INT64_MAX;
      vis[i] = false;
    }

    std::priority_queue<Node> q;
    for (int i = 0; i < k; ++i) {
      closest_house[i] = i;
      dis[i] = 0;
      q.push(Node(i, dis[i]));
    }

    while (!q.empty()) {
      auto [u, c] = q.top();
      q.pop();
      if (vis[u])
        continue;
      vis[u] = true;

      for (auto [v, w] : g[u]) {
        if (dis[v] > c + w) {
          dis[v] = c + w;
          closest_house[v] = closest_house[u];
          q.push(Node(v, dis[v]));
        }
      }
    }
  }
  logd(closest_house);
  logd(dis);

  std::vector<Edge2> e2;
  for (auto [u, v, w] : e) {
    if (closest_house[u] != closest_house[v]) {
      e2.push_back(
          Edge2(closest_house[u], closest_house[v], dis[u] + dis[v] + w));
    }
  }
  std::sort(e2.begin(), e2.end());

  std::vector<int> f(k);
  for (int i = 0; i < k; ++i)
    f[i] = i;

  std::function<int(int)> find = [&](int x) -> int {
    return x == f[x] ? x : f[x] = find(f[x]);
  };

  auto merge = [&](int x, int y) -> void {
    x = find(x);
    y = find(y);
    if (x == y)
      return;
    f[x] = y;
  };

  int q;
  std::cin >> q;
  int l = -1;
  for (int i = 0; i < q; ++i) {
    int x, y;
    i64 t;
    std::cin >> x >> y >> t;
    --x, --y;
    while (l + 1 < e2.size() && e2[l + 1].w <= t) {
      merge(e2[l + 1].u, e2[l + 1].v);
      l = l + 1;
    }
    std::cout << (find(x) == find(y) ? "Yes" : "No") << "\n";
  }
}
```

</details>
