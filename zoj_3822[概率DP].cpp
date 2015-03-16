/*************************************************************************
    > File Name: zoj_3822.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 日 10/12 20:25:15 2014
 ************************************************************************/

/* *
 *
 * 思路：
 * dp[i][j][k]表示：第i天，覆盖j行，覆盖k列的概率（当j == m, k == n的时候，表示第i天恰好覆盖m行n列的概率，需要去掉一种情况）
 *
 * */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

#define N (50)
#define M (50)

int t, m, n;
double dp[N * M + 5][N + 5][M + 5];
double ans;

void init() {
	scanf("%d %d", &n, &m);
	memset(dp[0], 0, sizeof(dp[0]));
}

void dp_f() {
	dp[0][0][0] = 1;
	for (int i = 1; i <= n * m; ++i) {
		for (int j = 0; j <= n; ++j) {
			for (int k = 0; k <= m; ++k) {
				dp[i][j][k] = 0;
				if (j - 1 >= 0) {
					dp[i][j][k] += ((double)(k * (n - j + 1))) / (m * n - i + 1) * dp[i - 1][j - 1][k];
				}
				if (k - 1 >= 0) {
					dp[i][j][k] += ((double)(j * (m - k + 1))) / (m * n - i + 1) * dp[i - 1][j][k - 1];
				}
				if (j - 1 >= 0 && k - 1 >= 0) {
					dp[i][j][k] += ((double)((n - j + 1) * (m - k + 1))) / (m * n - i + 1) * dp[i - 1][j - 1][k - 1];
				}
				 if ((i - 1) < j * k && (j < n || k < m)) {
					dp[i][j][k] += ((double)((j * k - i + 1))) / (m * n - i + 1) * dp[i - 1][j][k];
				}
			}
		}
	}
}

void get_ans() {
	ans = 0;
	for (int i = 0; i <= n * m; ++i) {
		ans += dp[i][n][m] * i;
	}
	printf("%.12lf\n", ans);
}

int main() {
	freopen("data", "r", stdin);
	
	scanf("%d", &t);
	while (t--) {
		init();
		dp_f();
		get_ans();
	}

	return 0;
}
