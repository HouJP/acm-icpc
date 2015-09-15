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

int t, n;
char str[20010];
int indl;
int indr;
int ans_ind;
int ans_dir;

/*--------------- 后缀数组 BEGIN ------------------*/

#define N (20010 * 2)

int wa[N], wb[N], wv[N], ws[N];
int r[N], sa[N];

int cmp(int *r, int a, int b, int l) {
	return r[a] == r[b] && r[a + l] == r[b + l];
}

// n = len(str) + 1
// m = max(r[i]) + 1
void da(int *r, int *sa, int n, int m) {
	int i, j, p, *x = wa, *y = wb, *t;
	for (i = 0; i < m; ++i)	ws[i] = 0;
	for (i = 0; i < n; ++i) ++ws[x[i] = r[i]];
	for (i = 1; i < m; ++i) ws[i] += ws[i - 1];
	for (i = n - 1; i >= 0; --i) sa[--ws[x[i]]] = i;
	for (j = 1, p = 1; p < n; j *= 2, m = p) {
		for (p = 0, i = n - j; i < n; ++i) y[p++] = i;
		for (i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
		for (i = 0; i < n; ++i) wv[i] = x[y[i]];
		for (i = 0; i < m; ++i) ws[i] = 0;
		for (i = 0; i < n; ++i) ws[wv[i]]++;
		for (i = 1; i < m; ++i) ws[i] += ws[i - 1];
		for (i = n - 1; i >= 0; --i) sa[--ws[wv[i]]] = y[i];
		for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; ++i)
			x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
	}
}

/*--------------- 后缀数组 END ------------------*/

void init() {
	scanf("%d", &t);
}

void in() {
	scanf("%d", &n);
	scanf("%s", str);
	ans_ind = ans_dir = 0;
	indl = indr = 0;
}

void run() {
	if (0 == n) {
		return;
	}
	// clockwise
	REP(i, n) {
		r[i] = str[i] - 'a' + 1;
	}
	REP(i, n - 1) {
		r[i + n] = str[i] - 'a' + 1;
	}
	r[2 * n - 1] = 0;
	da(r, sa, 2 * n, 27);
	REPD(i, 2 * n) {
		if (sa[i] < n) {
			indl = sa[i];
			break;
		}
	}
	//printf("indl = %d\n", indl);

	// counterclockwise
	REP(i, n) {
		r[i] = 'z' - str[n - 1 - i] + 1;
	}
	REP(i, n - 1) {
		r[i + n] = 'z' - str[n - 1 - i] + 1;
	}
	r[2 * n - 1] = 0;
	da(r, sa, 2 * n, 27);
	REP(i, 2 * n) {
		if (sa[i] < n) {
			indr = sa[i];
			break;
		}
	}
	indr = n - 1 - indr;
	//printf("indr = %d\n", indr);

	// compare
	REP(i, n) {
		if (str[(indl + i) % n] > str[(((indr - i) % n) + n) % n]) {
			ans_ind = indl;
			ans_dir = 0;
			return;
		} 
		if (str[(indl + i) % n] < str[(((indr - i) % n) + n) % n]) {
			ans_ind = indr;
			ans_dir = 1;
			return;
		}
	}

	ans_ind = indl;
	ans_dir = 0;

	if (indl < indr) {
		ans_ind = indl;
		ans_dir = 0;
		return;
	}
	if (indl > indr) {
		ans_ind = indr;
		ans_dir = 1;
		return;
	}
}

void out() {
	if (0 == n) {
		printf("1 0\n");
	} else {
		printf("%d %d\n", ans_ind + 1, ans_dir);
	}
}

void out(int cas) {
}

int main() {
	//freopen("data", "r", stdin);

	init();
	REP(i, t) {
		in();
		run();
		out();
	}

	return 0;
}
