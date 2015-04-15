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

int n;
int ans, ans2;
int cnt;
int p[11];
int p2[11];

void init() {
	p[0] = p2[0] = 1;
	for (int i = 1; i < 10; ++i) {
		p[i] = 2 * p[i - 1];
		p2[i] = 10 * p2[i - 1];
	}
}

void in() {
	ans = 0;
	ans2 = 0;
	cnt = 0;
}

void run() {
	int _n = n;
	while (_n) {
		++cnt;
		_n = _n / 10;
	}
	for (int i = cnt - 1; i >= 0; --i) {
		if (7 == (n / p2[i])) {
			ans += p[i];
		}
		n = n % p2[i];
	}

	for (int i = 1; i < cnt; ++i) {
		ans2 += p[i];
	}
}

void out() {
	printf("%d\n", ans + ans2 + 1);
}

void out(int cas) {
}

int main() {
	//freopen("data", "r", stdin);

	init();
	while (~scanf("%d", &n)) {
		in();
		run();
		out();
	}

	return 0;
}
