# AtCoder Beginner Contest 261

咕咕咕咕。

## [E - Many Operations](https://atcoder.jp/contests/abc261/tasks/abc261_e)

<details>
<summary>题意</summary>

给定一个值$X$和一个长度为$n$的操作序列。

操作有3种：
1. 将$X$替换成$x \operatorname{and} a_i$；
2. 将$X$替换成$x \operatorname{or} a_i$；
3. 将$X$替换成$x \operatorname{xor} a_i$。

接下来共操作$n$次，第$i$次操作时，依次执行操作序列中前$i$个操作。

每次操作之后，输出当前$X$的值。

其中$1 \le n \le 2 \times {10}^5$。

</details>

<details>
<summary>思路</summary>

作为整数不好搞，看成二进制，然后按位处理。

对于每一位，其实可以将多个操作压缩成一个操作，具体做法就是把真值表搞出来。

然后离线处理一下就完事了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: E - Many Operations
// Contest: AtCoder - AtCoder Beginner Contest 261
// URL: https://atcoder.jp/contests/abc261/tasks/abc261_e
// Memory Limit: 1024 MB
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
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

void solve_case(int Case) {
  int n, X;
  std::cin >> n >> X;

  std::vector<int> T(n), A(n);
  for (int i = 0; i < n; ++i)
    std::cin >> T[i] >> A[i];

  std::vector<int> ans(n, 0);

  for (int j = 29; j >= 0; --j) {
    std::vector<int> x = {0, 1};
    std::vector<int> a = {0, 1};
    for (int i = 0; i < n; ++i) {
      std::vector<int> b;
      int y = ((A[i] >> j) & 1);
      if (T[i] == 1) {
        if (y == 0) {
          b = {0, 0};
        } else {
          b = {0, 1};
        }
      } else if (T[i] == 2) {
        if (y == 0) {
          b = {0, 1};
        } else {
          b = {1, 1};
        }
      } else if (T[i] == 3) {
        if (y == 0) {
          b = {0, 1};
        } else {
          b = {1, 0};
        }
      }
      a[0] = b[a[0]];
      a[1] = b[a[1]];

      x[0] = a[x[0]];
      x[1] = a[x[1]];

      int z = ((X >> j) & 1);
      int w = x[z];
      if (w)
        ans[i] |= (1 << j);
    }
  }

  for (int i = 0; i < n; ++i)
    std::cout << ans[i] << "\n";
}

