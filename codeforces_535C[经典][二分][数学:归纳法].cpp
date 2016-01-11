/*************************************************************************
    > File Name: demo.cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 二  4/14 23:36:55 2015
 ************************************************************************/

/*
 * 思路
 *
 * 这道题二分+数学归纳法
 *
 * 首先需要能发现这条定理: 对于序列h1, h2, h3, ..., hn, 如果该序列对于(m, t)可满足，当且仅当 max(h1, h2, h3, ..., hn) <= t && sum(h1, h2, ..., hn) <= m * t.
 * 如果要问怎么才能想到，对题目深层次的理解，这个没办法强求。
 *
 * 证明(数学归纳法):
 *	假设对于h1, h2, h3, ..., hn满足以上两个条件, 那么
 *		h1, h2, h3, ..., hn中 (hi == t) 的个数不超过m, 那么我们令最大的m个元素值减1，那么得到的h1', h2', h3', ..., hn'中， max(h1', h2', h3', .., hn') <= t - 1 && sum(h1', h2', h3', ..., hn') <= m * t - m = m * (t - 1). 得证。
 *
 * 注:
 *	怎么归纳呢？ 首先假设当前在满足条件的情况下是可解的，那么向前走一步(也就是令m个元素减1)之后，依然是满足条件的，也就是依然可解，那么假设就成立。
 *
 * 复杂度很好算 q * O(t)
 *
 * */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define LL long long
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) > (b) ? (b) : (a))
#define ABS(a) ((a) > 0 ? (a) : (-(a)))

LL a, b, n;
LL l, t, m, r;

LL binary(LL left, LL right) {
	while (left <= right) {
		LL mid = (left + right) / 2;
		//printf("mid = %I64d\n", mid);
		//printf("sum = %I64d\n", (2 * a + (l + mid - 2) * b) * (mid - l + 1) / 2);
		if ((2 * a + (l + mid - 2) * b) * (mid - l + 1) / 2 <= t * m) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	return right;
}

void in() {
}

void run() {
	for (int i = 0; i < n; ++i) {
		scanf("%I64d%I64d%I64d", &l, &t, &m);
		//printf("before r = %I64d\n", (1 + (t - a) / b));
		r = binary(l, 1 + (t - a) / b);
		if (r < l) {
			printf("-1\n");
		} else {
			printf("%I64d\n", r);
		}
	}
}

void out() {
}

void out(int cas) {
}

int main() {
	//freopen("data", "r", stdin);

	while (~scanf("%I64d%I64d%I64d", &a, &b, &n)) {
		in();
		run();
		out();
	}

	return 0;
}
