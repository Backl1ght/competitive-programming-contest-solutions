# Aising Programming Contest 2022（AtCoder Beginner Contest 255）

ABC比较简单，DF过于经典。

## [E - Lucky Numbers](https://atcoder.jp/contests/abc255/tasks/abc255_e)

<details>
<summary>题意</summary>

给定一个长度为$n - 1$的数组$s$，和长度为$m$的数组$t$。

要求构造出一个满足$\forall i \in [1, n - 1], a_i + a_{i + 1} = s_i$的数组$a$，并且最大化满足$a_i \in \{t_i | 1 \le i \le m\}$的$i$的数量。

</details>

<details>
<summary>思路</summary>

观察可得：$a_0$确定了，则$a$就确定了。

观察可得：$a_0$加1，则后面奇数位都得减1，偶数位都得加1。所以其他位置的修改可以映射成$a_0$的修改。

考虑初始时令$a_0 = 0$，然后计算其他$a_i$。

注意到目标集合的大小是很小的，所以可以对于每个$a_i$，枚举目标集合中的数，看自身和目标的差距，然后将这个差距映射到$a_0$的增量，统计增量出现的次次数。

出现次数最多的增量，它的出现次数就是答案。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: E - Lucky Numbers
// Contest: AtCoder - Aising Programming Contest 2022（AtCoder Beginner Contest 255）
// URL: https://atcoder.jp/contests/abc255/tasks/abc255_e
// Memory Limit: 1024 MB
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
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

void solve_case(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<i64> s(n - 1), t(m);
  for (int i = 0; i < n - 1; ++i)
    std::cin >> s[i];
  for (int i = 0; i < m; ++i)
    std::cin >> t[i];

  std::vector<i64> a(n);
  a[0] = 0;
  for (int i = 0; i < n - 1; ++i) {
    a[i + 1] = s[i] - a[i];
  }

  std::map<i64, int> cnt;
  for (int i = 0; i < n; ++i) {
    if (i & 1) {
      for (int j = 0; j < m; ++j) {
        i64 d = t[j] - a[i];
        ++cnt[d];
      }
    } else {
      for (int j = 0; j < m; ++j) {
        i64 d = t[j] - a[i];
        ++cnt[-d];
      }
    }
  }

  int ans = 0;
  for (auto [k, v] : cnt) {
    ans = std::max(ans, v);
  }

  std::cout << ans << "\n";
}

```

</details>

## [G - Constrained Nim](https://atcoder.jp/contests/abc255/tasks/abc255_g)

<details>
<summary>题意</summary>

有$n$个石堆，第$i$个石堆有$a_i$个石子。

两个人在这些石堆上玩NIM游戏，但是带禁手，禁手的意思是有$m$个限制$(x_i, y_i)$，对于有$x_i$个石子的石堆，你不能拿走恰好$y_i$个石子。

问是否先手必胜。

其中，$1 \le n, m \le 2 \times {10}^{5}，1 \le a_i \le {10}^{18}, 1 \le y_i \le x_i \le {10}^{18}$。

</details>

<details>
<summary>思路</summary>

公平组合游戏，想到SG函数。

多堆石子的话就是NIM和，现在只需要解决单堆石子的问题。

对于一堆大小为$x$的石子，其SG函数的值$g(x) = \operatorname{mex}_{y \in S(x)}\{ y \}$，其中$\mathbf{S}(x)$表示从$x$一步能转移到的位置，假设$\mathbf{Y}(x) = \{ x_i - y_i | x_i = x, 1 \le i \le m\}$，则$\mathbf{S}(x) = \{ i| 1 \le i \le n - 1 \} \setminus \mathbf{Y}(x)$。

注意到大部分的$x$是没有禁手限制的，对于没有禁手的位置$x$，$g(x) = h(x - 1) + 1$，其中$h(x) = \max_{0 \le y \le x-1}g(y)$。

对于有禁手的位置$x$，它一步能转移到的位置中相比没有禁手缺了一些，可能会导致某个$g(y)$的出现次数降为$0$，从而降低$g(x)$。出现次数降为$0$的$g(y)$中的最小值即为$g(x)$的取值。

为了方便讨论将$(0, 0)$也当成异常点。

由此，如果把$y = g(x)$画出来的话就是由斜率为1的直线和异常点组成，例如下面这个样子。
```
        *
      *
     *
   *   *
  *
 *  *
