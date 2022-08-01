# Codeforces Round #811 (Div. 3)

咕咕咕。

## [D. Color with Occurrences](https://codeforces.com/contest/1714/problem/D)

<details>
<summary>题意</summary>

给定文本串$t$，和$n$个模式串$s_i$。

初始时$t$的每个字符都是黑色的，如果$t$的某个子串和$s_i$相等，则可以通过一次染色将这个子串中的字符都染成红色。

一个模式串可以用多次，$t$中的一个字符可以被染色多次，红色的字符再次染色的结果还是红色。

问染色几次可以把$t$中所有字符染成红色，要求出输出次数以及方案。

其中$1 \le |t| \le 100, 1 \le n, |s_i| \le 10$。

</details>

<details>
<summary>思路</summary>

如果$t_{l} t_{l+1} \dots t_{r}$和某个$s_i$相等，则对于$l \le i \le r$，向$r + 1$连边，表示从$i$可以转移到$r + 1$。这个由于参数比较小，直接暴力就可以了。

然后跑个最短路就可以得到最小染色次数，方案数就是再记录个路径。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: D. Color with Occurrences
// Contest: Codeforces - Codeforces Round #811 (Div. 3)
// URL: https://codeforces.com/contest/1714/problem/D
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

const int INF = 0x3f3f3f3f;

void solve_case(int Case) {
  std::string t;
  std::cin >> t;
  int m = static_cast<int>(t.size());

  std::vector<std::vector<int>> f(m + 1, std::vector<int>(m + 1, INF));
  std::vector<std::vector<int>> g(m + 1, std::vector<int>(m + 1, -1));
  std::vector<std::vector<int>> h(m + 1, std::vector<int>(m + 1, -1));
  std::vector<std::vector<int>> w(m + 1, std::vector<int>(m + 1, -1));

  int n;
  std::cin >> n;
  for (int k = 0; k < n; ++k) {
    std::string s;
    std::cin >> s;
    int l = static_cast<int>(s.size());

    if (l > m)
      continue;

    for (int i = 0; i + l - 1 < m; ++i) {
      bool flag = true;
      for (int j = 0; j < l; ++j) {
        if (t[i + j] != s[j]) {
          flag = false;
          break;
        }
      }
      if (flag) {
        for (int j = i; j < i + l; ++j) {
          f[j][i + l] = 1;
          g[j][i + l] = k;
          h[j][i + l] = i + l;
          w[j][i + l] = i;
        }
      }
    }
  }

  for (int k = 0; k <= m; ++k) {
    for (int i = 0; i <= m; ++i) {
      for (int j = 0; j <= m; ++j) {
        if (f[i][j] > f[i][k] + f[k][j]) {
          f[i][j] = f[i][k] + f[k][j];
          h[i][j] = h[i][k];
        }
      }
    }
  }

  if (f[0][m] == INF) {
    std::cout << "-1\n";
  } else {
    std::cout << f[0][m] << "\n";
    int p = 0;
    while (p != m) {
      logd(p);
      int q = h[p][m];
      std::cout << g[p][q] + 1 << " " << w[p][q] + 1 << "\n";
      p = q;
    }
  }
}
```

</details>

## [E. Add Modulo 10](https://codeforces.com/contest/1714/problem/E)

<details>
<summary>题意</summary>

给定长度为$n$的数组$a$。支持下述这一操作：
- 选择一个$i$，令$a_i = a_i + (a_i \mod 10)$。

同一个$i$可以选择多次。问通过零或多次操作，是否能够使$a$中所有数相等。

其中$1 \le n \le 2 \times {10}^5, 0 \le a_i \le {10}^9$。

</details>

<details>
<summary>思路</summary>

根据$a_i \mod 10$分类讨论，假设数$x$个位数为$y$，那么假设对$x$进行一次操作过后的得到$z$，则有$z$的个位数为$2y \mod 10$。根据这个把转移图建出来。

然后就可以发现转移图可以分成两个部分$\{0, 5\}$和其他。

对于个位数为$0$的数$x$，继续对$x$进行操作$x$也不会发生变化。

对于个位数为$5$的数$x$，对$x$进行一次操作过后，再继续对$x$进行操作$x$也不会发生变化。

对于其余情况，可以无止境的对$x$进行操作，每次操作都会得到一个新的数，且其个位数的变化满足$\dots \to 2 \to 4 \to 8 \to 6 \to 2 \to \dots$。

**观察1**：假设对$a_i$操作$t_i$次得到的结果满足条件，那么对所有$t_i$同时加上某个自然数，结果依然满足条件。

由此，不妨对所有个位数为$5$的数先操作一次，转成个位数为$0$的数。

然后，如果存在个位数为$0$的数，那么有解当且仅当$a$中所有元素已经相等了。

现在，只需要考虑没有数个位数为$0$且没有数个位数为$5$的情况。

**观察2**：此时，通过有限次操作一定可以使$x$的个位数为$6$。

**观察3**：对于个位数为$6$的数$x$，对$x$进行操作直到下一次$x$个位数为$6$时，$\frac{x - 6}{10}$的值增加了$2$，即$\frac{x - 6}{10}$的奇偶性不会改变。

由此，不妨先将所有数个位数搞成$6$，然后看$\frac{x - 6}{10}$的奇偶性，有解当且仅当对于所有$x$，$\frac{x - 6}{10}$同奇偶。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: E. Add Modulo 10
// Contest: Codeforces - Codeforces Round #811 (Div. 3)
// URL: https://codeforces.com/contest/1714/problem/E
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
    int x;
    std::cin >> x;

    if (x % 10 == 0)
      ;
    else if (x % 10 == 5) {
      x = x + 5;
    } else {
      while (x % 10 != 6) {
        x = x + x % 10;
      }
    }

    a[i] = x;
  }

  std::vector<int> c(10);
  for (int x : a) {
    ++c[x % 10];
  }

  bool flag;
  if (c[0] > 0) {
    int ma = *std::max_element(a.begin(), a.end());
    int mi = *std::min_element(a.begin(), a.end());
    flag = ma == mi;
  } else {
    std::vector<int> d(2);
    for (int x : a) {
      ++d[(x - 6) / 10 % 2];
    }
    flag = !(d[0] > 0 && d[1] > 0);
  }

  std::cout << (flag ? "Yes" : "No") << "\n";
}
```

