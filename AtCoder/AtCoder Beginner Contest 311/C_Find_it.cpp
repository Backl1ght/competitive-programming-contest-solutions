// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<std::vector<int>> g(n);
  std::vector<int> indeg(n, 0);
  for (int i = 0; i < n; ++i) {
    int u, v;
    u = i;
    std::cin >> v;
    --v;
    g[u].push_back(v);
    ++indeg[v];
  }

  std::queue<int> q;
  std::vector<bool> vis(n, false);
  for (int i = 0; i < n; ++i)
    if (indeg[i] == 0)
      q.push(i);
  while (!q.empty()) {
    int u = q.front();
    q.pop();

    vis[u] = true;

    for (int v : g[u]) {
      --indeg[v];
      if (indeg[v] == 0) {
        q.push(v);
      }
    }
  }

  int rt;
  std::vector<int> tag(n);
  std::vector<int> stack, ans;
  bool flag = false;
  std::function<void(int)> dfs = [&](int u) {
    stack.push_back(u);
    for (int v : g[u]) {
      if (v == rt) {
        ans = stack;
        flag = true;
        break;
      }
      if (tag[v] == rt)
        continue;
      tag[v] = rt;
      dfs(v);
    }
    stack.pop_back();
  };

  for (int i = 0; i < n; ++i) {
    if (!vis[i]) {
      rt = i;
      tag[i] = rt;
      dfs(i);
      if (flag)
        break;
    }
  }

  std::cout << ans.size() << "\n";
  for (int v : ans)
    std::cout << v + 1 << " ";
}
