// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/stdext/container.h"

void Initialize() {}

inline bool bit_intersect(int mask1, int mask2) {
  return (mask1 & mask2) != 0;
}

struct State {
  stdext::min_heap<std::pair<int, int>> q;
  i32 usable_medicine_mask;
  i64 strength;

  // Since the given graph is a tree, new monster you meet after killed some
  // monster will always be alive monster.
  //
  // So as used medicine.
};

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<std::vector<int>> adj(n);
  std::vector<int> t(n), s(n), g(n);
  std::vector<int> medicine_id1(n), medicine_id2;
  int num_medicine = 0;
  for (int i = 1; i < n; ++i) {
    int parent;
    std::cin >> parent;
    --parent;
    adj[parent].push_back(i);

    std::cin >> t[i] >> s[i] >> g[i];
    if (t[i] == 2) {
      medicine_id1[i] = num_medicine;
      medicine_id2.push_back(i);
      ++num_medicine;
    }
  }
  i64 max_s = *std::max_element(s.begin(), s.end());

  std::vector<State> dp(1 << num_medicine);
  std::function<void(State&)> go = [&](State& state) {
    while (!state.q.empty()) {
      auto [monster_strength, monster_id] = state.q.top();
      if (state.strength < monster_strength)
        break;
      state.q.pop();
      if (monster_strength != 0)
        state.strength = std::min(max_s, state.strength + g[monster_id]);

      for (int v : adj[monster_id]) {
        if (t[v] == 1) {
          state.q.push({s[v], v});
        } else if (t[v] == 2) {
          state.usable_medicine_mask |= (1 << medicine_id1[v]);
        }
      }
    }
  };
  dp[0].q.push({0, 0});
  dp[0].strength = 1;
  go(dp[0]);

  for (int mask = 0; mask < (1 << num_medicine); ++mask) {
    for (int i = 0; i < num_medicine; ++i) {
      if (bit_intersect(dp[mask].usable_medicine_mask, 1 << i)) {
        State state = dp[mask];
        state.usable_medicine_mask -= (1 << i);
        state.strength = std::min(max_s, state.strength * g[medicine_id2[i]]);
        state.q.push({0, medicine_id2[i]});
        go(state);

        int new_mask = (mask | (1 << i));
        if (state.strength > dp[new_mask].strength)
          dp[new_mask] = state;
      }
    }
  }

  std::cout << (dp.back().strength >= max_s ? "Yes" : "No") << "\n";
}
