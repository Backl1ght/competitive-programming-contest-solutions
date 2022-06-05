# AtCoder Beginner Contest 254

A和B跳过。

## [C - K Swap](https://atcoder.jp/contests/abc254/tasks/abc254_c)

<details>
<summary>题意</summary>

给定长度为$n$的数组$a$，每次可以从$[1, n - k]$中选择一个$i$然后交换$a_i$和$a_{i + k}$，问是否能通过有限次的操作将$a$升序排序。

其中$2 \le n \le 2 \times {10}^5$。

</details>

<details>
<summary>思路</summary>

操作可以看成：模$k$同余的位置上的元素两两间可以交换，模$k$不同余的位置上的元素无法交换。

将位置拆分成多个模$k$同余的极大子集，最终是有序的话那子集内肯定也有序，所以在子集内部排好序。

如果这样还不能让$a$有序那就无解了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: C - K Swap
// Contest: AtCoder - AtCoder Beginner Contest 254
// URL: https://atcoder.jp/contests/abc254/tasks/abc254_c
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
  int n, k;
  std::cin >> n >> k;

  std::vector<int> a(n);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i];

  for (int i = 0; i < k; ++i) {
    std::vector<int> b;
    for (int j = i; j < n; j += k)
      b.push_back(a[j]);
    std::sort(b.begin(), b.end());
    for (int j = i, p = 0; j < n; j += k)
      a[j] = b[p++];
  }

  for (int i = 1; i < n; ++i)
    if (a[i - 1] > a[i]) {
      std::cout << "No\n";
      return;
    }
  std::cout << "Yes\n";
}

```

</details>

## [D - Together Square](https://atcoder.jp/contests/abc254/tasks/abc254_d)

<details>
<summary>题意</summary>

给定$n$，问满足$1 \le i, j \le n$且$i * j$是完全平方数的$(i, j)$的数量。

其中$1 \le n \le 2 \times {10}^5$。

</details>

<details>
<summary>思路</summary>

记$x$的质因数分解为$x = \prod {p_i}^{e_i}$。

$x$是完全平方数当且仅当$e_i$全是偶数。

假设数$f(y) = \prod_{e_i \text{ is odd}} {p_i}^{e_i}$，则$x * y$是完全平方数当且仅当$f(x) = f(y)$。

对$1$到$n$中的数跑质因数分解求出所有$f(x)$，$O(n \sqrt{n})$可以搞定。

然后就是简单数数了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: D - Together Square
// Contest: AtCoder - AtCoder Beginner Contest 254
// URL: https://atcoder.jp/contests/abc254/tasks/abc254_d
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

  std::vector<int> f(n + 1);
  for (int i = 1; i <= n; ++i) {
    f[i] = 1;
    int x = i;
    for (int j = 2; j * j <= i; ++j) {
      if (x % j == 0) {
        int e = 0;
        while (x % j == 0) {
          x /= j;
          ++e;
        }
        if (e & 1)
          f[i] *= j;
      }
    }
    if (x > 1)
      f[i] *= x;
  }

  i64 ans = 0;
  std::vector<int> cnt(n + 1);
  for (int i = 1; i <= n; ++i) {
    ans += 2 * cnt[f[i]] + 1;
    ++cnt[f[i]];
  }

  std::cout << ans << "\n";
}

```

</details>

## [E - Small d and k](https://atcoder.jp/contests/abc254/tasks/abc254_e)

<details>
<summary>题意</summary>

给定一张$n$个点$m$条边的无向图，保证每个点的度数至多为3。

要求回答$q$个询问$(x_i, k_i)$，每个询问要求回答：距离$x_i$不超过$k_i$的点的下标之和。

其中$1 \le n, q \le 1.5 \times {10}^5, 0 \le k_i \le 3$。

</details>

<details>
<summary>思路</summary>

