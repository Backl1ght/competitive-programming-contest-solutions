# Codeforces Round #821 (Div. 2)

## [A. Consecutive Sum](https://codeforces.com/contest/1733/problem/A)

根据下标模 $k$ 的结果把数组分成 $k$ 类，连续的 $k$ 个数字必定种类互不相同，然后就把每一类最大的那个数求出来然后累加即可。

## [B. Rule of League](https://codeforces.com/contest/1733/problem/B)

假设 $x < y$。

假设有 $a$ 个人赢 $x$ 场， $b$ 个人赢 $y$ 场，那么有 $ax + by = n - 1, a + b = n$。

如果 $x > 0$，有 $ax + by >= n$ ，无解。

如果 $y = 0$，有 $ax + by = 0$，无解。

此时$x = 0, y > 0$，$by = n - 1$，有解当且仅当 $y \mid (n - 1)$。

输出方案的话就是第一场随便选个选手赢，这个选手会连赢 $y$ 场，然后在第 $y + 1$ 场输掉，然后第 $y + 1$ 场的胜者又连赢 $y$ 场，以次类推。

## [C. Parity Shuffle Sorting](https://codeforces.com/contest/1733/problem/C)

考虑让 $a_1 = a_2 = \dots = a_n$。

首先操作首元素和尾元素，现在首尾相等。

然后，对于中间的每一个元素，都可以选择跟首元素或者尾元素操作，从而变成首元素或者尾元素。

## [D1. Zero-One (Easy Version)](https://codeforces.com/contest/1733/problem/D1)

首先，令$c_i = a_i \operatorname{xor} b_i$，那么问题转化为通过这些操作使得 $c_i$ 变成全 `0` 的最小代价。

每次操作会让 $c_i$ 中 `1` 的个数减 2 ，不变或者加 2 。所以当 $c_i$ 中有奇数个 `1` 时无解。

现在 $c_i$ 中有偶数个 `1` 。

本题中 $x \ge y$，那么优先用 $y$ 操作。

假设只有两个 `1` 且两者相邻，只有这个时候才可能使用 $x$ 。可以考虑使用一次 $x$，或者使用两次 $y$，取二者较小值。

否则无脑用 $y$。

## [D2. Zero-One (Hard Version)](https://codeforces.com/contest/1733/problem/D2)

现在只需要考虑 $x < y$ 的情况，这个时候被零或多个 `0` 分隔的两个 `1` 使用多次 $x$ 可能会比使用一次 $y$ 更优。 

考虑使用DP解决，默认先无脑用 $y$ ，然后看借助 $x$ 替换掉 $y$ 能省多少钱。$dp_{i}$ 表示前 $i$ 个元素通过把 $y$ 替换成 $x$ 最多能省多少钱。

假设第$i$ 个 `1` 在 $p_i$ 上。对于第 $i$ 个 $1$ ，它可以通过 $p_i - p_{i - 1}$ 次 $x$ 把这两个 `1` 变成 `0`，相比一次 $y$ 节省了 $y - x(p_i - p_{i-1})$，则有 $dp_i = \max(dp_{i - 1}, dp_{i - 2} + y - x(p_i - p_{i-1}))$，其中前者表示不替换，后者表示使用替换。

最终答案为 $\frac{|p|}{2} y - dp_{|p|}$。

<details>
<summary>AC代码</summary>

