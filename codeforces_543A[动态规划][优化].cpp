/*************************************************************************
    > File Name: 3.cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 五  5/ 8 10:49:44 2015
 ************************************************************************/

/*
 * m个人，如果要做n件事情，同一个人做n件事情的代价都是一样的，不同的人做同一件事情代价是不一样的。那么给定一个代价的阈值，计算有多少中分配方法，使得m个人完成n件事情的代价不超过阈值。
 * 假设i个人完成j件事情花费代价为k的方案数为dp[i][j][k] = dp[i - 1][j][k] + dp[i][j - 1][k - a[i]]。
 * 这样使得问题可以在n^3的复杂度内可解。省略第一维（不断覆盖），那么空间复杂度为n^2。
 * 原始dp方程为：
 * dp[i][j][k] = sig[jj:0~j](dp[i][jj][k - a[i]*(j - jj))
 *
 * 关于上述的优化证明其实很好想，dp[i][j - 1][k - a[i]] = sig[jj:0~j-1](dp[i][jj][k - a[i] * (j - jj)),脑补一个三维立方体的结构，沿着x,y,z三轴方向扫描，需要的部分信息已经在前面累加过了，直接拿出来用就好了。
 *
 * */

#include <cstdio>
#include <cstring>

using namespace std;

#define MAXN (500)

int n, m, b, mod;
int a[MAXN + 5];
int dp[MAXN + 5][MAXN + 5];

void in() {
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i + 1]);
	}
	memset(dp, 0, sizeof(dp));
}

void run() {
	for (int i = 0; i <= b; ++i) {
		dp[0][i] = 1;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			for (int k = 0; k <= b; ++k) {
				if (k - a[i] >= 0) {
					dp[j][k] = (dp[j][k] + dp[j - 1][k - a[i]]) % mod;
				} 
			}
		}
	}
}

void out() {
	printf("%d\n", dp[m][b]);
}

int main() {
	//freopen("data", "r", stdin);

	while (~scanf("%d%d%d%d", &n, &m, &b, &mod)) {
		in();
		run();
		out();
	}

	return 0;
}
