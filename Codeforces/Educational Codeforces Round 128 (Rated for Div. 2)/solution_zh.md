# Educational Codeforces Round 128 (Rated for Div. 2)

## [A. Minimums and Maximums](https://codeforces.com/contest/1680/problem/A)

<details>
<summary>题意</summary>

问同时满足下列条件的最小数组长度：
- 至少有$l_1$个，至多有$r_1$个元素等于最小值
- 至少有$l_2$个，至多有$r_2$个元素等于最大值

</details>

<details>
<summary>思路</summary>

首先肯定是只包含最小值和最大值数组长度会更小。

然后就是如果最小值和最大值相等的情况，这种情况下要么$l_1 \le l_2 \le r_1$答案为$l_2$或者$l_2 \le l_1 \le r_2$答案为$l_1$。

剩余情况就都是有$l_1$个较小值和$l_2$个较大值，答案为$l_1 + l_2$。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: A. Minimums and Maximums
// Contest: Codeforces - Educational Codeforces Round 128 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1680/problem/A
// Memory Limit: 512 MB
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
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

void solve_case(int Case) {
  int l1, r1, l2, r2;
  std::cin >> l1 >> r1 >> l2 >> r2;
  if (l1 <= l2) {
    if (l2 <= r1)
      std::cout << l2 << "\n";
    else
      std::cout << l1 + l2 << "\n";
  } else if (l1 > l2) {
    if (l1 <= r2)
      std::cout << l1 << "\n";
    else
      std::cout << l1 + l2 << "\n";
  }
}
```

</details>


## [B. Robots](https://codeforces.com/contest/1680/problem/B)

<details>
<summary>题意</summary>

给一个矩阵，里面的格子要么是空的，要么是机器人。

你可以给机器人下指令，让**所有**机器人**同时**向上下左右4个方向的其中一个移动一个格子，所有机器人的移动方向**相同**。

不可以让任何机器人出界，问是否存在一个指令序列使得有机器人位于最左上角的格子。

</details>

<details>
<summary>思路</summary>

观察可得：有解当且仅当最靠左的机器人和最靠上的机器人是同一个机器人。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: B. Robots
// Contest: Codeforces - Educational Codeforces Round 128 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1680/problem/B
// Memory Limit: 512 MB
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
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

void solve_case(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::string> s(n);
  for (int i = 0; i < n; ++i)
    std::cin >> s[i];

  int x1 = -1, y1 = -1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (x1 == -1 && s[i][j] == 'R') {
        x1 = i, y1 = j;
      }
    }
  }

  int x2 = -1, y2 = -1;
  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < n; ++i) {
      if (x2 == -1 && s[i][j] == 'R') {
        x2 = i, y2 = j;
      }
    }
  }

  std::cout << ((x1 == x2 && y1 == y2) ? "YES" : "NO") << "\n";
}
```

</details>

## [C. Binary String](https://codeforces.com/contest/1680/problem/C)

<details>
<summary>题意</summary>

给你一个只包含$0$或者$1$的字符串，可以从开头和结尾删除任意长度的字符，要求使得代价最小。

代价等于下面两个值中的最大值：
1. 留下的$0$的个数。
2. 删去的$1$的个数。

其中字符串长度至多为$2 \times 10^5$。

</details>

<details>
<summary>思路</summary>

二分+双指针。

二分答案，假设为$mid$，那么通过双指针去维护一个区间使得区间内$0$的个数不超过$mid$。

对于双指针维护的有效区间$[l, r]$，假设保留$[l, r]$，那么此时的代价通过前缀和很容易就能算，如果代价小于等于$mid$那就说明当前二分的答案可行。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: C. Binary String
// Contest: Codeforces - Educational Codeforces Round 128 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1680/problem/C
// Memory Limit: 512 MB
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
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

