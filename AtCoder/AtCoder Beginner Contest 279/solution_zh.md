# AtCoder Beginner Contest 279

咕咕咕。

## [D - Freefall](https://atcoder.jp/contests/abc279/tasks/abc279_d)

三分求极值，注意下标得是整数，所以最后再搜索三分结果附近的整数。

直接求导应该也可以。

<details>
<summary>AC代码</summary>

```cpp
// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  double a, b;
  std::cin >> a >> b;

  auto f = [&](double x) { return x * b + a / std::sqrt(1 + x); };

  const double eps = 1e-8;
  double l = 0, r = a, ml, mr, fl, fr;
  int limit = 128;
  while (r - l > eps) {
    logd(std::to_string(l), std::to_string(r), std::to_string(r - l));
    ml = l + (r - l) / 3;
    mr = r - (r - l) / 3;

    fl = f(ml);
    fr = f(mr);

    if (fl > fr)
      l = ml;
    else
      r = mr;

    --limit;
    if (limit == 0)
      break;
  }

  double ans = f(0);
  for (int i = -32; i <= 32; ++i) {
    i64 x = l + i;
    if (x >= 0)
      ans = std::min(ans, f(x));
  }

  std::cout << std::fixed << std::setprecision(10) << ans << "\n";
}


```

</details>


## [E - Cheating Amidakuji](https://atcoder.jp/contests/abc279/tasks/abc279_e)

操作的前缀和很容易维护，但是操作的后缀和不好维护。

假设仅操作前 $i$ 个操作之后，$i$ 位于 $p_i$ 处， $x_i$ 表示 $i$ 的位置，即 $x_{p_i} = i$ 。

结论：$p$ 和 $s$ 互为对方的逆，即交换 $p$ 和 $s$相当于把操作顺序翻转。

现在后缀和也能维护了。

<details>
<summary>AC代码</summary>

```cpp
// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(m);
  for (int i = 0; i < m; ++i)
    std::cin >> a[i], --a[i];

  std::vector<int> b(n);
  std::iota(b.begin(), b.end(), 0);

  auto p = b;
  auto s = b;
  for (int i = 0; i < m; ++i) {
    std::swap(p[a[i]], p[a[i] + 1]);
  }

  std::vector<int> x(n);
  for (int i = 0; i < n; ++i)
    x[p[i]] = i;

  std::vector<int> y(n);
  for (int i = 0; i < n; ++i)
    y[i] = i;

  std::vector<int> ans(m);
  for (int i = m - 1; i >= 0; --i) {
    std::swap(x[p[a[i]]], x[p[a[i] + 1]]);
    std::swap(p[a[i]], p[a[i] + 1]);

    logd(p, s);
    ans[i] = s[x[0]];

    std::swap(y[s[a[i]]], y[s[a[i] + 1]]);
    std::swap(s[a[i]], s[a[i] + 1]);
  }
  logd(p, x);

  for (int i = 0; i < m; ++i)
    std::cout << ans[i] + 1 << "\n";
}

```

</details>



## [F - BOX](https://atcoder.jp/contests/abc279/tasks/abc279_f)

并查集，额外维护集合代表元素和其所属容器的双射即可。

<details>
<summary>AC代码</summary>

```cpp
// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/ds/dsu.h"

void Initialize() {}

void SolveCase(int Case) {
  int n, q;
  std::cin >> n >> q;

  int k = n - 1;
  ds::DSU d(n + q);
  std::vector<int> c(n + q, -1), p(n + q, -1);
  for (int i = 0; i < n; ++i) {
    c[i] = i;
    p[i] = i;
  }
  for (int i = 0; i < q; ++i) {
    int op;
    std::cin >> op;

    if (op == 1) {
      int x, y;
      std::cin >> x >> y;
      --x, --y;

      if (c[y] == -1)
        continue;

      if (c[x] == -1) {
        c[x] = c[y];
        p[c[x]] = x;
        c[y] = -1;
      } else {
        d.f_[c[y]] = c[x];
        p[c[y]] = -1;
        c[y] = -1;
      }
    } else if (op == 2) {
      int x;
      std::cin >> x;
      --x;

      ++k;

      if (c[x] == -1) {
        c[x] = k;
        p[k] = x;
      } else {
        d.f_[k] = c[x];
      }
    } else if (op == 3) {
      int x;
      std::cin >> x;
      --x;

      x = d.leader(x);
      std::cout << p[x] + 1 << "\n";
    }
  }
}

```

</details>


## [G - At Most 2 Colors](https://atcoder.jp/contests/abc279/tasks/abc279_g)

假设 $dp_{i, j}$ 表示前 $i$ 的元素，上一个和 $a_i$ 不同的元素为 $a_j$。

然后有以下几种转移：
- $a_i = a_{i - 1}$： $\forall j < i, dp_{i, j} \to dp_{i + 1, j}$
- $a_i = a_{j}$： $\forall j < i, dp_{i, j} \to dp_{i + 1, i}$
- $a_i \ne a_{i - 1}$ 且 $a_i \ne a_{j}$： $\forall j \le i - k, dp_{i, j} \to dp_{i + 1, i}$

