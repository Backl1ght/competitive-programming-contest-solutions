# Panasonic Programming Contest 2022(AtCoder Beginner Contest 251)

A，B，C跳过。

## [D - At Most 3 (Contestant ver.)](https://atcoder.jp/contests/abc251/tasks/abc251_d)

<details>
<summary>题意</summary>

构造一个集合：
- 大小不超过$300$的集合
- 集合中元素大小不能超过$10^6$
- 使得所有$[1,W]$中的数都可以通过任选集合中不超过$3$个元素然后加起来得到。

其中$W \le 10^6$。

</details>

<details>
<summary>思路</summary>

可以无脑输出$W = 10^6$的答案，然后这个答案可以按100进制拆分构造。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: D - At Most 3 (Contestant ver.)
// Contest: AtCoder - Panasonic Programming Contest 2022(AtCoder Beginner
// Contest 251) URL: https://atcoder.jp/contests/abc251/tasks/abc251_d Memory
// Limit: 1024 MB Time Limit: 2000 ms
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
  int w;
  std::cin >> w;

  std::set<int> s;
  for (int i = 1; i <= 99; ++i) {
    s.insert(i);
  }
  for (int i = 1; i <= 99; ++i) {
    s.insert(i * 100);
  }
  for (int i = 1; i <= 100; ++i) {
    s.insert(i * 10000);
  }

  std::cout << s.size() << "\n";
  for (int v : s)
    std::cout << v << " ";
  std::cout << "\n";
}
```

</details>

## [E - Takahashi and Animals](https://atcoder.jp/contests/abc251/tasks/abc251_e)

<details>
<summary>题意</summary>

给定一个长度为$n$的数组$a$，$a_i$表示可以花费$a_i$的代价选$i$和$i+1$，特别的$a_n$对应$n$和$1$。

问选取$[1,n]$所有元素的最小代价。

其中$n \le 3 \times 10^5$。

</details>

<details>
<summary>思路</summary>

环不好DP但是链好DP。枚举第一个元素选与不选，就能将环的DP转化成链的DP。

链的DP就是相邻两个元素至少要选一个，挺经典的。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: E - Tahakashi and Animals
// Contest: AtCoder - Panasonic Programming Contest 2022(AtCoder Beginner
// Contest 251) URL: https://atcoder.jp/contests/abc251/tasks/abc251_e Memory
// Limit: 1024 MB Time Limit: 2000 ms
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

  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
  }

  if (n == 2) {
    std::cout << std::min(a[1], a[2]) << "\n";
    return;
  }

  i64 ans0, ans1;

  // do not choose a_1
  {
    std::vector<std::vector<i64>> dp(n + 1, std::vector<i64>(2, INT64_MAX));
    dp[2][0] = a[2];
    dp[2][1] = a[2];
    for (int i = 3; i <= n; ++i) {
      dp[i][0] = dp[i - 1][1];
      dp[i][1] = std::min(dp[i - 1][0], dp[i - 1][1]) + a[i];
    }
    ans0 = dp[n][1];
  }

  // choose a_1
  {
    std::vector<std::vector<i64>> dp(n + 1, std::vector<i64>(2, INT64_MAX));
    dp[3][0] = a[2];
    dp[3][1] = a[3];
    for (int i = 4; i <= n - 1; ++i) {
      dp[i][0] = dp[i - 1][1];
      dp[i][1] = std::min(dp[i - 1][0], dp[i - 1][1]) + a[i];
    }
    dp[n - 1][0] = dp[n - 2][1] + a[n];
    ans1 = std::min(dp[n - 1][0], dp[n - 1][1]) + a[1];
  }

  std::cout << std::min(ans0, ans1) << "\n";
}
```

</details>

## [F - Two Spanning Trees](https://atcoder.jp/contests/abc251/tasks/abc251_f)

<details>
<summary>题意</summary>

给一个无向图，让你构造两棵生成树：
1. 所有非树边$(u, v)$，$u$是$v$其中一个是另外一个的祖先成立。
2. 所有非树边$(u, v)$，$u$和$v$其中一个是另外一个的祖先不成立。

图中点数和边数至多为$2 \times 10^5$。

</details>

<details>
<summary>思路</summary>

第一种是DFS树，第二种是BFS树。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: F - Two Spanning Trees
// Contest: AtCoder - Panasonic Programming Contest 2022(AtCoder Beginner
// Contest 251) URL: https://atcoder.jp/contests/abc251/tasks/abc251_f Memory
// Limit: 1024 MB Time Limit: 2000 ms
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

void work1(const std::vector<std::vector<int>>& g) {
  int n = g.size();
  std::vector<bool> vis(n, false);
  std::vector<std::pair<int, int>> a;
  std::function<void(int, int)> dfs = [&](int u, int fa) {
    if (fa != -1)
      a.push_back(std::make_pair(fa, u));
    vis[u] = true;
    for (int v : g[u]) {
      if (v == fa || vis[v])
        continue;
      dfs(v, u);
    }
  };
  dfs(0, -1);
  for (auto [u, v] : a)
    std::cout << u + 1 << " " << v + 1 << "\n";
}

void work2(const std::vector<std::vector<int>>& g) {
  int n = g.size();
  std::vector<bool> vis(n, false);
  std::vector<std::pair<int, int>> a;

  std::queue<int> q;
  q.push(0);
  vis[0] = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : g[u]) {
      if (!vis[v]) {
        vis[v] = true;
        q.push(v);
        a.push_back(std::make_pair(u, v));
      }
    }
  }
  for (auto [u, v] : a)
    std::cout << u + 1 << " " << v + 1 << "\n";
}

