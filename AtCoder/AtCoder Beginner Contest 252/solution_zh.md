# AtCoder Beginner Contest 252

A，B，C跳过。

## [D - Distinct Trio](https://atcoder.jp/contests/abc252/tasks/abc252_d)

<details>
<summary>题意</summary>

求满足$i < j < k$且$a_i,a_j,a_k$这3个数两两互不相等的$(i, j, k)$的数量。

$n \le 2 \times 10^5$。

</details>

<details>
<summary>思路</summary>

正着不好算，逆向思考一下就行。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: D - Distinct Trio
// Contest: AtCoder - AtCoder Beginner Contest 252
// URL: https://atcoder.jp/contests/abc252/tasks/abc252_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
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
  int n;
  std::cin >> n;

  std::map<int, int> cnt;
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    ++cnt[x];
  }

  i64 ans = i64(1) * n * (n - 1) / 2 * (n - 2) / 3;
  for (auto [_, c] : cnt) {
    if (c >= 3) {
      ans = ans - i64(1) * c * (c - 1) / 2 * (c - 2) / 3;
    }
    if (c >= 2) {
      ans = ans - i64(1) * c * (c - 1) / 2 * (n - c);
    }
  }
  std::cout << ans << "\n";
}

```

</details>

## [E - Road Reduction](https://atcoder.jp/contests/abc252/tasks/abc252_e)

<details>
<summary>题意</summary>

给一张$n$个点$m$条边的无向图，现在只能保留$n - 1$条边，需要使得图保持连通且使$\sum_{i = 2}^n d_i$最小，其中$d_i$表示$1$到$i$的简单路径长度。

问应该保留哪些边？

$n, m \le 2 \times 10^5$。

</details>

<details>
<summary>思路</summary>

一眼最短路树，跑遍dijkstra就行了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: E - Road Reduction
// Contest: AtCoder - AtCoder Beginner Contest 252
// URL: https://atcoder.jp/contests/abc252/tasks/abc252_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
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

struct Edge {
  int v;
  int w;
  int eid;
  Edge() {}
  Edge(int _v, int _w, int _eid) : v(_v), w(_w), eid(_eid) {}
};

struct Node {
  int u;
  i64 c;
  Node() {}
  Node(int _u, i64 _c) : u(_u), c(_c) {}
  bool operator<(const Node& nd) const { return c > nd.c; }
};

void solve_case(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<Edge>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    --u, --v;
    g[u].push_back(Edge(v, w, i));
    g[v].push_back(Edge(u, w, i));
  }

  std::vector<i64> dis(n, INT64_MAX);
  std::vector<bool> vis(n, false);
  std::vector<int> use(n, -1);

  std::priority_queue<Node> q;
  dis[0] = 0;
  q.push(Node(0, dis[0]));
  while (!q.empty()) {
    auto [u, c] = q.top();
    q.pop();

    if (vis[u])
      continue;
    vis[u] = true;

    for (auto [v, w, eid] : g[u]) {
      if (dis[v] > c + w) {
        dis[v] = c + w;
        use[v] = eid;
        q.push(Node(v, dis[v]));
      }
    }
  }

  for (int i = 1; i < n; ++i) {
    std::cout << use[i] + 1 << " \n"[i + 1 == n];
  }
}

```

</details>

## [F - Bread](https://atcoder.jp/contests/abc252/tasks/abc252_f)

<details>
<summary>题意</summary>

给一条长度为$L$的绳子。

每次可以选择一条长度为$K$的绳子，以$K$的代价将其分成两段，每段的长度需要是整数。

需要得到$n$条绳子分给$n$个人，第$i$个人得到的绳子长度为$a_i$，可以有绳子剩下来，问最小代价。

$n \le 2 \times 10^5，1 \le a_i \le 10^9, \sum_i a_i \le L \le 10^15$。

</details>

<details>
<summary>思路</summary>

如果$L = \sum_i a_i$，那就是构成huffman树的做法最优。

