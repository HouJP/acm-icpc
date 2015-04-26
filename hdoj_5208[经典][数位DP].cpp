/*************************************************************************
    > Author: HouJP
    > Mail: houjp1992@gmail.com
 ************************************************************************/

/*
 * 思路：数位DP经典
 *
 * 比赛的时候想到从高位向低位考虑，但是没有想到用DP，而是二分查找上下界，复杂度过不了。
 *
 * 主要是没有发现不需要二分查找上下界，当枚举了上一个bit的状态(0/1)的时候，这个bit之后的bits组成的范围其实随之固定了，要么上下界还是边界，要么下界全为0，要么上界全为1。
 *
 * 到这里就应该很自然的过渡到DP，加记忆化搜索。
 *
 * */

#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
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

#define LEN (30)

int t, l1, r1, l2, r2, ans;
bool vis[LEN + 5][2][2][2][2];
int dp[LEN + 5][2][2][2][2];

void init() {
	scanf("%d", &t);
}

int dp_f(int p, bool sl1, bool sr1, bool sl2, bool sr2) {
	if (-1 == p) {
		return 0;
	} 
	if (vis[p][sl1][sr1][sl2][sr2]) {
		return dp[p][sl1][sr1][sl2][sr2];
	}
	bool nl1, nr1, nl2, nr2;
	if (sl1) {
		nl1 = 0;
	} else {
		nl1 = l1 >> p & 0x01;
	}
	if (sr1) {
		nr1 = 1;
	} else {
		nr1 = r1 >> p & 0x01;
	}
	if (sl2) {
		nl2 = 0;
	} else {
		nl2 = l2 >> p & 0x01;
	} 
	if (sr2) {
		nr2 = 1;
	} else {
		nr2 = r2 >> p & 0x01;
	}
	//printf("p = %d\tnl1 = %d\tnr1 = %d\tnl2 = %d\tnr2 = %d\n", p, nl1, nr1, nl2, nr2);
	if (nl1 != nr1 && nl2 != nr2) {
		dp[p][sl1][sr1][sl2][sr2] = (0 << p) | MAX(dp_f(p - 1, sl1, 1, sl2, 1), dp_f(p - 1, 1, sr1, 1, sr2));
	}
	if (nl1 != nr1 && nl2 == nr2) {
		if (nl2) {
			dp[p][sl1][sr1][sl2][sr2] = (1 << p) | dp_f(p - 1, sl1, 1, sl2, sr2);
		} else {
			dp[p][sl1][sr1][sl2][sr2] = (1 << p) | dp_f(p - 1, 1, sr1, sl2, sr2);
		}
	}
	if (nl1 == nr1 && nl2 != nr2) {
		if (nl1) {
			dp[p][sl1][sr1][sl2][sr2] = (0 << p) | dp_f(p - 1, sl1, sr1, 1, sr2);
		} else {
			dp[p][sl1][sr1][sl2][sr2] = (0 << p) | dp_f(p - 1, sl1, sr1, sl2, 1);
		}
	}
	if (nl1 == nr1 && nl2 == nr2) {
		dp[p][sl1][sr1][sl2][sr2] = ((nl1 == nl2 ? 0 : 1) << p) | dp_f(p - 1, sl1, sr1, sl2, sr2);
	}
	vis[p][sl1][sr1][sl2][sr2] = 1;
	//printf("%d\t%d\t%d\t%d\t%d\tdp = %d\n", p, sl1, sr1, sl2, sr2, dp[p][sl1][sr1][sl2][sr2]);
	return dp[p][sl1][sr1][sl2][sr2];
}

void in() {
	scanf("%d%d%d%d", &l1, &r1, &l2, &r2);

	reset(vis, 0);
}

void run() {
	ans = dp_f(30, 0, 0, 0, 0);
}

void out() {
}

void out(int cas) {
	printf("Case #%d: %d\n", cas, ans);
}

int main() {
	freopen("data", "r", stdin);

	init();
	REP(i, t) {
		in();
		run();
		out(i + 1);
	}

	return 0;
}
