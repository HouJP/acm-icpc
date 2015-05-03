/*************************************************************************
    > Author: HouJP
    > Mail: houjp1992@gmail.com
 ************************************************************************/

/* 
 * 思路
 *
 * 第一步，抽象，这道题求解的是sigma(gcd(ai, aj) * (gcd(ai, aj) - 1)), 1 <= i, j <= n.
 * 接下来：
 *	需要枚举最大公约数，接下来需要知道的是，当最大公约数=k的时候，(ai, aj)的对数，设为f(k)。
 *	如果已知a1~an中k的倍数有m个，那么f(k) = m^2 - f(2k) - f(3k) - ...
 *
 * */

#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
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
#define MOD (10007)

int n, a, ans;
int cnt[MAXN + 5];
int f[MAXN + 5];

void in() {
}

void run() {
}

void out() {
}

void out(int cas) {
}

int main() {
	freopen("data", "r", stdin);

	while (~scanf("%d", &n)) {
		reset(cnt, 0);
		ans = 0;

		REP(i, n) {
			scanf("%d", &a);
			int endf = int(sqrt(double(a)));
			FOR(j, 1, endf) {
				if (0 == (a % j)) {
					++cnt[j];
					if (j != (a / j)) {
						++cnt[a / j];
					}
				}
			}
		}

		FORD(i, MAXN, 1) {
			f[i] = cnt[i] * cnt[i];
			for (int j = 2; j * i <= MAXN; ++j) {
				f[i] -= f[i * j];
			}
			ans = (ans + int((((LL)f[i]) * ((LL)(i * (i - 1)))) % MOD)) % MOD;
		}

		printf("%d\n", ans);
	}

	return 0;
}