现在可能会多出来一些绳子，可以证明只多出一段的时候代价是最小的，所以就在$a_1, a_2, \dots, a_n$的基础上，再加一段$L - \sum_i a_i$，然后跑huffman树。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: F - Bread
// Contest: AtCoder - AtCoder Beginner Contest 252
// URL: https://atcoder.jp/contests/abc252/tasks/abc252_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
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
  int n;
  i64 l;
  std::cin >> n >> l;

  std::priority_queue<i64, std::vector<i64>, std::greater<i64>> q;
  i64 z = 0;
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    q.push(x);
    z += x;
  }
  if (z < l)
    q.push(l - z);

  i64 ans = 0;
  while (q.size() > 1) {
    i64 x = q.top();
    q.pop();
    i64 y = q.top();
    q.pop();

    ans += x + y;
    q.push(x + y);
  }
  std::cout << ans << "\n";
}

```

</details>

## [G - Pre-Order](https://atcoder.jp/contests/abc252/tasks/abc252_g)

<details>
<summary>题意</summary>

给出一颗树的先序遍历，一个节点的多个子节点按从小到大的优先级遍历，问对应这个先序遍历的树有多少种。

树种节点个数至多为$500$。

</details>

<details>
<summary>思路</summary>

区间DP。

假设$dp_{l, r}$表示：以$?$为根，先序遍历为$?\ a_l\ a_{l + 1} \dots\ a_{r - 1}$的树的种类，其中$?$为一个虚拟节点。

可以把$l$替换到$?$的位置，所以$dp_{l + 1, r}$也可以表示以$l$为根，先序遍历为$a_l a_{l + 1}, \dots, a_{r-1}$的树的种类。类似地有答案为$dp_{2, n + 1}$。

对于$dp_{l, r}$，要么$?$只有一个子节点为$l$，要么$?$还包含其他子节点，由于遍历的优先级，下一个子节点$k$必须满足$a_l < a_k$。

$$
dp_{l, r} = 
\left\{
    \begin{align*}
    &1 & r - l \le 1\\
    & dp_{l + 1, r} + \sum_{\substack{l + 1 \le k < r\\a_l < a_k}} dp_{l + 1, k} \times dp_{k, r} & \text{ohterwise}
    \end{align*}
\right.
$$

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: G - Pre-Order
// Contest: AtCoder - AtCoder Beginner Contest 252
// URL: https://atcoder.jp/contests/abc252/tasks/abc252_g
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
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
void solve_case(int Case) {
  int n;
  std::cin >> n;

  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i)
    std::cin >> a[i];

  std::vector<std::vector<int>> dp(n + 2, std::vector<int>(n + 2));
  for (int l = n + 1; l >= 2; --l) {
    for (int r = l; r <= n + 1; ++r) {
      if (l == r)
        dp[l][r] = 1;
      else {
        dp[l][r] = dp[l + 1][r];
        for (int k = l + 1; k + 1 <= r; ++k) {
          if (a[l] < a[k])
            dp[l][r] = (dp[l][r] + i64(1) * dp[l + 1][k] * dp[k][r] % mod) % mod;
        }
      }
    }
  }
  logd(dp);
  std::cout << dp[2][n + 1] << "\n";
}

```

</details>

## [Ex - K-th beautiful Necklace](https://atcoder.jp/contests/abc252/tasks/abc252_h)

<details>
<summary>题意</summary>

给$n$个宝石，第$i$珍珠颜色为$c_i$，价值为$v_i$，可以每种颜色的珍珠选一个构成一条项链，项链的权值为每颗珍珠权值的异或和。

求可能组出来的所有项链中，第$k$大的项链权值。

$n \le 70, v_i < 2^60, k \le 10^18$，颜色数目不超过$n$。

</details>

<details>
<summary>思路</summary>

