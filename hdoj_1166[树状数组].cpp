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

#define INF (0x3f3f3f3f)
#define NINF ((-1)*INF)
#define INFLL (0x3f3f3f3f3f3f3f3fLL)
#define NINFLL ((-1)*INFLL)

#define MAXN (50000)

int array[MAXN + 5];

int lowbit(int x) {
	return x & (-x);
}

void modify(int x, int add) {
	while (x <= MAXN) {
		array[x] += add;
		x += lowbit(x);
	}
}

int get_sum(int x) {
	int ret = 0;
	while (x != 0) {
		ret += array[x];
		x -= lowbit(x);
	}
	return ret;
}

int t, l, r, num, n;
char cmd[20];

void init() {
	scanf("%d", &t);
}

void in(int cas) {
	printf("Case %d:\n", cas);
	memset(array, 0, sizeof(array));

	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &num);
		modify(i + 1, num);
	}

	while (~scanf("%s", cmd) && (strcmp(cmd, "End"))) {
		scanf("%d%d", &l, &r);
		//printf("%s: %d, %d\n", cmd, l, r);
		if (!strcmp(cmd, "Query")) {
			printf("%d\n", get_sum(r) - get_sum(l - 1));
		} else if (!strcmp(cmd, "Add")) {
			modify(l, r);
		} else {
			modify(l, -1 * r);
		}
	}
}

void run() {
}

void out() {
}

void out(int cas) {
}

int main() {
	freopen("data", "r", stdin);

	init();
	REP(i, t) {
		in(i + 1);
		run();
		out();
	}

	return 0;
}
