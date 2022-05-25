# Educational Codeforces Round 129 (Rated for Div. 2)

## [A. Game with Cards](https://codeforces.com/contest/1681/problem/A)

<details>
<summary>题意</summary>

两个人，每个人手上有一些牌，牌上写有数字。两个人轮流出牌，其中一个人先出，后面如果要出牌，牌上的数字必须比前一张牌要大。第一个不能出牌的人就输。

问两个人是否是先手必胜？

每个人牌的数量至多为$50$。

</details>

<details>
<summary>思路</summary>

答案只和两个人手上最大的牌有关。先手必胜当且仅当先手手上最大牌**大于等于**后手手上的最大牌。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: A. Game with Cards
// Contest: Codeforces - Educational Codeforces Round 129 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1681/problem/A
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
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
  int n;
  std::cin >> n;

  int ma = 0;
  for (int i = 1; i <= n; ++i) {
    int x;
    std::cin >> x;
    ma = std::max(ma, x);
  }

  int m;
  std::cin >> m;
  int mb = 0;
  for (int i = 1; i <= m; ++i) {
    int x;
    std::cin >> x;
    mb = std::max(mb, x);
  }

  std::cout << (ma >= mb ? "Alice" : "Bob") << "\n";
  std::cout << (ma > mb ? "Alice" : "Bob") << "\n";
}
```

</details>

## [B. Card Trick](https://codeforces.com/contest/1681/problem/B)

<details>
<summary>题意</summary>

给长度为$n$的数组$a$，长度为$m$的数组$b$。

执行$m$次操作，每次将$a$中前$b_j$个元素移动到末尾，相对顺序不变。

问执行完操作之后，$a$的首元素。

$n, m$至多为$2 \times 10^5$。

</details>

<details>
<summary>思路</summary>

第$j$次操作相当于将$a_i$替换为$a_{(i + b_j) \mod n}$。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: B. Card Trick
// Contest: Codeforces - Educational Codeforces Round 129 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1681/problem/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
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
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int& v : a)
    std::cin >> v;

  int m;
  std::cin >> m;
  std::vector<int> b(m);
  for (int& v : b)
    std::cin >> v;

  int p = 0;
  for (int i = 0; i < m; ++i) {
    p = (p + b[i]) % n;
  }

  std::cout << a[p] << "\n";
}
```

</details>

## [C. Double Sort](https://codeforces.com/contest/1681/problem/C)

<details>
<summary>题意</summary>

给定两个长度为$n$的数组$a$和$b$。每次可以选择两个下标$i$和$j$，然后交换$a_i$和$a_j$，交换$b_i$和$b_j$。

问是否能在$10^4$次操作内将$a$和$b$都变有序。

$n$至多为$100$。

</details>

<details>
<summary>思路</summary>

对$a$选择排序。

然后再尝试对$b$选择排序。假设当前位于$i$，后面的最小值位于$p$，由于$a$已经有序了，想把后面的值换到前面只能是$a_i = a_p$。