对于每个询问，满足条件的点不超过$3^3 = 27$个，直接BFS或者DFS就完事了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: E - Small d and k
// Contest: AtCoder - AtCoder Beginner Contest 254
// URL: https://atcoder.jp/contests/abc254/tasks/abc254_e
// Memory Limit: 1024 MB
// Time Limit: 3500 ms
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
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  auto Q = [&](int x, int k) -> i64 {
    i64 ans = 0;

    std::unordered_map<int, bool> vis;
    std::queue<int> q;
    q.push(x);
    vis[x] = true;

    for (int d = 0; d <= k; ++d) {
      int size = q.size();
      for (int i = 0; i < size; ++i) {
        int u = q.front();
        q.pop();

        ans += u + 1;

        for (int v : g[u]) {
          if (vis.count(v))
            continue;
          vis[v] = true;
          q.push(v);
        }
      }
    }

    return ans;
  };

  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    int x, k;
    std::cin >> x >> k;
    --x;

    std::cout << Q(x, k) << "\n";
  }
}

```

</details>

## [F - Rectangle GCD](https://atcoder.jp/contests/abc254/tasks/abc254_f)

<details>
<summary>题意</summary>

给定两个长度为$n$的数组$a$和$b$。

有一个$n \times n$的矩阵$M$满足$M_{i, j} = a_i + b_j$。

要求回答$q$个询问$(x_1, y1, x_2, y_2)$，每个询问需要回答位于以$(x_1, y_1)$为左上角，$(x_2, y_2)$为右下角的矩阵中，所有元素的GCD。

其中$1 \le n, q \le 2 \times {10}^5, 1 \le a_i, b_i \le 10^9$。

</details>

<details>
<summary>思路</summary>

由于$gcd(a, b) = gcd(a - b, b)$，所以从第$y_2$列到第$y_1 + 1$列，让第$j$列减去第$j - 1$列，这样每一行的后$y_2 - y_1$列就都成了$b_{j+ 1} - b_j, y_1 \le j \le y_2 - 1$。

对第$x_1 + 1$行到第$x_2$行做类似的操作，得到$a_{i + 1} - a_i, x_1 \le i \le x_2 - 1$。

现在矩阵中只剩$a_i + b_j$，$a_{i + 1} - a_i, x_1 \le i \le x_2 - 1$，$b_{j+ 1} - b_j, y_1 \le j \le y_2 - 1$以及一堆$0$，其中$0$可以直接诶忽略。

答案即为这三部分的GCD。

后两部分就是差分数组的区间GCD，由于GCD有可重复性，所以直接RMQ就可以$O(n \log n) \sim O(1)$求出GCD。

现在就是3个数的GCD了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: F - Rectangle GCD
// Contest: AtCoder - AtCoder Beginner Contest 254
// URL: https://atcoder.jp/contests/abc254/tasks/abc254_f
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

struct RMQ {
  std::vector<int> lg;
  std::vector<std::vector<int>> a;
  RMQ(const std::vector<int>& d) {
    int n = d.size();

    lg = std::vector<int>(n + 1);
    lg[1] = 0;
    for (int i = 2; i <= n; ++i)
      lg[i] = lg[i >> 1] + 1;

    a = std::vector<std::vector<int>>(n, std::vector<int>(lg[n] + 1));
    for (int i = 0; i < n; ++i)
      a[i][0] = d[i];
    for (int j = 1; j <= lg[n]; ++j) {
      for (int i = 0; i + (1 << (j - 1)) < n; ++i) {
        a[i][j] = std::gcd(a[i][j - 1], a[i + (1 << (j - 1))][j - 1]);
      }
    }
  }

  int query(int l, int r) {
    int k = lg[r - l + 1];
    return std::gcd(a[l][k], a[r - (1 << k) + 1][k]);
  }
};

void solve_case(int Case) {
  int n, q;
  std::cin >> n >> q;

  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i];
  for (int i = 0; i < n; ++i)
    std::cin >> b[i];

  std::vector<int> da(n - 1), db(n - 1);
  for (int i = 0; i + 1 < n; ++i) {
    da[i] = a[i + 1] - a[i];
    db[i] = b[i + 1] - b[i];
  }

  RMQ DA(da), DB(db);

  for (int i = 0; i < q; ++i) {
    int x1, y1, x2, y2;
    std::cin >> x1 >> x2 >> y1 >> y2;
    --x1, --y1, --x2, --y2;
    int ans = a[x1] + b[y1];
    logd(ans);
    if (x2 > x1) {
      ans = std::gcd(ans, DA.query(x1, x2 - 1));
    }
    if (y2 > y1) {
      ans = std::gcd(ans, DB.query(y1, y2 - 1));
    }
    std::cout << ans << "\n";
  }
}

```

</details>

## [G - Elevators](https://atcoder.jp/contests/abc254/tasks/abc254_g)