</details>

## [F. Build a Tree and That Is It](https://codeforces.com/contest/1714/problem/F)

<details>
<summary>题意</summary>

给定4个数$n, d_{12}, d_{23}, d_{31}$，要求构造出满足下述条件的一颗树：
- 树有$n$个节点。
- 节点1到节点2的距离为$d_{12}$。
- 节点2到节点3的距离为$d_{23}$。
- 节点3到节点1的距离为$d_{31}$。

其中$3 \le n \le 2 \times {10}^5$。

</details>

<details>
<summary>思路</summary>

假设构造下面这种形状的树, `//`表示零或多条边。
```
        1
       //
       x
     // \\
     2   3
```

令$d(u, v)$表示$u$到$v$的距离。记$d(1, x) = a, d(x, 2) = b, d(x, 3) = c$，则有
$$
\left\{
\begin{aligned}
d_{12} = a + b\\
d_{23} = b + c\\
d_{31} = a + c\\
\end{aligned}
\right.
$$

然后就可以解出$a, b, c$。

$a, b, c$必须为整数且不能为负数，否则无解。

若$b, c$同时为零，2和3这两个点重合，无解。

构建这个树至少需要$a + b + c + 1$个点，当$a + b + c + 1 > n$时无解。

然后可以根据$c$是否等于零分类讨论，再模拟一下即可。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: F. Build a Tree and That Is It
// Contest: Codeforces - Codeforces Round #811 (Div. 3)
// URL: https://codeforces.com/contest/1714/problem/F
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
  int n, d12, d23, d31;
  std::cin >> n >> d12 >> d23 >> d31;

  if ((d12 + d23 - d31) % 2 != 0) {
    std::cout << "NO\n";
    return;
  }

  int b = (d12 + d23 - d31) / 2;
  int a = d12 - b;
  int c = d31 - a;
  logd(a, b, c);

  if (a < 0 || b < 0 || c < 0 || (b == 0 && c == 0) || a + b + c > n - 1) {
    std::cout << "NO\n";
    return;
  }

  std::vector<std::pair<int, int>> E;
  std::vector<int> p;

  if (c > 0) {
    int u = 1, x = 4;
    p.push_back(1);
    for (int i = 0; i < a + b - 1; ++i) {
      E.push_back(std::make_pair(p.back(), x));
      p.push_back(x);
      ++x;
    }
    E.push_back(std::make_pair(p.back(), 2));
    p.push_back(2);

    for (int i = 0; i < b; ++i) {
      p.pop_back();
    }

    for (int i = 0; i < c - 1; ++i) {
      E.push_back(std::make_pair(p.back(), x));
      p.push_back(x);
      ++x;
    }
    E.push_back(std::make_pair(p.back(), 3));
    p.push_back(3);

    while (x <= n) {
      E.push_back(std::make_pair(p.back(), x));
      p.push_back(x);
      ++x;
    }
  } else {
    int u = 1, x = 4;
    p.push_back(1);
    for (int i = 0; i < a - 1; ++i) {
      E.push_back(std::make_pair(p.back(), x));
      p.push_back(x);
      ++x;
    }
    E.push_back(std::make_pair(p.back(), 3));
    p.push_back(3);

    for (int i = 0; i < b - 1; ++i) {
      E.push_back(std::make_pair(p.back(), x));
      p.push_back(x);
      ++x;
    }
    E.push_back(std::make_pair(p.back(), 2));
    p.push_back(2);

    while (x <= n) {
      E.push_back(std::make_pair(p.back(), x));
      p.push_back(x);
      ++x;
    }
  }

  std::cout << "YES\n";
  for (auto [u, v] : E) {
    std::cout << u << " " << v << "\n";
  }
}
```

</details>

## [G. Path Prefixes](https://codeforces.com/contest/1714/problem/G)

这题好水，不详细写了。

大概就是DFS记录到根的路径，然后二分。

<details>
<summary>AC代码</summary>

```cpp
// Problem: G. Path Prefixes
// Contest: Codeforces - Codeforces Round #811 (Div. 3)
// URL: https://codeforces.com/contest/1714/problem/G
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
  std::vector<int> a(n), b(n);
  for (int i = 1; i < n; ++i) {
    int p;
    std::cin >> p >> a[i] >> b[i];
    --p;
    g[p].push_back(i);
  }

  std::vector<int> r(n);
  i64 SA = 0, SB = 0;
  std::vector<i64> B;
  std::function<void(int)> dfs = [&](int u) {
    SA += a[u], SB += b[u];
    B.push_back(SB);

    if (u != 0) {
      r[u] = std::upper_bound(B.begin(), B.end(), SA) - B.begin() - 1;
      logd(u, SA, B, r[u]);
    }

    for (int v : g[u]) {
      dfs(v);
    }

    SA -= a[u], SB -= b[u];
    B.pop_back();
  };
  dfs(0);

  for (int i = 1; i < n; ++i)
    std::cout << r[i] << " \n"[i + 1 == n];
}
```

</details>