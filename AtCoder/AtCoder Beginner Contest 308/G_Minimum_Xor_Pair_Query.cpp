// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

const int N = 3e5 + 5;
const int M = 31;
const int MAXL = N * M;
int tr[MAXL][2], e[MAXL], mn[MAXL];
int tot;

int trie_new_node() {
  ++tot;
  tr[tot][0] = tr[tot][1] = 0;
  e[tot] = 0;
  mn[tot] = std::numeric_limits<int>::max();

  return tot;
}

void trie_init() {
  tot = -1;
  trie_new_node();
  trie_new_node();
}

void trie_insert(int x) {
  int p = 1;
  for (int i = M - 1; i >= 0; --i) {
    int c = ((x >> i) & 1);
    if (!tr[p][c]) {
      tr[p][c] = trie_new_node();
    }
    p = tr[p][c];
    ++e[p];
  }
}

void trie_delete(int x) {
  int p = 1;
  for (int i = M - 1; i >= 0; --i) {
    int c = ((x >> i) & 1);
    p = tr[p][c];
    --e[p];
  }
}

int trie_get(int i, int p) {
  if (i < 0)
    return 0;

  if (e[tr[p][0]])
    return trie_get(i - 1, tr[p][0]);
  return trie_get(i - 1, tr[p][1]) + (1 << i);
}

void trie_pushup(int i, int p, int x) {
  mn[p] = std::numeric_limits<int>::max();

  if (i == -1) {
    if (e[p] > 1) {
      logd(p);
      mn[p] = 0;
    }
    return;
  }

  int c = ((x >> i) & 1);
  trie_pushup(i - 1, c == 0 ? tr[p][0] : tr[p][1], x);
  mn[p] = std::min(mn[tr[p][0]], mn[tr[p][1]]);
  if (mn[p] == std::numeric_limits<int>::max()) {
    if (e[tr[p][0]] == 1 && e[tr[p][1]] == 1) {
      int lv = trie_get(i - 1, tr[p][0]);
      int rv = (1 << i) + trie_get(i - 1, tr[p][1]);
      logd(i, lv, rv);
      mn[p] = lv ^ rv;
    }
  }
  logd(p, mn[p]);
}

void SolveCase(int Case) {
  int q;
  std::cin >> q;
  trie_init();

  for (int _ = 0; _ < q; ++_) {
    int op;
    std::cin >> op;
    if (op == 1) {
      int x;
      std::cin >> x;
      trie_insert(x);
      trie_pushup(M - 1, 1, x);
    } else if (op == 2) {
      int x;
      std::cin >> x;
      trie_delete(x);
      trie_pushup(M - 1, 1, x);
    } else if (op == 3) {
      std::cout << mn[1] << std::endl;
    }
  }
}
