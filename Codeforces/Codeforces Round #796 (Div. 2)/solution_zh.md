# Codeforces Round #796 (Div. 2)

## [A. Cirno's Perfect Bitmasks Classroom](https://codeforces.com/contest/1688/problem/A)

<details>
<summary>题意</summary>

给定一个数$x$，输出满足$x \operatorname{and} y > 0$且$x \operatorname{xor} y > 0$的最小的$y$。

其中$1 \le x \le 2^{30}$。

</details>

<details>
<summary>思路</summary>

就是$y$和$x$的二进制表示至少要有一位不同，至少要有一位相同。

如果$x$的二进制里只有一个1，那么相同的那一位就确定了，还需要再把另外的一位变成1，贪心取最小的就可以了。

如果$x$的二进制表示有多个1，那么由于$y$要最小，所以$y$的二进制只会有一个1，贪心取最小的也就是$y$等于$x$的least significant bit。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: A. Cirno's Perfect Bitmasks Classroom
// Contest: Codeforces - Codeforces Round #796 (Div. 2)
// URL: https://codeforces.com/contest/1688/problem/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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
  int x, y;
  std::cin >> x;
  y = (x & -x);
  if (x == y) {
    if (x == 1)
      y += 2;
    else
      y += 1;
  }
  std::cout << y << "\n";
}

```

</details>

## [B. Patchouli's Magical Talisman](https://codeforces.com/contest/1688/problem/B)

<details>
<summary>题意</summary>

给定一个长度为$n$的数组$a$，给定以下两种操作：
1. 从$a$中选择两个数$a_i$和$a_j$，将这两个数从$a$中删除，然后再向$a$中插入$a_i + a_j$。
2. 从$a$中选择一个偶数$x$，将其替换成$\frac{x}{2}$。

问让$a$中不包含偶数的最小操作次数。

其中$1 \le n \le 2 \times {10}^5, 1 \le a_i \le {10}^9$。

</details>

<details>
<summary>思路</summary>

$a$中没有偶数，答案为零。

注意到，消除$a$中的一个偶数至少要用一个操作，而如果$a$中已经有奇数了，那么就可以将这个奇数依次和所有偶数合并，那么每个偶数都可以通过一次操作删除，已经是最优的了。

如果$a$中没有奇数，那么就看怎么用最小的代价通过操作2造出奇数，这个枚举一下就可以了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: B. Patchouli's Magical Talisman
// Contest: Codeforces - Codeforces Round #796 (Div. 2)
// URL: https://codeforces.com/contest/1688/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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

  int mi = INT_MAX;
  int c0 = 0, c1 = 0;
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;

    if (x % 2 == 0)
      ++c0;
    else
      ++c1;

    int t = 0;
    while (x % 2 == 0) {
      ++t;
      x = x / 2;
    }
    if (t != 0)
      mi = std::min(mi, t);
  }

  if (c0 == 0)
    std::cout << "0\n";
  else if (c1 != 0)
    std::cout << c0 << "\n";
  else
    std::cout << mi + n - 1 << "\n";
}


```

</details>

## [C. Manipulating History](https://codeforces.com/contest/1688/problem/C)

<details>
<summary>题意</summary>

有一个长度为$1$的初始字符串$s_0$，通过一个长度为$2n$的操作序列$t$，变成了$s_n$。

第$i$次操作就是将$s_{i - 1}$的一个子串$t_{2i - 1}$替换为$t_{2i}$，从而得到$s_i$，其中$1 \le i \le n$。

现在给出$s_n$和打乱了顺序的$t$，要求还原出$s_0$。

所有字符串的长度之和不超过$2 \times {10}^5$。

</details>

<details>
<summary>思路</summary>

这题卡了好久导致E想出来了没来得及做。感觉智商是越来越不行了。

$t$和$s_n$中的所有字符，只有初始字符会出现奇数次，所以统计字符出现的次数，出现奇数次的那个就是答案。

证明的话，假设$z$表示没有打乱顺序的操作序列，除去$z_1$，其他字符替换进$s_i$的时候会出现一次，被替换出$s_i$或者在$s_n$中会出现一次，所以一定是出现偶数次。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: C. Manipulating History
// Contest: Codeforces - Codeforces Round #796 (Div. 2)
// URL: https://codeforces.com/contest/1688/problem/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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

  std::vector<int> c(26, 0);
  for (int i = 0; i <= 2 * n; ++i) {
    std::string s;
    std::cin >> s;
    for (char ch : s) {
      ++c[ch - 'a'];
    }
  }
  logd(c);

  char ans = '?';
  for (int i = 0; i < 26; ++i) {
    if (c[i] & 1) {
      if (ans == '?') {
        ans = i + 'a';
      } else {
        assert(false);
      }
    }
  }
  std::cout << ans << "\n";
}

