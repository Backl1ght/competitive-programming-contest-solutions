// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int H, W, N;
  std::cin >> H >> W >> N;

  std::vector<std::vector<int>> a(H + 1, std::vector<int>(W + 1, 0));
  for (int i = 0; i < N; ++i) {
    int x, y;
    std::cin >> x >> y;
    a[x][y] = 1;
  }

  for (int i = 1; i <= H; ++i) {
    for (int j = 1; j <= W; ++j) {
      a[i][j] += -a[i - 1][j - 1] + a[i][j - 1] + a[i - 1][j];
    }
  }
  logd(a);

  auto S = [&](int x, int y, int d) {
    return a[x][y] - a[x][y - d] - a[x - d][y] + a[x - d][y - d];
  };

  i64 ans = 0;
  for (int i = 1; i <= H; ++i) {
    for (int j = 1; j <= W; ++j) {
      if (S(i, j, 1) != 0)
        continue;

      int l = 2, r = std::min(i, j), k = 1;
      while (l <= r) {
        int mid = (l + r) >> 1;
        if (S(i, j, mid) == 0)
          l = mid + 1, k = mid;
        else
          r = mid - 1;
      }
      ans += k;
    }
  }
  std::cout << ans << "\n";
}
