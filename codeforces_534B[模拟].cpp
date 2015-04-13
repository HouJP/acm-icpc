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
#define ABS(a) ((a) > 0 ? (a) : (-(a)))

int v1, v2, t, d, p1, p2;
int ans;

void init() {
}

void in() {
	ans = v1 + v2;
	p1 = 1;
	p2 = t;
}

void run() {
	while (true) {
		if (p2 - p1 <= 1) {
			break;
		}
		if (v1 < v2) {
			v1 += d;
			ans += v1;
			++p1;
		} else {
			v2 += d;
			ans += v2;
			--p2;
		}
	}
}

void out() {
	printf("%d\n", ans);
}

int main() {
	//freopen("data", "r", stdin);

	while (~scanf("%d%d%d%d", &v1, &v2, &t, &d)) {
		in();
		run();
		out();
	}

	return 0;
}
