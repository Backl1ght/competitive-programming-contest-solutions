// Problem: G - Dream Team
// Contest: AtCoder - AtCoder Beginner Contest 247
// URL: https://atcoder.jp/contests/abc247/tasks/abc247_g
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
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

template <typename Cap, typename Cost>
struct mcmf_graph {
  struct Edge {
    int v, nxt;
    Cap cap, flow;
    Cost cost;
    Edge() {}
    Edge(int _v, int _nxt, Cap _cap, Cost _cost)
        : v(_v), nxt(_nxt), cap(_cap), flow(0), cost(_cost) {}
  };

  int V, E;
  std::vector<int> h;
  std::vector<Edge> e;

  mcmf_graph() : V(0) {}
  mcmf_graph(int _V) : V(_V), h(_V + 1, -1) {}

  inline void addarc(int u, int v, Cap cap, Cost cost) {
    assert(1 <= u && u <= V);
    assert(1 <= v && v <= V);
    e.push_back(Edge(v, h[u], cap, cost));
    h[u] = e.size() - 1;
  }

  inline void addedge(int u, int v, Cap cap, Cost cost) {
    addarc(u, v, cap, cost);
    addarc(v, u, 0, -cost);
  }

  std::pair<Cap, Cost> mcmf(int s, int t) {
    assert(1 <= s && s <= V);
    assert(1 <= t && t <= V);
    assert(s != t);

    Cap flow = 0;
    Cost cost = 0;

    std::vector<int> pe(V + 1);
    std::vector<bool> inq(V + 1);
    std::vector<Cost> dis(V + 1);
    std::vector<Cap> incf(V + 1);

    auto spfa = [&]() {
      const Cap INF = std::numeric_limits<Cap>::max();
      std::fill(dis.begin(), dis.end(), INF);
      std::queue<int> q;
      q.push(s);
      dis[s] = 0;
      incf[s] = INF;
      incf[t] = 0;
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int i = h[u]; i != -1; i = e[i].nxt) {
          int v = e[i].v, _cap = e[i].cap, _cost = e[i].cost;
          if (_cap == 0 || dis[v] <= dis[u] + _cost)
            continue;
          dis[v] = dis[u] + _cost;
          incf[v] = min(_cap, incf[u]);
          pe[v] = i;
          if (!inq[v])
            q.push(v), inq[v] = true;
        }
      }
      return incf[t];
    };

    auto update = [&]() {
      flow += incf[t];
      for (int i = t; i != s; i = e[pe[i] ^ 1].v) {
        e[pe[i]].cap -= incf[t];
        e[pe[i] ^ 1].cap += incf[t];
        cost += incf[t] * e[pe[i]].cost;
      }
    };

    while (spfa())
      update();

    return std::make_pair(flow, cost);
  }

  std::vector<Cost> solve(int s, int t) {
    assert(1 <= s && s <= V);
    assert(1 <= t && t <= V);
    assert(s != t);

    Cap flow = 0;
    Cost cost = 0;

    std::vector<int> pe(V + 1);
    std::vector<bool> inq(V + 1);
    std::vector<Cost> dis(V + 1);
    std::vector<Cap> incf(V + 1);

    auto spfa = [&]() {
      const Cap INF = std::numeric_limits<Cap>::max();
      std::fill(dis.begin(), dis.end(), INF);
      std::queue<int> q;
      q.push(s);
      dis[s] = 0;
      incf[s] = 1;
      incf[t] = 0;
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int i = h[u]; i != -1; i = e[i].nxt) {
          int v = e[i].v;
          Cap _cap = e[i].cap;
          Cost _cost = e[i].cost;
          if (_cap == 0 || dis[v] <= dis[u] + _cost)
            continue;
          dis[v] = dis[u] + _cost;
          incf[v] = std::min(_cap, incf[u]);
          pe[v] = i;
          if (!inq[v])
            q.push(v), inq[v] = true;
        }
      }
      return incf[t];
    };

    auto update = [&]() {
      flow += incf[t];
      for (int i = t; i != s; i = e[pe[i] ^ 1].v) {
        e[pe[i]].cap -= incf[t];
        e[pe[i] ^ 1].cap += incf[t];
        cost += incf[t] * e[pe[i]].cost;
      }
    };

    std::vector<Cost> ret;
    while (spfa()) {
      update();
      ret.push_back(-cost);
      logd(cost);
    }
    return ret;
  }
};

const int M = 155;
void solve_case(int Case) {
  int n;
  std::cin >> n;
  std::vector<int> a(n), b(n), c(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i] >> b[i] >> c[i];
    ++a[i];
    ++b[i];
  }

  auto university = [&](int x) { return x; };
  auto subject = [&](int x) { return x + M; };
  int S = 2 * M + 1;
  int T = 2 * M + 2;

  mcmf_graph<i64, i64> g(2 * M + 5);

  std::vector<bool> va(M, false);
  for (int i = 0; i < n; ++i) {
    if (!va[a[i]]) {
      g.addedge(S, university(a[i]), 1, 0);
      va[a[i]] = true;
    }
  }

  for (int i = 0; i < n; ++i) {
    g.addedge(university(a[i]), subject(b[i]), 1, -c[i]);
  }

  std::vector<bool> vb(M, false);
  for (int i = 0; i < n; ++i) {
    if (!vb[b[i]]) {
      g.addedge(subject(b[i]), T, 1, 0);
      vb[b[i]] = true;
    }
  }

  auto ans = g.solve(S, T);
  std::cout << ans.size() << "\n";
  for (int i = 0; i < ans.size(); ++i)
    std::cout << ans[i] << "\n";
}