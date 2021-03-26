#include <bits/stdc++.h>
using namespace std;
 
void solve(int Case) { // printf("Case #%d: ", Case);
    string a, b;
    cin >> a >> b;

    unordered_set<string> s;
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j <= i; ++j) {
            s.insert(a.substr(j, i - j + 1));
        }
    }

    int ans = a.size() + b.size();
    for (int i = 0; i < b.size(); ++i) {
        for (int j = 0; j <= i; ++j) {
            string ss = b.substr(j, i - j + 1);
            if (s.count(ss)) {
                ans = min(ans, int(a.size() + b.size() - 2 * ss.size()));
            }
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T = 1;
    cin >> T;
    for (int _ = 1; _ <= T; _++) solve(_);
    return 0;
}