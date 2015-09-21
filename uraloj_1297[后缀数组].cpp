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

#define N (2010)
#define M (310)
#define L (30)

char str[N];
int num[N];
int len;
int h_pow[L + 5];
int dp[N][L];
int ans = 0;
int ans_pos = 0;

int wa[N], wb[N], wv[N];
int ws[N]; 
int r[N], sa[N];
int irank[N], height[N];

int cmp(int *r, int a, int b, int l) {
	return r[a] == r[b] && r[a + l] == r[b + l];
}

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

// n = len(str)
void calheight(int *r, int *sa, int n) {
	int i, j, k = 0;
	for (i = 1; i <= n; ++i) irank[sa[i]] = i;
	for (i = 0; i < n; height[irank[i++]] = k)
		for (k ? k-- : 0, j = sa[irank[i] - 1]; r[i + k] == r[j + k]; k++);
}

/*------------- SPARSE TABLE BEGIN -------------*/

void init_pow_2() {
	h_pow[0] = 1;
	for (int i = 1; i <= L; ++i) {
		h_pow[i] = 2 * h_pow[i - 1];
	}
}

void sparse_table(int len) {
	int k = (int)(log((double)len) / log(2.0));
	for (int i = 0; i < len; ++i) {
		dp[i][0] = i;
	}
	for (int j = 1; j <= k; ++j) {
		int end = len - h_pow[j];
		for (int i = 0; i <= end; ++i) {
			int a = dp[i][j - 1];
			int b = dp[i + h_pow[j- 1]][j - 1];
			if (height[a] < height[b]) {
				dp[i][j] = a;
			} else {
				dp[i][j] = b;
			}
		}
	}
}

int rmq(int x, int y) {
	int len = y - x + 1;
	int k = (int)(log((double)len) / log(2.0));
	int a = dp[x][k];
	int b = dp[y - h_pow[k] + 1][k];
	if (height[a] < height[b]) {
		return a;
	} else {
		return b;
	}
}


/*------------- SPARSE TABLE END ---------------*/


void init() {
	init_pow_2();
}

void in() {
	ans = 0;
	ans_pos = 0;
}

void run() {
	len = strlen(str);
	REP(i, len) {
		num[i] = str[i];
	}
	num[len] = 256;
	REP(i, len) {
		num[i + len + 1] = str[len - 1 - i];
	}
	num[2 * len + 1] = 0;
	da(num, sa, 2 * (len + 1), 300);
	calheight(num, sa, 2 * len + 1);
	sparse_table(2 * (len + 1));
	REP(i, len) {
		int tmp;
		tmp = height[rmq(MIN(irank[i], irank[2 * (len + 1) - 2 - i]) + 1, MAX(irank[i], irank[2 * (len + 1) - 2 - i]))];
		if ((2 * tmp - 1) > ans) {
			ans = 2 * tmp - 1;
			ans_pos = i - tmp + 1;
		}
		tmp = height[rmq(MIN(irank[i + 1], irank[2 * (len + 1) - 2 - i]) + 1, MAX(irank[i + 1], irank[2 * (len + 1) - 2 - i]))];
		if ((2 * tmp) > ans) {
			ans = 2 * tmp;
			ans_pos = i - tmp + 1;
		}
	}
}

void out() {
	FOR(i, ans_pos, ans_pos + ans - 1) {
		printf("%c", str[i]);
	}
	printf("\n");
}

void out(int cas) {
}

int main() {
	freopen("data", "r", stdin);

	init();
	while (~scanf("%s", str)) {
		in();
		run();
		out();
	}

	return 0;
}
