# AtCoder Beginner Contest 314

## [D - LOWER](https://atcoder.jp/contests/abc314/tasks/abc314_d)

拿一个数组记录一下操作 1 的时间戳，然后操作 2 和操作 3 最后只有一个会生效，记录左后一个的时间戳和类型，记为 $x$ 和 $y$。

然后扫一遍每个位置，如果对应操作 1 的时间戳早于 $x$，那么就根据 $y$ 修改大小写。

<details>
<summary>核心代码</summary>

```cpp
// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::string s;
  std::cin >> s;

  std::vector<int> ts(n, -1);

  int m;
  std::cin >> m;
  int f = 0;
  for (int i = 1; i <= m; ++i) {
    int t, x;
    char c;
    std::cin >> t >> x >> c;
    if (t == 1) {
      --x;
      s[x] = c;
      ts[x] = i;
    } else if (t == 2) {
      f = i;
    } else if (t == 3) {
      f = -i;
    }
  }

  for (int i = 0; i < n; ++i) {
    if (std::abs(f) > ts[i]) {
      if (f < 0)
        s[i] = std::toupper(s[i]);
      if (f > 0)
        s[i] = std::tolower(s[i]);
    }
  }

  std::cout << s << "\n";
}

```

</details>

## [E - Roulettes](https://atcoder.jp/contests/abc314/tasks/abc314_e)

记 $e_i$ 表示已经有 $i$ 分了，达到至少 $M$ 分需要的钱的期望的最小值。

此时，如果选择玩轮盘 $j$ ，那么有

$$
E(i, j) = C_j + \frac{1}{P_j} \sum_{k = 1}^{P_j} e_{i + S_{j, k}}
$$

其中 $E(i, j)$ 表示有 $i$ 分，然后选择完轮盘 $j$，达到至少 $M$ 分需要的钱的期望。易得

$$
e_i = \min_{j = 1}^{N} E(i, j)
$$

$e_0$ 就是答案，$e_{i, i \ge M} = 0$。从后往前递推就能算出答案。

现在其实还有点问题就是 $S_{j, k}$ 可能为 $0$。但是如果摇到 $0$ 的话，后续的策略还是不会变，因为当前积分不变，最优策略也不变。所以这里可以做一个转化，假设 $S_{j, k}$ 中有 $Z_j$ 个零，每次有 $\frac{P_j - Z_j}{P_j}$ 的概率摇到非零，不断使用该轮盘首次摇到非零的期望轮数为 $\frac{P_j}{P_j - Z_j}$。然后该轮盘就可以等价为将所有零去掉，然后代价为 $C_j \frac{P_j}{P_j - Z_j}$ 。

<details>
<summary>核心代码</summary>

```cpp
// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<double> c(n);
  std::vector<std::vector<int>> s(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> c[i];

    int p;
    std::cin >> p;

    for (int j = 0; j < p; ++j) {
      int x;
      std::cin >> x;
      if (x)
        s[i].push_back(x);
    }

    c[i] *= 1.0 * p / s[i].size();
  }

  std::vector<double> e(m, 1e18);
  for (int i = m - 1; i >= 0; --i) {
    double mn = 1e18;
    for (int j = 0; j < n; ++j) {
      double cost = c[j];
      for (int k = 0; k < s[j].size(); ++k) {
        if (i + s[j][k] < m)
          cost += 1.0 * e[i + s[j][k]] / s[j].size();
      }
      mn = std::min(mn, cost);
    }
    e[i] = mn;
  }

  std::cout << std::fixed << std::setprecision(12) << e[0] << "\n";
}

```

</details>

## [F - A Certain Game](https://atcoder.jp/contests/abc314/tasks/abc314_f)

就把对应的二叉树建出来，树上的边带有一个权值表示对应儿子胜利的概率。

每个选手的答案就是把从他对应的叶子到根这一路径上的概率加起来。借助路径压缩（或者说并查集）就能得到线性复杂度的解法。

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

  std::vector<int> sz(2 * n + 1);
  std::vector<int> l(2 * n + 1), r(2 * n + 1);
  std::vector<int> fa(2 * n + 1);
  std::function<int(int)> leader = [&](int x) {
    if (fa[x] == x)
      return x;
    fa[x] = leader(fa[x]);
    return fa[x];
  };
  for (int i = 1; i <= n; ++i) {
    sz[i] = 1;
    fa[i] = i;
  }
  int tot = n;
  for (int i = 0; i < n - 1; ++i) {
    int p, q;
    std::cin >> p >> q;

    int u = leader(p);
    int v = leader(q);

    int rt = ++tot;
    sz[rt] = sz[u] + sz[v];
    l[rt] = u;
    r[rt] = v;
    fa[u] = rt;
    fa[v] = rt;
    fa[rt] = rt;

    logd(p, q, sz[rt], sz[u], sz[v]);
  }

  std::vector<mint> e(2 * n + 1, mint(0));
  for (int i = tot; i > n; --i) {
    mint d = mint(sz[i]).inv();
    e[l[i]] += e[i] + d * sz[l[i]];
    e[r[i]] += e[i] + d * sz[r[i]];
  }

  for (int i = 1; i <= n; ++i)
    std::cout << e[i].value() << " \n"[i == n];
}

```

</details>

## [G - Amulets](https://atcoder.jp/contests/abc314/tasks/abc314_g)

To be solved.

<!-- <details>
<summary>核心代码</summary>

```cpp
```

</details> -->

## [Ex - Disk and Segments](https://atcoder.jp/contests/abc314/tasks/abc314_h)

To be solved.

<!-- <details>
<summary>核心代码</summary>

```cpp
```

</details> -->