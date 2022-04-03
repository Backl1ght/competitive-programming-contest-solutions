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