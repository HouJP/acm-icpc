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

#define N (200000 + 5)

int t, n, m;
LL a[N], b[N], ans;

bool cmp(LL a, LL b) {
	return a > b;
}

void init() {
	scanf("%d", &t);
}

void in() {
	ans = 0;
	scanf("%d%d", &n, &m);
	REP(i, n) {
		scanf("%I64d", &a[i]);
	}
	REP(i, m) {
		scanf("%I64d", &b[i]);
	}
}

void run() {
	sort(a, a + n, cmp);
	sort(b, b + m);

	int tmp = MIN(n, m);
	REP(i, tmp) {
		if (a[i] > b[i]) {
			ans += a[i] - b[i];
		} else {
			break;
		}
	}
}

void out() {
	printf("%I64d\n", ans);
}

void out(int cas) {
}

int main() {
	freopen("data", "r", stdin);

	init();
	REP(i, t) {
		in();
		run();
		out();
	}

	return 0;
}
