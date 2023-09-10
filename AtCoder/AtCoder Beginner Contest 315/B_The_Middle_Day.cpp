// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<int> d(n + 1);
  for (int i = 1; i <= n; ++i)
    std::cin >> d[i];

  int sum = std::accumulate(d.begin(), d.end(), 0);
  int x = (sum + 1) / 2;
  for (int a = 1; a <= n; ++a) {
    if (x > d[a]) {
      x -= d[a];
      continue;
    }

    std::cout << a << " " << x << "\n";
    break;
  }
}
