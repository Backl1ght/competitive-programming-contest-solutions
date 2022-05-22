# 2022 Google Kick Start Round C

## [New Password](https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb4d1/0000000000b20f15)

<details>
<summary>题意</summary>

给一个字符串，问最少几步能补到满足下列条件：
- 长度至少为7
- 至少有一个小写字母
- 至少有一个大写字母
- 至少有一个数字
- 至少有一个特殊符号

</details>

<details>
<summary>思路</summary>

先补充到满足后面4个条件，大概就是每种类型的字符没有的话就随便加一个。

现在只可能不满足长度条件，可以添加任意字符知道长度大于等于7。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: New Password
// Contest: Google Coding Competitions - Round C 2022 - Kick Start 2022
// URL: https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb4d1/0000000000b20f15
// Memory Limit: 1024 MB
// Time Limit: 20000 ms
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
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

void solve_case(int Case) {
  std::cout << "Case #" << Case << ": ";
  int n;
  std::cin >> n;
  std::string s;
  std::cin >> s;

  {
    bool flag = false;
    for (char ch : s) {
      if (std::islower(ch))
        flag = true;
    }
    if (!flag)
      s += 'a';
  }

  {
    bool flag = false;
    for (char ch : s) {
      if (std::isupper(ch))
        flag = true;
    }
    if (!flag)
      s += 'A';
  }

  {
    bool flag = false;
    for (char ch : s) {
      if (std::isdigit(ch))
        flag = true;
    }
    if (!flag)
      s += '0';
  }

  {
    bool flag = false;
    for (char ch : s) {
      if (ch == '#' || ch == '@' || ch == '*' || ch == '&')
        flag = true;
    }
    if (!flag)
      s += '#';
  }
  while (s.size() < 7)
    s += '*';

  std::cout << s << "\n";
}

```

</details>

## [Range Partition](https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb4d1/0000000000b20deb)

<details>
<summary>题意</summary>

给一个$1$到$n$的排列，让你将其划分为两部分，要求两部分元素和之比为$x : y$。

$n$至多为$10^5$。

</details>

<details>
<summary>思路</summary>

总和可以算，比例已知，可以算出来其中一部分的元素之和。

然后就是用$[1, n]$去构造出这个元素和，经典结论，从大到小枚举，能用就用。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: Range Partition
// Contest: Google Coding Competitions - Round C 2022 - Kick Start 2022
// URL: https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb4d1/0000000000b20deb
// Memory Limit: 1024 MB
// Time Limit: 5000 ms
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
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

void solve_case(int Case) {
  std::cout << "Case #" << Case << ": ";
  int n, x, y;
  std::cin >> n >> x >> y;

  int s = (1 + n) * n / 2;
  if (s % (x + y) != 0) {
    std::cout << "IMPOSSIBLE\n";
    return;
  }

  i64 sa = i64(s) * x / (x + y);
  std::vector<int> ans;
  for (int i = n; i >= 1; --i) {
    if (sa >= i) {
      ans.push_back(i);
      sa -= i;
    }
  }

  std::cout << "POSSIBLE\n";
  std::cout << ans.size() << "\n";
  for (int i = 0; i < ans.size(); ++i)
    std::cout << ans[i] << " \n"[i + 1 == ans.size()];
}

```

</details>

## [Ants on a Stick](https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb4d1/0000000000b209bc)

<details>
<summary>题意</summary>

$n$只蚂蚁，在长为$L$的树枝上运动。

所有蚂蚁的移动速率恒定为$1$，但是方向可能不同，两只蚂蚁相遇之后会立刻翻转方向，不会产生位移。

树枝两侧都可以离开树枝，蚂蚁一旦走出树枝的范围就不会再对其他蚂蚁产生影响。

给蚂蚁的初始位置和初始运动方向，要求给出蚂蚁离开树枝范围的顺序，相同时间离开的蚂蚁按下标升序。

$n$至多为$10^5$。

</details>

<details>
<summary>思路</summary>

观察：两只蚂蚁相遇其实相当于两只蚂蚁交换初始位置和方向，然后继续运动。

由此可以推导出离开树枝的时间只和蚂蚁的初始位置和方向有关。

首先按初始位置排序，左侧的蚂蚁如果向左走那就直接离开了，记录前面向右走的蚂蚁。

假设现在遇到一只向左走的蚂蚁，观察可得：相当于把向左走的蚂蚁加入序列，然后将序列**循环右移**一个位置。此时最左侧的蚂蚁变成向左走的了，将其弹出序列。

这里，循环右移过程中只交换初始位置和方向，不交换标号。

模拟一遍得到最后的序列，然后就可以算出每个标号的蚂蚁离开树枝的时间，然后再排序一下就能得到答案。

