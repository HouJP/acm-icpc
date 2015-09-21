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

#define N (201324)
#define MOD (530600414LL)

int n, t;
LL num[N];
LL bak[N];
LL frt[N];
LL len[N];
LL ans[N];

void init() {
	scanf("%d", &t);
	//printf("t = %d\n", t);

	num[1] = num[2] = 0;
	bak[1] = bak[2] = 0;
	frt[1] = frt[2] = 0;
	len[1] = 1;
	len[2] = 2;
	ans[1] = ans[2] = 0;
	num[3] = 1;
	frt[3] = 0;
	bak[3] = 3;
	len[3] = 3;
	ans[3] = 0;
	FOR(i, 4, N - 10) {
		//printf("i = %d\n", i);
		num[i] = (num[i - 1] + num[i - 2]) % MOD;
		frt[i] = (frt[i - 1] + (len[i - 2] * num[i - 1]) % MOD + frt[i - 2]) % MOD;
		bak[i] = (bak[i - 2] + (len[i - 1] * num[i - 2]) % MOD + bak[i - 1]) % MOD;
		len[i] = (len[i - 1] + len[i - 2]) % MOD;
		ans[i] = (ans[i - 1] + ans[i - 2] + (num[i - 2] * frt[i - 1]) % MOD + (num[i - 1] * bak[i - 2]) % MOD) % MOD;
		//printf("num[i] = %d, frt[i] = %d, bak[i] = %d, ans[i] = %d\n", num[i], frt[i], bak[i], ans[i]);
	}
}

void in() {
	scanf("%d", &n);
	//printf("n = %d\n", n);
}

void run() {
}

void out() {
	//printf("Case %d: %I64d\n", (ans[n] + MOD) % MOD);
}

void out(int cas) {
	printf("Case #%d: %I64d\n", cas, (ans[n] + MOD) % MOD);
}

int main() {
	int size = 256 << 20; // 256MB
    char *p = (char*)malloc(size) + size;
    __asm__("movl %0, %%esp\n" :: "r"(p));
	//freopen("data", "r", stdin);

	init();
	REP(i, t) {
		in();
		run();
		out(i + 1);
	}

	return 0;
}
