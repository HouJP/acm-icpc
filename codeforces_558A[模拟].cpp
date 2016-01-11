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

#define N (200 + 5)

struct Node {
	int pos;
	int num;
};

int n;
Node nodes[N];
int cnt[2];
int ans;
int sum[N];

bool cmp(Node a, Node b) {
	return a.pos < b.pos;
}

void init() {
}

void in() {
	ans = 0;
	reset(cnt, 0);

	REP(i, n) {
		scanf("%d%d", &nodes[i].pos, &nodes[i].num);
		if (nodes[i].pos < 0) {
			++cnt[0];
		} else {
			++cnt[1];
		}
	}
}

void run() {
	sort(nodes, nodes + n, cmp);

	sum[0] = nodes[0].num;
	FOR(i, 1, n - 1) {
		sum[i] = sum[i - 1] + nodes[i].num;
	}
	if (cnt[0] < cnt[1]) {
		ans = sum[2 * cnt[0]];
	} else if (cnt[0] > cnt[1]) {
		if (n - 2 * cnt[1] - 1 == 0) {
			ans = sum[n - 1];
		} else {
			ans = sum[n - 1] - sum[n - 1 - 2 * cnt[1] - 1];
		}
	} else {
		ans = sum[n - 1];
	}
}

void out() {
	printf("%d\n", ans);
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
