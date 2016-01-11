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

#define N (100000 + 2)

double a[2 * N];
double ans;
int n, w;

void init() {
}

void in() {
	int n2 = 2 * n;
	for (int i = 0; i < n2; ++i) {
		scanf("%lf", &a[i]);
	}
}

void run() {
	sort(a, a + 2 * n);
	if (2 * a[0] > a[n]) {
		ans = a[n] / 2 * 3 * n;
	} else {
		ans = a[0] * 3 * n;
	}
	if (ans > w) {
		ans = w;
	}
}

void out() {
	printf("%lf\n", ans);
}

void out(int cas) {
}

int main() {
	//freopen("data", "r", stdin);

	init();
	while (~scanf("%d%d", &n, &w)) {
		in();
		run();
		out();
	}

	return 0;
}