最差情况下，选择排序交换$\frac{n^2}{2}$次，排两次也不会超出限制。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: C. Double Sort
// Contest: Codeforces - Educational Codeforces Round 129 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1681/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
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
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> a(n);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i].first;
  for (int i = 0; i < n; ++i)
    std::cin >> a[i].second;

  std::vector<std::pair<int, int>> ans;
  for (int i = 0; i < n; ++i) {
    int p = i;
    for (int j = i + 1; j < n; ++j) {
      if (a[j].first < a[p].first) {
        p = j;
      }
    }
    if (p != i) {
      std::swap(a[i], a[p]);
      ans.push_back({i, p});
    }
  }

  for (int i = 0; i < n; ++i) {
    int p = i;
    for (int j = i + 1; j < n; ++j) {
      if (a[j].second < a[p].second) {
        p = j;
      }
    }
    if (p != i) {
      if (a[i].first == a[p].first) {
        std::swap(a[i], a[p]);
        ans.push_back({i, p});
      } else {
        std::cout << "-1\n";
        return;
      }
    }
  }
  std::cout << ans.size() << "\n";
  for (auto [x, y] : ans)
    std::cout << x + 1 << " " << y + 1 << "\n";
}
```

</details>

## [D. Required Length](https://codeforces.com/contest/1681/problem/D)

<details>
<summary>题意</summary>

给一个数$x$，每次你可以选择$x$的一个十进制数位，然后将$x$替换为$y \times x$。

问把$x$变成$n$为十进制数的最小操作。

</details>

<details>
<summary>思路</summary>

记忆化爆搜，证明不会，复杂度$O(\text{能过})$。

爆搜+剪枝也能过。

</details>

<details>
<summary>记忆化代码</summary>

```cpp
// Problem: D. Required Length
// Contest: Codeforces - Educational Codeforces Round 129 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1681/problem/D
// Memory Limit: 512 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
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
  i64 x;
  std::cin >> n >> x;

  logd(n, x);

  auto b10 = [](i64 x) {
    i64 r = 0;
    while (x) {
      ++r;
      x = x / 10;
    }
    return r;
  };

  auto m10 = [](i64 x) {
    i64 r = 0;
    while (x) {
      r = std::max(r, x % 10);
      x = x / 10;
    }
    return r;
  };

  auto s10 = [](i64 x) {
    std::set<int> s;
    while (x) {
      if (x % 10 > 1)
        s.insert(x % 10);
      x = x / 10;
    }
    return s;
  };

  auto t10 = [](i64 x) {
    int t = 0;
    while (x) {
      t |= (1 << (x % 10));
      x = x / 10;
    }
    return t;
  };

  auto f10 = [](i64 x) {
    int f = 0;
    while (x) {
      f = x % 10;
      x = x / 10;
    }
    return f;
  };

  if (m10(x) == 1 || b10(x) > n) {
    std::cout << "-1\n";
    return;
  }

  std::unordered_map<i64, int> mp;
  std::function<int(i64)> DP = [&](i64 x) -> int {
    if (mp.count(x))
      return mp[x];

    int b = b10(x);
    if (b == n) {
      mp[x] = 0;
      return 0;
    }
    if (b > n) {
      return 0x3f3f3f3f;
    }

    auto s = s10(x);
    int mi = 0x3f3f3f3f;
    for (int y : s) {
      mi = std::min(mi, DP(x * y) + 1);
    }
    mp[x] = mi;
    return mi;
  };
  int ans = DP(x);

  std::cout << ans << "\n";
}

```

</details>

<details>
<summary>剪枝代码</summary>

```cpp
// Problem: D. Required Length
// Contest: Codeforces - Educational Codeforces Round 129 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1681/problem/D
// Memory Limit: 512 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
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
  i64 x;
  std::cin >> n >> x;

  i64 p10[20];
  p10[0] = 1;
  for (int i = 1; i <= 19; ++i) {
    p10[i] = p10[i - 1] * 10;
  }

  int b = 0;
  while (x >= p10[b + 1])
    ++b;

  auto t10 = [](i64 x) {
    int t = 0;
    while (x) {
      t |= (1 << (x % 10));
      x = x / 10;
    }
    return t;
  };

  auto h = [&](i64 x, int n) {
    int r = 0;
    while (x < p10[n - 1]) {
      r = r + 1;
      x = x * 9;
    }
    return r;
  };

  if (x > p10[n - 1]) {
    std::cout << "-1\n";
    return;
  }

  int ans = INT_MAX;
  std::function<void(i64, int)> BF = [&](i64 x, int d) -> void {
    if (d >= ans)
      return;

    if (x >= p10[n - 1]) {
      ans = std::min(ans, d);
      return;
    }

    if (d + h(x, n) >= ans) {
      return;
    }

    int t = t10(x);
    for (int y = 9; y >= 2; --y) {
      if ((t >> y) & 1) {
        BF(y * x, d + 1);
      }
    }
  };
  BF(x, 0);
  if (ans == INT_MAX)
    ans = -1;

  std::cout << ans << "\n";
}

