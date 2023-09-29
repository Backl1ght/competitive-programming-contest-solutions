// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<int> p(n);
  for (int i = 0; i < n; ++i)
    std::cin >> p[i];
  std::sort(p.begin(), p.end());

  std::vector<std::pair<int, int>> a(m);
  for (int i = 0; i < m; ++i)
    std::cin >> a[i].first;
  for (int i = 0; i < m; ++i)
    std::cin >> a[i].second;
  std::sort(a.begin(), a.end());

  i64 ans = 0;
  std::priority_queue<int> D;
  for (int i = 0, j = 0; i < n; ++i) {
    while (j < m && a[j].first <= p[i]) {
      D.push(a[j].second);
      ++j;
    }

    int x = p[i];
    if (!D.empty()) {
      x -= D.top();
      D.pop();
    }
    ans += x;
  }

  std::cout << ans << "\n";
}
