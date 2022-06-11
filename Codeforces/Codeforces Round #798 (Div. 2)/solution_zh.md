# Codeforces Round #798 (Div. 2)

## [A. Lex String](https://codeforces.com/contest/1689/problem/A)

<details>
<summary>题意</summary>

给定长度为$n$的串$a$和长度为$m$的串$b$，保证没有字符同时出现在两个串中。

有一个初始为空的串$c$，支持以下两种操作：
1. 从$a$中选一个字符，将其从$a$中删除，然后加到$c$的末尾。
2. 从$b$中选一个字符，将其从$b$中删除，然后加到$c$的末尾。

还有一个限制：同一个操作不能连续使用超过$k$次。

要求不断操作至$a$和$b$至少有一个空串，问字典序最小的$c$。

其中$n, m, k \le 100$。

</details>

<details>
<summary>思路</summary>

因为要字典序最小，肯定就是贪心先加小的字符。

不妨先给$a$和$b$，排个序，然后就是一个类似归并排序合并的过程。

合并过程中记录上一次使用的是哪一个操作，这个操作连续使用了多少次，如果当期最优的操作不满足条件就使用另外一个操作。

模拟一下完事。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: A. Lex String
// Contest: Codeforces - Codeforces Round #798 (Div. 2)
// URL: https://codeforces.com/contest/1689/problem/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

void solve_case(int Case) {
  int n, m, k;
  std::cin >> n >> m >> k;
  std::string a, b;
  std::cin >> a;
  std::cin >> b;

  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());

  std::string c;
  int pa = 0, pb = 0, x = 0, y = -1;
  while (pa < n && pb < m) {
    int z = 0;
    if (a[pa] < b[pb]) {
      z = 0;
    } else {
      z = 1;
    }

    if (y == z && x == k)
      z ^= 1;

    if (z == 0) {
      c += a[pa++];
    } else {
      c += b[pb++];
    }

    if (z == y) {
      ++x;
    } else {
      x = 1;
      y = z;
    }
  }

  std::cout << c << "\n";
}
```

</details>

## [B. Mystic Permutation](https://codeforces.com/contest/1689/problem/B)

<details>
<summary>题意</summary>

给定一个长度为$n$的排列$p$，问满足下列条件且字典序最小的排序$q$：
- $\forall i \in [1, n], p_i \ne q_i$。

其中$n \le 1000$。

</details>

<details>
<summary>思路</summary>

可能最优的答案是$q_i = i$，但是这个排列可能存在不满足条件的位置。

从左至右遍历所有位置，当前位置不满足条件时通过调整使其满足条件，具体调整就是$i < n$时交换$q_i$和$q_{i + 1}$，$i = n$时交换$q_{i}$和$q_{i - 1}$。

正确性没太仔细证，大概就是每次调整都会使字典序变大，然后每次贪心使用了字典序增加最小的操作，且前面的操作权重更大。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: B. Mystic Permutation
// Contest: Codeforces - Codeforces Round #798 (Div. 2)
// URL: https://codeforces.com/contest/1689/problem/B
// Memory Limit: 256 MB
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
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    --a[i];
  }

  if (n == 1) {
    std::cout << "-1\n";
    return;
  }

  std::vector<int> b(n);
  std::iota(b.begin(), b.end(), 0);
  for (int i = 0; i < n; ++i) {
    if (b[i] == a[i]) {
      if (i == n - 1) {
        std::swap(b[i], b[i - 1]);
      } else {
        std::swap(b[i], b[i + 1]);
      }
    }
  }

  for (int i = 0; i < n; ++i)
    std::cout << b[i] + 1 << " \n"[i + 1 == n];
}
```

</details>

## [C. Infected Tree](https://codeforces.com/contest/1689/problem/C)

<details>
<summary>题意</summary>

给定一颗$n$棵节点的二叉树，树以$1$为根。

初始时，树的根节点被病毒感染了。

接下来的过程会重复$n$次：
1. 你可以选择一个节点$u$，删除节点$u$及所有一端是$u$的边；你也可以选择不操作。
2. 被感染的点会扩散病毒，对于一个被感染的点$u$，和它邻接的点都会被感染；已经被感染的点保持会保持被感染。

问你最多能保多少个点不被感染且不被删除。

其中$n \le 3 \times {10}^5$。

</details>

<details>
<summary>思路</summary>

树形DP。

令$dp_u$表示$u$已经被感染了，通过后续操作$u$的子树中最多能保多少个点。显然$dp_1$即为答案。

如果$u$是叶子，则$dp_u = 0$。

如果$u$只有一个儿子$v$，则$dp_u = sz_v - 1$。

如果$u$有两个儿子，分别记为$l, r$，则$dp_u = \max(dp_l + sz_r - 1, dp_r + sz_l - 1)$。

然后就是DFS跑一炮算答案了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: C. Infected Tree
// Contest: Codeforces - Codeforces Round #798 (Div. 2)
// URL: https://codeforces.com/contest/1689/problem/C
// Memory Limit: 256 MB
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
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

