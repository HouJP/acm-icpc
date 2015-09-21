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

#define N (1000000 + 10)

int nxt[N];
char tstr[N];
int tlen;
int ans;

// nxt数组下表范围 [0, len(tstr)]
void get_next() {
	int j = 0, k = -1;
	nxt[j] = k;
	while (j < tlen) {
		if (k == -1 || tstr[j] == tstr[k]) {
			nxt[++j] = ++k;
		} else {
			k = nxt[k];
		}
	}
}    


void init() {
}

void in() {
	tlen = strlen(tstr);
	ans = 1;
}

void run() {
	get_next();
	if (0 == tlen % (tlen - nxt[tlen])) {
		ans = tlen / (tlen - nxt[tlen]);
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
	while (~scanf("%s", tstr) && 0 != strcmp(tstr, ".")) {
		in();
		run();
		out();
	}

	return 0;
}
