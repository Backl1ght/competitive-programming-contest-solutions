// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  const int dx[4] = {0, 1, 0, -1};
  const int dy[4] = {-1, 0, 1, 0};

  auto get_d = [](char ch) {
    int d = -1;
    if (ch == '<')
      d = 0;
    else if (ch == 'v')
      d = 1;
    else if (ch == '>')
      d = 2;
    else if (ch == '^')
      d = 3;
    return d;
  };

  int n, m;
  std::cin >> n >> m;
  std::vector<std::string> s(n);
  for (int i = 0; i < n; ++i)
    std::cin >> s[i];

  int sx, sy;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (s[i][j] == 'S') {
        sx = i;
        sy = j;
      } else {
        int d = get_d(s[i][j]);
        if (d == -1)
          continue;

        int x = i, y = j;
        while (true) {
          int nx = x + dx[d];
          int ny = y + dy[d];
          if (0 <= nx && nx < n && 0 <= ny && ny < m && s[nx][ny] != '#' &&
              get_d(s[nx][ny]) == -1) {
            x = nx;
            y = ny;
            s[x][y] = '!';
          } else {
            break;
          }
        }

        logd(s);
      }
    }
  }

  std::vector<std::vector<int>> vis(n, std::vector<int>(m, -1));
  std::queue<std::pair<int, int>> q;
  q.push({sx, sy});
  vis[sx][sy] = 0;
  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();

    for (int d = 0; d < 4; ++d) {
      int nx = x + dx[d];
      int ny = y + dy[d];

      if (0 <= nx && nx < n && 0 <= ny && ny < m && s[nx][ny] != '#' &&
          s[nx][ny] != '!' && vis[nx][ny] == -1 && get_d(s[nx][ny]) == -1) {
        if (s[nx][ny] == 'G') {
          std::cout << vis[x][y] + 1 << "\n";
          return;
        } else {
          vis[nx][ny] = vis[x][y] + 1;
          q.push({nx, ny});
        }
      }
    }
  }
  std::cout << "-1\n";
}
