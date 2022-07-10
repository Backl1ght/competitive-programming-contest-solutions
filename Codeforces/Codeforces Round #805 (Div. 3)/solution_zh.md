# Codeforces Round #805 (Div. 3)

咕咕咕咕。

## [E. Split Into Two Sets](https://codeforces.com/contest/1702/problem/E)

<details>
<summary>题意</summary>

有$n$张牌，每张牌上写有两个数字，问是否能将牌分成两个集合，使得单个集合中的牌上的数字构成的集合没有重复元素。

其中$2 \le n \le 2 \times{10}^5$。

</details>

<details>
<summary>思路</summary>

转化成图论问题，令每个数字对应一个节点，问题从将牌分成两个集合转换成将数字分成两个集合。

对于牌$(x, y)$，在点$x$和点$y$之间连边，表示选了$x$就得选$y$。

如果图中存在奇环，那么就无解；反之则有解。

**注意**：当某个点的出度大于$2$时无解。

然后就是DFS跑二分图染色。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: E. Split Into Two Sets
// Contest: Codeforces - Codeforces Round #805 (Div. 3)
// URL: https://codeforces.com/contest/1702/problem/E
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

  std::vector<std::vector<int>> g(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    --x, --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  bool flag = true;
  std::vector<int> c(n, -1);
  std::function<void(int)> coloring = [&](int u) {
    for (int v : g[u]) {
      if (c[v] != -1) {
        if (c[v] == c[u])
          flag = false;
      } else {
        c[v] = 1 - c[u];
        coloring(v);
      }
    }
  };
  for (int i = 0; i < n; ++i) {
    if (c[i] == -1) {
      c[i] = 0;
      coloring(i);
    }
  }
  for (int i = 0; i < n; ++i) {
    if (g[i].size() > 2) {
      flag = false;
    }
  }

  std::cout << (flag ? "YES" : "NO") << "\n";
}

```

</details>

## [F. Equate Multisets](https://codeforces.com/contest/1702/problem/F)

<details>
<summary>题意</summary>

给定两个集合$a, b$，支持两种操作：
- 将$b$中的某个元素$x$变成$2x$。
- 将$b$中的某个元素$x$变成$\lfloor \frac{x}{2}\rfloor$

不能改变$a$中的元素，问通过上述两种操作是否能使$b$和$a$中元素相同。

其中$2 \le |a|, |b| \le 2 \times {10}^5$。

</details>

<details>
<summary>思路</summary>

先将$b$中数字不断乘2不会影响答案，因为后续还可以从过整除2变回来。所以可以先将$b$中的元素不断乘2直到大于等于$\max\{a\}$，这样后续就可以只考虑整除2操作了。

此外，此时如果$x \in a$是偶数，则可以对$x$使用整除2操作，这个操作等价于对某个$y \in b$使用乘2操作。

因为现在只需要考虑整除2操作，$b$中元素只会变小，所以就可以贪心了，具体就是贪心的先尝试构造$\max\{ a \}$。

此时$b$中大于$\max\{ a \}$的元素都不能直接用了，所以可以先将$b$中大于$\max\{ a \}$的元素不断整除2直到$b$中没有元素大于$\max\{ a \}$。

此时，若$b$中包含$\max\{ a \}$，即$\max\{ b \} = \max\{ a \}$，就认为构造出了$\max\{ a \}$；否则，若$\max\{ a \}$为奇数则无解，反之则对$\max\{ a \}$执行整除2操作。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: F. Equate Multisets
// Contest: Codeforces - Codeforces Round #805 (Div. 3)
// URL: https://codeforces.com/contest/1702/problem/F
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
  logd(Case);

  int n;
  std::cin >> n;

  std::multiset<int> a, b;
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    a.insert(x);
  }
  int ma = *std::prev(a.end());
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    while (x < ma) {
      x = x * 2;
    }
    b.insert(x);
  }
  logd(b);

  while (!a.empty()) {
    auto it = std::prev(a.end());
    int x = *it;

    while (true) {
      auto jt = std::prev(b.end());
      int y = *jt;
      if (y <= x)
        break;
      b.erase(jt);
      b.insert(y / 2);
    }

    auto jt = std::prev(b.end());
    int y = *jt;

    if (x == y) {
      a.erase(it);
      b.erase(jt);
    } else {
      if (x % 2 == 0) {
        a.erase(it);
        a.insert(x / 2);
      } else {
        std::cout << "NO\n";
        return;
      }
    }
  }

  std::cout << "YES\n";
}

```

