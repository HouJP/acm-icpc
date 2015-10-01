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
#include <iostream>
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

LL c, k1, k2, b1;
LL a, b;
int cas;
int cnt;

LL fast_pow(LL a, LL e) {
	LL ret = 1;
	while (e) {
		if (e & 0x01) {
			ret = (ret * a) % c;
		}
		a = (a * a) % c;
		e >>= 1;
	}
	return ret;
}

void init() {
	cas = 0;
}

void in() {
	cnt = 0;
}

void run() {
	printf("Case #%d:\n", ++cas);
	for (int i = 1; i < c; ++i) {
		a = i;
		b = (c - fast_pow(a, (k1 + b1))) % c;
		b = (b + c) % c;
		if ((b > 0) 
			&& ((a == 0) 
				|| ((fast_pow(a, k1) - fast_pow(b, k2)) % c == 0))) {
			cout << a << " " << b << endl;
			++cnt;
		}
	}
}

void out() {
	if (0 == cnt) {
		cout << "-1" << endl;
	}
}

void out(int cas) {
}

int main() {
	freopen("data", "r", stdin);

	init();
	while (cin >> c >> k1 >> b1 >> k2) {
		in();
		run();
		out();
	}

	return 0;
}
