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
#include <iostream>

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

#define N (1010)

int t, n, p, w, h;
int a[N];
int ans; // 答案
int np; // 每段多少行
int nt; // 需要的总行数
int nl; // 一行多少字
int nnt; // 总共可以容纳多少行

void init() {
	cin >> t;
}

void in() {
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	ans = 1;
}

void run() {
	for (int i = w; i > 1; --i) {
		nl = w / i;
		nt = 0;
		nnt = p * (h / i);
		for (int j = 0; j < n; ++j) {
			np = a[j] / nl;
			if (a[j] % nl != 0) {
				np += 1;
			}
			nt += np;
		}
		if (nt <= nnt) {
			ans = i;
			break;
		}
	}
}

void out() {
	cout << ans << endl;
}

void out(int cas) {
}

int main() {
	freopen("data", "r", stdin);

	init();
	while (cin >> n >> p >> w >> h) {
		in();
		run();
		out();
	}

	return 0;
}