$O(n)$模拟实现循环右移，复杂度为$O(n^2)$，可以过前两个点。用平衡树模拟区间操作复杂度为$O(n \log n)$，可以过所有点。

</details>

<details>
<summary>线性模拟实现</summary>

```cpp
// Problem: Ants on a Stick
// Contest: Google Coding Competitions - Round C 2022 - Kick Start 2022
// URL: https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb4d1/0000000000b209bc
// Memory Limit: 1024 MB
// Time Limit: 20000 ms
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
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

void solve_case(int Case) {
  logd(Case);
  std::cout << "Case #" << Case << ": ";
  int n, l;
  std::cin >> n >> l;

  std::vector<std::array<int, 3>> a(n);
  for (int i = 0; i < n; ++i) {
    int p, d;
    std::cin >> p >> d;
    a[i] = {p, d, i};
  }
  std::sort(a.begin(), a.end());

  std::vector<int> q;
  for (int i = 0; i < n; ++i) {
    q.push_back(i);

    if (a[i][1] == 0) {
      logd(q);
      if (!q.empty()) {
        auto temp = a[q[q.size() - 1]];
        for (int i = q.size() - 1; i >= 1; --i) {
          a[q[i]][0] = a[q[i - 1]][0];
          a[q[i]][1] = a[q[i - 1]][1];
        }
        a[q[0]][0] = temp[0];
        a[q[0]][1] = temp[1];
        q.erase(q.begin());
      }
      logd(a, q);
    }
  }

  std::vector<int> t(n);
  for (int i = 0; i < n; ++i) {
    auto [p, d, id] = a[i];
    if (d == 0)
      t[id] = p;
    else
      t[id] = l - p;
  }
  logd(t);

  std::vector<int> id(n);
  std::iota(id.begin(), id.end(), 0);
  std::sort(id.begin(), id.end(), [&t](int x, int y) {
    if (t[x] == t[y])
      return x < y;
    return t[x] < t[y];
  });
  for (int i = 0; i < n; ++i)
    std::cout << id[i] + 1 << " \n"[i + 1 == n];
}

```

</details>

<details>
<summary>平衡树模拟实现</summary>

```cpp
// Problem: Ants on a Stick
// Contest: Google Coding Competitions - Round C 2022 - Kick Start 2022
// URL: https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb4d1/0000000000b209bc
// Memory Limit: 1024 MB
// Time Limit: 20000 ms
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
  std::cin >> T;
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
    // logd(get_size(a), get_size(b));
    split_size(b, 1, c, d);
    // logd(get_size(c), get_size(d));
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

  void debug() {
    std::function<void(node*)> dfs = [&](node* p) {
      if (!p)
        return;
      dfs(p->l);
      std::cerr << to_string(p->v) << " ";
      dfs(p->r);
    };
    dfs(root);
    std::cerr << std::endl;
  }
};

void solve_case(int Case) {
  logd(Case);
  std::cout << "Case #" << Case << ": ";
  int n, L;
  std::cin >> n >> L;

  std::vector<std::array<int, 3>> a(n);
  for (int i = 0; i < n; ++i) {
    int p, d;
    std::cin >> p >> d;
    a[i] = {p, d, i};
  }
  std::sort(a.begin(), a.end());

  Treap<std::pair<int, int>> T;
  std::vector<int> id(n);
  for (int i = 0; i < n; ++i) {
    T.ins(i + 1, std::make_pair(a[i][0], a[i][1]));
    // T.debug();
    id[i] = a[i][2];
  }

  int l = 0;
  for (int i = 0; i < n; ++i) {
    if (a[i][1] == 0) {
      T.right_rotate(l + 1, i + 1);
      logd(l, i);
      // T.debug();

      ++l;
    }
  }

  std::vector<int> t(n);
  for (int i = 0; i < n; ++i) {
    logd(i);
    std::pair<int, int> x = T.qry(i + 1);
    logd(i, x);
    auto [p, d] = x;
    if (d == 0)
      t[id[i]] = p;
    else
      t[id[i]] = L - p;
  }
  logd(t);

  std::iota(id.begin(), id.end(), 0);
  std::sort(id.begin(), id.end(), [&t](int x, int y) {
    if (t[x] == t[y])
      return x < y;
    return t[x] < t[y];
  });
  for (int i = 0; i < n; ++i)
    std::cout << id[i] + 1 << " \n"[i + 1 == n];
}

```

</details>

## [Palindromic Deletions](https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb4d1/0000000000b20d16)

<details>
<summary>题意</summary>

给定一个字符串$s$，其长度为$n$。你需要完成下面这一操作共$n$次，问得分的期望。

