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

#define N (100000 + 2)

char s[3][N];
int l[3];
int cnt[3][30];
int ans, ans1, ans2;

void init() {
}

void in() {
	memset(cnt, 0, sizeof(cnt));
	ans = ans1 = ans2 = 0;
}

void run() {
	for (int i = 0; i < 3; ++i) {
		l[i] = strlen(s[i]);
	}
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < l[i]; ++j) {
			++cnt[i][s[i][j] - 'a'];
		}
	}
	/*
	for (int j = 0; j < 26; ++j) {
		for (int i = 0; i < 3; ++i) {
			printf("%c:%d\t", 'a' + j, cnt[i][j]);
		}
		printf("\n");
	}
	*/
	for (int i = 0; ; ++i) {
		int cmax = N;
		bool flag = true;
		for (int j = 0; j < 26; ++j) {
			if (cnt[0][j] - i * cnt[1][j] < 0) {
				flag = false;
			}
		}
		if (!flag) {
			break;
		}
		for (int j = 0; j < 26; ++j) {
			if (cnt[2][j] == 0) {
				continue;
			}
			cmax = MIN(cmax, (cnt[0][j] - i * cnt[1][j]) / cnt[2][j]);
		}
		//printf("i = %d, cmax = %d\n", i, cmax);
		if (i + cmax > ans) {
			ans = i + cmax;
			ans1 = i;
			ans2 = cmax;
		}
	}
	//printf("ans = %d, ans1 = %d, asn2 = %d\n", ans, ans1, ans2);
}

void out() {
	for (int i = 0; i < ans1; ++i) {
		printf("%s", s[1]);
	}
	for (int i = 0; i < ans2; ++i)  {
		printf("%s", s[2]);
	}
	for (int i = 0; i < 26; ++i) {
		for (int j = 0; j < cnt[0][i] - ans1 * cnt[1][i] - ans2 * cnt[2][i]; ++j) {
			printf("%c", 'a' + i);
		}
	}
	printf("\n");
}

void out(int cas) {
}

int main() {
	//freopen("data", "r", stdin);

	init();
	while (~scanf("%s%s%s", s[0], s[1], s[2])) {
		in();
		run();
		out();
	}

	return 0;
}
