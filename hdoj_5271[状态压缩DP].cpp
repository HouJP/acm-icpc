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
#include <iostream>
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

#define MOD (1000000007)

struct Point {
	int x;
	int y;
	Point() {}
	Point(int _x, int _y): x(_x), y(_y) {}
};

struct Cond {
	Point p1;
	Point p2;
	int v;
	Cond() {

	}
	Cond(Point _p1, Point _p2, int _v): p1(_p1), p2(_p2), v(_v) {}
};

Cond cond[15];

LL dp[2][(1 << 10) + 5];
int flag;

int t, h, w, m, n;
int xx1, yy1, xx2, yy2, v;
int xx[30], yy[30];
int cntx, cnty;

LL fast_pow(LL a, int e) {
	LL ret = 1;
	while (e) {
		if (e & 1) {
			ret = (ret * a) % MOD;
		}
		a = (a * a) % MOD;
		e >>= 1;
	}
	return ret;
}

int get_minv(Point p1, Point p2) {
	int minv = m;
	REP(i, n) {
		if ((p1.x >= cond[i].p1.x - 1) 
			&& (p1.y >= cond[i].p1.y - 1)
			&& (p2.x <= cond[i].p2.x)
			&& (p2.y <= cond[i].p2.y)) {
			minv = MIN(minv, cond[i].v);
		}
	}
	return minv;
}

int get_minc(Point p1, Point p2, int minv) {
	int minc = 0;
	REP(i, n) {
		if ((p1.x >= cond[i].p1.x - 1) 
			&& (p1.y >= cond[i].p1.y - 1)
			&& (p2.x <= cond[i].p2.x)
			&& (p2.y <= cond[i].p2.y)
			&& (minv == cond[i].v)) {
			minc |= (1 << i);
		}
	}
	return minc;
}

void init() {
	scanf("%d", &t);
}

void in() {
	scanf("%d%d%d%d", &h, &w, &m, &n);

	reset(dp, 0);
	flag = 0;
	dp[flag][0] = 1;

	cntx = cnty = 0;
	xx[cntx++] = 0;
	xx[cntx++] = h;
	yy[cnty++] = 0;
	yy[cnty++] = w;

	REP(i, n) {
		scanf("%d%d%d%d%d", &xx1, &yy1, &xx2, &yy2, &v);
		cond[i] = Cond(Point(xx1, yy1), Point(xx2, yy2), v);
		xx[cntx++] = xx1 - 1;
		yy[cnty++] = yy1 - 1;
		xx[cntx++] = xx2;
		yy[cnty++] = yy2;
	}

	sort(xx, xx + cntx);
	cntx = unique(xx, xx + cntx) - xx;
	sort(yy, yy + cnty);
	cnty = unique(yy, yy + cnty) - yy;
}

void run() {
	REP(i, cntx - 1) {
		REP(j, cnty - 1) {
			int nxt = flag ^ 1;
			int maxn = 1 << n;
			for (int k = 0; k < maxn; ++k) {
				dp[nxt][k] = 0;
			}
			int minv = get_minv(Point(xx[i], yy[j]), Point(xx[i + 1], yy[j + 1]));
			int minc = get_minc(Point(xx[i], yy[j]), Point(xx[i + 1], yy[j + 1]), minv);
			LL v1 = fast_pow(minv - 1, (xx[i + 1] - xx[i]) * (yy[j + 1] - yy[j]));
			LL v2 = (fast_pow(minv, (xx[i + 1] - xx[i]) * (yy[j + 1] - yy[j])) - v1 + MOD) % MOD;
			//int maxn = 1 << n;
			for (int k = 0; k < maxn; ++k) {
				if (dp[flag][k] == 0) {
					continue;
				}
				dp[nxt][k] = (dp[nxt][k] + dp[flag][k] * v1) % MOD;
				dp[nxt][k | minc] = (dp[nxt][k | minc] + dp[flag][k] * v2) % MOD;
			}
			flag = nxt;
		}
	}
}

void out() {
}

void out(int cas) {
	printf("Case #%d: %lld\n", cas, ((dp[flag][(1 << n) - 1]) + MOD) % MOD);
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
