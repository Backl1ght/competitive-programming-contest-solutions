# NOMURA Programming Contest 2022（AtCoder Beginner Contest 253）

A就是模拟一下。

B就是曼哈顿距离。

C就是`std::map`搞一搞。

D就是容斥一下。

## [E - Distance Sequence](https://atcoder.jp/contests/abc253/tasks/abc253_e)

<details>
<summary>题意</summary>

问满足下列条件的数组$a$有多少种：
- 长度为$n$
- 值域为$[1, m]$
- 相邻元素差值的绝对值大于$k$

其中$n \le 1000, m \le 5000, k \le m - 1$。

</details>

<details>
<summary>思路</summary>

$O(nm)$的DP就能搞定。

令$dp_{i, j}$表示长度为$i$，满足题目给定条件，且$a_i = j$的方案数。

那么有$dp_{i, j} = \sum_{|x - j| \ge k} dp_{i - 1, x}$，朴素的做法是$O(nm^2)$的。

注意到其实满足条件的$x$其实是$[1, i - k] \cup [i + k, m]$，加个前缀和优化就能做到$O(nm)$了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: E - Distance Sequence
// Contest: AtCoder - NOMURA Programming Contest 2022（AtCoder Beginner Contest 253）
// URL: https://atcoder.jp/contests/abc253/tasks/abc253_e
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
  int mod = 998244353;

  int n, m, k;
  std::cin >> n >> m >> k;

  if (k == 0) {
    int ans = 1;
    for (int i = 1; i <= n; ++i)
      ans = i64(1) * ans * m % mod;
    std::cout << ans << "\n";
    return;
  }

  std::vector<int> dp(m + 1);
  for (int i = 1; i <= m; ++i)
    dp[i] = 1;

  for (int _ = 2; _ <= n; ++_) {
    auto temp = dp;
    for (int j = 1; j <= m; ++j)
      temp[j] = (temp[j] + temp[j - 1]) % mod;

    for (int j = 1; j <= m; ++j) {
      dp[j] = 0;
      if (j - k >= 1) {
        dp[j] = (dp[j] + ((temp[j - k] - temp[0]) % mod + mod) % mod) % mod;
      }
      if (j + k <= m) {
        dp[j] = (dp[j] + ((temp[m] - temp[j + k - 1]) % mod + mod) % mod) % mod;
      }
    }
  }

  int ans = 0;
  for (int i = 1; i <= m; ++i)
    ans = (ans + dp[i]) % mod;

  std::cout << ans << "\n";
}
```
</details>

## [F - Operations on a Matrix](https://atcoder.jp/contests/abc253/tasks/abc253_f)

<details>
<summary>题意</summary>

给定一个$n$行$m$列的矩阵，初始是矩阵中元素全为0，要求支持$q$个操作，操作共有一下3种：
1. `1 l r x`： 给第$l$列到第$r$列的元素都加上$x$。
2. `2 i x`： 将第$i$行的元素都置为$x$。
3. `3 i j`： 输出当前第$i$行第$j$列元素的值。

其中，$n, m, q \le 2 \times 10^5$。

</details>

<details>
<summary>思路1</summary>

对于第1个操作，用可持久化线段树维护。

对于第2个操作，操作时记录下当时可持久化线段树的版本号以及$x$。

对于第3个操作，假设第$i$行维护的版本号为$old$，操作数为$x$。当前的版本号为$now$，则答案为$x + sum(now, j, j) - sum(old, j, j)$。其中$sum(v, l, r)$表示可持久化线段树第$i$个版本中区间$[l, r]$元素之和。

然后就是可持久化线段树区间加操作的维护了，指路HDU 4348。

</details>

<details>
<summary>思路2</summary>

可以借助离散化进一步简化问题。

对于每个操作3，它其实只和上一次修改第$i$行的操作2有关，可以把操作3挂到操作2上。

假设某个操作2$(i, x)$之前，操作1在第$j$行上共加了$A$。对于某个操作3$(i, j)$，假设上一句提到的$(i, x)$为该操作3前最后一个修改第$i$行，且此时操作1在第$j$行上共加了$B$，那么该操作3的答案为$x + B - A$。

$B$的话临时查寻即可，$x$和$B$的话就是把操作3挂到操作2上，然后在操作2操作的时候就加上。

现在就不需要可持久化了，普通线段树或者树状数组都可以搞。

</details>

<details>
<summary>思路1 AC代码</summary>

```cpp
// Problem: F - Operations on a Matrix
// Contest: AtCoder - NOMURA Programming Contest 2022（AtCoder Beginner Contest 253）
// URL: https://atcoder.jp/contests/abc253/tasks/abc253_f
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

