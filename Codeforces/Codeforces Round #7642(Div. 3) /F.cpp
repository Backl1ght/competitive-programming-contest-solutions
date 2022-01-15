// Problem: F. Let's Play the Hat?
// Contest: Codeforces - Codeforces Round #762 (Div. 3)
// URL: http://codeforces.com/contest/1619/problem/F
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

#define CPPIO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

using i64 = int64_t;
using u64 = uint64_t;

void solve_case(int Case);

int main() {
  CPPIO;
  int T = 1;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

struct People {
  int id, rank;
  bool operator<(const People& p) const { return rank > p.rank; }
};

void solve_case(int Case) {
  int N, M, K;
  cin >> N >> M >> K;

  priority_queue<People> q;
  for (int i = 0; i < N; ++i) {
    q.push((People){i + 1, 0});
  }

  for (int k = 0; k < K; ++k) {
    priority_queue<People> p;

    int X = N % M;
    for (int i = 0; i < M; ++i) {
      int capacity = i < X ? (N + M - 1) / M : N / M;
      cout << capacity;
      for (int j = 0; j < capacity; ++j) {
        auto [id, rank] = q.top();
        q.pop();
        cout << " " << id;

        if (i < X)
          p.push((People){id, rank + 1});
        else
          p.push((People){id, rank});
      }
      cout << "\n";
    }
    
    swap(p, q);
  }
}