```

</details>

## [D. The Enchanted Forest](https://codeforces.com/contest/1688/problem/D)

<details>
<summary>题意</summary>

在$x$轴上有$n$个点，给定一个长度为$n$的数组$a_i$表示每个点上初始的资源数。

每一秒每个点还会刷新$1$个资源。

你可以在这$n$个点中随意取一个点作为起点，每一秒你可以不移动或者移动到相邻点，并收集所在点的资源。

问$k$秒能收集到的最大资源数。

其中$1 \le n \le 2 \times {10}^5, 1 \le k \le {10}^9, 1 \le a_i \le {10}^9$。

</details>

<details>
<summary>思路</summary>

可以将资源数拆分乘两部分算，一部分是初始的，一部分是后面刷新出来的。

假设$k < n$，那么第一部分借助前缀和可以线性算出最大值，第二部分是固定的直接高斯求和。

假设$k \ge n$，那么第一部分就是固定的了，第二部分有两种策略，第一种是$1 \rightarrow n \rightarrow 1 \dots$左右横跳，第二种是等资源长好了在一次收过去割韭菜。猜结论加模拟了一下发现第二种策略不劣于第一种，然后就是数数了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: D. The Enchanted Forest
// Contest: Codeforces - Codeforces Round #796 (Div. 2)
// URL: https://codeforces.com/contest/1688/problem/D
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
  int n, k;
  std::cin >> n >> k;

  std::vector<i64> a(n + 1);
  for (int i = 1; i <= n; ++i)
    std::cin >> a[i];

  if (n == 1) {
    i64 ans = a[1] + k - 1;
    std::cout << ans << "\n";
    return;
  }

  std::vector<i64> b(n + 1);
  for (int i = 1; i <= n; ++i)
    b[i] = b[i - 1] + a[i];

  i64 ans = 0;
  if (k < n) {
    i64 ma = 0;
    for (int i = k; i <= n; ++i)
      ma = std::max(ma, b[i] - b[i - k]);
    ans += ma;
    ans += i64(1) * (k - 1) * k / 2;
  } else {
    ans += b[n];
    ans += i64(1) * (n - 1) * n / 2;
    k -= n;
    ans += i64(1) * k * n;
  }

  std::cout << ans << "\n";
}

```

</details>

## [E. Railway System](https://codeforces.com/contest/1688/problem/E)

<details>
<summary>题意</summary>

交互题。

有张$n$个点$m$条边的图，每次你可以输出一个边的子集来询问这个子集的最大生成树。

你需要通过不超过$2m$次操作确定这个图的最小生成树。

其中$1 \le n \le 200, 1 \le m \le 500$。

</details>

<details>
<summary>思路1</summary>

剩半个小时做这题，思路是对的，但是交互题没有调出来，就差一点点，赛后没多久改了个if就过了。

首先，通过一次询问可以确定这个图的最大生成树。

然后，通过$m$次询问可以确定这个图每一条边的边权。

接下来$m - 1$次操作从权值大的边开始枚举，每次操作取确定当前枚举到的这条边是否属于最小生成树。只有$m - 1$次操作所以最小的那一条边没有询问次数来确定了，但是根据Kruskal算法的过程可以推出最小的那一条边一定会在最小生成树里面，所以不询问也不影响答案的正确性。

维护一个集合$E$，从全集开始，如果枚举到的边不属于最小生成树，那么就将其从$E$中删除，这样$m - 1$次操作完就能得到最小生成树了。假设当前枚举到的边为$e = (u, v, w)$，$E$对应的最大生成树权值为$V$，询问$E \setminus \{e\}$得到的最大生成树权值为$v$。如果$V - w < v$，那么就说明这条边不属于最小生成树。

</details>

<details>
<summary>思路2</summary>

写题解的时候突然发现搞复杂了，就$m$次询问确定边权，再$m$次询问用来跑Kruskal就可以了。<del>（我是弱智</del>

</details>

<details>
<summary>思路1 AC代码</summary>

