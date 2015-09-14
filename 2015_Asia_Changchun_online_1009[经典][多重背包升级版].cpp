/*************************************************************************
    > Author: HouJP
    > Mail: houjp1992@gmail.com
 ************************************************************************/

/**
 * 多重背包用来解这样一类问题：多种物品，价值和体积各不相同，每种物品有限个数，背包体积为V，问背包可装的最大价值。
 * 有两种优化方式：
 * 	1.	物品个数的二进制优化。
 *	2.	当背包体积过于巨大的时候，不适合在体积的维度上DP。原先在体积上DP求解的是某体积下可容纳的最大价值，那么可以转换为以价值作为维度，求解装载某价值物品所需要的最小体积。适用于限制价值、体积过于庞大的情况（求解达到某个最小价值所需要的最小体积）。
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

#define V (50010)
#define N (210)

const int v = 50000;
int t, n, m, p;
int minv, minc;
int x, y, z;
int f[V];
bool has_ans;

inline void zero_one_pack_2(int cost, int weight) {
	FORD(i, v, cost) {
		f[i] = MAX(f[i], f[i - cost] + weight);
	}
}

inline void multiple_pack_2(int cost, int weight, int amount) {
	int k = 1;
	while (k < amount) {
		zero_one_pack_2(k * cost, k * weight);
		amount -= k;
		k <<= 1;
	}
	if (amount > 0) {
		zero_one_pack_2(amount * cost, amount * weight);
	}
}

inline void zero_one_pack(int cost, int weight) {
	FORD(i, p - 1, 0) {
		int cost_now = MIN(p, i + cost);
		f[cost_now] = MIN(f[cost_now], f[i] + weight);
	}
}

inline void multiple_pack(int cost, int weight, int amount) {
	int k = 1;
	while (k < amount) {
		zero_one_pack(k * cost, k * weight);
		amount -= k;
		k <<= 1;
	}
	if (amount > 0) {
		zero_one_pack(amount * cost, amount * weight);
	}
}

void init() {
	scanf("%d", &t);
}

void in() {
	has_ans = true;
	scanf("%d%d%d", &n, &m, &p);
}

void run() {
	// first 
	reset(f, 0x3f);
	f[0] = 0;
	REP(i, n) {
		scanf("%d%d%d", &x, &y, &z);
		multiple_pack(x, y, z);
	}
	if (f[p] < INF) {
		minv = f[p];
	} else {
		has_ans = false;
		return;
	}
	
	// second
	reset(f, 0);
	REP(i, m) {
		scanf("%d%d%d", &x, &y, &z);
		multiple_pack_2(y, x, z);
	}

	minc = INF;
	FORD(i, v, 0) {
		if (f[i] >= minv) {
			minc = i;
		}
	}
	if (minc == INF) {
		has_ans = false;
		return;
	}
}

void out() {
	if (has_ans) {
		printf("%d\n", minc);
	} else {
		printf("TAT\n");
	}
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
