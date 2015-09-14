/*************************************************************************
    > Author: HouJP
    > Mail: houjp1992@gmail.com
 ************************************************************************/

/*
 * 思路
 *
 * dp[i][k] = min(dp[i'][k-1] + seg[i'+1][i]), k-1 <= i' <= i
 * limit[i-1][k] <= limit[i][k] <= limit[i][k+1]
 * 四边形优化适用于dp方程中，枚举的变量i'被两维变量分别限制。
 * 各种变量赋初值很重要。
 */

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

#define N (1000 + 5) 

int n, m;
int num[N];
int dp[N][N];
int seg[N][N];
int limit[N][N];

void init() {
}

void in() {
	reset(dp, 0x7f);

	REP(i, n) {
		scanf("%d", &num[i]);
	}
}

void run() {
	REP(i, n) {
		FOR(j, i, n - 1) {
			if (i == j) {
				seg[i][j] = 0;
			} else {
				seg[i][j] = seg[i][j - 1] + num[i] * num[j];
			}
		}
	}
	FOR(i, 3, n) {
		FOR(j, 0, n - i) {
			seg[j][j + i - 1] += seg[j + 1][j + i - 1];
		}
	}
	/*
	REP(i, n) {
		REP(j, n) {
			printf("%d\t", seg[i][j]);
		}
		printf("\n");
	}
	*/
	REP(i, n) {
		FORD(k, i + 1, 1) {
			if (0 == i) {
				dp[i][k] = 0;
				limit[i][k] = -1;
			} else {
				if (k == i + 1) {
					dp[i][k] = 0;
					limit[i][k] = i - 1;
				} else {
					if (k == 1) { // !important
						dp[i][k] = seg[0][i];
						limit[i][k] = -1;
					} else {
						int minn = MAX(0, limit[i - 1][k]);
						int maxx = MIN(i - 1, limit[i][k + 1]);
						FOR(j, minn, maxx) {
							if (dp[i][k] > dp[j][k - 1] + seg[j + 1][i]) {
								dp[i][k] = dp[j][k - 1] + seg[j + 1][i];
								limit[i][k] = j;
							}
						}
					}
				}
			}
		}
	}
	/*
	REP(i, n) {
		REP(j, m + 2) {
			printf("%d\t", limit[i][j]);
		}
		printf("\n");
	}

	REP(i, n) {
		REP(j, m + 2) {
			printf("%d\t", dp[i][j]);
		}
		printf("\n");
	}
	*/
}

void out() {
	printf("%d\n", dp[n - 1][m + 1]);
}

void out(int cas) {
}

int main() {
	//freopen("data", "r", stdin);

	init();
	while (~scanf("%d%d", &n, &m) && (0 != n || 0 != m)) {
		in();
		run();
		out();
	}

	return 0;
}