```cpp
// Problem: E. Railway System
// Contest: Codeforces - Codeforces Round #796 (Div. 2)
// URL: https://codeforces.com/contest/1688/problem/E
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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

#undef BACKLIGHT

int main(int argc, char* argv[]) {
  CPPIO;
#ifdef BACKLIGHT
  int T = 10;
#else
  int T = 1;
#endif
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

std::mt19937 rng(time(0));
void solve_case(int Case) {
  int n, m;

#ifdef BACKLIGHT
  n = 200, m = 500;
  auto rnd = [&](int l, int r) { return l + rng() % (r - l + 1); };

  auto Kruskal = [&](std::vector<std::array<int, 3>> e, auto comp) {
    std::sort(e.begin(), e.end(), comp);
    std::vector<int> f(n);
    std::iota(f.begin(), f.end(), 0);
    std::function<int(int)> find = [&](int x) -> int {
      return x == f[x] ? x : (f[x] = find(f[x]));
    };

    int r = 0;
    for (auto [l, u, v] : e) {
      u = find(u);
      v = find(v);
      if (u == v)
        continue;
      r += l;
      f[u] = v;
    }
    return r;
  };

  std::vector<std::array<int, 3>> e(m);
  for (int i = 0; i < m; ++i) {
    int u = rnd(0, n - 1);
    int v;
    do {
      v = rnd(0, n - 1);
    } while (u == v);
    int l = rnd(1, 1e6);
    e[i] = {l, u, v};
  }
  int answer = Kruskal(e, [](std::array<int, 3> a, std::array<int, 3> b) { return a[0] < b[0]; });

  auto Q = [&](std::string s) {
    std::vector<std::array<int, 3>> e1;
    for (int i = 0; i < m; ++i) {
      if (s[i] == '1') {
        e1.push_back(e[i]);
      }
    }
    std::sort(e1.begin(), e1.end(),
              [](std::array<int, 3> a, std::array<int, 3> b) { return a[0] > b[0]; });

    std::vector<int> f(n);
    std::iota(f.begin(), f.end(), 0);
    std::function<int(int)> find = [&](int x) -> int {
      return x == f[x] ? x : (f[x] = find(f[x]));
    };

    int r = 0;
    for (auto [l, u, v] : e1) {
      u = find(u);
      v = find(v);
      if (u == v)
        continue;
      r += l;
      f[u] = f[v];
    }

    return r;
  };

#else
  std::cin >> n >> m;

  auto Q = [](std::string s) {
    std::cout << "? " << s << std::endl;
    int r;
    std::cin >> r;
    return r;
  };

#endif

  std::string s(m, '1');
  int all = Q(s);

  std::vector<int> l(m);
  std::string t(m, '0');
  for (int i = 0; i < m; ++i) {
    t[i] = '1';
    l[i] = Q(t);
    t[i] = '0';
  }

  std::vector<int> id(m);
  std::iota(id.begin(), id.end(), 0);
  std::sort(id.begin(), id.end(), [&](int x, int y) -> bool { return l[x] > l[y]; });
  t = std::string(m, '1');
  for (int i = 0; i < m - 1; ++i) {
    int x = id[i];
    t[x] = '0';
    int temp = Q(t);
    if (temp > all - l[x]) {
      all = temp;
    } else {
      t[x] = '1';
    }
  }

  std::cout << "! " << all << std::endl;
#ifdef BACKLIGHT
  logd(all, answer);
  assert(all == answer);
#endif
}

```

</details>

<details>
<summary>思路2 AC代码</summary>

```cpp
// Problem: E. Railway System
// Contest: Codeforces - Codeforces Round #796 (Div. 2)
// URL: https://codeforces.com/contest/1688/problem/E
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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

// #undef BACKLIGHT

int main(int argc, char* argv[]) {
  CPPIO;
#ifdef BACKLIGHT
  int T = 10;
#else
  int T = 1;
#endif
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

std::mt19937 rng(time(0));
void solve_case(int Case) {
  int n, m;

#ifdef BACKLIGHT
  n = 200, m = 500;
  auto rnd = [&](int l, int r) { return l + rng() % (r - l + 1); };

  auto Kruskal = [&](std::vector<std::array<int, 3>> e, auto comp) {
    std::sort(e.begin(), e.end(), comp);
    std::vector<int> f(n);
    std::iota(f.begin(), f.end(), 0);
    std::function<int(int)> find = [&](int x) -> int {
      return x == f[x] ? x : (f[x] = find(f[x]));
    };

    int r = 0;
    for (auto [l, u, v] : e) {
      u = find(u);
      v = find(v);
      if (u == v)
        continue;
      r += l;
      f[u] = v;
    }
    return r;
  };

  std::vector<std::array<int, 3>> e(m);
  for (int i = 0; i < m; ++i) {
    int u = rnd(0, n - 1);
    int v;
    do {
      v = rnd(0, n - 1);
    } while (u == v);
    int l = rnd(1, 1e6);
    e[i] = {l, u, v};
  }
  int answer = Kruskal(e, [](std::array<int, 3> a, std::array<int, 3> b) { return a[0] < b[0]; });

  auto Q = [&](std::string s) {
    std::vector<std::array<int, 3>> e1;
    for (int i = 0; i < m; ++i) {
      if (s[i] == '1') {
        e1.push_back(e[i]);
      }
    }
    std::sort(e1.begin(), e1.end(),
              [](std::array<int, 3> a, std::array<int, 3> b) { return a[0] > b[0]; });

    std::vector<int> f(n);
    std::iota(f.begin(), f.end(), 0);
    std::function<int(int)> find = [&](int x) -> int {
      return x == f[x] ? x : (f[x] = find(f[x]));
    };

    int r = 0;
    for (auto [l, u, v] : e1) {
      u = find(u);
      v = find(v);
      if (u == v)
        continue;
      r += l;
      f[u] = f[v];
    }

    return r;
  };

#else
  std::cin >> n >> m;

  auto Q = [](std::string s) {
    std::cout << "? " << s << std::endl;
    int r;
    std::cin >> r;
    return r;
  };

#endif

  std::vector<int> l(m);
  std::string t(m, '0');
  for (int i = 0; i < m; ++i) {
    t[i] = '1';
    l[i] = Q(t);
    t[i] = '0';
  }

  std::vector<int> id(m);
  std::iota(id.begin(), id.end(), 0);
  std::sort(id.begin(), id.end(), [&](int x, int y) -> bool { return l[x] < l[y]; });
  t = std::string(m, '0');
  int last = 0;
  for (int i = 0; i < m; ++i) {
    int x = id[i];
    t[x] = '1';
    int temp = Q(t);
    if (temp == last + l[x]) {
      last = temp;
    } else {
      t[x] = '0';
    }
  }

  std::cout << "! " << last << std::endl;
#ifdef BACKLIGHT
  logd(last, answer);
  assert(last == answer);
#endif
}

```

