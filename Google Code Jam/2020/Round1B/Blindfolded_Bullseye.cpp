#include<bits/stdc++.h>
using namespace std;

const long long N = 1e9;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> dist(0, 2 * N);
inline long long rnd() {
    return dist(rng) - N;
}

#define debug(x) cerr << #x << " : " << x << endl;
char s[50];
long long A, B, C = 250000000;
void solve() {
    long long x, y;

    for (x = -3; x <= 3; x++) {
        for(y = -3; y <=3; y++) {
            printf("%lld %lld\n", x*C, y*C); fflush(stdout);
            scanf("%s", s);
            assert(s[0]!='W');
            if(s[0]=='C') return;
            if(s[0]=='H')break;
        }
        if(s[0]=='H')break;
    }

    long long _x = 0, __x = 0, _y = 0, __y = 0;
    long long l, r, mid;

    // left
    l = -N; r = x*C;
    while(l <= r) {
        mid = (l+r)>>1;
        printf("%lld %lld\n", mid, y*C); fflush(stdout);
        scanf("%s", s);
        assert(s[0]!='W');
        if(s[0]=='C') return;
        if(s[0]=='H') r = mid-1;
        else l = mid + 1;
    }
    _x = l;


    // right
    l = x*C; r = N;
    while(l <= r) {
        mid = (l+r)>>1;
        printf("%lld %lld\n", mid, y*C); fflush(stdout);
        scanf("%s",s);
        assert(s[0]!='W');
        if(s[0]=='C') return;
        if(s[0]=='H') l = mid+1;
        else r = mid - 1;
    }
    __x = r;

    // up
    l = -N; r = y*C;
    while(l <= r) {
        mid = (l+r)>>1;
        printf("%lld %lld\n", x*C, mid); fflush(stdout);
        scanf("%s",s);
        assert(s[0]!='W');
        if(s[0]=='C') return;
        if(s[0]=='H') r = mid-1;
        else l = mid + 1;
    }
    _y = l;

    //down
    l = y*C; r = N;
    while(l <= r) {
        mid = (l+r)>>1;
        printf("%lld %lld\n", x*C, mid); fflush(stdout);
        scanf("%s", s);
        assert(s[0]!='W');
        if(s[0]=='C') return;
        if(s[0]=='H') l = mid+1;
        else r = mid - 1;
    }
    __y = r;

    cerr << _x << " " << __x << " " << _y << " " << __y << endl;

    x = (_x + __x) / 2;
    y = (_y + __y) / 2;

    printf("%lld %lld\n", x, y); fflush(stdout);
    scanf("%s",s);
    assert(s[0]=='C');
}

int main()
{
// #ifdef BACKLIGHT
//     // freopen("in.txt", "r", stdin);
// #endif
	long long T;
	scanf("%lld %lld %lld", &T, &A, &B);
	for (long long Case = 1; Case <= T; Case ++) solve();
	return 0;
}