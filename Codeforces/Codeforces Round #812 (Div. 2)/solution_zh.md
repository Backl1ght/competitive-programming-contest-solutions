# Codeforces Round #812 (Div. 2)

咕。

## [B. Optimal Reduction](https://codeforces.com/contest/1713/problem/B)

观察可得：对于所有$b$，其中要求操作次数最少的为$\max \{ a \}$.

然后就是看$f(a)$是不是等于$\max \{ a \}$了，这个只需要满足$a$是单峰的就行。

<details>
<summary>AC代码</summary>

```cpp
// Problem: B. Optimal Reduction
// Contest: Codeforces - Codeforces Round #812 (Div. 2)
// URL: https://codeforces.com/contest/1713/problem/B
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
  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i)
    std::cin >> a[i];

  std::vector<int> pma(n + 1);
  for (int i = 1; i <= n; ++i) {
    pma[i] = std::max(pma[i - 1], a[i]);
  }

  std::vector<int> sma(n + 2);
  for (int i = n; i >= 1; --i) {
    sma[i] = std::max(sma[i + 1], a[i]);
  }

  bool flag = true;
  for (int i = 2; i <= n - 1; ++i) {
    if (a[i] < pma[i - 1] && a[i] < sma[i + 1]) {
      flag = false;
    }
  }

  std::cout << (flag ? "YES" : "NO") << "\n";
}
```

</details>

## [C. Build Permutation](https://codeforces.com/contest/1713/problem/C)

手推了一下，然后猜结论：从n开始往前搞，尽可能构造大的平方数，一定能够得出答案。

<details>
<summary>AC代码</summary>

```cpp
// Problem: C. Build Permutation
// Contest: Codeforces - Codeforces Round #812 (Div. 2)
// URL: https://codeforces.com/contest/1713/problem/C
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

  std::set<int> s;
  for (int i = 0; i < n; ++i) {
    s.insert(i);
  }

  int x = 0;
  while ((x + 1) * (x + 1) <= n + n - 1) {
    x = x + 1;
  }
  logd(x, n);

  std::vector<int> p(n, -1);
  for (int i = n - 1; i >= 0; --i) {
    while (true) {
      if (x < 0) {
        std::cout << "-1\n";
        return;
      }
      int y = x * x - i;
      if (s.count(y)) {
        p[i] = y;
        s.erase(y);
        break;
      } else {
        x = x - 1;
      }
    }
  }

  // for (int i = 0; i < n; ++i) {
  //   int z = int(sqrt(i + p[i]));
  //   assert(z * z == i + p[i]);
  // }

  for (int i = 0; i < n; ++i)
    std::cout << p[i] << " \n"[i + 1 == n];
}
```

</details>

## [D. Tournament Countdown](https://codeforces.com/contest/1713/problem/D)

首先，直接朴素的模拟要$2^n - 1$次操作，不可行。

然后，观察发现对于$4$个人的比赛，其实只需要2次操作就可以确定胜者，然后就可以自底向上4个为一组搞。这样的话，相当于可以用2次操作干掉3个人，一共要干掉$2^n - 1$个人，次数就是$\lceil (2^n - 1)\frac{2}{3} \rceil = \lfloor \frac{2^{n + 1}}{3} \rfloor$

<details>
<summary>AC代码</summary>

```cpp
// Problem: D. Tournament Countdown
// Contest: Codeforces - Codeforces Round #812 (Div. 2)
// URL: https://codeforces.com/contest/1713/problem/D
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

std::mt19937 rng(114514);

void solve_case(int Case) {
  int n;

#ifdef BACKLIGHT
  n = 17;
#else
  std::cin >> n;
#endif

  int limit = ((1 << (n + 1)) + 2) / 3;

#ifdef BACKLIGHT
  std::vector<int> c(1 << n, 0);
  std::vector<int> p(1 << n);
  std::iota(p.begin(), p.end(), 0);

  while (p.size() > 1) {
    std::vector<int> np;
    for (int i = 0; i < p.size(); i += 2) {
      if (rng() & 1) {
        np.push_back(p[i + 1]);
        ++c[p[i + 1]];
      } else {
        np.push_back(p[i]);
        ++c[p[i]];
      }
    }
    p = np;
  }
  int std = p[0];

  int count = 0;
  auto Q = [&c, &count, &limit](int a, int b) -> int {
    ++count;
    assert(count <= limit);

    int r;
    if (c[a] == c[b])
      r = 0;
    else if (c[a] > c[b])
      r = 1;
    else
      r = 2;
    return r;
  };
#else
  int count = 0;
  auto Q = [&count, &limit](int a, int b) -> int {
    ++count;
    assert(count <= limit);
    std::cout << "? " << a + 1 << " " << b + 1 << std::endl;
    int r;
    std::cin >> r;
    return r;
  };
#endif

  std::vector<int> a(1 << n);
  std::iota(a.begin(), a.end(), 0);
  while (a.size() > 1) {
    std::vector<int> na;
    if (a.size() == 2) {
      int r = Q(a[0], a[1]);
      assert(r != 0);
      if (r == 1)
        na.push_back(a[0]);
      else
        na.push_back(a[1]);
    } else {
      for (int i = 0; i < a.size(); i += 4) {
        int r0 = Q(a[i], a[i + 2]);
        if (r0 == 0) {
          int r1 = Q(a[i + 1], a[i + 3]);
          assert(r1 != 0);
          if (r1 == 1) {
            na.push_back(a[i + 1]);
          } else if (r1 == 2) {
            na.push_back(a[i + 3]);
          }
        } else if (r0 == 1) {
          int r1 = Q(a[i], a[i + 3]);
          assert(r1 != 0);
          if (r1 == 1) {
            na.push_back(a[i]);
          } else if (r1 == 2) {
            na.push_back(a[i + 3]);
          }
        } else if (r0 == 2) {
          int r1 = Q(a[i + 1], a[i + 2]);
          assert(r1 != 0);
          if (r1 == 1) {
            na.push_back(a[i + 1]);
          } else if (r1 == 2) {
            na.push_back(a[i + 2]);
          }
        }
      }
    }
    a = na;
  }
  int ans = a[0];

  std::cout << "! " << ans + 1 << std::endl;

#ifdef BACKLIGHT
  logd(std, ans);
  assert(std == ans);
#endif
}

```

