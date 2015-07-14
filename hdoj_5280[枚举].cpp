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

#define N (1000 + 5)
#define INF (0x3f3f3f3f3f3f3f3fLL)

int t;
LL n, p;
LL sum[N][N];
LL minn[N][N];
LL ans;

void init() {
	scanf("%d", &t);
}

void in() {
	scanf("%I64d%I64d", &n, &p);

	reset(sum, 0);
	ans = (-1) * INF;

	for (int i = 0; i < n; ++i) {
		scanf("%I64d", &sum[i][i]);
		minn[i][i] = sum[i][i];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			sum[i][j] = sum[i][j - 1] + sum[j][j];
			minn[i][j] = MIN(minn[i][j - 1], sum[j][j]);
		}
	}
}

void run() {
	for (int i = 0; i < n; ++i) {
		for (int j = i; j < n; ++j) {
			//printf("i = %d, j = %d, sum = %I64d\n", i, j, sum[i][j]);
			ans = MAX(ans, sum[i][j] + p - minn[i][j]);
			if ((j - i + 1) != n) {
				ans = MAX(ans, sum[i][j]);
			}
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
	//while (~scanf("%I64d%I64d", &n, &p)) {
		in();
		run();
		out();
	}

	return 0;
}