// persistant segment tree with lazy tag.
const int maxn = 2e5 + 5;
const int SIZE = maxn << 5;
#define ll long long
#define lson l, m
#define rson m + 1, r

int rt[maxn], ls[SIZE], rs[SIZE], sz;
ll sum[SIZE], lazy[SIZE];

void pushup(int rt, int m) {
  sum[rt] = sum[ls[rt]] + sum[rs[rt]] + (ll)lazy[rt] * m;
}

void build(int& rt, int l, int r) {
  rt = ++sz;
  lazy[rt] = 0;
  if (l == r) {
    sum[rt] = 0;
    return;
  }

  int m = (l + r) >> 1;
  build(ls[rt], lson);
  build(rs[rt], rson);
  pushup(rt, r - l + 1);
}

void update(int pre, int& rt, int L, int R, int l, int r, ll c) {
  rt = ++sz;
  lazy[rt] = lazy[pre];
  sum[rt] = sum[pre];
  ls[rt] = ls[pre];
  rs[rt] = rs[pre];
  if (L <= l && r <= R) {
    lazy[rt] += c;
    sum[rt] += (ll)c * (r - l + 1);
    return;
  }

  int m = (l + r) >> 1;
  if (L <= m)
    update(ls[pre], ls[rt], L, R, lson, c);
  if (R > m)
    update(rs[pre], rs[rt], L, R, rson, c);
  pushup(rt, r - l + 1);
}

ll query(int rt, int L, int R, int l, int r) {
  if (L <= l && r <= R) {
    return sum[rt];
  }

  ll ret = (ll)lazy[rt] * (R - L + 1);
  int m = (l + r) >> 1;
  if (R <= m)
    ret += query(ls[rt], L, R, lson);
  else if (L > m)
    ret += query(rs[rt], L, R, rson);
  else
    ret += query(ls[rt], L, m, lson) + query(rs[rt], m + 1, R, rson);
  return ret;
}

void solve_case(int Case) {
  int n, m, q;
  std::cin >> n >> m >> q;

  int version = 0;
  sz = 0;
  build(rt[version], 1, m);

  std::vector<std::pair<int, int>> row(n + 1, std::pair(0, 0));

  for (int i = 1; i <= q; ++i) {
    int op;
    std::cin >> op;
    if (op == 1) {
      int l, r, x;
      std::cin >> l >> r >> x;
      ++version;
      update(rt[version - 1], rt[version], l, r, 1, m, x);
    } else if (op == 2) {
      int p, x;
      std::cin >> p >> x;
      row[p] = std::pair<int, int>(x, version);
    } else if (op == 3) {
      int x, y;
      std::cin >> x >> y;
      int old_version = row[x].second;
      ll ans = row[x].first + query(rt[version], y, y, 1, m) - query(rt[old_version], y, y, 1, m);
      std::cout << ans << "\n";
    }
  }
}

```

</details>
<details>
<summary>思路2 AC代码</summary>

```cpp
// Problem: F - Operations on a Matrix
// Contest: AtCoder - NOMURA Programming Contest 2022（AtCoder Beginner Contest 253）
// URL: https://atcoder.jp/contests/abc253/tasks/abc253_f
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
struct FenwickTree {
  int n;
  std::vector<T> c;
  FenwickTree(int _n) : n(_n), c(n + 1) {}
  inline int lb(int x) { return x & -x; }
  void add(int x, T d) {
    for (; x <= n; x += lb(x))
      c[x] += d;
  }
  T getsum(int x) {
    T r = 0;
    for (; x; x -= lb(x))
      r += c[x];
    return r;
  }
  T getsum(int l, int r) { return getsum(r) - getsum(l - 1); }
};