```cpp
// Problem: D2. Zero-One (Hard Version)
// Contest: Codeforces - Codeforces Round #821 (Div. 2)
// URL: https://codeforces.com/contest/1733/problem/D2
// Memory Limit: 512 MB
// Time Limit: 3000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#define ASSERT(x) ;
#define serialize() std::string("")
#endif

using i64 = int64_t;
using u64 = uint64_t;

void Initialize();
void SolveCase(int Case);

int main(int argc, char* argv[]) {
  CPPIO;
  int T = 1;
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    SolveCase(t);
  }
  return 0;
}

void Initialize() {}

void SolveCase(int Case) {
  int n, x, y;
  std::cin >> n >> x >> y;

  std::string a, b;
  std::cin >> a;
  std::cin >> b;

  std::vector<int> p;
  for (int i = 0; i < n; ++i) {
    if (a[i] != b[i]) {
      p.push_back(i);
    }
  }

  if (p.size() % 2 == 1) {
    std::cout << "-1\n";
    return;
  }

  if (x >= y) {
    if (p.size() == 2 && p[0] + 1 == p[1]) {
      std::cout << std::min(x, 2 * y) << "\n";
    } else {
      i64 ans = i64(1) * y * (p.size() / 2);
      std::cout << ans << "\n";
    }
    return;
  }

  // x < y
  {
    std::vector<i64> dp(p.size() + 1);
    dp[0] = 0;
    for (int i = 1; i <= p.size(); ++i) {
      dp[i] = dp[i - 1];
      if (i >= 2) {
        i64 delta = y - i64(1) * (p[i - 1] - p[i - 2]) * x;
        dp[i] = std::max(dp[i], dp[i - 2] + delta);
      }
    }
    std::cout << i64(1) * y * (p.size() / 2) - dp[p.size()] << "\n";
  }
}

```

</details>

## [E. Conveyor](https://codeforces.com/contest/1733/problem/E)

> **观察1**: 把矩阵按 $x+y$ 的值划分为 $240$ 类，每一类都构成一条对角线。则每个时刻每一条对角线上都至多只有一个球，且这个球在下一秒会移动到下一条对角线上。

从$(0, 0)$ 移动到询问的点 $(x, y)$ 需要 $x+y$ 秒，所以如果 $t < x + y$ 则不可能有球移动到 $(x, y)$ 所在的对角线上，也就不可能有解。

$t$ 时刻位于第 $x+y$ 条对角线上的球，在 $t - x - y$ 时刻从 $(0, 0)$ 出发。此前一共有 $t - x - y$ 个球经过 $(0, 0)$。在这个时刻之后从 $(0, 0)$ 出发的小球不会影响答案。

> **观察2**：如果一共有 $a$ 个小球经过 $(i, j)$，那么其中有 $\lceil \frac{a}{2} \rceil$ 个会经过 $(i, j + 1)$， $\lfloor \frac{a}{2} \rfloor$ 个会经过 $(i + 1, j)$。

这样就可以求出每个位置，前 $t - x - y$ 秒都有多少个球经过，记为 $f(i, j)$。

现在开始模拟 $t - x - y$ 时刻从 $(0, 0)$ 出发的小球的运动轨迹。根据题意，如果 $f(i, j)$ 是奇数，那么小球会移动到 $(i + 1, j)$；如果 $f(i, j)$ 为偶数，则小球会移动到 $(i, j + 1)$。

由此再模拟 $x + y$ 步，就能得到该小球最终的所在位置。判断是否和 $(x, y)$ 一致即可。

<details>
<summary>AC代码</summary>

```cpp
// Problem: E. Conveyor
// Contest: Codeforces - Codeforces Round #821 (Div. 2)
// URL: https://codeforces.com/contest/1733/problem/E
// Memory Limit: 256 MB
// Time Limit: 3000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#define ASSERT(x) ;
#define serialize() std::string("")
#endif

using i64 = int64_t;
using u64 = uint64_t;

void Initialize();
void SolveCase(int Case);

int main(int argc, char* argv[]) {
  CPPIO;
  int T = 1;
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    SolveCase(t);
  }
  return 0;
}

void Initialize() {}

void SolveCase(int Case) {
  i64 t;
  int x, y;
  std::cin >> t >> x >> y;

  if (t < x + y) {
    std::cout << "NO\n";
    return;
  }

  std::vector<std::vector<i64>> f(120, std::vector<i64>(120, 0));
  f[0][0] = t - x - y;
  for (int i = 0; i < 120; ++i) {
    for (int j = 0; j < 120; ++j) {
      if (j + 1 < 120)
        f[i][j + 1] += (f[i][j] + 1) / 2;
      if (i + 1 < 120)
        f[i + 1][j] += f[i][j] / 2;
    }
  }

  int X = 0, Y = 0;
  for (int i = 0; i < x + y; ++i) {
    if (X == 120 || Y == 120) {
      std::cout << "NO\n";
      return;
    }
    if (f[X][Y] & 1)
      ++X;
    else
      ++Y;
  }

  std::cout << ((X == x && Y == y) ? "YES" : "NO") << "\n";
}

```

</details>