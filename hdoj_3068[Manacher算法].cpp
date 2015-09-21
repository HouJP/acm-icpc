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

//#define mp make_pair
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

#define MAXN (110010) // 原字符串长度
char ma[MAXN * 2];
int mp[MAXN * 2];
char s[MAXN]; // 用来存储原字符串
int ans, len;

/*------------ Manacher BEGIN ---------------*/

// 回文串长度 = mp[i] - 1
// @parameter s 原字符串
// @parameter len 原字符串长度
void manacher(char s[], int len) {
	int l = 0;
	ma[l++] = '$';
	ma[l++] = '#';
	for (int i = 0; i < len; ++i) {
		ma[l++] = s[i];
		ma[l++] = '#';
	}
	ma[l] = 0;
	int mx = 0, id = 0;
	for (int i = 0; i < l; ++i) {
		mp[i] = mx > i ? MIN(mp[2 * id - i], mx - i) : 1;
		while (ma[i + mp[i]] == ma[i - mp[i]]) ++mp[i];
		if (i + mp[i] > mx) {
			mx = i + mp[i];
			id = i;
		}
	}
}

/*
 * abaaba
 * i:		0 1 2 3 4 5 6 7 8 9 10 11 12 13
 * ma[i]:	$ # a # b # a # a # b  #  a  #
 * mp[i]:	1 1 2 1 4 1 2 7 2 1 4  1  2  1

 int main() {
 	while (scanf("%s", s) == 1) {
 		int len = strlen(s);
 		manacher(s, len);
 		int ans = 0;
 		for (int i = 0; i < 2 * len + 2; ++i) {
 			ans = MAX(ans, mp[i] - 1);
 		}
 		printf("%d\n", ans);
 	}
 	return 0;
 }
 */


/*------------ Manacher END ---------------*/

void init() {
}

void in() {
	ans = 0;
	len = strlen(s);
}

void run() {
	manacher(s, len);
	REP(i, 2 * len + 2) {
		ans = MAX(ans, mp[i] - 1);
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
	while (~scanf("%s", s)) {
		in();
		run();
		out();
	}

	return 0;
}