```

</details>

## [F - Sorting Color Balls](https://atcoder.jp/contests/abc261/tasks/abc261_f)

<details>
<summary>题意</summary>

给$n$个数排序，支持交换相邻元素这一操作。

每个数还带一个颜色，交换同色元素不花费代价，否则花费$1$的代价。

问将$n$个数排成非降序的最小代价。

其中$1\le n \le 3 \times {10}^5$。

</details>

<details>
<summary>思路</summary>

观察可得：对于$x_i$，它对答案的贡献为：满足$j < i$且$x_j > x_i$且$c_j \ne c_i$的$j$的个数。即答案为满足$j < i$且$x_j > x_i$且$c_j \ne c_i$的二元组$(i, j)$的个数。

为了方便计算将代价拆成两部分：满足$j < i$且$x_j > x_i$的二元组$(i, j)$的个数 减去 满足$j < i$且$x_j > x_i$且$c_j = c_i$的二元组$(i, j)$的个数。

现在问题就是个逆序对计数，数据结构随便搞搞。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: F - Sorting Color Balls
// Contest: AtCoder - AtCoder Beginner Contest 261
// URL: https://atcoder.jp/contests/abc261/tasks/abc261_f
// Memory Limit: 1024 MB
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

template <typename ValueType>
class Treap {
 private:
  typedef int32_t size_t;

  struct Node {
    ValueType value;
    uint32_t priority;
    size_t size;
    Node* left;
    Node* right;
  };
  Node* root_;
  std::mt19937 rng_;

 private:
  Node* NewNode(ValueType value) {
    Node* p = new Node;
    p->value = value;
    p->priority = rng_();
    p->size = 1;
    p->left = p->right = nullptr;
    return p;
  }

  void Free(Node*& p) {
    if (p) {
      delete p;
      p = nullptr;
    }
  }

  size_t GetSize(Node* p) { return p ? p->size : 0; }

  void PushUp(Node* p) {
    if (!p)
      return;
    p->size = GetSize(p->left) + 1 + GetSize(p->right);
  }

  std::pair<Node*, Node*> SplitValue(Node* p, const ValueType& value) {
    if (!p)
      return {nullptr, nullptr};

    std::pair<Node*, Node*> result;
    if (p->value <= value) {
      auto right_result = SplitValue(p->right, value);
      p->right = right_result.first;

      result.first = p;
      result.second = right_result.second;
    } else {
      auto left_result = SplitValue(p->left, value);
      p->left = left_result.second;

      result.first = left_result.first;
      result.second = p;
    }
    PushUp(p);

    return result;
  }

  Node* Merge(Node* a, Node* b) {
    if (a == nullptr)
      return b;
    else if (b == nullptr)
      return a;

    Node* result;
    if (a->priority < b->priority) {
      result = a;
      a->right = Merge(a->right, b);
      PushUp(a);
    } else {
      result = b;
      b->left = Merge(a, b->left);
      PushUp(b);
    }

    return result;
  }

 public:
  Treap() : root_(nullptr), rng_(std::chrono::steady_clock::now().time_since_epoch().count()) {}

  ~Treap() {
    std::function<void(Node*)> dfs = [&](Node* p) -> void {
      if (!p)
        return;
      dfs(p->left);
      dfs(p->right);
      freep(p);
    };
    dfs(root_);
  }

  void Insert(const ValueType& value) {
    auto [a, b] = SplitValue(root_, value);
    a = Merge(a, NewNode(value));
    root_ = Merge(a, b);
  }

  void Delete(const ValueType& value) {
    auto [a, b] = SplitValue(root_, value);
    auto [c, d] = SplitValue(a, value - 1);

    assert(d);

    Node* temp = d;
    d = Merge(d->left, d->right);
    Free(temp);

    a = Merge(c, d);
    root_ = Merge(a, b);
  }

  size_t GetRank(const ValueType& value) {
    auto [a, b] = SplitValue(root_, value - 1);
    size_t result = GetSize(a) + 1;
    root_ = Merge(a, b);
    return result;
  }

  ValueType GetKth(size_t k) {
    assert(k <= GetSize(root_));
    Node* p = root_;

    ValueType result;
    while (p) {
      if (k <= GetSize(p->left)) {
        p = p->left;
      } else if (k == GetSize(p->left) + 1) {
        result = p->value;
        break;
      } else {
        k -= GetSize(p->left) + 1;
        p = p->right;
      }
    }
    return result;
  }

  ValueType GetPrev(const ValueType& value) {
    auto [a, b] = SplitValue(root_, value - 1);

    assert(a != nullptr);
    Node* c = a;
    while (c->right)
      c = c->right;
    ValueType result = c->value;

    root_ = Merge(a, b);

    return result;
  }

  ValueType GetNext(const ValueType& value) {
    auto [a, b] = SplitValue(root_, value);

    assert(b != nullptr);
    Node* c = b;
    while (c->left)
      c = c->left;
    ValueType result = c->value;

    root_ = Merge(a, b);

    return result;
  }

  size_t Get(const ValueType& value) {
    auto [a, b] = SplitValue(root_, value);
    size_t result = GetSize(b);
    root_ = Merge(a, b);
    return result;
  }
};
using Tp = Treap<int>;

std::mt19937 rng(114514);
int rnd(int l, int r) {
  return l + rng() % (r - l + 1);
}

void solve_case(int Case) {
  int n;
  std::cin >> n;

  std::vector<int> c(n), x(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> c[i];
    --c[i];
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> x[i];
  }

  std::vector<std::vector<int>> d(n);
  for (int i = 0; i < n; ++i) {
    d[c[i]].push_back(x[i]);
  }

  i64 ans = 0;
  Tp t;
  for (int i = 0; i < n; ++i) {
    ans += t.Get(x[i]);
    t.Insert(x[i]);
  }

  for (int i = 0; i < n; ++i) {
    Tp tp;
    for (int v : d[i]) {
      ans -= tp.Get(v);
      tp.Insert(v);
    }
  }

  std::cout << ans << "\n";
}


```

</details>

## [G - Replace](https://atcoder.jp/contests/abc261/tasks/abc261_g)

<details>
<summary>题意</summary>

