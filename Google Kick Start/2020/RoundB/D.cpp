#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;

double lg[N], lstr[N], lstc[N];
int main()
{
#ifdef BACKLIGHT
    freopen("in.txt", "r", stdin);
#endif

	lg[0] = 0;
	for (int i =1; i <= 2e5; ++i) lg[i] = lg[i-1] + log2(i);

	int T;
	scanf("%d", &T);
	for (int Case = 1; Case <= T; Case ++) {
		int n, m, l, r, u, d;
		scanf("%d %d %d %d %d %d", &n, &m, &l, &u, &r, &d);

		lstr[1] = pow(2, lg[1 + n - 2] - lg[1 - 1] - lg[n - 1] - 1 - n + 2);
		for (int i = 2; i <= m; i++) {
			lstr[i] = lstr[i-1] + 0.5 * pow(2, lg[i + (n-1)- 2] - lg[i - 1] - lg[(n-1) - 1] - i - (n-1) + 2);
		}

		lstc[1] = pow(2, lg[1 + m - 2] - lg[1 - 1] - lg[m - 1] - 1 - m + 2);
		for (int i = 2; i <= n; i++) {
			lstc[i] = lstc[i-1] + 0.5 * pow(2, lg[i + (m-1)- 2] - lg[i - 1] - lg[(m-1) - 1] - i - (m-1) + 2);
		}

		double ans = 0, tmp;
		for (int i = 1; i <= l - 1; ++i) {
			int D = l + d - i;
			if(D > m) continue;
			else if(D == m) {
				ans += lstc[i];
			}
			else {
				tmp = lg[i + D - 2] - lg[i - 1] - lg[D - 1] - i - D + 2;
				ans += pow(2, tmp);
			}
		}

		for (int i = 1; i <= u - 1; ++i) {
			int R = r + u - i;
			if(R > n) continue;
			else if(R == n) {
				ans += lstr[i];
			}
			else {
				tmp = lg[i + R - 2] - lg[i - 1] - lg[R - 1] - i - R + 2;
				ans += pow(2, tmp);
			}
		}

		printf("Case #%d: %.12lf\n", Case, ans);
	}
	return 0;
}