</details>

## [E. Cross Swapping](https://codeforces.com/contest/1713/problem/E)

比赛的时候剩半个小时做这题，没搞出来，甚至思路都完全不对。

对于$a_{i, j}$，它要么保持不动，要么只能换到$a_{j, i}$。然后就可以将矩阵划分成左上角和右下角两个部分，后续只需要考虑左上角。

$a_{i, j}$保持不动需要$k = i$和$k = j$这两个操作同时操作，或者同时不操作。换到$a_{j, i}$需要只操作$k = i$和$k = j$这两个操作其中一个。对于$a_{i, j}$，看它和$a_{j, i}$的关系，可以判断出$a_{i, j}$换到$a_{j, i}$上会不会更优。

把每个$i$分为两个状态：操作和不操作。如果$a_{i, j} < a_{j, i}$的话，就说明$i$和$j$状态不能一样；如果$a_{i, j} > a_{j, i}$的话，就说明$i$和$j$状态需要一样。根据这个关系就可以建出图把问题转化成图论问题。现在这个问题有点像2-SAT，只是2-SAT要求不能有冲突，而这个问题出现冲突的时候可以以权重大的优先。

对于建出来的图中的每个连通块，对于其中权重最大的节点$i$，它是否操作其实都是可行的。因为对于和节点$i$对应的操作，以$a_{i, j}$换到$a_{j, i}$为例，它操作了那么$j$不操作就可以，它不操作那么$j$操作就可以。这样子，默认连通块中权重最大的节点不操作的话，节点是否操作就可以用带权并查集维护。

<details>
<summary>AC代码</summary>

```cpp
// Problem: E. Cross Swapping
// Contest: Codeforces - Codeforces Round #812 (Div. 2)
// URL: https://codeforces.com/contest/1713/problem/E
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

class WDSU {
 public:
  WDSU(int n) : n_(n), f_(n_), type_(n_) {
    for (int i = 0; i < n_; ++i) {
      f_[i] = i;
      type_[i] = 0;
    }
  }

  int find(int x) {
    if (x != f_[x]) {
      int fx = f_[x];
      int ffx = find(fx);

      f_[x] = ffx;
      type_[x] = type_[x] ^ type_[fx];
    }
    return f_[x];
  }

  void merge(int x, int y, int z) {
    int fx = find(x), fy = find(y);
    if (fx == fy)
      return;

    f_[fy] = fx;
    type_[fy] = type_[x] ^ type_[y] ^ z;
  }

  int type(int x) {
    int fx = find(x);
    return type_[x];
  }

 private:
  int n_;
  std::vector<int> f_;
  std::vector<int> type_;
};

void solve_case(int Case) {
  int n;
  std::cin >> n;

  std::vector<std::vector<int>> a(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> a[i][j];
    }
  }

  WDSU d(n);
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (a[i][j] < a[j][i]) {
        d.merge(i, j, 0);
      }
      if (a[i][j] > a[j][i]) {
        d.merge(i, j, 1);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    if (d.type(i) == 1) {
      for (int j = 0; j < n; ++j)
        std::swap(a[i][j], a[j][i]);
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << a[i][j] << " \n"[j + 1 == n];
    }
  }
}

```

</details>

## [F. Lost Array](https://codeforces.com/contest/1713/problem/F)

To be solved.