```

</details>

## [E. Labyrinth Adventures](https://codeforces.com/contest/1681/problem/E)

<details>
<summary>题意</summary>

将一个$n \times n$的矩阵分成多层，点$(i, j)$位于第$\max(i, j)$层。

认为共享一条边的格子为相邻的格子。

同层内相邻点可以随意移动，跨层只能通过层与层之间的门移动。

每一层都有两个门，一个向上开，一个向右开。

要求回答$q$个询问：从$(x_1, y_1)$到$(x_2, y_2)$的最短路长度。

$n \le 10^5, q \le 2 \times 10^5$。

</details>

<details>
<summary>思路</summary>

**观察1**：$(x_1, y_1)$和$(x_2, y_2)$同层，答案为两点间曼哈顿距离。

**观察2**：假设每次是从层数小的走向层数大的，这个过程中，不会走向层数低的层。
**证明**：同层内要走向更高层，一定要走到层内某一个门。在矩阵中，如果没有门的限制，两点间最短距离为曼哈顿距离，而同层内移动已经能做到这个最短了，没有必要往低层走。

然后从起点走到终点的化，就可以看成是起点走到当层的门，当层的门走到终点前一层的门，最走再走到终点这三个过程。第一个和第三个都是可以直接枚举算的，而第二个过程就是相当于2行$n$列的DP，一个经典的DP问题了。

根据观察2，整个过程只会往高层走，由此第二个过程其实可以像倍增LCA那样子做优化，具体就是维护一个$dp_{i, j, k, l}$表示从第$i$层第$k$个门走到第$i + 2^j$第$l$个门的最短距离，这个可以$O(n \log n)$求出来。然后查询的时候再通过至多$O(\log n)$次跳跃求出第二个过程的答案。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: E. Labyrinth Adventures
// Contest: Codeforces - Educational Codeforces Round 129 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1681/problem/E
// Memory Limit: 512 MB
// Time Limit: 6000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
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
  auto manhattan = [](int x1, int y1, int x2, int y2) -> i64 {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
  };
  int n;
  std::cin >> n;

  std::vector<std::vector<std::pair<int, int>>> door(2, std::vector<std::pair<int, int>>(n - 1));
  for (int i = 0; i < n - 1; ++i) {
    std::cin >> door[0][i].first >> door[0][i].second;
    std::cin >> door[1][i].first >> door[1][i].second;
  }

  int x = 1, lg = 0;
  while (x <= n) {
    x = x * 2;
    ++lg;
  }
  std::vector<std::vector<std::vector<std::vector<i64>>>> dis(
      n - 1, std::vector<std::vector<std::vector<i64>>>(
                 lg, std::vector<std::vector<i64>>(2, std::vector<i64>(2, 0x3f3f3f3f3f3f3f3fLL))));
  for (int i = 0; i + 1 < n - 1; ++i) {
    for (int d1 = 0; d1 < 2; ++d1) {
      for (int d2 = 0; d2 < 2; ++d2) {
        auto s = door[d1][i];
        if (d1 == 0)
          ++s.first;
        else
          ++s.second;
        auto t = door[d2][i + 1];
        dis[i][0][d1][d2] = manhattan(s.first, s.second, t.first, t.second) + 1;
      }
    }
  }
  for (int j = 1; j < lg; ++j) {
    for (int i = 0; i + 1 < n - 1; ++i) {
      if (i + (1 << (j - 1)) >= n - 2)
        break;
      for (int d1 = 0; d1 < 2; ++d1) {
        for (int d2 = 0; d2 < 2; ++d2) {
          for (int k = 0; k < 2; ++k) {
            dis[i][j][d1][d2] = std::min(
                dis[i][j][d1][d2], dis[i][j - 1][d1][k] + dis[i + (1 << (j - 1))][j - 1][k][d2]);
          }
        }
      }
    }
  }

  auto SP = [&](int x1, int y1, int x2, int y2) -> i64 {
    logd(x1, y1, x2, y2);
    i64 ans = INT64_MAX;

    int curr = std::max(x1, y1) - 1, dest = std::max(x2, y2) - 2;
    std::vector<i64> dp = {0, 0};
    for (int i = 0; i < 2; ++i) {
      dp[i] = manhattan(x1, y1, door[i][curr].first, door[i][curr].second);
      logd(x1, y1, door[i][curr].first, door[i][curr].second);
    }
    logd(curr, dp, dest);
    for (int b = lg; b >= 0; --b) {
      if (curr + (1 << b) <= dest) {
        auto temp = dp;
        dp[0] = dp[1] = INT64_MAX;
        for (int i = 0; i < 2; ++i) {
          for (int j = 0; j < 2; ++j) {
            dp[j] = std::min(dp[j], temp[i] + dis[curr][b][i][j]);
          }
        }
        curr += (1 << b);
        logd(curr, dp);
      }
    }
    assert(curr == dest);
    for (int i = 0; i < 2; ++i) {
      auto pos = door[i][dest];
      if (i == 0)
        ++pos.first;
      else
        ++pos.second;
      ans = std::min(ans, dp[i] + manhattan(pos.first, pos.second, x2, y2) + 1);
    }
    return ans;
  };

  int q;
  std::cin >> q;
  for (int _ = 0; _ < q; ++_) {
    int x1, y1, x2, y2;
    i64 ans = INT64_MAX;
    std::cin >> x1 >> y1 >> x2 >> y2;
    if (std::max(x1, y1) == std::max(x2, y2)) {
      ans = manhattan(x1, y1, x2, y2);
    } else {
      if (std::max(x1, y1) > std::max(x2, y2)) {
        std::swap(x1, x2);
        std::swap(y1, y2);
      }
      ans = std::min(ans, SP(x1, y1, x2, y2));
    }
    std::cout << ans << "\n";
  }
}

```

</details>

## [F. Unique Occurrences](https://codeforces.com/contest/1681/problem/F)

<details>
<summary>题意</summary>

