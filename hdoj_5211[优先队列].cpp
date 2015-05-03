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

#define MAXN (10000)

int n, num[MAXN + 5], id[MAXN + 5], a, ans;
vector<vector<int> > yz;
priority_queue<int, vector<int>, greater<int> > que[MAXN + 5];

void init() {
	yz.assign(MAXN + 5, vector<int>());
	FOR(i, 1, MAXN) {
		int endf = int(sqrt(i));
		FOR(j, 1, endf) {
			if (0 == (i % j)) {
				yz[i].pb(j);
				yz[i].pb(i / j);
			}
		}
	}

	/*
	int tmp = 0;
	FOR(i, 1, MAXN) {
		printf("%d : ", i);
		tmp = MAX(tmp, sz(yz[i]));
		REP(j, sz(yz[i])) {
			printf("%d\t", yz[i][j]);
		}
		printf("\n");
	}
	printf("%d\n", tmp);
	*/
}

void in() {
	ans = 0;
	reset(id, 0);
	FOR(i, 0, MAXN) {
		while (!que[i].empty()) {
			que[i].pop();
		}
	}

	REP(i, n) {
		scanf("%d", &a);
		num[i] = a;
		que[a].push(i);
	}
}

void run() {
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < yz[num[i]].size(); ++j) {
			int tmp = yz[num[i]][j];
			while (!que[tmp].empty() && que[tmp].top() < i) {
				id[que[tmp].top()] = i;
				que[tmp].pop();
			}
		}
	}
}

void out() {
	for (int i = 0; i < n; ++i) {
		if (id[i]) {
			ans += id[i] + 1;
		}
	}
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