void solve_case(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> g(n);
  for (int i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  work1(g);
  work2(g);
}
```

</details>

## [G - Intersection of Polygons](https://atcoder.jp/contests/abc251/tasks/abc251_g)

<details>
<summary>题意</summary>

给定一个有$n$个点的凸包$P$。

给定$m$个平移$(x_i, y_i)$，表示凸包$P_i$是通过将$P$沿着$(x_i, y_i)$平移得到。

给定$q$个询问$(x_i, y_i)$，问是不是$m$个平移生成的凸包$P_i$都包含点$(x_i, y_i)$。

其中$n \le 50, m, q \le 2 \times 10^5$。

</details>

<details>
<summary>思路</summary>

将凸包转换成半平面交，求出$n \times m$个半平面的交，如果点位于交内，则`Yes`，否则`No`。

这里由于凸包是平移生成的，所以可以将一条边平移生成的多个半平面归到一类，每一类保留最严格的那个半平面即可快速求出半平面交。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: G - Intersection of Polygons
// Contest: AtCoder - Panasonic Programming Contest 2022(AtCoder Beginner
// Contest 251) URL: https://atcoder.jp/contests/abc251/tasks/abc251_g Memory
// Limit: 1024 MB Time Limit: 2000 ms
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

int sgn(i64 x) {
  if (x < 0)
    return -1;
  if (x > 0)
    return 1;
  return 0;
}

struct point {
  int x, y;
  point() {}
  point(int _x, int _y) : x(_x), y(_y) {}

  friend point operator+(const point& a, const point& b) {
    return point(a.x + b.x, a.y + b.y);
  }

  friend point operator-(const point& a, const point& b) {
    return point(a.x - b.x, a.y - b.y);
  }
};

i64 det(const point& a, const point& b) {
  return i64(1) * a.x * b.y - i64(1) * a.y * b.x;
}

struct line {
  point s, e;
  line() {}
  line(point _s, point _e) : s(_s), e(_e) {}

  int relationToPoint(const point& a) {
    i64 area = det(e - s, a - s);
    return sgn(area);
  }
};

void solve_case(int Case) {
  int n;
  std::cin >> n;
  std::vector<point> p(n);
  for (int i = 0; i < n; ++i)
    std::cin >> p[i].x >> p[i].y;

  std::vector<line> h(n);
  int m;
  std::cin >> m;
  for (int _ = 0; _ < m; ++_) {
    point d;
    std::cin >> d.x >> d.y;

    for (int i = 0; i < n; ++i) {
      point s = p[i] + d;
      point e = p[(i + 1) % n] + d;
      if (_ == 0 || h[i].relationToPoint(s) != -1) {
        h[i] = line(s, e);
      }
    }
  }

  int q;
  std::cin >> q;
  for (int _ = 0; _ < q; ++_) {
    point a;
    std::cin >> a.x >> a.y;

    bool flag = true;
    for (int i = 0; i < n; ++i) {
      if (h[i].relationToPoint(a) == -1) {
        flag = false;
      }
    }

    std::cout << (flag ? "Yes" : "No") << "\n";
  }
}
```

</details>

## [Ex - Fill Triangle](https://atcoder.jp/contests/abc251/tasks/abc251_h)

<details>
<summary>题意</summary>

给你定一个数字三角形的第$n$层，让你求出第$k$层。

记第$i$层第$j$个元素为$B_{i, j}$，则$B_{i, j} = (B_{i + 1, j} + B_{i + 1, j + 1}) \mod 7$。

$n \le 10^9, k \le \min(n, 10^5)$且第$n$层中的数字可以分解成不超过$200$个连续且序列中元素值都相等的极大子序列。

</details>

<details>
<summary>思路</summary>

$\binom{i}{j} = (\binom{i + 7^n}{j} + \binom{i + 7^n}{j + 7^n}) \mod 7$。

根据这个就可以选最大的$d$满足$n - 7^d \ge k$，然后算出$n - 7^d$行。不断往上跳就能计算出第$k$行的情况。

每次跳的时候就双指针模拟一下。

</details>


<details>
<summary>AC代码</summary>

```cpp
// Problem: Ex - Fill Triangle
// Contest: AtCoder - Panasonic Programming Contest 2022(AtCoder Beginner
// Contest 251) URL: https://atcoder.jp/contests/abc251/tasks/abc251_h Memory
// Limit: 1024 MB Time Limit: 4000 ms
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
  int n, m, k;
  std::cin >> n >> m >> k;

  std::vector<std::pair<int, int>> a(m);
  for (int i = 0; i < m; ++i)
    std::cin >> a[i].first >> a[i].second;

  while (n > k) {
    int d = 1;
    while (n - 7 * d >= k)
      d = d * 7;

    std::vector<std::pair<int, int>> b;
    int la = 0, ra = 0;
    int tempd = d;
    while (tempd > a[ra].second) {
      tempd -= a[ra].second;
      ++ra;
    }
    int cl = a[la].second, cr = a[ra].second - tempd;

    while (ra < a.size()) {
      int first = (a[la].first + a[ra].first) % 7;
      int second = std::min(cl, cr);

      if (b.empty() || b.back().first != first) {
        b.emplace_back(first, second);
      } else {
        b.back().second += second;
      }

      cl -= second, cr -= second;
      if (cl == 0)
        cl = a[++la].second;
      if (cr == 0)
        cr = a[++ra].second;
    }

    a = b;
    n -= d;
    logd(d, k);
  }

  for (auto [f, s] : a) {
    for (int i = 0; i < s; ++i)
      std::cout << f << " ";
  }
  std::cout << "\n";
}
```

</details>