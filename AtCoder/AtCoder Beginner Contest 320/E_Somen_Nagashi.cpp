// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/stdext/container.h"

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<i64> sum(n, 0);
  stdext::min_heap<int> pq;
  stdext::min_heap<std::pair<int, int>> tq;
  for (int i = 0; i < n; ++i)
    pq.push(i);
  for (int i = 0; i < m; ++i) {
    int t, w, s;
    std::cin >> t >> w >> s;

    while (!tq.empty() && tq.top().first <= t) {
      auto [time, ind] = tq.top();
      tq.pop();
      pq.push(ind);
    }

    if (!pq.empty()) {
      int ind = pq.top();
      pq.pop();
      sum[ind] += w;
      tq.push({t + s, ind});
    }
  }

  for (int i = 0; i < n; ++i)
    std::cout << sum[i] << "\n";
}
