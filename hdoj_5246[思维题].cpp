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

#define N (10000 + 2)

int t;
LL n, m, k, now;
LL num[N];
bool ans;

void init() {
	scanf("%d", &t);
}

void in() {
	bool ans = false;
	scanf("%I64d%I64d%I64d", &n, &m, &k);
	for (int i = 0; i < n; ++i) {
		scanf("%I64d", &num[i]);
	}
}

void run() {
	sort(num, num + n);
	if (m >= num[n - 1]) {
		ans = true;
		return;
	}
	int from = upper_bound(num, num + n, m) - num - 1;
	if (from == -1) {
		ans = false;
		return;
	}
	for (int i = from + 1; i < n; ++i) {
		if (num[i - 1] + k < num[i]) {
			ans = false;
			return;
		} else {
			if (num[i - 1] + k >= num[n - 1]) {
				ans = true;
				return;
			} else {
				--k;
			}
		}
	}
}

void out() {
}

void out(int cas) {
	printf("Case #%d:\n", cas);
	if (ans) {
		printf("why am I so diao?\n");
	} else {
		printf("madan!\n");
	}
}

int main() {
	freopen("data", "r", stdin);

	init();
	for (int i = 1; i <= t; ++i) {
		in();
		run();
		out(i);
	}

	return 0;
}
