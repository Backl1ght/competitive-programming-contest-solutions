# AtCoder Beginner Contest 312

## [D - Count Bracket Sequences](https://atcoder.jp/contests/abc312/tasks/abc312_d)

记 `(` 为 $+1$ ，`)` 为 $-1$ ，那么括号序列合法等价于没有前缀和小于 $0$ 且整个序列之和为 $0$ 。

然后就是简单 DP 了，记 $dp_{i, j}$ 表示前 $i$ 个符号，然后前缀和为 $j$ 的方案数，中途如果前缀和小于 $0$ 就不转移。

$dp_{N, 0}$ 即为答案，然后可以滚动数组优化空间。

<details>
<summary>核心代码</summary>

```cpp
// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/math/modular/mod_int.h"

using mint = math::ModInt998;

void Initialize() {}

void SolveCase(int Case) {
  std::string s;
  std::cin >> s;
  int n = s.size();

  std::vector<mint> dp(n, mint(0));
  dp[0] = 1;
  for (int i = 0; i < n; ++i) {
    std::vector<mint> ndp(n, mint(0));
    for (int j = 0; j < n; ++j) {
      if (s[i] == '(') {
        if (j + 1 < n)
          ndp[j + 1] += dp[j];
      } else if (s[i] == ')') {
        if (j)
          ndp[j - 1] += dp[j];
      } else {
        if (j + 1 < n)
          ndp[j + 1] += dp[j];
        if (j)
          ndp[j - 1] += dp[j];
      }
    }
    dp = std::move(ndp);
  }
  std::cout << dp[0].value() << "\n";
}

```

</details>

## [E - Tangency of Cuboids](https://atcoder.jp/contests/abc312/tasks/abc312_e)

$N$ 比较大但坐标轴范围都很小，考虑一个 $O(XYZ)$ 的枚举方案，就是把三维空间中每个单位方块属于哪一个长方体标出来（根据题目可得每个单位方块至多属于一个长方体），然后对于每个单位方块枚举与其共用某个面的方块，看这两个方块是否属于不同长方体，如果是那就说明找到了两个表面有交集的长方体。

<details>
<summary>核心代码</summary>

```cpp
// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/std_extension/n_vector.h"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  auto a = stdext::n_vector<int>(101, 101, 101, -1);

  for (int i = 0; i < n; ++i) {
    int x1, y1, z1;
    std::cin >> x1 >> y1 >> z1;

    int x2, y2, z2;
    std::cin >> x2 >> y2 >> z2;

    for (int x = x1; x <= x2 - 1; ++x) {
      for (int y = y1; y <= y2 - 1; ++y) {
        for (int z = z1; z <= z2 - 1; ++z) {
          a[x][y][z] = i;
        }
      }
    }
  }

  std::vector<std::set<int>> s(n);
  for (int x = 0; x <= 100; ++x) {
    for (int y = 0; y <= 100; ++y) {
      for (int z = 0; z <= 100; ++z) {
        if (a[x][y][z] == -1)
          continue;

        for (int dx : {-1, 0, 1}) {
          for (int dy : {-1, 0, 1}) {
            for (int dz : {-1, 0, 1}) {
              int c = 0;
              if (dx != 0)
                ++c;
              if (dy != 0)
                ++c;
              if (dz != 0)
                ++c;
              if (c != 1)
                continue;

              int nx = x + dx;
              int ny = y + dy;
              int nz = z + dz;
              if (0 <= nx && nx <= 100 && 0 <= ny && ny <= 100 && 0 <= nz &&
                  nz <= 100 && a[nx][ny][nz] != -1 &&
                  a[x][y][z] != a[nx][ny][nz]) {
                s[a[x][y][z]].insert(a[nx][ny][nz]);
              }
            }
          }
        }
      }
    }
  }

  for (int i = 0; i < n; ++i)
    std::cout << s[i].size() << "\n";
}

```

</details>

## [F - Cans and Openers](https://atcoder.jp/contests/abc312/tasks/abc312_f)

为了方便描述，记第一种物体为可乐，第二种物体为啤酒，第三种物体为开瓶器。

每种物体都是 $X_i$ 越大越好。将物理分类，依次记为数组 $a, b, c$ 。

然后考虑枚举拿多少个开瓶器，假设拿了 $k$ 个，那么就可以拿 $M - k$ 个可乐或者啤酒，然后这些可乐和啤酒都是 $X_i$ 越大越好，所以一定会拿其中前 $M - k$ 大的。这个其实可以用一个小顶堆维护。

