#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5;

int n, a[N];
int main() {
    scanf("%d", &n);

    int v1, v2, p = 1;
    for (int i = 2; i <= n; ++i) {
        printf("? %d %d\n", p, i); fflush(stdout);
        scanf("%d", &v1);
        assert(v1 != -1);

        printf("? %d %d\n", i, p); fflush(stdout);
        scanf("%d", &v2);
        assert(v2 != -1);

        if (v1 > v2) a[p] = v1, p = i;
        else a[i] = v2;
    }
    a[p] = n;

    printf("!");
    for (int i = 1;  i <= n; ++i) printf(" %d", a[i]);
    printf("\n");
    return 0;
}