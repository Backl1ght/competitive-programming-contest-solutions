// Problem: F - Cards
// Contest: AtCoder - AtCoder Beginner Contest 247
// URL: https://atcoder.jp/contests/abc247/tasks/abc247_f
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
  Modular(const ValueType& value) : value_(normalize(value)) {}

  ValueType value() const { return value_; }

  Modular inv() const { return Modular(power(value_, mod_ - 2)); }

  Modular power(size_t exponent) const {
    return Modular(power(value_, exponent));
  }

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
// using Mint = Modular<int, 1'000'000'007>;
using Mint = Modular<int, 998'244'353>;

void solve_case(int Case) {
  int n;
  std::cin >> n;

  std::vector<Mint> f(n + 1, Mint(0)), h(n + 1, Mint(0));
  f[1] = Mint(2);
  f[2] = Mint(3);
  for (int i = 3; i <= n; ++i)
    f[i] = f[i - 1] + f[i - 2];

  h[1] = Mint(1);
  h[2] = Mint(3);
  h[3] = Mint(4);
  for (int i = 4; i <= n; ++i)
    h[i] = f[i - 1] + f[i - 3];

  std::vector<int> p(n), q(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> p[i], --p[i];
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> q[i], --q[i];
  }
  logd(p, q);

  std::vector<std::vector<int>> g(n);
  for (int i = 0; i < n; ++i) {
    g[p[i]].push_back(q[i]);
    g[q[i]].push_back(p[i]);
  }

  Mint ans(1);
  std::vector<bool> visited(n, false);
  std::function<void(int, int&)> dfs = [&](int u, int& count) -> void {
    logd(u);
    visited[u] = true;
    ++count;
    for (int v : g[u]) {
      if (!visited[v])
        dfs(v, count);
    }
  };
  for (int i = 0; i < n; ++i) {
    if (visited[i])
      continue;
    int count = 0;
    dfs(i, count);
    ans = ans * h[count];
    logd(count);
  }
  std::cout << ans.value() << "\n";
}