# AtCoder Beginner Contest 313

## [D - Odd or Even](https://atcoder.jp/contests/abc313/tasks/abc313_d)

通过共计 $k + 1$ 次询问可以确定 $a_i(i \le k)$ 和 $a_{k + 1}$ 的同异关系，具体操作如下：

- 查询序列 $x_i = i$，记结果为 $r_0$。
- 查询 $k$ 轮，第 $j$ 轮查的序列为 $x_j = k + 1, x_i = i(i \ne j)$ ，记结果为 $r_j$ 。

此时有 $a_i = a_{k + 1} \iff r_i = r_0, a_i \ne a_{k + 1} \iff r_i \ne r_0$ 。注意到 $k$ 必定为奇数，所以以下两种情况必定有且仅有一种成立：

- $a_i, i \le k$ 中有奇数个数和$a_{k + 1}$相等，偶数个不等。
- $a_i, i \le k$ 中有偶数个数和$a_{k + 1}$相等，奇数个不等。

不管是那种情况，都能结合 $r_0$ 推出 $a_{k + 1}$ 的值，进而得到 $a_i(i \le k)$ 的值。

然后对于 $a_i(i > k + 1)$ ，已经有 $k + 1$ 个知道值的数了，随便拿 $k - 1$ 个出来一起查就可以了。

<details>
<summary>核心代码</summary>

```cpp
// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, k;
  std::cin >> n >> k;

  std::vector<int> a(n, -1);

  std::vector<int> x(k);
  auto Q = [&]() {
    std::cout << "?";
    for (int v : x)
      std::cout << " " << v + 1;
    std::cout << std::endl;

    int r;
    std::cin >> r;
    return r;
  };

  for (int i = 0; i < k; ++i)
    x[i] = i;
  int r0 = Q();
  std::vector<int> same_as_ak;
  std::vector<int> diff_with_ak;
  for (int i = 0; i < k; ++i) {
    x[i] = k;

    int r = Q();
    if (r == r0) {
      same_as_ak.push_back(i);
    } else {
      diff_with_ak.push_back(i);
    }

    x[i] = i;
  }
  if (r0 == 1) {
    if (same_as_ak.size() % 2 == 1)
      a[k] = 1;
    else
      a[k] = 0;
  } else if (r0 == 0) {
    if (same_as_ak.size() % 2 == 0)
      a[k] = 1;
    else
      a[k] = 0;
  }
  for (int ind : same_as_ak)
    a[ind] = a[k];
  for (int ind : diff_with_ak)
    a[ind] = (a[k] ^ 1);

  for (int i = k + 1; i < n; ++i) {
    x[k - 1] = i;
    int r = Q();
    if (r == r0)
      a[i] = a[k - 1];
    else
      a[i] = (a[k - 1] ^ 1);
  }

  std::cout << "!";
  for (int i = 0; i < n; ++i)
    std::cout << " " << a[i];
  std::cout << std::endl;
}

```

</details>

## [E - Duplicate](https://atcoder.jp/contests/abc313/tasks/abc313_e)

易得当有连续两个大于一的位时无解。

现在考虑其中的某个 $a_ia_{i + 1}(a_i = 1， i + 1 \le N)$，每轮 $a_i$ 会多出 $a_{i+ 1} - 1$ 份，假设 $a_{i + 1}$ 经过 $x$ 轮后消失，那么 $a_i$ 一共会被复制 $x(a_{i+ 1} - 1)$ 份。然后根据式子从后往前递推即可。

<details>
<summary>核心代码</summary>

```cpp
// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/math/modular/mod_int.h"
using mint = math::ModInt998;

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::string s;
  std::cin >> s;

  std::vector<int> a(n);
  for (int i = 0; i < n; ++i)
    a[i] = s[i] - '0';

  for (int i = 1; i < n; ++i) {
    if (a[i - 1] > 1 && a[i] > 1) {
      std::cout << "-1\n";
      return;
    }
  }

  mint ans = 0;
  for (int i = n - 1; i >= 0; --i) {
    ans += ans * (a[i + 1] - 1) + 1;
  }
  ans -= 1;

  std::cout << ans.value() << "\n";
}

```

</details>

