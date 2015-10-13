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

/* 树状数组求最值
 *
 * 树状数组求解最值只能往一个方向改变，即求解最大值的时候modify操作只能增大。
 */
#define lowbit(u) (u&(-u))
#define MAXN (10000)

int s[MAXN + 5];

void add(int u, int v) {
	for (int i = u; i <= MAXN; i += lowbit(i)) s[i] = MAX(s[i], v);
}

int sum(int u) {
	int ans = 0;
	for(int i = u; i; i -= lowbit(i)) ans = MAX(ans, s[i]);
	return ans;
}

/* 树状数组 END */

#define N (100000)
int num[2 * N + 5];
int ss[N + 5][2];
int ans, n;

int solve(int l, int r) {
	if (l > r) {
		return MAXN;
	}

	reset(s, 0);
	for (int i = l; i <= r; ++i) {
		int tmp_pos = MAXN - num[i];
		int ret = sum(tmp_pos);
	
		if (MAXN == num[i]) {
			ss[i - l][0] = ret;
		} else {
			add(tmp_pos, num[i] + ret);
			ss[i - l][0] = num[i] + ret;
		}

		if (i > l) {
			ss[i - l][0] = MAX(ss[i - l][0], ss[i - l - 1][0]);
		}
	}

	reset(s, 0);
	for (int i = r; i >= l; --i) {
		int tmp_pos = MAXN - num[i];
		int ret = sum(tmp_pos);

		if (MAXN == num[i]) {
			ss[i - l][1] = ret;
		} else {
			add(tmp_pos, num[i] + ret);
			ss[i - l][1] = num[i] + ret;
		}

		if (i < r) {
			ss[i - l][1] = MAX(ss[i - l][1], ss[i - l + 1][1]);
		}
	}

	int ret = MAX(ss[r - l][0], ss[0][1]);
	for (int i = 0; i < r - l; ++i) {
		ret = MAX(ret, ss[i][0] + ss[i + 1][1]);
	}

	return ret + MAXN;
}

void init() {
}

void in() {
	ans = 0;

	REP(i, n) {
		scanf("%d", &num[i]);
		num[i + n] = num[i];
	}
}

void run() {
	for (int i = 0; i < n; ++i) {
		if (num[i] == MAXN) {
			ans = MAX(ans, solve(i + 1, i + n - 1));
		}
	}
}

void out() {
	printf("%d\n", ans);
}

void out(int cas) {
}

int main() {
	freopen("data", "r", stdin);

	init();
	while (~scanf("%d", &n)) {
		in();
		run();
		out();
	}

	return 0;
}