**观察**： 项链的种类不会超过$3^{\frac{n}{3}}$种。
**证明**：假设颜色为$c$的珍珠有$n_c$颗。尝试构造$n_c$使得$\sum_c n_c = N$且$\prod_c n_c$最大化。
- $n_c = 1$，假设有另外一种颜色$c^\prime$，$n_c \times n_{c^\prime} \le n_c + n_{c^\prime}$，则$c$可以和$c^\prime$合并得到更多的项链种类。
- $n_c = 2$，由于$2^3 \le 3^2$，3个2可以合并成两个3从而得到更多的项链种类。
- $n_c \ge 4$，由于$2(n_c - 2) \ge n_c$,可以将$n_c$拆成$2$和$n_c - 2$从而获得更更多项链种类。
  
由此最差情况下$n_c \in {2, 3}$且至多只有两个$2$，至多有$O(3^{\frac{n}{3}})$种项链。

然后可以将珍珠对半分，然后两边分别枚举出$O(3^{\frac{n}{6}})$种项链，分别记为集合$A$和$B$，再由异或运算的结合律，合并两边的结果，从而得出答案。

可以将$B$中的数存进01-trie，这样每个$A_i$就可以通过01-trie实现$O(\log V)$查询$A_i \oplus B_j > x$的$j$的数量，再通过二分（从高位开始枚举每一位是0还是1）实现$O(3^{\frac{n}{6}} \log^2 V)$的做法。这个复杂度还是不够优秀。

可以将插入和查询按照位拆分成多步，用一个数组记录上一步的结果，在上一步的基础上推出下一步，这样就查询的时候就不用每次都从trie的根开始往下走，每个$A_i$就可以实现$O(1)$查询$A_i \oplus B_j > x$的$j$的数量，时间复杂度为$O(3^{\frac{n}{6}} \log V)$。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: Ex - K-th beautiful Necklace
// Contest: AtCoder - AtCoder Beginner Contest 252
// URL: https://atcoder.jp/contests/abc252/tasks/abc252_h
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
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

struct Node {
  Node* child[2];
  int count;
};

void solve_case(int Case) {
  int n, c;
  i64 k;
  std::cin >> n >> c >> k;

  std::vector<std::vector<i64>> cc(c);
  for (int i = 0; i < n; ++i) {
    int x;
    i64 y;
    std::cin >> x >> y;
    --x;
    cc[x].push_back(y);
  }

  std::function<void(int, int, i64, std::vector<i64>&)> gen = [&](int p, int t, i64 x,
                                                                  std::vector<i64>& A) -> void {
    if (p == t) {
      A.push_back(x);
      return;
    }
    for (i64 v : cc[p]) {
      gen(p + 1, t, x ^ v, A);
    }
  };

  int d = c / 2;
  std::vector<i64> A, B;
  gen(0, d + 1, 0, A);
  gen(d + 1, c, 0, B);

  Node* null = new Node;
  null->child[0] = null->child[1] = null;
  null->count = 0;

  Node* root = new Node;
  root->child[0] = root->child[1] = null;
  root->count = B.size();

  std::vector<Node*> pa(A.size(), root), pb(B.size(), root);

  i64 ans = 0;
  for (i64 w = 59; w >= 0; --w) {
    for (int i = 0; i < (int)B.size(); ++i) {
      int c = (B[i] >> w) & 1;
      if (pb[i]->child[c] == null) {
        Node* new_node = new Node;
        new_node->child[0] = new_node->child[1] = null;
        new_node->count = 0;
        pb[i]->child[c] = new_node;
      }
      pb[i] = pb[i]->child[c];
      ++pb[i]->count;
    }

    i64 gt = 0;
    for (int i = 0; i < (int)A.size(); ++i) {
      int c = (A[i] >> w) & 1;
      gt = gt + (pa[i]->child[c ^ 1]->count);
    }

    if (gt < k) {
      // ans + 0
      k -= gt;

      for (int i = 0; i < (int)A.size(); ++i) {
        int c = (A[i] >> w) & 1;
        pa[i] = pa[i]->child[c];
      }
    } else {
      // ans + 1
      ans = ans | (i64(1) << w);
      for (int i = 0; i < (int)A.size(); ++i) {
        int c = (A[i] >> w) & 1;
        pa[i] = pa[i]->child[c ^ 1];
      }
    }
    logd(k);
  }
  std::cout << ans << "\n";
}

```

</details>