void solve_case(int Case) {
  std::string s;
  std::cin >> s;
  logd(s);

  int n = s.size();
  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i)
    a[i] = s[i - 1] - '0';
  logd(a);

  std::vector<int> b0(n + 1);
  for (int i = 1; i <= n; ++i)
    b0[i] = b0[i - 1] + (a[i] == 0);

  std::vector<int> b1(n + 1);
  for (int i = 1; i <= n; ++i)
    b1[i] = b1[i - 1] + (a[i] == 1);

  // if (b1[n] == 0 || b1[1] == 0) {
  // std::cout << "0\n";
  // return;
  // }
  //
  auto check = [&](int k) -> bool {
    if (b0[n] <= k)
      return true;
    if (b1[n] <= k)
      return true;
    int l = 1, r = 0;
    int c[2] = {0, 0};
    while (r + 1 <= n) {
      r = r + 1;
      ++c[a[r]];

      while (l <= r && c[0] > k) {
        --c[a[l]];
        l = l + 1;
      }
      if (l <= r) {
        int cost = std::max(b0[r] - b0[l - 1], b1[n] - (b1[r] - b1[l - 1]));
        logd(l, r, cost);
        if (cost <= k)
          return true;
      }
    }
    return false;
  };

  int l = 0, r = n, mid, ans = n + 1;
  while (l <= r) {
    mid = (l + r) >> 1;
    logd(mid);
    if (check(mid))
      r = mid - 1, ans = mid;
    else
      l = mid + 1;
  }
  logd(ans);
  std::cout << ans << "\n";
}
```

</details>



## [D. Dog Walking](https://codeforces.com/contest/1680/problem/D)

<details>
<summary>题意</summary>

给你一个长度为$n$的数组$a$，你可以将$a_i = 0$的地方替换成$[-k, k]$之间的任意整数。

要求最后$\sum_{i = 1}^{n} a_i = 0$，问能够达到的最大的$\max_j \sum_{i = 1}^{j} a_i$

其中，$1 \le n \le 3000, -10^9 \le a_i \le 10^9, 1 \le k \le 10^9$。

</details>

<details>
<summary>思路</summary>

在整个过程中所能达到的，最靠左的点为$l$，最靠右的点为$r$，那么答案即为$r - l + 1$。

对于一段操作序列，假设从$0$开始，这个过程中能走到最靠左的点和能走到最靠右的点是容易维护的，且中间任意点都是可达的。由于$n$至多只有$3000$，所以所有连续子序列的对应的端点是可以求的。

然后肯定要尽量避免左右横跳，所以向左和向右其中一个操作肯定是连续的。所以，对于$a_i = 0$的位置，可以将其分为3个连续的部分：
1. 向右（左）走。
2. 向左（右）走。
3. 再向右（左）走。

枚举步骤2对应的区间，然后枚举这个区间向左还是向右一共两种情况，算出收益，再取最大值即可。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: D. Dog Walking
// Contest: Codeforces - Educational Codeforces Round 128 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1680/problem/D
// Memory Limit: 256 MB
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

void solve_case(int Case) {
  int n, k;
  std::cin >> n >> k;

  std::vector<int> a(n + 2);
  for (int i = 1; i <= n; ++i)
    std::cin >> a[i];

  using range = std::pair<i64, i64>;
  auto add = [&k](const range& r, int a) {
    if (a == 0)
      return range(r.first - k, r.second + k);
    return range(r.first + a, r.second + a);
  };

  auto dis = [](i64 x) { return x < 0 ? -x + 1 : x + 1; };

  std::vector<range> prev(n + 2);
  for (int i = 1; i <= n; ++i) {
    prev[i] = add(prev[i - 1], a[i]);
  }
  std::vector<range> suff(n + 2);
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; ++j) {
      suff[i] = add(suff[i], a[j]);
    }
  }
  if (prev[n].first > 0 || prev[n].second < 0) {
    std::cout << "-1\n";
    return;
  }

  i64 ans = 0;
  for (int i = 1; i <= n; ++i) {
    range c;
    for (int j = i; j <= n; ++j) {
      c = add(c, a[j]);

      i64 l = std::max(-prev[i - 1].second - suff[j + 1].second, c.first);
      i64 r = std::min(-prev[i - 1].first - suff[j + 1].first, c.second);
      logd(c, l, r);
      if (l <= r) {
        ans = std::max({ans, dis(l), dis(r)});
      }
    }
  }
  std::cout << ans << "\n";
}
```

</details>

## [E. Moving Chips](https://codeforces.com/contest/1680/problem/E)