void solve_case(int Case) {
  int n;
  std::cin >> n;

  std::vector<std::vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  std::vector<int> sz(n, 0);
  std::function<void(int, int)> dfs_size = [&](int u, int fa) {
    sz[u] = 1;
    for (int v : g[u]) {
      if (v == fa)
        continue;
      dfs_size(v, u);
      sz[u] += sz[v];
    }
  };
  dfs_size(0, -1);

  std::vector<int> dp(n, 0);
  std::function<void(int, int)> dfs_ans = [&](int u, int fa) {
    std::vector<int> a;
    for (int v : g[u]) {
      if (v == fa)
        continue;
      dfs_ans(v, u);
      a.push_back(v);
    }

    if (a.size() == 0) {
      dp[u] = 0;
    } else if (a.size() == 1) {
      dp[u] = sz[a[0]] - 1;
    } else {
      dp[u] = std::max(dp[a[0]] + sz[a[1]] - 1, dp[a[1]] + sz[a[0]] - 1);
    }
  };
  dfs_ans(0, -1);

  std::cout << dp[0] << "\n";
}
```

</details>

## [D. Lena and Matrix](https://codeforces.com/contest/1689/problem/D)

<details>
<summary>题意</summary>

给定一个$n$行$m$列的矩阵，矩形的每一个元素是黑色或者白色的，要求求出一个点$(a, b)$最小化
$$
\max_{\substack{1 \le i \le n\\(x_i, y_i) \text{ is black}}} |a - x_i| + |b - y_i|.
$$
其中$n, m \le 1000$。

</details>

<details>
<summary>思路1</summary>

对于一个点$(x, y)$，离他最远的黑点可能在他的左上，右上，左下或者右下，而每个方向上的最远的黑点是可以通过DP做到$O(n^2)$时间计算的。

然后再枚举一遍所有点就可以得出答案。

</details>

<details>
<summary>思路2</summary>

把要求最小化的式子分类讨论一下，可以得到：
1. $a + b + (-x_i + y_i)$
2. $a - b + (-x_i - y_i)$
3. $-a + b + (x_i - y_i)$
4. $-a - b + (x_i + y_i)$

然后就可以发现：所有黑点中只有4个是有效的，分别是最小化4个式子后半部分的点。

先遍历一遍求出4个有效点，然后在遍历一遍算答案就行了。

</details>

<details>
<summary>思路1 AC代码</summary>

```cpp
// Problem: D. Lena and Matrix
// Contest: Codeforces - Codeforces Round #798 (Div. 2)
// URL: https://codeforces.com/contest/1689/problem/D
// Memory Limit: 256 MB
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
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