void solve_case(int Case) {
  int n, m, q;
  std::cin >> n >> m >> q;

  FenwickTree<i64> t(m);
  std::vector<std::array<int, 4>> a(q + 1);
  std::vector<std::vector<int>> QueryAt(q + 1);
  std::vector<int> last(n + 1);

  std::vector<i64> ans;

  for (int i = 1; i <= q; ++i) {
    int op;
    std::cin >> op;

    if (op == 1) {
      int l, r, d;
      std::cin >> l >> r >> d;
      a[i] = {op, l, r, d};
    } else if (op == 2) {
      int x, d;
      std::cin >> x >> d;
      a[i] = {op, x, d, i};

      last[x] = i;
    } else if (op == 3) {
      int x, y;
      std::cin >> x >> y;

      int ans_id = ans.size();
      ans.push_back(0);

      a[i] = {op, x, y, ans_id};

      int last_x = last[x];
      QueryAt[last_x].push_back(i);
    }
  }

  for (int i = 1; i <= q; ++i) {
    int op = a[i][0];
    if (op == 1) {
      auto [_, l, r, d] = a[i];
      t.add(l, d);
      t.add(r + 1, -d);
    } else if (op == 2) {
      auto [_1, _2, d, _3] = a[i];

      for (int query_id : QueryAt[i]) {
        auto [_1, _2, y, ans_id] = a[query_id];
        ans[ans_id] += d;
        ans[ans_id] -= t.getsum(y);
      }
    } else if (op == 3) {
      auto [_1, _2, y, ans_id] = a[i];
      ans[ans_id] += t.getsum(y);
    }
  }

  for (int i = 0; i < ans.size(); ++i)
    std::cout << ans[i] << "\n";
}


```

</details>

## [G - Swap Many Times](https://atcoder.jp/contests/abc253/tasks/abc253_g)

<details>
<summary>题意</summary>

将所有满足$1 \le x < y \le n$的二元组按字典序排序，其中第$i$个记为$(x_i, y_i)$。

现在给定一个长度为$n$的数组$a_i = i$，给定$L, R$，对于$i = L \dots R$，依次对换$a_{x_i}和a_{y_i}$的值。

输出操作完之后的$a$。

</details>

<details>
<summary>思路1</summary>

对于二元组$(x_i, y_i)$，将其放到第$x_i$行。

特判需要操作的区间占某一行中间的情况。

对于剩余情况，可以发现需要操作的二元组可以分成3个部分：第$x$行末尾，第$x+1$行到$y-1$行全部，和第$y$行的开头。

**观察1**：如果第$i$行的二元组都操作，相当于将$a_i,\dots a_n$循环右移。有$O(n)$行的二元组满足行中二元组都要操作。

**观察2**：剩余操作至多占两行，也就是$O(n)$个操作。

借助平衡树维护区间信息，两个操作都可以单次$O(\log n)$搞，总的时间复杂度为$O(n \log n)$。

</details>

<details>
<summary>思路2</summary>

在思路1的基础上进行优化。

**观察3**:第$x+1$行到$y-1$行全都操作，相当于翻转$a_{x+1} \dots a_n$，然后再翻转$a_{y} \dots a_n$。

根据这个就可以$O(n)$搞了，第$x$行末尾暴力搞，第$x+1$行到$y-1$行的操作拆成了两次翻转，第$y$行开头暴力搞，总的时间复杂度为$O(n)$。

</details>

<details>
<summary>思路1 AC代码</summary>

```cpp
// Problem: G - Swap Many Times
// Contest: AtCoder - NOMURA Programming Contest 2022（AtCoder Beginner Contest 253）
// URL: https://atcoder.jp/contests/abc253/tasks/abc253_g
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

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
struct Treap {
  struct node {
    node *l, *r;
    unsigned rnd;
    T v;
    int sz;
    node(T _v) : l(NULL), r(NULL), rnd(rng()), sz(1), v(_v) {}
  };

  inline int get_size(node*& p) { return p ? p->sz : 0; }

