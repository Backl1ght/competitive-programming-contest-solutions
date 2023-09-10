// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<std::vector<int>> g(n);
  for (int i = 0; i < n; ++i) {
    int c;
    std::cin >> c;
    g[i].resize(c);
    for (int j = 0; j < c; ++j) {
      std::cin >> g[i][j];
      --g[i][j];
    }
  }

  std::vector<int> vis(n);
  vis[0] = true;
  std::function<void(int)> dfs = [&](int u) {
    for (int v : g[u]) {
      if (vis[v])
        continue;
      vis[v] = true;
      dfs(v);
    }
  };
  dfs(0);

  std::vector<std::vector<int>> r(n);
  std::vector<int> indeg(n);
  for (int u = 0; u < n; ++u) {
    for (int v : g[u]) {
      if (vis[u] && vis[v]) {
        r[v].push_back(u);
        ++indeg[u];
      }
    }
  }

  std::queue<int> q;
  std::vector<int> ans;
  for (int i = 0; i < n; ++i) {
    if (vis[i] && indeg[i] == 0)
      q.push(i);
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();

    ans.push_back(u);

    for (int v : r[u]) {
      --indeg[v];
      if (indeg[v] == 0)
        q.push(v);
    }
  }
  ans.pop_back();

  for (int v : ans)
    std::cout << v + 1 << " ";
}