const int N = 1005;
int n, m;
char s[N][N];
int dp1[N][N], dp2[N][N], dp3[N][N], dp4[N][N];
void solve_case(int Case) {
  std::cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    std::cin >> s[i] + 1;

  for (int i = 0; i <= n + 1; ++i) {
    for (int j = 0; j <= m + 1; ++j) {
      dp1[i][j] = dp2[i][j] = dp3[i][j] = dp4[i][j] = -1;
    }
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (s[i][j] == 'B')
        dp1[i][j] = 0;
      if (dp1[i - 1][j] != -1)
        dp1[i][j] = std::max(dp1[i][j], dp1[i - 1][j] + 1);
      if (dp1[i][j - 1] != -1)
        dp1[i][j] = std::max(dp1[i][j], dp1[i][j - 1] + 1);
      if (dp1[i - 1][j - 1] != -1)
        dp1[i][j] = std::max(dp1[i][j], dp1[i - 1][j - 1] + 2);
    }
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = m; j >= 1; --j) {
      if (s[i][j] == 'B')
        dp2[i][j] = 0;
      if (dp2[i - 1][j] != -1)
        dp2[i][j] = std::max(dp2[i][j], dp2[i - 1][j] + 1);
      if (dp2[i][j + 1] != -1)
        dp2[i][j] = std::max(dp2[i][j], dp2[i][j + 1] + 1);
      if (dp2[i - 1][j + 1] != -1)
        dp2[i][j] = std::max(dp2[i][j], dp2[i - 1][j + 1] + 2);
    }
  }

  for (int i = n; i >= 1; --i) {
    for (int j = 1; j <= m; ++j) {
      if (s[i][j] == 'B')
        dp3[i][j] = 0;
      if (dp3[i + 1][j] != -1)
        dp3[i][j] = std::max(dp3[i][j], dp3[i + 1][j] + 1);
      if (dp3[i][j - 1] != -1)
        dp3[i][j] = std::max(dp3[i][j], dp3[i][j - 1] + 1);
      if (dp3[i + 1][j - 1] != -1)
        dp3[i][j] = std::max(dp3[i][j], dp3[i + 1][j - 1] + 2);
    }
  }

  for (int i = n; i >= 1; --i) {
    for (int j = m; j >= 1; --j) {
      if (s[i][j] == 'B')
        dp4[i][j] = 0;
      if (dp4[i + 1][j] != -1)
        dp4[i][j] = std::max(dp4[i][j], dp4[i + 1][j] + 1);
      if (dp4[i][j + 1] != -1)
        dp4[i][j] = std::max(dp4[i][j], dp4[i][j + 1] + 1);
      if (dp4[i + 1][j + 1] != -1)
        dp4[i][j] = std::max(dp4[i][j], dp4[i + 1][j + 1] + 2);
    }
  }

  int min_dist = INT_MAX, x, y;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      int dist = std::max({dp1[i][j], dp2[i][j], dp3[i][j], dp4[i][j]});
      if (dist < min_dist) {
        x = i, y = j;
        min_dist = dist;
      }
    }
  }

  std::cout << x << " " << y << "\n";
}
```

</details>

## [E. ANDfinity](https://codeforces.com/contest/1689/problem/E)

<details>
<summary>题意</summary>

给定一个长度为$n$的数组$a$，有以下两种操作：
1. 选一个$a_i$，然后将其加1。
2. 选一个$a_i > 0$，然后将其减1。

根据$a$去建图：如果$a_i \operatorname{AND} a_j > 0$就在$i$和$j$之间连一条边。

问最少的操作次数使得建出来的图是连通的。

其中$n \le 2000, a_i < 2^{30}$。

</details>

<details>
<summary>思路</summary>

首先$a_i = 0$肯定是孤立点，不妨先对所有这种点加1。

**观察可得**：此时至多还需要两次操作就可以使图连通。

**证明**：记$f(x)$为$x$的least significant bit。记$\max_i f(a_i) = k$，有$m$个点$p_i$满足$f(a_{p_i}) = k$。$m = 1$时令$a_{p_1}$减1即可；否则选择$p_1$将其减1，选择$p_2$将其加1，则$f(a_i) < k$的点都与$p_1$连通，$p_1$与$p_2$连通，$p_2$与$p_i, 3 \le i \le m$连通。由此，通过至多两次操作就一定可以使图连通。

对于固定的$a$判断建出来的图是否连通可以借助并查集$O(n \log V)$做，然后分类讨论：
- 如果初始的时候就已经连通了，那就不需要再操作了。复杂度$O(n \log V)$。
- 只需要操作1次，就枚举这个操作是什么，看操作完是否连通。操作有$2n$种，每次判断$O(n \log V)$，复杂度共$O(n^2 \log V)$。
- 需要两次操作，就按照证明里的步骤去搞。复杂度$O(n \log V)$。

总的时间复杂度为$O(n^2 \log V)$。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: E. ANDfinity
// Contest: Codeforces - Codeforces Round #798 (Div. 2)
// URL: https://codeforces.com/contest/1689/problem/E
// Memory Limit: 256 MB
// Time Limit: 4000 ms
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
  for (int i = 0; i < n; ++i)
    std::cin >> a[i];

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (a[i] == 0) {
      ++ans;
      a[i] = 1;
    }
  }

  auto connected = [&]() -> bool {
    std::vector<int> f(n + 32), sz(n + 32);
    std::function<int(int)> find = [&](int x) { return x == f[x] ? x : f[x] = find(f[x]); };
    auto merge = [&](int x, int y) {
      x = find(x), y = find(y);
      if (x == y)
        return;
      f[x] = y;
      sz[y] += sz[x];
    };
    for (int i = 0; i < n + 32; ++i) {
      f[i] = i;
      sz[i] = i < n ? 1 : 0;
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < 30; ++j) {
        if ((a[i] >> j) & 1) {
          merge(i, n + j);
        }
      }
    }
    return sz[find(0)] == n;
  };

  if (!connected()) {
    bool flag = false;
    for (int i = 0; i < n; ++i) {
      a[i] = a[i] - 1;
      if (connected()) {
        flag = true;
        ++ans;
        break;
      }
      a[i] = a[i] + 1;
    }
    if (!flag) {
      for (int i = 0; i < n; ++i) {
        a[i] = a[i] + 1;
        if (connected()) {
          flag = true;
          ++ans;
          break;
        }
        a[i] = a[i] - 1;
      }
    }

    if (flag) {
      ;
    } else {
      int max_low_bit = 0;
      for (int i = 0; i < n; ++i) {
        max_low_bit = std::max(max_low_bit, (a[i] & -a[i]));
      }

      for (int i = 0; i < n; ++i) {
        if ((a[i] & -a[i]) == max_low_bit) {
          --a[i];
          ++ans;
          break;
        }
      }
      for (int i = 0; i < n; ++i) {
        if ((a[i] & -a[i]) == max_low_bit) {
          ++a[i];
          ++ans;
          break;
        }
      }
    }
  }

  std::cout << ans << "\n";
  for (int i = 0; i < n; ++i)
    std::cout << a[i] << " \n"[i + 1 == n];
}
```

</details>