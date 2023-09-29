// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, t, m;
  std::cin >> n >> t >> m;

  std::vector<std::vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  int ans = 0;
  std::vector<std::set<int>> teams(t);
  int num_teams = 0;
  std::function<void(int)> dfs = [&](int p) {
    if (p == n) {
      if (num_teams == t)
        ++ans;
      return;
    }

    for (int i = 0; i < num_teams; ++i) {
      bool can = true;
      for (int v : g[p]) {
        if (teams[i].count(v)) {
          can = false;
          break;
        }
      }

      if (can) {
        teams[i].insert(p);
        dfs(p + 1);
        teams[i].erase(p);
      }
    }

    if (num_teams != t) {
      teams[num_teams].insert(p);
      ++num_teams;
      dfs(p + 1);
      --num_teams;
      teams[num_teams].erase(p);
    }
  };
  dfs(0);
  std::cout << ans << "\n";
}
