/*************************************************************************
    > Author: HouJP
    > Mail: houjp1992@gmail.com
 ************************************************************************/

/**
 * 后缀数组求解，TLE
 * */

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

// N 是字符串长度，M是字符最大值
#define N (1000000 + 10)
#define M (300 + 10)
#define L (25)

int len;
char str[N];
int h_pow[L + 5]; // 事先保存2^x，不需要重复计算
int dp[N + 5][L + 5]; // sparse table的DP数组
int minn[N];
int ans;

/*--------------- 后缀数组 BEGIN ------------------*/

int wa[N], wb[N], wv[N];
int ws[N]; // 注意这里维度是MAX(M, N)
int r[N], sa[N];
int irank[N], height[N];

int cmp(int *r, int a, int b, int l) {
	return r[a] == r[b] && r[a + l] == r[b + l];
}

// r数组存储字符串，数值非负，且要额外增加一个值“0”
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

// n = len(str)
void calheight(int *r, int *sa, int n) {
	int i, j, k = 0;
	for (i = 1; i <= n; ++i) irank[sa[i]] = i;
	for (i = 0; i < n; height[irank[i++]] = k)
		for (k ? k-- : 0, j = sa[irank[i] - 1]; r[i + k] == r[j + k]; k++);
}

// da和calheight中的n不是一个概念，同时height数组的有效范围是height[1] ~ height[n]，其中height[1] = 0
// height[i] = suffix(sa[i - 1]) 和 suffix(sa[i])的最长公共前缀，也就是排名相邻的两个后缀的最长公共前缀。
// sa[] 排第几的是谁？
// rank[] 你排第几？

// 调用
// da(r, sa, n + 1, 128);
// calheight(r, sa, n);

/*--------------- 后缀数组 END ------------------*/

void init() {
}

void in() {
	ans = 1;
	len = strlen(str);
}

void run() {
	REP(i, len) {
		r[i] = str[i];
	}
	r[len] = 0;
	da(r, sa, len + 1, M - 10);
	calheight(r, sa, len);

	minn[irank[0] - 1] = height[irank[0]];
	FORD(i, irank[0] - 2, 1) {
		minn[i] = MIN(minn[i + 1], height[i + 1]);
	}
	minn[irank[0] + 1] = height[irank[0] + 1];
	FOR(i, irank[0] + 2, len) {
		minn[i] = MIN(minn[i - 1], height[i]);
	}
	FOR(i, 1, len) {
		if (i == irank[0]) {
			continue;
		}
		if (minn[i] != len - sa[i]) {
			continue;
		}
		if ((len % sa[i]) != 0) {
			continue;
		}
		ans = MAX(ans, len / sa[i]);
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
	while (~scanf("%s", str) && strcmp(str, ".") != 0) {
		in();
		run();
		out();
	}

	return 0;
}
