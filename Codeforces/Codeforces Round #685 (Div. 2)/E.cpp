#include <bits/stdc++.h>
using namespace std;

#define FOR(i, _, __) for (int i = (_); i <= (__); ++i)

const int N = (1 << 16) + 5;

int n, a[N], b[N], vis[N];

int p1, p2;
bool existEqual() {
    FOR(i, 2, n) {
        if (b[i] == 0) {
            p1 = 1; p2 = i;
            return true;
        }

        if (vis[b[i]]) {
            p1 = vis[b[i]];
            p2 = i;
            return true;
        }

        vis[b[i]] = i;
    }
    return false;
}

int main()
{
    cin >> n;

    FOR(i, 2, n) {
        cout << "XOR" << " " << 1 << " " << i << endl;
        cin >> b[i];
    }

    if (existEqual()) {
        // a_{p1} = a_{p2}
        cout << "OR" << " " << p1 << " " << p2 << endl;
        cin >> a[p1];
        a[1] = b[p1] ^ a[p1];
    } else {
        // a pairwise distinct
        int v1, v2;
        FOR(i, 2, n) {
            if (b[i] == 1) p1 = i;
            if (b[i] == 2) p2 = i;
        }
        cout << "AND 1 " << p1 << endl;
        cin >> v1;

        cout << "AND 1 " << p2 << endl;
        cin >> v2;

        a[1] = v1 | v2;
    }

    FOR(i, 2, n) a[i] = b[i] ^ a[1];

    cout << "!";
    FOR(i, 1, n) cout << " " << a[i];
    cout << endl;
    return 0;
}