- 随机选择$s$一个字符，将其删去，得到一个新的$s$
- 如果这个新的$s$是回文串，得一分

</details>

<details>
<summary>思路</summary>

第一个点随便暴力就过了。

第二个点的话，观察可得：对于某个长度为$k$的回文子序列，他对答案的贡献为$\frac{k! (n - k)!}{n!}$。具体含义为先把$n - k$个字符删掉，共$(n - k)!$种方案，然后这$k$个字符后续也要删掉，共$k!$种方案，因为完全随机，所以概率为$\frac{k! (n - k)!}{n!}$。

然后只需要求出长度为$k$的回文子序列有几个，再乘上概率就是期望了。可以借助DP求长度为$k$的回文子序列数量。

假设$dp_{k, l, r}$表示$s_{l}s_{l+1}\dots s_{r}$构成的长度为$k$的回文子序列数量。长度为$0$和长度为$1$的可以直接算。

对于$k >= 2$，如果$s_l = s_r$，那么就可以在所有由$s_{l+1}s_{l+2}\dots s_{r-1}$构成的回文子序列的基础上获得新的长度为$k$的回文子序列，数量为$dp_{k - 2, l + 1, r - 1}$；否则没有新增的回文子序列，通过容斥可得这部分为$dp_{k, l + 1, r} + dp_{k, l, r - 1} - dp_{k, l + 1, r - 1}$。

然后就是$O(n^3)$DP跑出所有$dp_{k, 0, n - 1}$然后算期望了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: Palindromic Deletions
// Contest: Google Coding Competitions - Round C 2022 - Kick Start 2022
// URL: https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb4d1/0000000000b20d16
// Memory Limit: 1024 MB
// Time Limit: 30000 ms
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
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

const int mod = 1e9 + 7;
int qp(int a, int b) {
  int r = 1;
  while (b) {
    if (b & 1)
      r = i64(1) * r * a % mod;
    a = i64(1) * a * a % mod;
    b >>= 1;
  }
  return r;
}

int inv(int x) {
  return qp(x, mod - 2);
}

int slow(int n, std::string s) {
  int ans = 0;
  if (n <= 8) {
    std::function<void(std::string s, int)> dfs = [&](std::string s, int p) -> void {
      p = i64(1) * p * inv(s.size()) % mod;
      for (int i = 0; i < s.size(); ++i) {
        std::string t = s.substr(0, i) + s.substr(i + 1);
        // logd(p, t);
        std::string r = t;
        std::reverse(r.begin(), r.end());
        if (t == r) {
          ans = (ans + p) % mod;
        }
        if (!t.empty())
          dfs(t, p);
      }
    };
    dfs(s, 1);
  } else {
    assert(false);
  }
  return ans;
}

int fast(int n, std::string s) {
  int ans = 0;

  std::vector<int> fact(n + 1);
  fact[0] = 1;
  for (int i = 1; i <= n; ++i)
    fact[i] = i64(1) * fact[i - 1] * i % mod;

  std::vector<std::vector<std::vector<int>>> dp(
      n + 1, std::vector<std::vector<int>>(n, std::vector<int>(n, 0)));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      dp[0][i][j] = 1;
      dp[1][i][j] = std::max(0, j - i + 1);
    }
  }
  for (int k = 2; k <= n; ++k) {
    for (int len = 2; len <= n; ++len) {
      for (int i = 0; i + len - 1 < n; ++i) {
        int j = i + len - 1;
        dp[k][i][j] = (dp[k][i][j] + dp[k][i + 1][j]) % mod;
        dp[k][i][j] = (dp[k][i][j] + dp[k][i][j - 1]) % mod;
        dp[k][i][j] = ((dp[k][i][j] - dp[k][i + 1][j - 1]) % mod + mod) % mod;
        if (k >= 2 && s[i] == s[j])
          dp[k][i][j] = (dp[k][i][j] + dp[k - 2][i + 1][j - 1]) % mod;
      }
    }
  }
  logd(dp);
  for (int k = 0; k < n; ++k) {
    ans = (ans + i64(1) * dp[k][0][n - 1] * fact[k] % mod * fact[n - k] % mod) % mod;
  }
  ans = i64(1) * ans * inv(fact[n]) % mod;
  return ans;
}

void solve_case(int Case) {
  logd(Case);
  std::cout << "Case #" << Case << ": ";
  int n;
  std::cin >> n;
  std::string s;
  std::cin >> s;

  int ans = fast(n, s);
  std::cout << ans << "\n";
#ifdef BACKLIGHT
  if (n <= 8) {
    int S = slow(n, s);
    logd(S, ans);
    // assert(S == ans);
  }
#endif
}

```

</details>