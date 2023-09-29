// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, k;
  std::cin >> n >> k;

  std::priority_queue<std::pair<int, int>> q;
  i64 sum = 0;
  for (int i = 0; i < n; ++i) {
    int a, b;
    std::cin >> a >> b;
    q.push({-a, b});
    sum += b;
  }

  int t = 1;
  while (true) {
    logd(t, sum, k);
    if (sum <= k)
      break;

    auto [a, b] = q.top();
    q.pop();
    logd(a, b);
    sum -= b;
    t = -a + 1;
  }
  std::cout << t << "\n";
}
