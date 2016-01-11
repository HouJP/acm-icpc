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

#define N (2000 + 2)

int n;
int a[N];
int b[N];
int c[N];

bool cmp(int a, int b) {
	return a > b;
}

void init() {
}

void in() {
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
}

void run() {
	sort(b, b + n);
	c[n - 1] = 1;
	for (int i = n - 2; i >= 0; --i) {
		if (b[i] == b[i + 1]) {
			c[i] = c[i + 1];
		} else {
			c[i] = n - i;
		}
	}
	/*
	for (int i = 0; i < n; ++i) {
		printf("a = %d, b = %d, c = %d\n", a[i], b[i], c[i]);
	}
	*/
}

void out() {
	for (int i = 0; i < n; ++i) {
		int pos = lower_bound(b, b + n, a[i]) - b;
		pos = c[pos];
		if (0 != i) {
			printf(" ");
		}
		printf("%d", pos);
	}
	printf("\n");
}

void out(int cas) {
}

int main() {
	//freopen("data", "r", stdin);

	init();
	while (~scanf("%d", &n)) {
		in();
		run();
		out();
	}

	return 0;
}
