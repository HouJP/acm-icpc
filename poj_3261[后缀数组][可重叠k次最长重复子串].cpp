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

#define N (20010)
#define M (1000010)

int n, k;
int num[N];
int ans;

/*--------------- 后缀数组 BEGIN ------------------*/

int wa[N], wb[N], wv[N], ws[M];
int r[N], sa[N];
int irank[N], height[N];

int cmp(int *r, int a, int b, int l) {
	return r[a] == r[b] && r[a + l] == r[b + l];
}

// r数组要额外增加一个值“0”
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

// 可重叠的k次最长重复子串
bool judge(int len) {
	int cnt = 0;
	int ret = 0;
	FOR(i, 2, n) {
		if (height[i] < len) {
			ret = MAX(ret, cnt);
			cnt = 0;
		} 
		++cnt;
	}
	ret = MAX(ret, cnt);
	if (ret >= k) {
		return true;
	} else {
		return false;
	}
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
	//printf("n = %d, k = %d\n", n, k);
	REP(i, n) {
		scanf("%d", &num[i]);
		++num[i];
	}
}

void run() {
	num[n] = 0;
	da(num, sa, n + 1, M);
	calheight(num, sa, n);
	int left = 0, right = n, mid;
	while (left <= right) {
		mid = (left + right) / 2;
		//printf("left = %d, mid= %d, right = %d\n", left, mid, right);
		if (judge(mid)) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	ans = left - 1;
}

void out() {
	printf("%d\n", ans);
}

void out(int cas) {
}

int main() {
	freopen("data", "r", stdin);

	init();
	while (~scanf("%d%d", &n, &k)) {
		in();
		run();
		out();
	}

	return 0;
}