给定初始串$s$和目标串$t$，以及$k$个转移$(c_i, a_i)$，表示可以将$s_i$中的一个字符$c_i$替换成$a_i$。

问将$s$变成$t$的最小转移次数。

其中$1 \le |s|, |t|, k, |a_i| \le 50$。

</details>

<details>
<summary>思路</summary>

动态规划。

记$s[l; r]$表示$s_{l}s_{l+1}\dots s_{r}$，$f(l, r, c)$表示从字符$c$变成$t[l; r - 1]$的最小操作次数，$g(l, r, i, j)$表示从$a_i[0; j - 1]$变成$t[l; r - 1]$的最小操作次数。

为方便讨论，记$a_{k}$为$s$。易得答案为$g_{0, |t|, k, |s|}$。

$f$的转移:
- $t[l; r]$匹配了完整的$a_i$时，那么就可以从$c_i$转移到$a_i$再转移到$t[l; r]$。即$g(l, r, i, |a_i|) + 1$可以用来更新$f(l, r, c_i)$。
- $|a_i| = 1$时，则可以从$c_i$转移到$a_i[0]$，即$f(l, r, x) + dis(x, y)$可以用来更新$f(l, r, y)$，其中$x, y$可以是任意字符，$dis(x, y)$表示从$x$转移到$y$的代价。这里的$dis$可以搞个最短路求。

$g$的转移：
- $t[l; r]$匹配了$a_i[0; j - 1]$时，在此基础上可以拓展$a_i[j]$从而匹配$t[l; r^\prime], r^\prime > r$。即对于$l \le m < r$，$g(l, m, i, j) + f(m, r, a_i[j])$可以用来更新$g(l, r, i, j + 1)$。
- $f(l, r, a_i[0])$可以用来更新$g(l, r, i, 1)$。

根据转移的特点，升序枚举$r$套降序枚举$l$，即可保证求解某个问题时，依赖的子问题已经全部解决，然后就可以愉快的转移了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: G - Replace
// Contest: AtCoder - AtCoder Beginner Contest 261
// URL: https://atcoder.jp/contests/abc261/tasks/abc261_g
// Memory Limit: 1024 MB
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
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

template <typename T>
std::vector<T> Vector(size_t n, T init) {
  return std::vector<T>(n, init);
}

template <typename T>
std::vector<std::vector<T>> Vector(size_t n, size_t m, T init) {
  using value_type = decltype(Vector<T>(0, T()));
  return std::vector<value_type>(n, Vector<T>(m, init));
}

template <typename T>
std::vector<std::vector<std::vector<T>>> Vector(size_t n, size_t m, size_t k, T init) {
  using value_type = decltype(Vector<T>(0, 0, T()));
  return std::vector<value_type>(n, Vector<T>(m, k, init));
}

template <typename T>
std::vector<std::vector<std::vector<std::vector<T>>>> Vector(size_t n,
                                                             size_t m,
                                                             size_t k,
                                                             size_t l,
                                                             T init) {
  using value_type = decltype(Vector<T>(0, 0, 0, T()));
  return std::vector<value_type>(n, Vector<T>(m, k, l, init));
}

const int INF = 0x3f3f3f3f;