  inline void push_up(node*& p) {
    if (!p)
      return;
    p->sz = get_size(p->l) + get_size(p->r) + 1;
  }

  node* root = NULL;

  node* merge(node* a, node* b) {
    if (!a)
      return b;
    if (!b)
      return a;
    if (a->rnd < b->rnd) {
      a->r = merge(a->r, b);
      push_up(a);
      return a;
    } else {
      b->l = merge(a, b->l);
      push_up(b);
      return b;
    }
  }

  void split_val(node* p, const T& k, node*& a, node*& b) {
    if (!p)
      a = b = NULL;
    else {
      if (p->v <= k) {
        a = p;
        split_val(p->r, k, a->r, b);
        push_up(a);
      } else {
        b = p;
        split_val(p->l, k, a, b->l);
        push_up(b);
      }
    }
  }

  void split_size(node* p, int k, node*& a, node*& b) {
    if (!p)
      a = b = NULL;
    else {
      if (get_size(p->l) < k) {
        a = p;
        split_size(p->r, k - get_size(p->l) - 1, a->r, b);
        push_up(a);
      } else {
        b = p;
        split_size(p->l, k, a, b->l);
        push_up(b);
      }
    }
  }

  void ins(int p, T val) {
    node *a, *b;
    split_size(root, p - 1, a, b);
    a = merge(a, new node(val));
    root = merge(a, b);
  }

  void del(T val) {
    node *a, *b, *c, *d;
    split_val(root, val, a, b);
    split_val(a, val - 1, c, d);
    node* e = d;
    d = merge(d->l, d->r);
    delete e;
    a = merge(c, d);
    root = merge(a, b);
  }

  T qry(int p) {
    node *a, *b, *c, *d;
    split_size(root, p - 1, a, b);
    split_size(b, 1, c, d);
    T result = c->v;
    b = merge(c, d);
    root = merge(a, b);
    return result;
  }

  void right_rotate(int l, int r) {
    node *a, *b, *c, *d;
    split_size(root, l - 1, a, b);
    split_size(b, r - l + 1, c, d);

    {
      node *e, *f;
      split_size(c, r - l, e, f);
      c = merge(f, e);
    }

    b = merge(c, d);
    root = merge(a, b);
  }

  void swap(int l, int r) {
    node *a, *b, *c, *d;
    split_size(root, l - 1, a, b);
    split_size(b, r - l + 1, c, d);

    {
      node *e, *f;
      split_size(c, r - l, e, f);

      node *g, *h;
      split_size(e, 1, g, h);

      e = merge(f, h);
      c = merge(e, g);
    }

    b = merge(c, d);
    root = merge(a, b);
  }

  void debug() {
#ifdef BACKLIGHT
    std::function<void(node*)> dfs = [&](node* p) {
      if (!p)
        return;
      dfs(p->l);
      std::cerr << to_string(p->v) << " ";
      dfs(p->r);
    };
    dfs(root);
    std::cerr << std::endl;
#endif
  }
};

void solve_case(int Case) {
  int n;
  std::cin >> n;

  i64 l, r;
  std::cin >> l >> r;

  Treap<int> t;
  for (int i = 1; i <= n; ++i)
    t.ins(i, i);
  t.debug();

  i64 L = 1, R = 0;
  int len = n - 1;
  for (int i = 1; i <= n - 1; ++i) {
    L = R + 1;
    R = L + len - 1;
    --len;

    if (R < l)
      continue;
    if (L > r)
      continue;

    if (L >= l && R <= r) {
      t.right_rotate(i, n);
      logd("S", i);
      t.debug();
      continue;
    }

    int j = i + 1;
    i64 y = L;
    while (y < l) {
      ++j;
      ++y;
    }
    while (y <= r && y <= R) {
      t.swap(i, j);
      ++j;
      ++y;
    }
  }

  for (int i = 1; i <= n; ++i)
    std::cout << t.qry(i) << " \n"[i == n];
}

