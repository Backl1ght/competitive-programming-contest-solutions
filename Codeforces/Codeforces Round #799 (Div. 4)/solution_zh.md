# Codeforces Round #799 (Div. 4)

前面的题感觉没啥好写的，咕咕咕

## [H. Gambling](https://codeforces.com/contest/1692/problem/H)

<details>
<summary>题意</summary>

给定一个长度为$n$的数组$x$，问使得最终钱数最大的$a, l, r$。

收益的计算方式为，初始有$1$的钱，从$x_l$到$x_r$，遇到一个$x_i = a$钱就乘二，反之除2。这里的除法不取整，就是说会搞出$\frac{1}{2}$这种数字。

其中$1 \le n \le 2 \times {10}^5, 1 \le x_i \le {10}^9$。

</details>

<details>
<summary>思路</summary>

转化一下就是最终的钱等于$2^{\sum_{i = l}^{r} [x_i = a] - \sum_{i = l}^{r} [x_i \ne a]}$。然后为了方便计算比较指数的大小就可以了。

这个问题可以转化成最大子区间和的问题，然后就是DP了。

具体的转化为：对于某个值$a$，构造一个权值数组$w$，如果$x_i = a$就令$w_i = 1$，反之令$w_i = -1$，那么$w$的最大子区间和就是答案。

不加任何优化需要$O(n^2)$次转移必TLE，需要加点优化。

观察可得最终答案区间的两端的值一定等于$a$，因为把两端不等于$a$的值去掉收益为正。由此第$i$个位置只需要考虑$a = x_i$的情况。

现在就只需要$O(n)$次转移了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: H. Gambling
// Contest: Codeforces - Codeforces Round #799 (Div. 4)
// URL: https://codeforces.com/contest/1692/problem/H
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

  std::vector<int> x(n);
  for (int i = 0; i < n; ++i)
    std::cin >> x[i];

  std::map<int, std::array<int, 3>> dp;
  int max_gain = 0, a, l, r;
  for (int i = 0; i < n; ++i) {
    int v = x[i];
    if (!dp.count(v)) {
      dp[v] = {1, i, i};
    } else {
      auto [gain, l, r] = dp[v];
      int cost = i - r - 1;
      if (gain >= cost) {
        dp[v] = {gain - cost + 1, l, i};
      } else {
        dp[v] = {1, i, i};
      }
    }

    if (dp[v][0] > max_gain) {
      max_gain = dp[v][0];
      a = v;
      l = dp[v][1];
      r = dp[v][2];
    }
  }

  std::cout << a << " " << l + 1 << " " << r + 1 << "\n";
}

```

</details>