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

#define MAXN (100000 + 2)

int t, cas, n, ans;
int num[MAXN];

bool judge(int x) {
	int pre = num[0] - x;
	for (int i = 1; i < n; ++i) {
		if (pre >= num[i] + x) {
			return false;
		} else {
			pre = MAX(pre + 1, num[i] - x);
		}
	}
	return true;
}

void init() {
	scanf("%d", &t);
}

void in() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &num[i]);
	}
}

void run() {
	int l = 0, r = 1000000, m;
	while (l <= r) {
		m = (l + r) / 2;
		if (judge(m)) {
			r = m - 1;
		} else {
			l = m + 1;
		}
	}
	ans = l;
}

void out() {
	printf("Case #%d:\n%d\n", cas, ans);
}

void out(int cas) {
}

int main() {
	freopen("data", "r", stdin);

	init();
	for (cas = 1; cas <= t; ++cas) {
		in();
		run();
		out();
	}

	return 0;
}
