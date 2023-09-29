// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  const static auto S = "snuke";

  int n, m;
  std::cin >> n >> m;
  std::vector<std::string> s(n);
  for (int i = 0; i < n; ++i)
    std::cin >> s[i];

  if (s[0][0] != 's') {
    std::cout << "No\n";
    return;
  }

  std::queue<std::array<int, 3>> q;
  std::vector<std::vector<bool>> vis(n, std::vector<bool>(m, false));
  vis[0][0] = false;
  q.push({0, 0, 0});
  while (!q.empty()) {
    auto [x, y, z] = q.front();
    q.pop();

    if (x == n - 1 && y == m - 1) {
      std::cout << "Yes\n";
      return;
    }

    int nz = (z + 1) % 5;
    for (int dx : {-1, 0, 1}) {
      for (int dy : {-1, 0, 1}) {
        if (std::abs(dx) + std::abs(dy) != 1)
          continue;
        int nx = x + dx;
        int ny = y + dy;
        if (nx < 0 || nx >= n || ny < 0 || ny >= m)
          continue;
        if (vis[nx][ny])
          continue;
        if (s[nx][ny] != S[nz])
          continue;

        vis[nx][ny] = true;
        q.push({nx, ny, nz});
      }
    }
  }

  std::cout << "No\n";
}
