// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/stdext/container.h"

void Initialize() {}

void SolveCase(int Case) {
  const int dx[] = {0, 0, 1, -1};
  const int dy[] = {1, -1, 0, 0};

  int n, m;
  std::cin >> n >> m;
  std::vector<std::string> s(n);
  for (int i = 0; i < n; ++i)
    std::cin >> s[i];

  auto vis = stdext::n_vector<bool>(n, m, 4, false);
  std::queue<std::array<int, 3>> q;
  for (int i = 0; i < 4; ++i) {
    q.push({1, 1, i});
    vis[1][1][i] = true;
  }
  while (!q.empty()) {
    auto [x, y, d] = q.front();
    q.pop();

    int nx = x + dx[d];
    int ny = y + dy[d];
    if (0 <= nx && nx < n && 0 <= ny && ny < m) {
      if (s[nx][ny] == '.') {
        if (!vis[nx][ny][d]) {
          vis[nx][ny][d] = true;
          q.push({nx, ny, d});
        }
      } else {
        for (d = 0; d < 4; ++d) {
          if (!vis[x][y][d]) {
            vis[x][y][d] = true;
            q.push({x, y, d});
          }
        }
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      bool flag = false;
      for (int d = 0; d < 4; ++d)
        if (vis[i][j][d])
          flag = true;
      if (flag)
        ++ans;
    }
  }
  std::cout << ans << "\n";
}
