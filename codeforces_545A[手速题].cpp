/*************************************************************************
    > Author: HouJP
    > Mail: houjp1992@gmail.com
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <map>

using namespace std;

#define LL long long

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x)	x.begin(), x.end()
#define rall(x)	x.rbegin(), x.rend()
#define sz(a)	int(a.size())
#define reset(a, x)	memset(a, x, sizeof(a))

#define MAX(a,b)		((a) > (b) ? (a) : (b))
#define MIN(a,b)		((a) > (b) ? (b) : (a))
#define ABS(a)			((a) > 0 ? (a) : (-(a)))
#define FOR(i, a, b)	for(int i = a; i <= b; ++i)
#define FORD(i, a, b)	for(int i = a; i >= b; --i)
#define REP(i, n)		for(int i = 0, _n = n; i < _n; ++i)
#define REPD(i, n)		for(int i = n - 1; i >= 0; --i)
#define FORSZ(i, x)		for(int i = 0; i < sz(x); ++i)

#define MAXN (100 + 2)
bool ans[MAXN];
int cnt;
int n, a;

void init() {
}

void in() {
    memset(ans, 0, sizeof(ans));
    cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j= 0; j < n; ++j) {
            scanf("%d", &a);
            if ((1 == a) || (3 == a)) {
                ans[i] = true;
            }
        }
        if (!ans[i]) {
            ++cnt;
        }
    }
}

void run() {
    bool fir = true;
    printf("%d\n", cnt);
    for (int i = 0; i < n; ++i) {
        if (!ans[i]) {
            if (!fir) {
                printf(" ");
            } else {
                fir = false;
            }
            printf("%d", i + 1);
        }
    }
    if (cnt)
        printf("\n");
}

void out() {
}

void out(int cas) {
}

int main() {
	//freopen("data", "r", stdin);

	init();
    while (~scanf("%d", &n)) {
        in();
        run();
        out();
    }

	return 0;
}