## [F - Flip Machines](https://atcoder.jp/contests/abc313/tasks/abc313_f)

首先，对于 $X_i = Y_i$ 的机器进行特判，如果朝下的数比朝上的大就使用，反之就不用。此后只需要讨论 $X_i \ne Y_i$ 的情况了。

然后，对于任意的 $S$ ，假设其中有 $k(k > 0)$ 个位置 $p_i(1 \le i \le k)$ 满足 $X_{p_i} = j $ 或者 $Y_{P_i} = j$ ， 那么第 $j$ 张牌有 $\frac{1}{2}$ 的概率正面朝上，有 $\frac{1}{2}$ 的概率反面朝上。

<details>
<summary>证明</summary>

假设其中有 $x$ 台机器选中了下标 $j$ ，那么有 $k - x$ 张牌选中了其他下标，当 $x$ 为奇数时第 $j$ 张牌反面朝上，当 $x$ 为偶数时第 $j$ 张牌正面朝上。

正面朝上的概率
$$
P = \sum_{0 \le x \le k, x \text{ is even}} \binom{k}{x} (\frac{1}{2})^k
$$

反面朝上的概率
$$
Q = \sum_{0 \le x \le k, x \text{ is odd}} \binom{k}{x} (\frac{1}{2})^k
$$

然后根据二项式定理 $(x + 1)^k = \sum_{i = 0}^{k} \binom{k}{i} x^i$，带入 $x = -1$ 可以得到
$$
\sum_{0 \le x \le k, x \text{ is even}} \binom{k}{x} = \sum_{0 \le x \le k, x \text{ is odd}} \binom{k}{x}
$$

然后就有 $P = Q = \frac{1}{2}$ 。

</details>

现在，确定了 $S$ 之后，每个位置朝上那一面的数字的期望就能确定了：

- 如果存在 $i \in S, X_i = j$ 或者 $Y_i = j$ ，那么第 $j$ 张牌朝上那一面的数字的期望为 $\frac{A_i + B_i}{2}$ 。
- 否则第 $j$ 张牌朝上那一面的数字的期望为 $A_i$ 。

根据正反面数的大小关系可以将剩余的牌分成两类 $P$ 和 $Q$，前者正面的数大于反面，后者则相反。然后就有

- 如果牌 $X_i$ 和牌 $Y_i$ 都属于 $P$，那么该机器必不选。
- 如果牌 $X_i$ 和牌 $Y_i$ 都属于 $Q$，那么该机器必选。

此后只需要考虑牌 $X_i$ 和牌 $Y_i$ 属于不同类的机器。

现在还有一个关键的观察就是：将每张牌看成图上的点，将每台机器看成一条无向边，那么当选了 $P$ 中的某张牌 $j$ 时，所有 $Q$ 中和 $j$ 邻接的牌也都要选。

### 官方题解的做法

- 直接暴力枚举 $P$ 的子集就能得到一个 $O(2^{|P|})$ 复杂度的解法，但是 $|P|$ 最大能到 $40$ ，算法还不够优秀。
- 记 $dp_{i, j}$ 表示考虑 $P$ 中前 $i$ 张牌，然后 $j$ 是此时用了的 $Q$ 的子集，的最大贡献，然后跑个 DP 也能算出答案，复杂度为 $O(2^{|Q|})$。

然后用 meet in the middle 的思想，$|P|$ 和 $|Q|$ 至少有一个小于等于 $20$，根据这个选择不同算法就能得到足够优秀的解法了。

<details>
<summary><del>丑陋的</del>核心代码</summary>

