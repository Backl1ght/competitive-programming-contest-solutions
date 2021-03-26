#include <bits/stdc++.h>
using namespace std;
 
void solve(int Case) { // printf("Case #%d: ", Case);
    string s;
    cin >> s;

    unordered_set<char> remain;
    for (char ch: s) remain.insert(ch);
    int m = remain.size(), t = m;

    auto unique = [&] (string s) {
        unordered_set<char> st;
        for (char ch: s) st.insert(ch);
        return st.size();
    };

    auto filter = [&] (string s, char target) {
        string res = "";
        int flag = false;
        for (char ch: s) {
            if (flag) {
                if (ch != target) res.push_back(ch);
            } else {
                if (ch == target) flag = true;
            }
        }
        return res;
    };

    auto can = [&] (string s, char ch) {
        string t = filter(s, ch);
        return unique(t) == m - 1;
    };

    string ans = "";
    for (int i = 0; i < t; ++i) {
        char ma = 0;
        for (char ch: remain) {
            if (can(s, ch)) ma = max(ma, ch);
        }

        ans.push_back(ma);
        remain.erase(ma);
        --m;
        s = filter(s, ma);
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