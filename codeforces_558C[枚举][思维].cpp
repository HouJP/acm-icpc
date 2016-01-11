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

#define N (100000 + 5)
#define M (20)

int n, num, ans;
char s[N][M];
int len[N];
int zero[N];
char pre[M];
int pre_len;


void init() {
}

void in() {
	reset(len, 0);
	reset(zero, 0);
	ans = INF;

	REP(i, n) {
		scanf("%d", &num);
		while (num) {
			s[i][len[i]++] = '0' + num % 2;
			num >>= 1;
		}
		s[i][len[i]] = '\0';
		//printf("%d\t%s\n", len[i], s[i]);
	}
}

void run() {
	REP(i, len[0]) {
		pre[i] = s[0][len[0] - 1 - i];
	}
	pre_len = len[0];
	pre[pre_len] = '\0';
	//printf("pre_len = %d, pre = %s\n", pre_len, pre);

	FOR(i, 1, n - 1) {
		int j;
		for (j = 0; j < pre_len && j < len[i]; ++j) {
			if (pre[j] != s[i][len[i] - 1 - j]) {
				break;
			}
		}
		pre_len = j;
	}
	pre[pre_len] = '\0';
	//printf("pre_len = %d\t, pre = %s\n", pre_len, pre);

	REP(i, n) {
		FORD(j, len[i] - 1 - pre_len, 0) {
			if ('0' == s[i][j]) {
				++zero[i];
			} else {
				break;
			}
		}
		//printf("len = %d, s = %s, zero = %d\n", len[i], s[i], zero[i]);
	}

	FOR(i, pre_len, M) {
		int tmp = 0;
		REP(j, n) {
			if (zero[j] + pre_len >= i) {
				tmp += len[j] - i;
			} else {
				tmp += len[j] - zero[j] - pre_len + i - zero[j] - pre_len;
			}
		}
		ans = MIN(ans, tmp);
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
