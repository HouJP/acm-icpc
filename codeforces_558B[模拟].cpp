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

#define N (1000000 + 5)

int lr[N][3];
int n, num;
int ans;
int min_len;
int max_num;

void init() {
}

void in() {
	reset(lr, -1);
	max_num = -1;
	min_len = INF;

	REP(i, n) {
		scanf("%d", &num);
		if (lr[num][0] == -1 || lr[num][0] > i) {
			lr[num][0] = i;
		}
		if (lr[num][1] == -1 || lr[num][1] < i) {
			lr[num][1] = i;
		}
		++lr[num][2];
		max_num = MAX(max_num, lr[num][2]);
	}
}

void run() {
	REP(i, N) {
		if ((lr[i][0] != -1) && (lr[i][2] == max_num) && (lr[i][1] - lr[i][0] < min_len)) {
			min_len = lr[i][1] - lr[i][0];
			ans = i;
		}
	}
}

void out() {
	printf("%d %d\n", lr[ans][0] + 1, lr[ans][1] + 1);
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