复杂度为 $O(nk)$，但是可以用树状数组优化到 $O(n \log n)$。

第一种转移相当于复制，但是其实可以不用操作，直接复用即可。

第二种转移就是求个和然后加到位置 $t_i$ 上。

第三种转移也是求个和然后加到位置 $t_i$ 上，但是要特判此前只用了一种颜色的情况。

<details>
<summary>AC代码</summary>

```cpp
// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/math/modular/mod_int.h"
using mint = math::ModInt998;

#include "hira/ds/fenwick_tree.h"

void Initialize() {}

void SolveCase(int Case) {
  int n, k, c;
  std::cin >> n >> k >> c;

  ds::FenwickTree<mint> t(n + 1, mint(0),
                          [](const mint& x, const mint& y) { return x + y; });
  t.Update(1, c);
  for (int i = 2; i <= n; ++i) {
    mint x = t.Query(2, i - 1);

    mint y = t.Query(1, 1) * (c - 1);

    mint z = i - k + 1 >= 2 ? t.Query(2, i - k + 1) * (c - 2) : 0;

    t.Update(i, x);
    t.Update(i, y);
    t.Update(i, z);

    logd(i, t, x, y, z);
  }

  mint ans = t.Query(n);

  std::cout << ans.value() << "\n";
}

```

</details>

## [Ex - Sum of Prod of Min](https://atcoder.jp/contests/abc279/tasks/abc279_h)

考虑使用生成函数解决这个问题。

将问题表述成生成函数的形式，则答案为

$$
[x^m] \prod_{i=1}^{n}(x + 2x^2 + 3x^3 + \dots + ix^i + ix^{x+1} + ix^{i+2})
$$

括号里的式子可以分成两部分，$\sum_{j = 1}^i jx^j$ 和 $\sum_{j = i + 1}^{n} i x^j$，用数列或者说级数相关知识可以将其化为

$$
[x^m] \prod_{i = 1}^n \frac{x(1 - x^i)}{{(1-x)}^2}
$$

将 $x$ 提出来得

$$
[x^{m - n}] \prod_{i = 1}^{n} \frac{1 - x^i}{{(1-x)}^2}
$$

把连乘换到分子分母上（乘法交换律）得

$$
[x^{m - n}] \frac{\prod_{i = 1}^{n} 1 - x^i}{{(1-x)}^{2n}}
$$

注意到我们只要求 $x^{m - n}$ 的系数，而 $\prod_{i = 1}^{n} 1 - x^i$ 再乘上 $1 - x^b, b > n$ 只会影响 $x^i, i > b$ 的系数，而 $m - n \le n$ ，所以前式等价与

$$
[x^{m - n}] \frac{\prod_{i = 1}^{+\infin} 1 - x^i}{{(1-x)}^{2n}}
$$

根据 [pentagonal number theorem](https://en.wikipedia.org/wiki/Pentagonal_number_theorem)将式子转化成

$$
[x^{m - n}] \frac{\sum_{k = -\infin}^{+\infin} {(-1)}^k x^{\frac{k(3k - 1)}{2}}}{{(1-x)}^{2n}}
$$

满足 $\frac{k(3 k - 1)}{2} \le m - n$ 的至多有 $O(\sqrt{n})$ 个，对于其中某个 $k$ 而言，记 $a = {(-1)}^{k}, e = \frac{k(3k - 1)}{2}$

$$
[x^{m - n}] \frac{ax^e}{{(1 - x)}^{2n}}
=[x^{m - n - e}] a\frac{1}{{(1 - x)}^{2n}}
=a\binom{m + n - 1 - e}{2n - 1}
$$

最后一个等号是因为数列 $a_n = \binom{m + n}{m}$ 对应的生成函数是 $\frac{1}{{(1 - x)}^{m + 1}}$。

题目给定的 $p$ 是一个较小的素数，所以这里的组合数可以用[Lucas's theorem](https://en.wikipedia.org/wiki/Lucas%27s_theorem)快速求。

时间复杂度为 $O(\sqrt{n} \log n + p)$。

<details>
<summary>AC代码</summary>

```cpp
// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/math/modular/lucas.h"

void Initialize() {}

void SolveCase(int Case) {
  i64 n, m;
  std::cin >> n >> m;

  const int p = 200'003;
  const auto binom = math::Lucas<p>::binom<i64>;
  using mint = math::Lucas<p>::mod_int_t;

  mint ans(0);
  for (i64 k = 0; k * (3 * k - 1) / 2 <= m - n; ++k) {
    // logd(k);
    i64 a = (k & 1) ? -1 : 1;
    i64 e = k * (3 * k - 1) / 2;
    ans += binom(m + n - 1 - e, 2 * n - 1) * a;
  }
  for (i64 k = -1; k * (3 * k + 1) / 2 <= m - n; --k) {
    // logd(k);
    i64 a = (k & 1) ? -1 : 1;
    i64 e = k * (3 * k - 1) / 2;
    ans += binom(m + n - 1 - e, 2 * n - 1) * a;
  }

  std::cout << ans.value() << "\n";
}

```

</details>
