/*************************************************************************
    > File Name: demo.cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 二  4/14 23:36:55 2015
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

#define N (1000)

int m[N + 5];
int t, n, ans1, ans2, maxd;

void init() {
	scanf("%d", &t);
}

void in() {
	maxd = 0;
	ans1 = ans2 = 0;

	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &m[i]);
		if (i) {
			maxd = MAX(maxd, m[i - 1] - m[i]);
			if (m[i - 1] - m[i] > 0) {
				ans1 += m[i - 1] - m[i];
			}
		}
	}
}

void run() {
	for (int i = 0; i < n - 1; ++i) {
		if (m[i] <= maxd) {
			ans2 += m[i];
		} else {
			ans2 += maxd;
		}
	}
}

void out() {
}

void out(int cas) {
	printf("Case #%d: %d %d\n", cas, ans1, ans2);
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