```

</details>

<details>
<summary>思路2 AC代码</summary>

```cpp
// Problem: G - Swap Many Times
// Contest: AtCoder - NOMURA Programming Contest 2022（AtCoder Beginner Contest 253）
// URL: https://atcoder.jp/contests/abc253/tasks/abc253_g
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
  int n;
  std::cin >> n;

  i64 l, r;
  std::cin >> l >> r;

  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i)
    a[i] = i;

  i64 L = 1, R = 0;
  int len = n - 1;
  int st = -1, ed = -1, flag = 0;
  for (int i = 1; i <= n - 1; ++i) {
    L = R + 1;
    R = L + len - 1;
    --len;

    if (R < l)
      continue;
    if (L > r)
      continue;

    if (L >= l && R <= r) {
      if (st == -1)
        st = i;
      ed = i;
      logd(st, ed);
      continue;
    }

    if (flag == 0 && st != -1) {
      std::reverse(a.begin() + st, a.end());
      std::reverse(a.begin() + ed + 1, a.end());
      flag = 1;
    }

    int j = i + 1;
    i64 y = L;
    while (y < l) {
      ++j;
      ++y;
    }
    while (y <= r && y <= R) {
      std::swap(a[i], a[j]);
      ++j;
      ++y;
    }
  }
  if (flag == 0 && st != -1) {
    std::reverse(a.begin() + st, a.end());
    std::reverse(a.begin() + ed + 1, a.end());
    flag = 1;
  }

  for (int i = 1; i <= n; ++i)
    std::cout << a[i] << " \n"[i == n];
}