</details>

## [G2. Passable Paths (hard version)](https://codeforces.com/contest/1702/problem/G)

<details>
<summary>题意</summary>

给定一颗$n$个节点的无向无根树，要求回答$q$个询问$(k_i, p_i)$：给定一个大小为$k_i$的点集$p_i$，问是否可以不重复经过一条边的遍历$p_i$，或者说是否存在一条简单路径经过$p_i$中所有点。

其中$1 \le n \le 2 \times {10}^5, \sum_i k_i \le 2 \times {10}^5$。

</details>

<details>
<summary>思路</summary>

不妨以节点$1$为根。

对于链$l$，若其满足$l_i$是$l_{i-1}$的父亲，就认为它是一条好链。

一条简单路径可以是一条好链，也可以是满足仅有末尾元素相等的两条好链。

考虑将$p_i$中的点按深度降序排序，然后从前到后的尝试将点放到至多两条好链上。

然后借助LCA模拟一下就完事了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: G2. Passable Paths (hard version)
// Contest: Codeforces - Codeforces Round #805 (Div. 3)
// URL: https://codeforces.com/contest/1702/problem/G2
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
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

class LCA {
 private:
  int n_;
  const std::vector<std::vector<int>>& g_;
  std::vector<int> f, sz, son, top;

  void dfs1(int u, int fa) {
    f[u] = fa;
    sz[u] = 1;
    son[u] = -1;
    for (int v : g_[u]) {
      if (v == fa)
        continue;
      dep[v] = dep[u] + 1;
      dfs1(v, u);
      sz[u] += sz[v];
      if (son[u] == -1 || sz[v] > sz[son[u]])
        son[u] = v;
    }
  }

  void dfs2(int u, int fa, int tp) {
    top[u] = tp;
    if (son[u] != -1)
      dfs2(son[u], u, tp);
    for (int v : g_[u]) {
      if (v == fa || v == son[u])
        continue;
      dfs2(v, u, v);
    }
  }

 public:
  std::vector<int> dep;

  LCA(const std::vector<std::vector<int>>& g) : n_(g.size()), g_(g) {
    dep.resize(n_);
    f.resize(n_);
    sz.resize(n_);
    son.resize(n_);
    top.resize(n_);

    dep[0] = 0;
    dfs1(0, 0);
    dfs2(0, 0, 0);
  }

  int lca(int u, int v) {
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]])
        std::swap(u, v);
      u = f[top[u]];
    }
    if (dep[u] > dep[v])
      std::swap(u, v);
    return u;
  }
};

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

  LCA t(g);
  logd(t.dep);

  int q;
  std::cin >> q;
  int k;
  std::vector<int> p(n);
  for (int _ = 0; _ < q; ++_) {
    std::cin >> k;
    for (int i = 0; i < k; ++i) {
      std::cin >> p[i];
      --p[i];
    }
    sort(p.begin(), p.begin() + k, [&](int x, int y) -> bool { return t.dep[x] > t.dep[y]; });

    bool flag = true;
    int l1 = p[0], l2 = -1, l = -1;
    for (int i = 1; i < k; ++i) {
      if (l2 == -1) {
        if (t.lca(l1, p[i]) != p[i]) {
          l2 = p[i];
          l = t.lca(p[0], p[i]);
          if (l != -1 && t.dep[p[k - 1]] < t.dep[l]) {
            flag = false;
            break;
          }
        } else {
          l1 = p[i];
        }
      } else {
        if (t.lca(l1, p[i]) == p[i]) {
          l1 = p[i];
          continue;
        }

        if (t.lca(l2, p[i]) == p[i]) {
          l2 = p[i];
          continue;
        }

        flag = false;
        break;
      }
    }

    std::cout << (flag ? "YES" : "NO") << "\n";
  }
}

```

</details>