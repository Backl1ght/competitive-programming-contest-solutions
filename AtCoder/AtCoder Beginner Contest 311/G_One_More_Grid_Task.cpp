// #define MULTIPLE_TASK
#include "hira/main.cpp"

template <typename ValueType>
class RMQ {
 private:
  using Operator = std::function<ValueType(const ValueType&, const ValueType&)>;

  int n_;
  std::vector<std::vector<ValueType>> a_;
  std::vector<int> lg_;
  Operator op_;

 public:
  RMQ() {}

  RMQ(const std::vector<ValueType>& a, const Operator& op) {
    n_ = a.size();
    op_ = op;

    lg_.resize(n_ + 1);
    lg_[1] = 0;
    for (int i = 2; i <= n_; ++i)
      lg_[i] = lg_[i >> 1] + 1;

    a_.resize(n_);
    for (int i = 0; i < n_; ++i) {
      a_[i].resize(lg_[n_] + 1);
      a_[i][0] = a[i];
    }
    for (int j = 1; j <= lg_[n_]; ++j) {
      for (int i = 0; i + (1 << (j - 1)) < n_; ++i) {
        a_[i][j] = op_(a_[i][j - 1], a_[i + (1 << (j - 1))][j - 1]);
      }
    }
  }

  const ValueType Query(int l, int r) {
    int k = lg_[r - l + 1];
    return op_(a_[l][k], a_[r - (1 << k) + 1][k]);
  }
};

void Initialize() {}

void SolveCase(int Case) {
  auto min_op = [](int x, int y) { return std::min(x, y); };

  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> a(n + 1, std::vector<int>(m + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      std::cin >> a[i][j];
    }
  }
  auto s = a;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
    }
  }
  auto S = [&](int x1, int y1, int x2, int y2) {
    return s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1];
  };

  std::vector<RMQ<int>> row_mn(n + 1);
  for (int i = 1; i <= n; ++i)
    row_mn[i] = RMQ<int>(a[i], min_op);

  i64 ans = 0;
  std::vector<int> L(n + 1), R(n + 1);
  auto update = [&](int l, int r, const std::vector<int>& mn) -> void {
    logd(l, r);
    {
      std::stack<int> stack;
      stack.push(0);
      for (int i = 1; i <= n; ++i) {
        while (stack.size() > 1 && mn[i] <= mn[stack.top()])
          stack.pop();
        L[i] = stack.top() + 1;
        stack.push(i);
      }
    }

    {
      std::stack<int> stack;
      stack.push(n + 1);
      for (int i = n; i >= 1; --i) {
        while (stack.size() > 1 && mn[i] <= mn[stack.top()])
          stack.pop();
        R[i] = stack.top() - 1;
        stack.push(i);
      }
    }

    for (int i = 1; i <= n; ++i)
      ans = std::max(ans, i64(1) * mn[i] * S(L[i], l, R[i], r));
  };

  std::vector<int> mn(n + 1);
  for (int l = 1; l <= m; ++l) {
    for (int r = l; r <= m; ++r) {
      for (int i = 1; i <= n; ++i)
        mn[i] = row_mn[i].Query(l, r);
      update(l, r, mn);
    }
  }

  std::cout << ans << "\n";
}