void solve_case(int Case) {
  std::string S, T;
  std::cin >> S >> T;
  int N = S.size(), M = T.size();

  int K;
  std::cin >> K;
  std::string C(K + 1, '?');
  std::vector<std::string> A(K + 1);
  for (int i = 0; i < K; ++i) {
    std::cin >> C[i] >> A[i];
  }
  C[K] = '*';
  A[K] = S;

  auto trans = Vector<int>(26, 26, INF);
  for (int i = 0; i < K; ++i) {
    if (static_cast<int>(A[i].size()) == 1) {
      int u = C[i] - 'a';
      int v = A[i][0] - 'a';
      trans[v][u] = 1;
    }
  }
  for (int i = 0; i < 26; ++i)
    trans[i][i] = 0;
  for (int k = 0; k < 26; ++k) {
    for (int i = 0; i < 26; ++i) {
      for (int j = 0; j < 26; ++j) {
        trans[i][j] = std::min(trans[i][j], trans[i][k] + trans[k][j]);
      }
    }
  }

  auto f = Vector<int>(M + 1, M + 1, 26, INF);
  auto g = Vector<int>(M + 1, M + 1, K + 1, 51, INF);

  // DP
  // init.
  for (int i = 0; i < M; ++i) {
    f[i][i + 1][T[i] - 'a'] = 0;
  }
  for (int i = 0; i <= M; ++i) {
    for (int k = 0; k <= K; ++k) {
      g[i][i][k][0] = 0;
    }
  }

  // trans.
  for (int r = 1; r <= M; ++r) {
    for (int l = r - 1; l >= 0; --l) {
      for (int i = 0; i <= K; ++i) {
        int L = static_cast<int>(A[i].size());
        for (int j = 0; j < L; ++j) {
          for (int m = l; m < r; ++m) {
            g[l][r][i][j + 1] = std::min(g[l][r][i][j + 1], g[l][m][i][j] + f[m][r][A[i][j] - 'a']);
          }
        }
        if (i != K) {
          f[l][r][C[i] - 'a'] = std::min(f[l][r][C[i] - 'a'], g[l][r][i][L] + 1);
        }
      }

      for (int u = 0; u < 26; ++u) {
        for (int v = 0; v < 26; ++v) {
          f[l][r][u] = std::min(f[l][r][u], f[l][r][v] + trans[v][u]);
        }
      }

      for (int i = 0; i <= K; ++i) {
        g[l][r][i][1] = std::min(g[l][r][i][1], f[l][r][A[i][0] - 'a']);
      }
    }
  }

  int ans = g[0][M][K][N];
  if (ans == INF)
    ans = -1;
  std::cout << ans << "\n";
}

```

</details>

## [Ex - Game on Graph](https://atcoder.jp/contests/abc261/tasks/abc261_h)

<details>
<summary>题意</summary>

给一个$n$个点$m$条边的有向图，边带权。

两个人完游戏，点$S$上有一个棋子。假设某个时刻棋子位于点$u$，则此时的操作者可以选择点$v$并将棋子移动到点$v$，要求边$u \to v$存在，且代价为边权。无法移动棋子时游戏结束。

可能存在游戏无法结束的情况，先手想要避免这种情况，后手想要造成这种情况，此外，先手想要最小化代价，后手想要最大化代价，两个人都以最优策略玩游戏。

问游戏是否可以结束，如果可以的话结束时代价是多少。

其中$1 \le n \le 2 \times {10}^5, 0 \le m \le 2 \times {10}^5$。

</details>

<details>
<summary>思路</summary>

建议先做ABC209E。

这个题目就是在ABC209E的基础上，还要求代价最小或者最大。可以搞个优先队列优先考虑代价小的点，然后在后手玩家操作时手动选择代价大的后继。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: Ex - Game on Graph
// Contest: AtCoder - AtCoder Beginner Contest 261
// URL: https://atcoder.jp/contests/abc261/tasks/abc261_h
// Memory Limit: 1024 MB
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
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

struct Edge {
  int v, w;
};

void solve_case(int Case) {
  int n, m, S;
  std::cin >> n >> m >> S;
  --S;

  std::vector<std::vector<Edge>> g(n);
  std::vector<int> deg(n, 0);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    --u, --v;
    g[v].push_back((Edge){u, w});
    ++deg[u];
  }

  std::vector<std::vector<i64>> dp(n, std::vector<i64>(2, -1));
  std::vector<i64> mx(n, 0);
  std::priority_queue<std::tuple<i64, int, int>, std::vector<std::tuple<i64, int, int>>,
                      std::greater<std::tuple<i64, int, int>>>
      q;
  for (int i = 0; i < n; ++i) {
    if (deg[i] == 0) {
      q.push(std::make_tuple(INT64_C(0), i, 0));
      q.push(std::make_tuple(INT64_C(0), i, 1));
    }
  }
  while (!q.empty()) {
    auto [x, u, t] = q.top();
    q.pop();

    if (dp[u][t] != -1)
      continue;
    dp[u][t] = x;

    if (t == 0) {
      for (auto [v, w] : g[u]) {
        mx[v] = std::max(mx[v], x + w);
        --deg[v];
        if (deg[v] == 0) {
          q.push(std::make_tuple(mx[v], v, 1));
        }
      }
    } else {
      for (auto [v, w] : g[u]) {
        q.push(std::make_tuple(x + w, v, 0));
      }
    }
  }

  if (dp[S][0] == -1)
    std::cout << "INFINITY\n";
  else
    std::cout << dp[S][0] << std::endl;
}

```

</details>