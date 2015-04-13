/*************************************************************************
    > File Name: demo.cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 日  4/12 23:55:05 2015
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define LL long long
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) > (b) ? (b) : (a))

#define N (200000)

LL n, a;
LL d[N + 5];
LL max_s, min_s;
LL ans, low, high;

void init() {
}

void in() {
	max_s = min_s = 0;
	for (int i = 0; i < n; ++i) {
		scanf("%I64d", &d[i]);
		max_s += d[i];
	}
	min_s = n;
	//printf("min = %lld, max = %lld\n", min_s, max_s);
}

void run() {
	for (int i = 0; i < n; ++i) {
		if (i) {
			printf(" ");
		}
		ans = 0;
		low = a - max_s + d[i];
		//printf("i = %d, low = %lld\n", i, low);
		if (low > 1) {
			ans += low - 1;
		}
		//printf("ans = %lld\n", ans);
		high = a - n + 1;
		//printf("i = %d, high = %lld\n", i, high);
		if (high < d[i]) {
			ans += d[i] - high;
		}
		printf("%I64d", ans);
	}
	printf("\n");
}

void out() {
}

void out(int cas) {
}

int main() {
	//freopen("data", "r", stdin);
	
	while (~scanf("%I64d%I64d", &n, &a)) {
		in();
		run();
		out();
	}

	return 0;
}
