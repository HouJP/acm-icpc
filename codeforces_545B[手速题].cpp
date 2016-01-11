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

#define MAXN (100000 + 2) 

char s1[MAXN], s2[MAXN];
int cnt;
int n;

void init() {
}

void in() {
	scanf("%s", s2);
}

void run() {
	n = strlen(s1);
	for (int i = 0; i < n; ++i) {
		if (s1[i] != s2[i]) {
			++cnt;
		}
	}
}

void out() {
	if (cnt % 2) {
		printf("impossible\n");
	} else {
		int tmp1 = 0, tmp2 = cnt / 2;
		for (int i = 0; i < n; ++i) {
			if (s1[i] == s2[i]) {
				printf("%c", s1[i]);
			} else {
				if (tmp1 < tmp2) {
					printf("%c", s1[i]);
					++tmp1;
				} else {
					printf("%c", s2[i]);
				}
			}
		}
		printf("\n");
	}
}

void out(int cas) {
}

int main() {
	//freopen("data", "r", stdin);

	init();
	while (~scanf("%s", s1)) {
		in();
		run();
		out();
	}

	return 0;
}
