// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/stdext/container.h"

void Initialize() {}

void SolveCase(int Case) {
  int n, d, p;
  std::cin >> n >> d >> p;

  std::vector<int> f(n);
  for (int i = 0; i < n; ++i)
    std::cin >> f[i];

  stdext::max_heap<int> q;
  i64 ans = 0;
  for (int i = 0; i < n; ++i) {
    ans += f[i];
    q.push(f[i]);
  }
  for (; !q.empty();) {
    i64 temp = 0;
    for (int i = 0; i < d; ++i) {
      if (q.empty())
        break;
      int u = q.top();
      q.pop();
      temp += u;
    }

    if (temp < p)
      break;
    ans += p - temp;
  }
  std::cout << ans << "\n";
}