</details>

## [F. Sanae and Giant Robot](https://codeforces.com/contest/1688/problem/F)

<details>
<summary>题意</summary>

给两个长度为$n$的数组$a$和$b$，以及$m$个区间$[l_i, r_i]$。每次你可以从这$m$个区间中选择一个满足$\sum_{i = l}^r a_i = \sum_{i = l}^r b_i$的区间$(l, r)$，然后对于$l \le i \le r$令$a_i = b_i$。

问通过上述操作是否可以将$a$变为$b$。

其中$1 \le n, m \le 2\times {10}^5，1 \le a_i, b_i \le {10}^9$。

</details>

<details>
<summary>思路</summary>

令$c_i = a_i - b_i$，$s$是$c$的前缀和数组。则区间$[l, r]$可以交换当且仅当$s_{l - 1} = s_r$，且交换过后对于$l \le i \le r$，$c_i = 0$均成立，相当于将区间内$s_i$都置成$s_{l - 1}$。

现在目标就是让$s_i = 0$对于$0 \le i \le n$均成立。

因为最后的目标是让所有位置都为零，所以置非零的数没有意义，所以可以将操作看成：对于区间$[l, r]$，如果$s_{l - 1} = s_r = 0$就将区间内的$s_i$都置0，最后看还有没有非零的$s_i$就可以了。

可以对于每个位置，维护一个以这个位置为端点的区间的集合，然后枚举所有为$0$的位置，再枚举以它为端点的区间，看是否可以将这个区间是否可以操作。由于是置$0$操作，每个点至多置1次。过程中用个`std::set`维护一下$s_i$非零的$i$就可以做到$O(n \log n)$的复杂度了。

</details>

<details>
<summary>AC代码</summary>

```cpp
// Problem: F. Sanae and Giant Robot
// Contest: Codeforces - Codeforces Round #796 (Div. 2)
// URL: https://codeforces.com/contest/1688/problem/F
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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
  int n, m;
  std::cin >> n >> m;

  std::vector<i64> a(n + 1), b(n + 1);
  for (int i = 1; i <= n; ++i)
    std::cin >> a[i];
  for (int i = 1; i <= n; ++i)
    std::cin >> b[i];

  std::vector<i64> s(n + 1);
  for (int i = 1; i <= n; ++i)
    s[i] = s[i - 1] + a[i] - b[i];

  std::vector<std::vector<int>> g(n + 1);
  for (int i = 1; i <= m; ++i) {
    int l, r;
    std::cin >> l >> r;
    --l;
    g[l].push_back(r);
    g[r].push_back(l);
  }

  std::queue<int> q;
  std::set<int> non_zero_positions;
  for (int i = 0; i <= n; ++i) {
    if (s[i] == 0) {
      q.push(i);
    } else {
      non_zero_positions.insert(i);
    }
  }

  while (!q.empty()) {
    int l = q.front();
    q.pop();
    for (int r : g[l]) {
      if (s[r] != 0)
        continue;

      int L = std::min(l, r);
      int R = std::max(l, r);
      logd(L, R, non_zero_positions);

      while (true) {
        auto it = non_zero_positions.lower_bound(L);
        if (it == non_zero_positions.end() || *it > R)
          break;
        s[*it] = 0;
        q.push(*it);
        non_zero_positions.erase(it);
      }
    }
  }

  std::cout << (non_zero_positions.empty() ? "YES" : "NO") << "\n";
}

```
</details>