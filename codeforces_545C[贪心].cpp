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

#define INF (0x3f3f3f3f3f3f3f3fLL)
#define DINF ((-1)*(INF))

#define MAXN (100000 + 5)

int n, cnt;
LL x[MAXN], h[MAXN];

void init() {
}

void in() {
	for (int i = 0; i < n; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		x[i] = a;
		h[i] = b;
	}
	cnt = 0;
}

void run() {
	for (int i = 0;i < n; ++i) {
		LL l, r;
		if (0 == i) {
			l = DINF;
		} 
		if (n - 1 == i) {
			r = INF;
		} else {
			r = x[i + 1];
		}

		if (x[i] - h[i] > l) {
			l = x[i];
			++cnt;
		} else if (x[i] + h[i] < r) {
			l = x[i] + h[i];
			++cnt;
		} else {
			l = x[i];
		}
	}
}

void out() {
	printf("%d\n", cnt);
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