给一颗$n$个节点的数，树上每一条边有一个权值。

令$f(u, v)$为$u$到$v$的路径上，只出现过一次的边权的数量。

求所有$\sum_{1\le v < u \le n} f(u, v)$。

$n$至多为$5 \times 10^5$。

</details>

<details>
<summary>思路</summary>

对于权值为$c$的边，如果将权值非$c$的边全部保留，权值为$c$的边全部删去，那么此时权值为$c$的边$(u, v)$对答案的贡献为$sz_u \times sz_v$。

然后就是LCT维护子树大小，这是个经典问题了，不会的话指路[Link Cut Tree - OI Wiki](https://oi-wiki.org/ds/lct/)。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: F. Unique Occurrences
// Contest: Codeforces - Educational Codeforces Round 129 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1681/problem/F
// Memory Limit: 1024 MB
// Time Limit: 6000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
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

struct LinkCutTree {
#define ls ch[x][0]
#define rs ch[x][1]
#define SIZE 500005

  int tot, sz[SIZE], sz2[SIZE], rev[SIZE], ch[SIZE][2], fa[SIZE];

  LinkCutTree() { tot = 0; }

  inline void init() { tot = 0; }

  inline void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = sz[x] = sz2[x] = rev[x] = 0; }

  inline int get(int x) { return ch[fa[x]][1] == x; }

  inline int isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }

  inline int newnode() {
    ++tot;
    sz[tot] = 1;
    ch[tot][0] = ch[tot][1] = fa[tot] = rev[tot] = 0;
    return tot;
  }

  inline void reverse(int x) {
    std::swap(ls, rs);
    rev[x] ^= 1;
  }

  inline void push_up(int x) { sz[x] = sz[ls] + 1 + sz[rs] + sz2[x]; }

  inline void push_down(int x) {
    if (rev[x]) {
      reverse(ls);
      reverse(rs);
      rev[x] = 0;
    }
  }

  inline void update(int x) {
    if (!isroot(x))
      update(fa[x]);
    push_down(x);
  }

  inline void rotate(int x) {
    int f = fa[x], g = fa[f], i = get(x);
    if (!isroot(f))
      ch[g][get(f)] = x;
    fa[x] = g;
    ch[f][i] = ch[x][i ^ 1];
    fa[ch[f][i]] = f;
    ch[x][i ^ 1] = f;
    fa[f] = x;
    push_up(f);
    push_up(x);
  }

  inline void splay(int x) {
    update(x);
    for (; !isroot(x); rotate(x))
      if (!isroot(fa[x]))
        rotate(get(fa[x]) == get(x) ? fa[x] : x);
  }

  inline void access(int x) {
    for (int y = 0; x; y = x, x = fa[x])
      splay(x), sz2[x] += sz[rs] - sz[y], rs = y, push_up(x);
  }

  inline void makeroot(int x) {
    access(x);
    splay(x);
    reverse(x);
  }

  inline int findroot(int x) {
    access(x);
    splay(x);
    while (ls)
      push_down(x), x = ls;
    return x;
  }

  inline void link(int x, int y) {
    makeroot(x);
    if (findroot(y) != x) {
      fa[x] = y;
      sz2[y] += sz[x];
    }
  }

  inline void cut(int x, int y) {
    makeroot(x);
    if (findroot(y) == x && fa[x] == y && ch[y][0] == x && !ch[y][1]) {
      fa[x] = ch[y][0] = 0;
      push_up(y);
    }
  }

  inline void split(int x, int y) {
    makeroot(x);
    access(y);
    splay(y);
  }
};

void solve_case(int Case) {
  int n;
  std::cin >> n;

  LinkCutTree lct;
  for (int i = 1; i <= n; ++i)
    lct.newnode();

  std::vector<std::array<int, 3>> E(n - 1);
  std::vector<std::vector<int>> C(n + 1);
  for (int i = 0; i < n - 1; ++i) {
    int u, v, x;
    std::cin >> u >> v >> x;
    logd(u, v, x);
    E[i] = {u, v, x};
    C[x].push_back(i);
    lct.link(u, v);
  }

  i64 ans = 0;
  for (int c = 1; c <= n; ++c) {
    for (int eid : C[c]) {
      auto [u, v, _] = E[eid];
      lct.cut(u, v);
    }

    for (int eid : C[c]) {
      auto [u, v, _] = E[eid];
      lct.makeroot(u);
      lct.makeroot(v);
      ans += i64(1) * lct.sz[u] * lct.sz[v];
    }

    for (int eid : C[c]) {
      auto [u, v, _] = E[eid];
      lct.link(u, v);
    }
  }

  std::cout << ans << "\n";
}

```

</details>