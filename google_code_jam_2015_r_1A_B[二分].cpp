/*************************************************************************
    > File Name: demo.cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created tt: 二  4/14 23:36:55 2015
 ************************************************************************/

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

#define B (1000)

LL t, n, b, l, tt;
int ans;
LL bt[B + 5];

LL get_num(LL endt) {
	if (endt < 0) {
		return 0;
	}
	LL ret = 0;
	for (int i = 0; i < b; ++i) {
		ret += (endt / bt[i] + 1);
	}
	return ret;
}

LL binary_search(LL left, LL right) {
	while (left <= right) {
		LL mid = (left + right) / 2;
		if (get_num(mid) >= n) {
			right = mid - 1;
		} else {
			left = mid + 1;
		}
	}
	return left;
}

void init() {
	scanf("%I64d", &t);
}

void in() {
	l = 0;

	scanf("%I64d%I64d", &b, &n);
	for (int i = 0; i < b; ++i) {
		scanf("%I64d", &bt[i]);
		l = MAX(l, bt[i]);
	}
}

void run() {
	tt = binary_search(0, l * n);
	LL p = get_num(tt - 1);
	for (ans = 0; ; ++ans) {
		if (0 == (tt % bt[ans])) {
			if ((++p) == n) {
				break;
			}
		}
	}
}

void out() {
}

void out(int cas) {
	printf("Case #%d: %d\n", cas, ans + 1);
}

int main() {
	//freopen("/Users/hugh_627/Downloads/data", "r", stdin);

	init();
	for (int i = 0; i < t; ++i) {
		in();
		run();
		out(i + 1);
	}

	return 0;
}