<details>
<summary>题意</summary>

给你一个$2$行$n$列的矩阵，每个格子要么是空的，要么装了一根薯条。

你每次可以选择一根薯条，然后让他向上下左右4个方向之一移动一个格子，不能出界。如果进入到一个装有薯条的格子，那么原本在目标格子中的那根薯条消失。

问使得最后只剩一根薯条的最小操作次数。

</details>

<details>
<summary>思路</summary>

DP。

首先，假设最靠左的薯条位于$l$列，最靠右的薯条位于$r$列。

观察可得：对于每一根薯条，如果它向左移动了就不可能再向右移动，反过来也一样。

由此，假设最后位于$(i, 0)$，那么就可以将$i$列以及左侧的点都移动到$(i, 0)$或者$(i, 1)$，再将右侧的点都移动到$(i + 1, 0)$或者$(i + 1, 1)$，然后再合并两个点。

然后就可以DP计算两个方向的最小代价，然后再通过上述否那根法合并得到答案。转移方程感觉挺直观的就不写了。

**注**：可以证明所有薯条只向右移动的答案也是最优的，可以只算一个方向，然后省去另一个方向和合并的代码。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: E. Moving Chips
// Contest: Codeforces - Educational Codeforces Round 128 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1680/problem/E
// Memory Limit: 256 MB
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
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

