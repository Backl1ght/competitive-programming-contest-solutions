// Problem: E - Bishop 2
// Contest: AtCoder - AtCoder Beginner Contest 246
// URL: https://atcoder.jp/contests/abc246/tasks/abc246_e
// Memory Limit: 2048 MB
// Time Limit: 6000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO \
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#endif

using i64 = int64_t;
using u64 = uint64_t;

void solve_case(int Case);

int main() {
  CPPIO;
  int T = 1;
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

const int N = 1505;
int n, ax, ay, bx, by;
char s[N][N];
int dis[N][N][5];
int dx[4] = {1, 1, -1, -1};
int dy[4] = {1, -1, 1, -1};

struct status {
  int x, y;
  int c;
  int d;
  status() {}
  status(int x, int y, int c, int d) {
    this->x = x;
    this->y = y;
    this->c = c;
    this->d = d;
  }
};

void solve_case(int Case) {
  std::cin >> n;
  std::cin >> ax >> ay;
  std::cin >> bx >> by;

  for (int i = 1; i <= n; ++i)
    std::cin >> (s[i] + 1);

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      for (int d = 0; d < 4; ++d)
        dis[i][j][d] = -1;

  int ans = -1;

  std::deque<status> q;
  for (int d = 0; d < 4; ++d) {
    q.push_back(status(ax, ay, 1, d));
    dis[ax][ay][d] = 1;
  }
  while (!q.empty()) {
    auto [x, y, c, d] = q.front();
    q.pop_front();

    if (c != dis[x][y][d])
      continue;

    if (x == bx && y == by) {
      ans = c;
      break;
    }

    for (int nd = 0; nd < 4; ++nd) {
      int nx = x + dx[nd];
      int ny = y + dy[nd];
      if (nx >= 1 && nx <= n && ny >= 1 && ny <= n && s[nx][ny] == '.') {
        int ndis = c + (d != nd);
        if (dis[nx][ny][nd] == -1 || ndis < dis[nx][ny][nd]) {
          dis[nx][ny][nd] = ndis;
          if (nd == d) {
            q.push_front(status(nx, ny, ndis, nd));
          } else {
            q.push_back(status(nx, ny, ndis, nd));
          }
        }
      }
    }
  }

  std::cout << ans << "\n";
}