更加具体地说，假设当前拿了 $k$ 个开瓶器，在此基础上继续多拿一个开瓶器。那么在之前的基础上，可以拿的可乐和啤酒的数量要减一，可能会需要把对顶弹出。然后，现在第 $\sum_{i = 1}^{k} c_i + 1$ 到第 $\sum_{i = 1}^{k + 1}$ 瓶啤酒就可以拿来考虑了，这些啤酒可能可以作为更优的选择替换掉堆中的可乐。

<details>
<summary>核心代码</summary>

```cpp
// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/std_extension/heap.h"

void Initialize() {}

void SolveCase(int Case) {
  int N, M;
  std::cin >> N >> M;

  std::vector<int> a, b, c;
  for (int i = 0; i < N; ++i) {
    int t, x;
    std::cin >> t >> x;
    if (t == 0)
      a.push_back(x);
    else if (t == 1)
      b.push_back(x);
    else
      c.push_back(x);
  }
  std::sort(b.begin(), b.end(), std::greater<>());
  std::sort(c.begin(), c.end(), std::greater<>());
  int pb = 0;

  i64 sum = 0, ans = 0;
  stdext::min_heap<int> heap;
  for (int v : a) {
    if (heap.size() < M) {
      sum += v;
      heap.push(v);
    } else {
      if (!heap.empty() && heap.top() < v) {
        sum -= heap.top();
        heap.pop();

        sum += v;
        heap.push(v);
      }
    }
  }
  ans = std::max(ans, sum);
  logd(ans, sum, heap);

  for (int i = 0; i < c.size(); ++i) {
    --M;
    if (M == 0)
      break;

    if (heap.size() > M) {
      sum -= heap.top();
      heap.pop();
    }

    int end = pb + c[i];
    for (; pb < end && pb < b.size(); ++pb) {
      int v = b[pb];

      if (heap.size() < M) {
        sum += v;
        heap.push(v);
      } else {
        if (!heap.empty() && heap.top() < v) {
          sum -= heap.top();
          heap.pop();

          sum += v;
          heap.push(v);
        }
      }
    }

    ans = std::max(ans, sum);
    logd(ans, sum, heap);
  }

  std::cout << ans << "\n";
}

```

</details>

## [G - Avoid Straight Line](https://atcoder.jp/contests/abc312/tasks/abc312_g)

树上 DP 。所有三元组的数量为 $\binom{n}{3}$ ，然后再求出所有可以由一条简单路径包括的三元组数量，前者减去后者即为答案。

假设 $sz_u$ 为子树 $u$ 的大小， $b_u$ 表示子树 $u$ 中满足 $x$ 是 $y$ 的祖先的二元组 $(x, y)$ 的数量。

那么对于子树 $u$ 和 $u$ 的某个儿子 $v$ ，有以下 4 种方案构造可以由一条简单路径包括的三元组：

- 在子树 $v$ 中选择一个点，拼上 $u$ 的其他子树的 $(x, y)$ 。
- 在 $u$ 的其他子树中选择一个点，拼上 $v$ 的 $(x, y)$ 。
- 选择 $u$，以及子树 $v$ 中的 $(x, y)$ 。
- 选择 $u$，子树 $u$ 种的一个点，子树 $v$ 中的一个点 。

然后有
$$
b_u = sz_u - 1 + \sum_{v \text{ is son of u}} b_v
$$

转移的时候注意别算重复了就可以。

<details>
<summary>核心代码</summary>

```cpp
// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
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

  if (n < 3) {
    std::cout << "0\n";
    return;
  }

  i64 ans = i64(1) * n * (n - 1) / 2 * (n - 2) / 3;

  std::vector<int> sz(n);
  std::vector<i64> b(n);
  std::function<void(int, int)> dfs = [&](int u, int fa) {
    sz[u] = 1;
    for (int v : g[u]) {
      if (v == fa)
        continue;
      dfs(v, u);

      ans -= i64(1) * (sz[u] - 1) * sz[v];
      ans -= b[u] * sz[v];
      ans -= b[v] * (sz[u] - 1);
      ans -= b[v];

      sz[u] += sz[v];
      b[u] += b[v];
    }

    b[u] += sz[u] - 1;
  };
  dfs(0, 0);
  logd(b);
  logd(sz);

  std::cout << ans << "\n";
}

```

</details>

## [Ex - snukesnuke](https://atcoder.jp/contests/abc312/tasks/abc312_h)

To be solved.

<!-- <details>
<summary>核心代码</summary>

```cpp
```

</details> -->