```

</details>


## [Ex - We Love Forest](https://atcoder.jp/contests/abc253/tasks/abc253_h)

<details>
<summary>题意</summary>

一张有$n$个点的图$G$，一开始边集为空。

接下来$N - 1$轮，每轮等概率从$[1, m]$选择一个整数$i$，将边$(u_i, v_i)$加入边集。

问每一轮过后，$G$是一个森林的概率。

$n \le 14, m \le 500$。

</details>

<details>
<summary>思路</summary>

官方题解要用到矩阵树定理，然而我不会，有篇用户题解用DP搞出来了。

假设$V$表示G的点集，$d(X, Y)$表示一端属于$X$另一端属于$Y$的边的数量，$f(S)$表示点集为$S$的树的数量，$g_i(S)$表示点集为$S$且包含$i$条边的森林数量。

因为等概率，所以是古典概率模型，即有

$$
prob_i = \frac{i! g_i(V)}{m^i}.
$$
其中，$i!$是因为边加入顺序的排列。

现在只需要求$g_i(V)$，这里可以用DP求，即

$$
g_i(S) = \sum_{T \subset S} f(T) g_{i - (|T| - 1)}(S \setminus T).
$$
$O(n)$枚举$i$，$O(3^n)$可以枚举所有的$(S, T)$，进而求出$g_i(V)$，这一步的复杂度为$O(n3^n)$。

现在只需要求$f(S)$了，这个还是可以DP求，即

$$
f(S) = 
\left\{
\begin{array}{ll}
1 & |S| \le 1\\
\frac{1}{2(|S| - 1)} \sum_{T \subset S} f(T) f(S \setminus T) d(T, S \setminus T) & \text{otherwise}\\
\end{array}
\right.
.
$$
其中，除$2$是因为$(T, S \setminus T)$和$(S \setminus T, T)$这两个算了两次，除$|S| - 1$是因为树$S$可以看成两个子集合通过一条边合并起来的，每条边都会算一次。

这里直接$O(3^n)$枚举子集算就可以了。

然后这里的$d(X, Y)$可以容斥，假设$e(S)$表示两端都在$S$中的边的数量，则$d(X, Y) = e(X \cup Y) - e(X) - e(Y)$。

然后$e(S)$的话直接暴力求就可以了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: Ex - We Love Forest
// Contest: AtCoder - NOMURA Programming Contest 2022（AtCoder Beginner Contest 253）
// URL: https://atcoder.jp/contests/abc253/tasks/abc253_h
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

template <typename ValueType, ValueType mod_, typename SupperType = int64_t>
class Modular {
 private:
  ValueType value_;

  ValueType normalize(ValueType value) const {
    if (value >= 0 && value < mod_)
      return value;
    value %= mod_;
    if (value < 0)
      value += mod_;
    return value;
  }

  ValueType power(ValueType value, size_t exponent) const {
    ValueType result = 1;
    ValueType base = value;
    while (exponent) {
      if (exponent & 1)
        result = SupperType(result) * base % mod_;
      base = SupperType(base) * base % mod_;
      exponent >>= 1;
    }
    return result;
  }

 public:
  explicit Modular(const ValueType& value) : value_(normalize(value)) {}

  ValueType value() const { return value_; }

  Modular inv() const { return Modular(power(value_, mod_ - 2)); }

  Modular power(size_t exponent) const { return Modular(power(value_, exponent)); }

  friend Modular operator+(const Modular& lhs, const Modular& rhs) {
    ValueType result = lhs.value() + rhs.value() >= mod_ ? lhs.value() + rhs.value() - mod_
                                                         : lhs.value() + rhs.value();
    return Modular(result);
  }

  friend Modular operator-(const Modular& lhs, const Modular& rhs) {
    ValueType result = lhs.value() - rhs.value() < 0 ? lhs.value() - rhs.value() + mod_
                                                     : lhs.value() - rhs.value();
    return Modular(result);
  }

  friend Modular operator*(const Modular& lhs, const Modular& rhs) {
    ValueType result = SupperType(1) * lhs.value() * rhs.value() % mod_;
    return Modular(result);
  }

  friend Modular operator/(const Modular& lhs, const Modular& rhs) {
    ValueType result = SupperType(1) * lhs.value() * rhs.inv().value() % mod_;
    return Modular(result);
  }
};
template <typename ValueType, ValueType mod, typename SupperType = int64_t>
std::string to_string(Modular<ValueType, mod, SupperType> modular) {
  return std::to_string(modular.value());
}
// using Mint = Modular<int, 1'000'000'007>;
using Mint = Modular<int, 998'244'353>;

void solve_case(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<Mint> e(1 << n, Mint(0));
  for (int _ = 0; _ < m; ++_) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;

    for (int mask = 0; mask < (1 << n); ++mask) {
      if ((mask >> u & 1) && (mask >> v & 1)) {
        e[mask] = e[mask] + Mint(1);
      }
    }
  }

  auto d = [&](int s, int t) -> Mint { return e[s | t] - e[s] - e[t]; };

  // calc f
  std::vector<Mint> f(1 << n, Mint(0));
  for (int s = 0; s < (1 << n); ++s) {
    if (__builtin_popcount(s) <= 1) {
      f[s] = Mint(1);
      continue;
    }
    for (int t = s; t; t = (t - 1) & s) {
      f[s] = f[s] + f[t] * f[s ^ t] * d(t, s ^ t);
    }
    f[s] = f[s] / Mint(2) / Mint(__builtin_popcount(s) - 1);
  }
  logd(f);

  // calc g
  std::vector<std::vector<Mint>> g(n, std::vector<Mint>(1 << n, Mint(0)));
  for (int i = 0; i < n; ++i) {
    for (int s = 0; s < (1 << n); ++s) {
      if (__builtin_popcount(s) == i + 1) {
        g[i][s] = f[s];
      }
      int lsb = (s & -s);
      for (int t = s; t; t = (t - 1) & s) {
        if (t & lsb) {
          if (i - (__builtin_popcount(t) - 1) >= 0) {
            g[i][s] = g[i][s] + f[t] * g[i - (__builtin_popcount(t) - 1)][s ^ t];
          }
        }
      }
    }
  }
  logd(g);

  std::vector<Mint> fact(n, Mint(0)), pm(n, Mint(0));
  fact[0] = pm[0] = Mint(1);
  for (int i = 1; i < n; ++i) {
    fact[i] = fact[i - 1] * Mint(i);
    pm[i] = pm[i - 1] * Mint(m);
  }

  for (int i = 1; i <= n - 1; ++i) {
    Mint ans = g[i][(1 << n) - 1];
    ans = ans * fact[i];
    ans = ans / pm[i];
    std::cout << ans.value() << "\n";
  }
}

```

</details>