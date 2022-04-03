## Ex - Product Modulo 2

这个题解是基于[官方题解](https://atcoder.jp/contests/abc245/editorial/3657)，但是官方题解我看了好久才看懂，所以在官方题解的基础上增加一些解释。

建议也看看B站里dls的讲解视频。

## 拆分

借助CRT可以将题目拆分成多个子问题，最后再合并，就可以得到原问题的答案。

CRT的式子$x \equiv a_i \mod m_i$，且$m_i$两两互素。

把$x$看成$N$，$m_i = {p_{i}}^{e_i}$，这样的话CRT的条件还是满足的。这里$M = \prod_{i} {p_i}^{e_i}$且对于每一个$i$都是一个子问题。

然后可以通过一个类似exLucas的过程，将子问题的答案拼成原问题的答案。

由于各个子问题之间是相互独立的，所以将所有子问题的答案乘起来就是原问题的答案。

## 解决子问题

记子问题为$f(p, e, K, N)$。

现在的问题就是要解决子问题，可以用生成函数结合快速幂来做。

首先，就是说$N_1$和$N_2$的质因子分解中，$p_i$的指数相同，那么$f(p, e, K, N_1) = f(p, e, K, N_2)$，这个可以用归纳法证明。所以可以将指数相同的数合并成一类，这样方便计算，最后要计算答案的时候再除以类的大小，就能得到原本的答案。

特别的，可以认为$N = 0$包含无穷大个$p$。

注意到$p^c \mod p^e$在$c > e$的时候都为$0$，所以可以将$c > e$的归为一类。

容易证明至多有$O(\log N)$个类的问题。

然后，包含$K$个数的答案可以由包含$K - 1$个数的答案推导得到，就是说如果$k = i + j$，那么包含$k$个$p$的答案可以由包含$i$个$p$的和包含$j$个$p$的答案合并得到。

但是一个一个推太慢了，所以使用快速幂来加速，因为是线性组合，所以成立。

其实就是说构造一个生成函数$f(x) = \sum_{i = 0}^{e} a_i x^i$，表示$a_i$表示包含$i$个$p$的方案数，特别的$a_e$表示包含大于等于$e$个$p$的方案数，则$f^{K}(x)$就是$K$个数相乘之后结果的方案数。

只有一个数的时候，可以方便的计算出$a_i$的值，就是$a_{e} = 0, a_{e - 1} = p - 1, a_{i} = a_{i + 1} \times p$。

## 注意

官方题解中也有提到，就是说可能出现除$0$的情况，但是因为$M \le 10^{12}$，所以这个时候指数$e = 1$，这个可以特判一下。

$N = 0$，那么就是$K$个数中任意一个为零即可，用所有方案减去全不为零的方案就是答案，即$p^{K} - (p-1)^{K}$。

$N \ne 0$，这个时候，前$K - 1$个数可以是任意非零元素，而最后一个元素是唯一确定的，即$a_K = N \times (\prod_{i = 1}^{K - 1} a_i)^{-1}$。所以方案数是$(p-1)^{K-1}$

## AC代码

```cpp
// Problem: Ex - Product Modulo 2
// Contest: AtCoder - AtCoder Beginner Contest 245
// URL: https://atcoder.jp/contests/abc245/tasks/abc245_h
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO \
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#endif

using i64 = int64_t;
using u64 = uint64_t;

void solve_case(int Case);

int main() {
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

  ValueType normalize(SupperType value) const {
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
  Modular() : value_(0) {}

  Modular(const SupperType& value) : value_(normalize(value)) {}

  ValueType value() const { return value_; }

  Modular inv() const { return Modular(power(value_, mod_ - 2)); }

  Modular power(size_t exponent) { return Modular(power(value_, exponent)); }

  friend Modular operator+(const Modular& lhs, const Modular& rhs) {
    ValueType result = lhs.value() + rhs.value() >= mod_
                           ? lhs.value() + rhs.value() - mod_
                           : lhs.value() + rhs.value();
    return Modular(result);
  }

  friend Modular operator-(const Modular& lhs, const Modular& rhs) {
    ValueType result = lhs.value() - rhs.value() < 0
                           ? lhs.value() - rhs.value() + mod_
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
template <typename StreamType,
          typename ValueType,
          ValueType mod,
          typename SupperType = int64_t>
StreamType& operator<<(StreamType& out,
                       const Modular<ValueType, mod, SupperType>& modular) {
  return out << modular.value();
}
template <typename StreamType,
          typename ValueType,
          ValueType mod,
          typename SupperType = int64_t>
StreamType& operator>>(StreamType& in,
                       Modular<ValueType, mod, SupperType>& modular) {
  ValueType value;
  in >> value;
  modular = Modular<ValueType, mod, SupperType>(value);
  return in;
}
// using mint = Modular<int, 1'000'000'007>;
using mint = Modular<int, 998'244'353>;
std::string to_string(mint v) {
  return to_string(v.value());
}

std::vector<std::pair<i64, i64>> factor(i64 n) {
  std::vector<std::pair<i64, i64>> pe;

  for (i64 i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      i64 e = 0;
      while (n % i == 0) {
        ++e;
        n = n / i;
      }
      pe.emplace_back(i, e);
    }
  }
  if (n > 1)
    pe.emplace_back(n, 1);
  return pe;
}

void solve_case(int Case) {
  i64 k, n, m;
  std::cin >> k >> n >> m;

  auto f = [](i64 p, i64 e, i64 k, i64 n) -> mint {
    auto cp = [](i64 n, i64 p) -> i64 {
      if (n == 0)
        return 1e9;
      i64 e = 0;
      while (n % p == 0) {
        ++e;
        n = n / p;
      }
      return e;
    };

    auto mul = [&](const std::vector<mint>& a,
                   const std::vector<mint>& b) -> std::vector<mint> {
      std::vector<mint> c(e + 1);
      for (i64 i = 0; i <= e; ++i) {
        for (i64 j = 0; j <= e; ++j) {
          c[std::min(e, i + j)] = c[std::min(e, i + j)] + a[i] * b[j];
        }
      }
      return c;
    };

    if (e == 1) {
      i64 pe = 1;
      for (int i = 1; i <= e; ++i)
        pe = pe * p;
      n = n % pe;
      if (n == 0)
        return mint(p).power(k) - mint(p - 1).power(k);
      else
        return mint(p - 1).power(k - 1);
    }

    i64 c = cp(n, p);
    if (c > e)
      c = e;

    std::vector<mint> r(e + 1), x(e + 1);
    r[0] = 1;
    x[e] = 1;
    x[e - 1] = p - 1;
    for (i64 i = e - 2; i >= 0; --i)
      x[i] = x[i + 1] * p;
    auto d = x;
    while (k) {
      if (k & 1)
        r = mul(r, x);
      x = mul(x, x);
      k >>= 1;
    }
    logd(r);

    return r[c] / d[c];
  };

  mint ans(1);
  auto pe = factor(m);
  logd(pe);
  for (auto [p, e] : pe) {
    ans = ans * f(p, e, k, n);
  }

  std::cout << ans.value() << "\n";
}
```