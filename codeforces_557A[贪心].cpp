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

int n;
int num[3][2];
int ans[3];

void init() {
}

void in() {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0;j < 2; ++j) {
			scanf("%d", &num[i][j]);
		}
	}
}

void run() {
	ans[0] = n - num[1][0] - num[2][0];
	if (ans[0] > num[0][1]) {
		ans[0] = num[0][1];
	}
	n = n - ans[0];
	ans[1] = n - num[2][0];
	if (ans[1] > num[1][1]) {
		ans[1] = num[1][1];
	}
	ans[2] = n - ans[1];
}

void out() {
	printf("%d %d %d\n", ans[0], ans[1], ans[2]);
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