```cpp
// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i] >> b[i];

  std::vector<int> x, y;
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;

    if (u == v && a[u] < b[u])
      std::swap(a[u], b[u]);

    if (u != v) {
      x.push_back(u);
      y.push_back(v);
    }
  }
  m = x.size();

  i64 maskP = 0, maskQ = 0;
  std::vector<int> P, Q;
  for (int i = 0; i < n; ++i) {
    if (a[i] >= b[i]) {
      maskP |= (i64(1) << i);
      P.push_back(i);
    } else {
      maskQ |= (i64(1) << i);
      Q.push_back(i);
    }
  }

  i64 must_chosen_Q = 0;
  std::vector<i64> adj(n);
  for (int i = 0; i < m; ++i) {
    bool fx = (a[x[i]] >= b[x[i]]);
    bool fy = (a[y[i]] >= b[y[i]]);
    if (fx == fy) {
      if (fx == false) {
        must_chosen_Q |= (i64(1) << x[i]);
        must_chosen_Q |= (i64(1) << y[i]);
      }
    } else {
      adj[x[i]] |= (i64(1) << y[i]);
      adj[y[i]] |= (i64(1) << x[i]);
    }
  }

  int ans = 0;
  if (P.size() < Q.size()) {
    for (int chosen_P = 0; chosen_P < (1 << P.size()); ++chosen_P) {
      int temp = 0;
      i64 chosen_Q = must_chosen_Q;
      for (int i = 0; i < P.size(); ++i) {
        if (chosen_P >> i & 1) {
          temp += a[P[i]] + b[P[i]];
          chosen_Q |= adj[P[i]];
        } else {
          temp += 2 * a[P[i]];
        }
      }
      for (int i : Q) {
        if (chosen_Q >> i & 1) {
          temp += a[i] + b[i];
        } else {
          temp += 2 * a[i];
        }
      }
      ans = std::max(ans, temp);
    }
  } else {
    // to reduce memory usage, we need some discretization.
    std::vector<int> id(n);
    for (int i = 0; i < Q.size(); ++i)
      id[Q[i]] = i;
    std::vector<i64> adjQ(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (adj[i] >> j & 1) {
          if (maskQ >> j & 1)
            adjQ[i] |= (i64(1) << id[j]);
        }
      }
    }
    i64 must_chosen_Q1 = 0;
    for (int i = 0; i < n; ++i)
      if (must_chosen_Q >> i & 1)
        must_chosen_Q1 |= (i64(1) << id[i]);

    std::vector<std::vector<int>> dp(P.size() + 1,
                                     std::vector<int>(1 << Q.size(), -1e9));
    dp[0][0] = 0;
    for (int i = 0; i < P.size(); ++i) {
      for (int j = 0; j < (1 << Q.size()); ++j) {
        dp[i + 1][j] = std::max(dp[i + 1][j], dp[i][j] + 2 * a[P[i]]);
        dp[i + 1][j | adjQ[P[i]]] =
            std::max(dp[i + 1][j | adjQ[P[i]]], dp[i][j] + a[P[i]] + b[P[i]]);
      }
    }
    for (int i = 0; i < (1 << Q.size()); ++i) {
      int temp = dp[P.size()][i];
      for (int j = 0; j < Q.size(); ++j) {
        if ((i | must_chosen_Q1) >> j & 1) {
          temp += a[Q[j]] + b[Q[j]];
        } else {
          temp += 2 * a[Q[j]];
        }
      }
      ans = std::max(ans, temp);
    }
  }

  std::cout << std::fixed << std::setprecision(12) << ans / 2.0 << "\n";
}

```

</details>

### jiangly的做法

暴力枚举，因为这样写 $P$ 和 $Q$ 会且只会枚举满一个，所以复杂度为 $O(\min \{2^{|P|}, 2^{|Q|}\})$ 。

<details>
<summary>核心代码</summary>