*
```

统计各个$g(x)$的出现次数，用异常点将函数图像分割为多段。对于有禁手的位置$x$，把禁手的位置删去，看是否会导致某个值出现的次数降为0。对于没有禁手的位置，找到它上一个异常点，然后带入直线方程算SG函数值。

统计每个$g(x)$的出现次数必定炸空间，但是斜率为1的直线上面的点可以优化掉。注意到把这些直线拼起来就是$y = x$，所以$1$到$h(x - 1)$各出现一次，这部分出现次数可以不存。所以只统计异常点SG函数的出现次数即可。

然后从左至右遍历一遍可能的异常点然后模拟一下就完事了，复杂度大概在$O((n + m) \log m)$。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: G - Constrained Nim
// Contest: AtCoder - Aising Programming Contest 2022（AtCoder Beginner Contest 255）
// URL: https://atcoder.jp/contests/abc255/tasks/abc255_g
// Memory Limit: 1024 MB
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
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

void solve_case(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<i64> a(n);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i];

  std::map<i64, std::vector<i64>> ban;
  for (int i = 0; i < m; ++i) {
    i64 x, y;
    std::cin >> x >> y;
    ban[x].push_back(x - y);
  }

  std::map<i64, i64> G, H;
  std::map<i64, int> cnt;
  G[0] = H[0] = 0;
  auto sg = [&](i64 x) {
    auto it = --G.upper_bound(x);
    i64 y = it->first;
    if (x == y)
      return it->second;
    return H[y] + x - y;
  };
  for (const auto& [x, Y] : ban) {
    i64 g = sg(x);
    i64 h = g - 1;

    std::map<i64, int> temp_cnt;
    for (i64 y : Y) {
      ++temp_cnt[sg(y)];
    }

    for (auto [v, c] : temp_cnt) {
      auto it = cnt.find(v);
      if (it == cnt.end() || c >= it->second + 1) {
        g = v;
        cnt[g]++;
        G[x] = g, H[x] = h;
        break;
      }
    }
  }

  i64 z = 0;
  for (int i = 0; i < n; ++i)
    z ^= sg(a[i]);
  std::cout << (z ? "Takahashi" : "Aoki") << "\n";
}

```

</details>

## [Ex - Range Harvest Query](https://atcoder.jp/contests/abc255/tasks/abc255_h)

<details>
<summary>题意</summary>

有$n$个资源点，第$i$个资源点每天刷新$i$个资源。

有$q$个操作$(d_i, l_i, r_i)$：在第$d_i$天收割$[l_i, r_i]$的资源，输出收割到的资源数，答案对$998244353$取模。

其中$1 \le n \le {10}^{18}, 1 \le q \le 2 \times {10}^5，1 \le d_1 < d_2 < \dots < d_q \le {10}^{18}, 1\le l_i \le r_i \le {10}^{18}$。

</details>

<details>
<summary>思路</summary>

卡G了，没看这道题，感觉比G简单。

用`std::set`维护每个位置上一次收割的时间，把相同时间收割的区间合并成1个元素，类似Chtholly Tree。

一次收割$(D, L, R)$可以对应拆分，删除，插入三种操作：
1. 左右边界所在区间可能没有被$[L, R]$完全包含，所以可能需要将左右边界不完整的区间拆分出来
2. 现在集合中$[L, R]$内的区间都是完全属于$[L, R]$的了，对于$[L, R]$内的区间统计贡献，然后删除
3. 最后再插入区间$[L, R]$，值全为$D$。

对于区间$[l, r]$，假设上一次收割的时间为$last$，本次收割的时间为$d$，则这段区间对于答案的贡献为
$$
\sum_{i = l}^{r} i (d - last) = \frac{(d - last) * (l + r) * (r - l + 1)}{2}
$$

初始时只有1个元素，每次收割插入一个元素，删除的元素最差不会超过插入元素的总数的3倍，由此插入和删除区间的总数为$O(q)$，总的复杂度为$O(n \log q)$。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: Ex - Range Harvest Query
// Contest: AtCoder - Aising Programming Contest 2022（AtCoder Beginner Contest 255）
// URL: https://atcoder.jp/contests/abc255/tasks/abc255_h
// Memory Limit: 1024 MB
// Time Limit: 8000 ms
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

const int mod = 998244353;
int add(int x, int y) {
  return x + y >= mod ? x + y - mod : x + y;
}
int sub(int x, int y) {
  return x - y < 0 ? x - y + mod : x - y;
}
int mul(int x, int y) {
  return i64(1) * x * y % mod;
}
int qp(int x, int y) {
  int r = 1;
  while (y) {
    if (y & 1)
      r = mul(r, x);
    x = mul(x, x);
    y >>= 1;
  }
  return r;
}
int inv(int x) {
  return qp(x, mod - 2);
}
const int inv2 = inv(2);

void solve_case(int Case) {
  i64 n, q;
  std::cin >> n >> q;
  std::set<std::array<i64, 3>> s;
  s.insert({1, n, 0});

  auto split = [&](i64 x) {
    if (x > n)
      return;
    auto it = --s.lower_bound({x + 1, 0, 0});
    auto [l, r, d] = (*it);
    if (l == x)
      return;
    s.erase(it);
    s.insert({l, x - 1, d});
    s.insert({x, r, d});
  };

  auto query = [&](i64 l, i64 r, i64 d) {
    auto cost = [](int l, int r, int z) {
      return mul(mul(z, mul(add(l, r), add(sub(r, l), 1))), inv2);
    };
    logd(l, r, d);

    logd(s);
    split(r + 1);
    logd(s);
    split(l);
    logd(s);

    int ans = 0;
    i64 p = l;
    while (p <= r) {
      auto it = s.lower_bound({p, 0, 0});
      auto [L, R, D] = (*it);
      s.erase(it);
      logd(s);

      ans = (ans + cost(L % mod, R % mod, (d - D) % mod)) % mod;
      p = R + 1;
    }
    s.insert({l, r, d});
    logd(s);

    return ans;
  };

  for (int _ = 0; _ < q; ++_) {
    i64 d, l, r;
    std::cin >> d >> l >> r;
    std::cout << query(l, r, d) << "\n";
  }
}

```

</details>