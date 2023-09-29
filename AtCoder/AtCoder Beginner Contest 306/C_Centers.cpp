// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<std::vector<int>> a(n);
  for (int i = 0; i < 3 * n; ++i) {
    int x;
    std::cin >> x;
    --x;
    a[x].push_back(i);
  }

  std::vector<int> id(n);
  std::iota(id.begin(), id.end(), 0);
  std::sort(id.begin(), id.end(),
            [&](int x, int y) { return a[x][1] < a[y][1]; });

  for (int i = 0; i < n; ++i)
    std::cout << id[i] + 1 << " \n"[i + 1 == n];
}
