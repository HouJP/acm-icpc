/*************************************************************************
    > File Name: bc_1.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 六  3/28 20:04:22 2015
 ************************************************************************/

/*
 * 思路
 *
 * 这题想了很久，并没有一下子想到答案中的式子，相当于证明了一次答案，但是结果还是可以继续化简的，而我忽略了这一点，造成代码冗长。
 *
 * ans = (C[n+m-2][n-1] * (n+m-1)) / C[n+m][n]
 * 这个式子继续化简就是官方给出的答案
 *
 * */

#include <cstdio>
#include <cstring>

#define LL long long

#define N (12)

int n, m, ans;
LL mu, zi, gcd;
LL cbt[2 * N + 5][2 * N + 5];

LL get_gcd(LL a, LL b) {
	LL ret = b;
	while (a % b) {
		ret = b;
		b = a % b;
		a = ret;
	}
	return b;
}

void init_cbt(int n) {
	for (int i = 0; i <= n; ++i) {
		cbt[i][0] = cbt[i][i] = 1;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= (n - 1); ++j) {
			cbt[i][j] = cbt[i - 1][j] + cbt[i - 1][j - 1];
		}
	}
}

void init() {
	init_cbt(N * 2);
}

void in() {
}

void run() {
	mu = cbt[n + m][n];
	zi = (n + m - 1) * cbt[n + m - 2][n - 1];
	gcd = get_gcd(mu, zi);
}

void out() {
	printf("%lld/%lld\n", zi / gcd, mu / gcd);
}

int main() {
	freopen("data", "r", stdin);

	init();
	while (~scanf("%d %d", &n, &m)) {
		in();
		run();
		out();
	}

	return 0;
}
