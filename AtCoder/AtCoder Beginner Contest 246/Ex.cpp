// Problem: Ex - 01? Queries
// Contest: AtCoder - AtCoder Beginner Contest 246
// URL: https://atcoder.jp/contests/abc246/tasks/abc246_h
// Memory Limit: 1024 MB
// Time Limit: 6000 ms
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

template <typename ValueType>
class Matrix {
 private:
  using MatrixDataType = std::vector<std::vector<ValueType>>;
  using RowDataType = std::vector<ValueType>;

  size_t n_;
  size_t m_;
  MatrixDataType a_;

 public:
  static Matrix zero(size_t n, size_t m) {
    MatrixDataType data(n, RowDataType(m, 0));
    return Matrix(move(data));
  }

  static Matrix one(size_t n, size_t m) {
    assert(n == m);
    MatrixDataType data(n, RowDataType(m, 0));
    for (size_t i = 0; i < n; ++i) {
      data[i][i] = 1;
    }
    return Matrix(move(data));
  }

 public:
  Matrix() : n_(0), m_(0) {}

  Matrix(const MatrixDataType& a) : n_(a.size()), m_(a[0].size()), a_(a) {}

  Matrix(const Matrix& matrix) : n_(matrix.n_), m_(matrix.m_), a_(matrix.a_) {}

  size_t n() const { return n_; }

  size_t m() const { return m_; }

  RowDataType& operator[](size_t row) { return a_[row]; }

  const ValueType& at(size_t row, size_t col) const { return a_[row][col]; }

  friend Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
    assert(lhs.m() == rhs.n());

    Matrix result = zero(lhs.n(), rhs.m());
    for (size_t i = 0; i < lhs.n(); ++i) {
      for (size_t j = 0; j < lhs.m(); ++j) {
        for (size_t k = 0; k < rhs.m(); ++k) {
          result[i][k] = result.at(i, k) + lhs.at(i, j) * rhs.at(j, k);
        }
      }
    }
    return result;
  }

  void operator=(const Matrix& rhs) {
    n_ = rhs.n_;
    m_ = rhs.m_;
    a_ = rhs.a_;
  }

  friend Matrix operator^(const Matrix& lhs, size_t exponent) {
    assert(lhs.n() == lhs.m());

    Matrix result = one(lhs.n(), lhs.m());
    Matrix base = lhs;
    while (exponent) {
      if (exponent & 1)
        result = result * base;
      base = base * base;
      exponent >>= 1;
    }
    return result;
  }
};
template <typename ValueType>
std::string to_string(const Matrix<ValueType>& matrix) {
  std::stringstream ss;
  ss << "[";
  for (size_t i = 0; i < matrix.n(); ++i) {
    ss << "[";
    for (size_t j = 0; j < matrix.m(); ++j) {
      ss << matrix.at(i, j).value() << ",]"[j == matrix.m() - 1];
    }
    ss << ",]"[i == matrix.n() - 1];
  }
  return ss.str();
}

const int N = 1e5 + 5;
int n, q;
char s[N];
Matrix<Mint> a[N << 2];
Matrix<Mint> R({{0}, {0}, {1}});
Matrix<Mint> M0({{1, 1, 1}, {0, 1, 0}, {0, 0, 1}});
Matrix<Mint> M1({{1, 0, 0}, {1, 1, 1}, {0, 0, 1}});
Matrix<Mint> M2({{1, 1, 1}, {1, 1, 1}, {0, 0, 1}});

void PushUp(int x) {
  a[x] = a[x << 1] * a[x << 1 | 1];
}

void Build(int x, int l, int r) {
  if (l == r) {
    if (s[l] == '0')
      a[x] = M0;
    else if (s[l] == '1')
      a[x] = M1;
    else
      a[x] = M2;
    return;
  }
  int mid = (l + r) >> 1;
  Build(x << 1, l, mid);
  Build(x << 1 | 1, mid + 1, r);
  PushUp(x);
}

void Update(int x, int l, int r, int p, char ch) {
  if (l == r && l == p) {
    if (ch == '0')
      a[x] = M0;
    else if (ch == '1')
      a[x] = M1;
    else
      a[x] = M2;
    return;
  }
  int mid = (l + r) >> 1;
  if (p <= mid)
    Update(x << 1, l, mid, p, ch);
  else
    Update(x << 1 | 1, mid + 1, r, p, ch);
  PushUp(x);
}

void solve_case(int Case) {
  std::cin >> n >> q;
  std::cin >> (s + 1);

  Build(1, 1, n);

  int p;
  char ch[5];
  for (int i = 0; i < q; ++i) {
    std::cin >> p >> ch;
    Update(1, 1, n, p, ch[0]);
    auto r = a[1] * R;
    logd(r);
    std::cout << (r.at(0, 0) + r.at(1, 0)).value() << "\n";
  }
}