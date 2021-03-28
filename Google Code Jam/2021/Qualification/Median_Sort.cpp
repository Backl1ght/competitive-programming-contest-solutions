#include<bits/stdc++.h>
using namespace std;

int N, r;

void dbg(string name, const vector<int>& v) {
    cerr << name << ": ";
    for (int x: v) cerr << x + 1 << " ";
    cerr << endl;
}
#define debug(x) dbg(#x, x);

void check(int x) {
    if (x == -1) exit(-1);
}

int cnt = 0;
map<tuple<int, int, int>, int> mp;
int query(int i, int j, int k) {
    ++i; ++j; ++k;
    if (mp.count(make_tuple(i, j, k))) return mp[make_tuple(i, j, k)] - 1;

    ++cnt;
    cout << i << " " << j << " " << k << endl;
    cin >> r;
    check(r);

    mp[make_tuple(i, j, k)] = r;
    mp[make_tuple(i, k, j)] = r;
    mp[make_tuple(j, i, k)] = r;
    mp[make_tuple(j, k, i)] = r;
    mp[make_tuple(k, i, j)] = r;
    mp[make_tuple(k, j, i)] = r;
    return r - 1;
}

vector<int> work(vector<int> a) {
    if (a.size() <= 2) {
        return a;
    }

    vector<int> c, p, b;
    int l = a[0], r = a[1];
    for (int i = 2; i < a.size(); ++i) {
        int k = query(l, r, a[i]);
        if (k == a[i]) c.push_back(a[i]);
        if (k == l) p.push_back(a[i]);
        if (k == r) b.push_back(a[i]);
    }

    c = work(c);
    p = work(p);
    b = work(b);

    if (c.size() >= 2) {
        int k = query(a[0], c[0], c[1]);
        if (k != c[0]) reverse(c.begin(), c.end());
    }
    if (p.size() >= 2) {
        int k = query(p[0], p[1], a[0]);
        if (k != p[1]) reverse(p.begin(), p.end());
    }
    if (b.size() >= 2) {
        int k = query(a[1], b[0], b[1]);
        if (k != b[0]) reverse(b.begin(), b.end());
    }

    vector<int> res;
    for (int x: p) res.push_back(x);
    res.push_back(a[0]);
    for (int x: c) res.push_back(x);
    res.push_back(a[1]);
    for (int x: b) res.push_back(x);

    return res;
}

void solve(int Case) {
    mp.clear(); cnt = 0;

    vector<int> a(N);
    for (int i = 0; i < N; ++i) a[i] = i;

    random_shuffle(a.begin(), a.end());

    vector<int> ans = work(a);

    for (int i = 0; i < N; ++i) cout << ans[i] + 1 << " ";
    cout << endl;

    cin >> r;
    check(r);

    cerr << cnt << endl;
}

int main() {
    int T, Q; 
    cin >> T >> N >> Q;
    for (int i = 1; i <= T; ++i) solve(i);
    return 0;
}
// python interactive_runner.py python local_testing_tool.py 0 -- Median_Sort.exe