void solve_case(int Case) {
  int n;
  std::cin >> n;

  std::string s[2];
  std::cin >> s[0];
  std::cin >> s[1];
  logd(n);

  std::vector<std::vector<int>> a(n + 2, std::vector<int>(2));
  int l = n + 1, r = 0;
  for (int i = 1; i <= n; ++i) {
    a[i][0] = (s[0][i - 1] == '*');
    a[i][1] = (s[1][i - 1] == '*');
    if (a[i][0] || a[i][1]) {
      l = std::min(l, i);
      r = std::max(r, i);
    }
  }

  std::vector<std::vector<int>> prev(n + 1, std::vector<int>(2));
  if (a[l][0] && a[l][1]) {
    prev[l][0] = 1;
    prev[l][1] = 1;
  } else if (a[l][0]) {
    prev[l][0] = 0;
    prev[l][1] = 0x3f3f3f3f;
  } else if (a[l][1]) {
    prev[l][0] = 0x3f3f3f3f;
    prev[l][1] = 0;
  }
  for (int i = l + 1; i <= r; ++i) {
    prev[i][0] = std::min(prev[i - 1][0] + 1 + a[i][1], prev[i - 1][1] + 2);
    prev[i][1] = std::min(prev[i - 1][1] + 1 + a[i][0], prev[i - 1][0] + 2);
  }

  std::vector<std::vector<int>> suff(n + 1, std::vector<int>(2));
  if (a[r][0] && a[r][1]) {
    suff[r][0] = 1;
    suff[r][1] = 1;
  } else if (a[r][0]) {
    suff[r][0] = 0;
    suff[r][1] = 0x3f3f3f3f;
  } else if (a[r][1]) {
    suff[r][0] = 0x3f3f3f3f;
    suff[r][1] = 0;
  }
  for (int i = r - 1; i >= l; --i) {
    suff[i][0] = std::min(suff[i + 1][0] + 1 + a[i][1], suff[i + 1][1] + 2);
    suff[i][1] = std::min(suff[i + 1][1] + 1 + a[i][0], suff[i + 1][0] + 2);
  }

  int ans = std::min({prev[r][0], prev[r][1], suff[l][0], suff[l][1]});
  for (int i = l + 1; i <= r - 1; ++i) {
    ans = std::min(
        {ans, prev[i][0] + suff[i + 1][0] + 1, prev[i][0] + suff[i + 1][1] + 2,
         prev[i][1] + suff[i + 1][0] + 2, prev[i][1] + suff[i + 1][1] + 1});
  }

  std::cout << ans << "\n";
}
```

</details>

## [F. Lenient Vertex Cover](https://codeforces.com/contest/1680/problem/F)

<details>
<summary>题意</summary>

给一个简单无向图，求一个**宽松**点覆盖。  

点覆盖：一个点的集合使得所有边至少有一个端点在集合中。

宽松点覆盖：至多有1条边它的两个端点都在集合中的点覆盖。

</details>

<details>
<summary>思路</summary>

考虑一个**严格**点覆盖：所有边都是只有一个端点都在集合中的点覆盖。

观察可得：偶环是严格点覆盖，奇环不是严格点覆盖。

所以一张有严格点覆盖的图不能有奇环，这可以联想到二分图。

先DFS跑一边二分图染色，顺便也得到一棵DFS树和非树边集合。

定义一条好边是两个端点颜色不同，一条坏边是两个端点颜色相同。

树边都是好边，非树边可能是好边也可能是坏边。

没有坏边的图有严格点覆盖，有坏边的图没有严格点覆盖。

而题目要求的是宽松点覆盖，至多有一条边两个端点都在点覆盖中相当于可以通过至多删一条边从而达到没有坏边。

如果坏边的数量等于0，那么就可以直接输出了。

如果坏边的数量等于1，把坏边删了也可以直接输出了。

如果坏边的数量大于等于2，删除一条非树边是解决不了问题的，还会有别的坏边。所以考虑删掉一条树边，看能不能解决问题。

删掉一条树边之后，可以通过一端在子树中的非树边使图重新连通，如果这条非树边是好的，并不会有什么改变；如果这条非树边是坏的，那么为了满足二分图的条件，子树中的点需要重新染色，这个操作会使一端在子树中的非树边中的好边变成坏边，坏边变成好边。如果一端在子树中的非树边中包含所有的坏边，且恰好只包含一条好边，那么就可以搞掉所有的坏边，从而满足题目要求。

实现的时候借助树上差分可以求出一端在子树中的好非树边和坏非树边的数量，然后再判断一下就可以了。

最后输出二分图的分量之一就可以了，注意可能有一个分量不是点覆盖，原因是删除边的操作并不是真的删除，只是把这条边当成了那条两个端点都在点覆盖中的边，选择另外一个分量的话这条边的两个端点就都不在点覆盖中了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: F. Lenient Vertex Cover
// Contest: Codeforces - Educational Codeforces Round 128 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1680/problem/F
// Memory Limit: 512 MB
// Time Limit: 5000 ms
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
  std::cin >> T;
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

  int cnt[2] = {0, 0};
  std::vector<std::vector<int>> sum(2, std::vector<int>(n, 0));

  int flip = 0;
  int dfs_clock = 0;
  std::vector<int> dfn(n);
  std::vector<int> c(n, -1);
  std::vector<std::vector<int>> h(n);
  std::function<void(int)> dfs_color = [&](int u) {
    dfn[u] = ++dfs_clock;
    for (int v : g[u]) {
      if (c[v] == -1) {
        c[v] = !c[u];
        h[u].push_back(v);
        dfs_color(v);
      } else if (dfn[v] < dfn[u]) {
        int type = c[u] == c[v];
        sum[type][v]--;
        sum[type][u]++;
        ++cnt[type];
        if (type == 1)
          flip = !c[u];
      }
    }
  };
  c[0] = 0;
  dfs_color(0);

  int ans = 0;

  std::function<void(int)> dfs_recolor = [&](int u) {
    logd(u);
    c[u] = !c[u];
    for (int v : h[u]) {
      dfs_recolor(v);
    }
  };

  bool finished = false;
  std::function<void(int)> dfs_ans = [&](int u) {
    for (int v : h[u]) {
      dfs_ans(v);
      if (not finished) {
        if (sum[1][v] == cnt[1] && sum[0][v] == 1) {
          logd(v);
          ans = 1;
          logd(c);
          dfs_recolor(v);
          logd(c);
          flip = !c[u];
          finished = true;
          continue;
        }
        for (int type : {0, 1})
          sum[type][u] += sum[type][v];
      }
    }
  };

  if (cnt[1] <= 1) {
    ans = 1;
  } else {
    dfs_ans(0);
  }

  if (ans == 0)
    std::cout << "NO\n";
  else {
    std::cout << "YES\n";
    for (int i = 0; i < n; ++i)
      std::cout << (c[i] ^ flip);
    std::cout << "\n";
  }
}
```

</details>