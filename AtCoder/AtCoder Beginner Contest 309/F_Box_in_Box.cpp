// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<std::array<int, 3>> a(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 3; ++j)
      std::cin >> a[i][j];
    std::sort(a[i].begin(), a[i].end());
  }
  std::sort(a.begin(), a.end());

  bool ans = false;
  std::function<void(int, int)> CDQ = [&](int l, int r) {
    if (l == r)
      return;

    int mid = (l + r) >> 1;
    CDQ(l, mid);
    CDQ(mid + 1, r);

    std::vector<std::array<int, 3>> b;
    b.reserve(r - l + 1);
    for (int i = l; i <= r; ++i)
      b.push_back({a[i][1], a[i][2], i});
    std::sort(b.begin(), b.end());
    int S1 = std::numeric_limits<int>::max(), S2 = S1;
    std::queue<std::pair<int, int>> Q1, Q2;
    for (const auto& [y, z, i] : b) {
      if (i <= mid) {
        if (a[i][0] < a[mid + 1][0])
          Q1.push({y, z});
        Q2.push({y, z});
      } else {
        while (!Q1.empty() && Q1.front().first < y) {
          S1 = std::min(S1, Q1.front().second);
          Q1.pop();
        }
        while (!Q2.empty() && Q2.front().first < y) {
          S2 = std::min(S2, Q2.front().second);
          Q2.pop();
        }
        if (S1 < z)
          ans = true;
        if (a[i][0] > a[mid][0]) {
          if (S2 < z)
            ans = true;
        }
      }
    }
  };
  CDQ(0, n - 1);

  std::cout << (ans ? "Yes" : "No") << "\n";
}