<details>
<summary>题意</summary>

有$n$幢高为${10}^9$的大楼，你可以通过天桥以$1$的代价从某幢大楼的某一层走到另一幢大楼的同一层。

有$m$台电梯$(a_i, b_i, c_i)$可以从第$a_i$幢大楼的第$x$层走到第$y$层，代价为$|x - y|$，其中$b_i \le x, y \le c_i$。

要求回答$q$个询问，每个询问要求回答从第$x$幢大楼的第$y$层走到第$z$幢大楼的第$w$层的最小代价。

其中$1 \le n, m, q \le 2 \times {10}^5$。

</details>

<details>
<summary>思路</summary>

走的过程是可逆的，所以可以处理一下使得询问总是从低层走到高层。

将答案分为两部分：使用电梯的代价和使用天桥的代价。

注意到这个过程中其实没有必要往底层走，所以使用电梯的代价为$w - y$。

同样的原因，可以类似倍增LCA那样子，借助倍增加速计算使用天桥的代价。

具体就是计算$dp_{i, j}$表示从$i$开始走$2^j$个天桥能达到的最高的点。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: G - Elevators
// Contest: AtCoder - AtCoder Beginner Contest 254
// URL: https://atcoder.jp/contests/abc254/tasks/abc254_g
// Memory Limit: 1024 MB
// Time Limit: 6000 ms
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
  // Merge elevator with intersection.
  auto merge = [](std::vector<std::array<int, 2>> a) -> std::vector<std::array<int, 2>> {
    if (a.empty())
      return {};

    std::sort(a.begin(), a.end());
    std::vector<std::array<int, 2>> temp;
    temp.push_back(a[0]);
    for (int i = 1; i < (int)a.size(); ++i) {
      auto [l1, r1] = temp.back();
      auto [l2, r2] = a[i];

      if (l2 <= r1) {
        temp.back()[1] = std::max(r1, r2);
      } else {
        temp.push_back({l2, r2});
      }
    }

    return temp;
  };

  // Sort the elevators by r, and filter out elevators that covered completely by another elevator.
  auto filter = [](std::vector<std::array<int, 2>> a) -> std::vector<std::array<int, 2>> {
    if (a.empty())
      return {};

    std::sort(a.begin(), a.end());
    std::vector<std::array<int, 2>> temp;
    temp.push_back(a[0]);
    for (int i = 1; i < (int)a.size(); ++i) {
      auto [l1, r1] = temp.back();
      auto [l2, r2] = a[i];

      if (r2 <= r1)
        continue;

      if (l1 == l2)
        temp.pop_back();

      temp.push_back({l2, r2});
    }

    return temp;
  };

  // dp[i][j] means the highest elevator you can reach that starting from the i-th elevator and then
  // use 2^j skybridge.
  auto DP = [](const std::vector<std::array<int, 2>>& a) -> std::vector<std::vector<int>> {
    int n = a.size();
    int lg = std::__lg(n) + 1;
    std::vector<std::vector<int>> dp(n, std::vector<int>(lg));

    for (int i = 0, j = 0; i < n; ++i) {
      while (j + 1 < n && a[j + 1][0] <= a[i][1])
        ++j;
      dp[i][0] = j;
    }

    for (int j = 1; j < lg; ++j) {
      for (int i = 0; i < n; ++i) {
        dp[i][j] = dp[dp[i][j - 1]][j - 1];
      }
    }
    return dp;
  };

  int n, m, q;
  std::cin >> n >> m >> q;

  std::vector<std::vector<std::array<int, 2>>> elev_in(n);
  std::vector<std::array<int, 2>> elev_all;
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    std::cin >> a >> b >> c;
    --a;
    elev_in[a].push_back({b, c});
  }
  for (int i = 0; i < n; ++i) {
    elev_in[i] = merge(elev_in[i]);
    for (auto [l, r] : elev_in[i])
      elev_all.push_back({l, r});
  }
  elev_all = filter(elev_all);

  auto dp = DP(elev_all);
  int lg = dp[0].size();

  for (int _ = 0; _ < q; ++_) {
    int x, y, z, w;
    std::cin >> x >> y >> z >> w;
    --x, --z;

    // Make it always move from lower floor to higher floor.
    if (y > w) {
      std::swap(x, z);
      std::swap(y, w);
    }

    // Split the answer into 2 parts, one part is cost of using elevator, the other is cost of using
    // skybridges.

    // The first part will always be w - y.
    int ans = w - y;

    // Try get closer to target by using elevator in the beginning building and the ending building.
    // After this, it can not get higher without using skybridges.
    {
      auto it = std::lower_bound(elev_in[x].begin(), elev_in[x].end(),
                                 std::array<int, 2>{y, 1'000'000'001});
      if (it != elev_in[x].begin()) {
        --it;
        if (y <= (*it)[1])
          y = (*it)[1];
      }
    }
    {
      auto it = std::lower_bound(elev_in[z].begin(), elev_in[z].end(),
                                 std::array<int, 2>{w, 1'000'000'001});
      if (it != elev_in[z].begin()) {
        --it;
        if (w <= (*it)[1])
          w = (*it)[0];
      }
    }

    // The second part.
    if (y >= w) {
      // Only need to use 1 skybridge. Or no need to use skybridge.
      if (x != z)
        ++ans;
    } else {
      // Find the elevator that cover the the y-th floor and with **largest** r.
      auto it =
          std::lower_bound(elev_all.begin(), elev_all.end(), std::array<int, 2>{y, 1'000'000'001});
      if (it == elev_all.begin()) {
        // No such elevator and then there is no elevator can be used.
        ans = -1;
      } else {
        --it;

        if (y > (*it)[1]) {
          // No such elevator and then there is no elevator can be used.
          ans = -1;
        } else {
          // Found an elevator and move to building where the elevator located.
          y = (*it)[1];
          ++ans;

          if (y >= w) {
            // Target achieved, move to the ending building (and use exatly 2 skybridges in total).
            ++ans;
          } else {
            // Optimized process using binary lifting. After this, y can reach the highest floor
            // below w.
            int p = it - elev_all.begin();
            for (int i = lg - 1; i >= 0; --i) {
              if (elev_all[dp[p][i]][1] < w) {
                p = dp[p][i];
                ans += (1 << i);
              }
            }

            // One more jump.
            p = dp[p][0];
            ++ans;

            y = elev_all[p][1];
            if (y < w) {
              // Can not reach w.
              ans = -1;
            } else {
              // Target achieved, move to the ending building.
              ++ans;
            }
          }
        }
      }
    }

    std::cout << ans << "\n";
  }
}

```

</details>

## [Ex - Multiply or Divide by 2](https://atcoder.jp/contests/abc254/tasks/abc254_h)

<details>
<summary>题意</summary>

给定两个长度为$n$的数组$a$和$b$，有以下两种操作：
1. 选择$a$中的一个元素$x$，将其替换为$2x$。
2. 选择$a$中的一个元素$x$，将其替换为$\lfloor \frac{x}{2} \rfloor$。

其中$1\le n \le {10}^5, 0 \le a_i, b_i \le {10}^9$。

</details>

<details>
<summary>思路</summary>

第一个操作可以看成将$b$中的一个偶数$y$替换为$\frac{y}{2}$。

然后，注意到两个数组中的最大值一定是要操作的，不妨贪心地选择大的先处理。

如果最大值在$y$中且$y$为奇数则无解，因为没有办法通过将$a$中的元素乘2来得到$y$。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: Ex - Multiply or Divide by 2
// Contest: AtCoder - AtCoder Beginner Contest 254
// URL: https://atcoder.jp/contests/abc254/tasks/abc254_h
// Memory Limit: 1024 MB
// Time Limit: 2500 ms
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

  std::multiset<int> a, b;
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    a.insert(x);
  }
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    b.insert(x);
  }

  int ans = 0;
  while (a.size()) {
    int x = *a.rbegin();
    int y = *b.rbegin();

    if (x == y) {
      a.erase(a.find(x));
      b.erase(b.find(y));
      continue;
    }

    ++ans;
    if (x < y) {
      if (y & 1) {
        ans = -1;
        break;
      }
      b.erase(b.find(y));
      y = y / 2;
      if (x == y) {
        a.erase(a.find(x));
      } else {
        b.insert(y);
      }
    } else {
      a.erase(a.find(x));
      x = x / 2;
      if (x == y) {
        b.erase(b.find(y));
      } else {
        a.insert(x);
      }
    }
  }

  std::cout << ans << "\n";
}

```

</details>
