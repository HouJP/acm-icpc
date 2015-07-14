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

#define N (1000 + 5) 
#define MOD (1000000007)

char a[N], b[N];
int len1, len2;
int t;
LL dp_len[N][N];
LL dp_cnt[N][N];
LL last[N][N];

void init() {
	scanf("%d", &t);
}

void in() {
	reset(last, 0);
	reset(dp_len, 0);
	reset(dp_cnt, 0);

	scanf("%s %s", &a[1], &b[1]);
	len1 = strlen(&a[1]);
	len2 = strlen(&b[1]);
	//printf("len1 = %d, len2 = %d\n", len1, len2);

	FOR(i, 0, len1) {
		dp_cnt[i][0] = 1;
	}
	FOR(i, 0, len2) {
		dp_cnt[0][i] = 1;
	}
}

void run() {
	FOR(i, 1, len1) {
		FOR(j, 1, len2) {
			if (a[i] == b[j]) {
				last[i][j] = j;
			} else {
				last[i][j] = last[i][j - 1];
			}
			//printf("i = %d, j = %d, last[i][j] = %I64d\n", i, j, last[i][j]);
			
			if (a[i] == b[j]) {
				dp_len[i][j] = dp_len[i - 1][j - 1] + 1;
			} else {
				dp_len[i][j] = MAX(dp_len[i - 1][j], dp_len[i][j - 1]);
			}
			//printf("i = %d, j = %d, dp_len[i][j] = %I64d\n", i, j, dp_len[i][j]);

			if (dp_len[i][j] == dp_len[i - 1][j]) {
				dp_cnt[i][j] = (dp_cnt[i][j] + dp_cnt[i - 1][j]) % MOD;
			}
			if ((last[i][j] > 0) && (dp_len[i][j] == (dp_len[i - 1][last[i][j] - 1] + 1))) {
				dp_cnt[i][j] = (dp_cnt[i][j] + dp_cnt[i - 1][last[i][j] - 1]) % MOD;
			}
			//printf("i = %d, j = %d, dp_cnt[i][j] = %I64d\n", i, j, dp_cnt[i][j]);
		}
	}
}

void out() {
	printf("%I64d\n", dp_cnt[len1][len2]);
}

void out(int cas) {
}

int main() {
	freopen("data", "r", stdin);

	init();
	REP(i, t) {
		in();
		run();
		out();
	}

	return 0;
}
