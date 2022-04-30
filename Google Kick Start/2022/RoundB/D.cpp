// Problem: Hamiltonian Tour
// Contest: Google Coding Competitions - Round B 2022 - Kick Start 2022
// URL:
// https://codingcompetitions.withgoogle.com/kickstart/round/00000000008caa74/0000000000acf318
// Memory Limit: 1024 MB
// Time Limit: 25000 ms
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
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

void solve_case(int Case) {
  std::cout << "Case #" << Case << ": ";

  int r, c;
  std::cin >> r >> c;

  std::vector<std::string> B(r);
  for (int i = 0; i < r; ++i) {
    std::cin >> B[i];
  }

  int count = 0;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      if (B[i][j] == '*')
        count += 4;
    }
  }

  std::vector<std::string> A(2 * r, std::string(2 * c, '?'));
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      if (B[i][j] == '*') {
        A[2 * i][2 * j] = 'E';
        A[2 * i][2 * j + 1] = 'S';
        A[2 * i + 1][2 * j + 1] = 'W';
        A[2 * i + 1][2 * j] = 'N';
      }
    }
  }

  std::vector<std::vector<bool>> visited(r, std::vector<bool>(c, false));
  std::function<void(int, int)> dfs = [&](int x, int y) -> void {
    visited[x][y] = true;

    for (int d = 0; d < 4; ++d) {
      int nx = x + dx[d];
      int ny = y + dy[d];
      if (nx >= 0 && nx < r && ny >= 0 && ny < c && B[nx][ny] == '*' &&
          !visited[nx][ny]) {
        if (d == 0) {
          A[2 * x][2 * y + 1] = 'E';
          A[2 * nx + 1][2 * ny] = 'W';
        } else if (d == 1) {
          A[2 * x + 1][2 * y] = 'W';
          A[2 * nx][2 * ny + 1] = 'E';
        } else if (d == 2) {
          A[2 * x + 1][2 * y + 1] = 'S';
          A[2 * nx][2 * ny] = 'N';
        } else if (d == 3) {
          A[2 * x][2 * y] = 'N';
          A[2 * nx + 1][2 * ny + 1] = 'S';
        }

        dfs(nx, ny);
      }
    }
  };
  dfs(0, 0);
  logd(A);

  int x = 0, y = 0;
  std::string ans;
  do {
    ans.push_back(A[x][y]);
    if (A[x][y] == 'E') {
      ++y;
    } else if (A[x][y] == 'W') {
      --y;
    } else if (A[x][y] == 'S') {
      ++x;
    } else if (A[x][y] == 'N') {
      --x;
    }
  } while (x != 0 || y != 0);

  if (ans.size() != count) {
    std::cout << "IMPOSSIBLE\n";
    return;
  }

  std::cout << ans << "\n";
}