```cpp
// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i] >> b[i];

  std::vector<int> x, y;
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;

    if (u == v && a[u] < b[u])
      std::swap(a[u], b[u]);

    if (u != v) {
      x.push_back(u);
      y.push_back(v);
    }
  }
  m = x.size();

  i64 maskP = 0, maskQ = 0;
  std::vector<int> P, Q;
  for (int i = 0; i < n; ++i) {
    if (a[i] >= b[i]) {
      maskP |= (i64(1) << i);
      P.push_back(i);
    } else {
      maskQ |= (i64(1) << i);
      Q.push_back(i);
    }
  }

  i64 must_chosen_Q = 0;
  std::vector<i64> adj(n);
  for (int i = 0; i < m; ++i) {
    bool fx = (a[x[i]] >= b[x[i]]);
    bool fy = (a[y[i]] >= b[y[i]]);
    if (fx == fy) {
      if (fx == false) {
        must_chosen_Q |= (i64(1) << x[i]);
        must_chosen_Q |= (i64(1) << y[i]);
      }
    } else {
      adj[x[i]] |= (i64(1) << y[i]);
      adj[y[i]] |= (i64(1) << x[i]);
    }
  }

  int ans = 0;
  std::function<void(int, i64, int)> dfs = [&](int x, i64 mask, int score) {
    if (x == P.size()) {
      for (int i : Q) {
        if (mask >> i & 1) {
          score += a[i] + b[i];
        } else {
          score += a[i] + a[i];
        }
      }

      ans = std::max(ans, score);
      return;
    }

    dfs(x + 1, mask, score + 2 * a[P[x]]);
    i64 new_mask = (mask | (adj[P[x]] & maskQ));
    if (new_mask != mask) {
      dfs(x + 1, new_mask, score + a[P[x]] + b[P[x]]);
    }
  };
  dfs(0, must_chosen_Q, 0);

  std::cout << std::fixed << std::setprecision(12) << ans / 2.0 << "\n";
}

```

</details>

## [G - Redistribution of Piles](https://atcoder.jp/contests/abc313/tasks/abc313_g)

易得对数组排序并不会影响结果，不妨先将数组排序。

首先，仅使用操作 1 可以得到 $\max_i a_i + 1$ 种序列 $b$ 。

然后考虑使用操作 2 得到剩余的其他情况。

当操作完操作 1 且此时所有位置都非零，这种情况下操作 2 其实就是操作 1 的逆，并不能得到新的 $b$ 。所以在 $a_1$ 不断减到 $0$ 的这段区间并不能靠操作 2 得到新的 $b$ 。

现在考虑 $a_1$ 刚好减到 $0$ 之后，此时数值大概长这样 $0, a_2, a_3, \dots, a_N$，记此时袋子里有 $s$ 颗石头。此时经过一次操作 1 之后，就可以通过操作 2 得到新的 $b$ 了，此次可以新增 $\lfloor \frac{s + n - 1}{n} \rfloor$ 个 $b$ 。如果此时 $a_2 > 0$ ，那么再经过一次操作 1 ，然后就又能通过操作 2 得到新的 $b$ 了。总结一下，在 $a_2$ 不断减到 $0$ 的过程中，一共新增了 $\sum_{i = 0}^{a_2 - 1} \lfloor \frac{(n - 1)i + s + n - 1}{n} \rfloor$ 个不同的 $b$ 。

以此类推到 $a_i(2 \le i \le N)$ 就能得到答案，但是朴素的算法时间复杂度为 $O(\max a)$ ，`TLE` 预定。

其实 $\sum_{i = 0}^{a_x - 1} \lfloor \frac{(n - x + 1)i + s + n - x + 1}{n} \rfloor$ 这个式子看成 $\sum_{i = 0}^{n} \lfloor \frac{ai + b}{c} \rfloor$ 的形式，而 $\sum_{i = 0}^{n} \lfloor \frac{ai + b}{c} \rfloor$ 的结果可以通过类欧几里得算法 $O(\log a)$ 得到，具体参见[OI Wiki](https://oi-wiki.org/math/number-theory/euclidean/) 或者搜 `floor_sum`。

现在的复杂度是 $O(M\log a)$，足够优秀了。

<details>
<summary>核心代码</summary>

```cpp
// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/math/misc.h"
#include "hira/math/modular/mod_int.h"

using mint = math::ModInt998;

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<i64> a(n);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i];
  std::sort(a.begin(), a.end());

  mint ans = a.back() + 1;
  i64 s = 0, d = 0;
  for (int i = 0; i < n; ++i) {
    a[i] -= d;
    if (a[i] == 0)
      continue;

    if (i > 0)
      ans += math::floor_sum(n - i, s + n - i, n, a[i] - 1);
    s += a[i] * (n - i);

    d += a[i];
  }

  std::cout << ans.value() << std::endl;
}

```

</details>

## [Ex - Group Photo](https://atcoder.jp/contests/abc313/tasks/abc313_h)

To be solved.

<!-- <details>
<summary>核心代码</summary>

```cpp
```

</details> -->
