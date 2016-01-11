/*************************************************************************
    > File Name: demo.cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 二  4/14 23:36:55 2015
 ************************************************************************/

/*
 * 思路
 *
 * 设 dp[i][j] 表示以第i个字符开始，第j个字符结尾的回文子序列个数。
 * 设 sum[i][j] 表示第i个字符和第j个字符之间（包括他俩）所包含的回文子序列个数。
 * 递推方程：
 *	dp[i][j] = 0 (if str[i] != str[j])
 *	dp[i][j] = sum[i + 1][j - 1] + 1 (if str[i] == str[j])
 *	sum[i][j] = sum[i + 1][j] + 求和(dp[i][i] + dp[i][i + 1] + ... + dp[i][j])
 * 刚开始的时候，求sum[i][j]的求和那部分直接用了树状数组，跑偏了，虽然能做出来，但是完全没有必要。仔细观察可知，sum那部分是单调递增的，一直累加就好了。
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
#define MOD (100007)
#define N (1000)

char str[N + 5];
int t, len, fend;
int dp[N + 5][N + 5];
int sum[N + 5][N + 5];
int left[N + 5];

void in() {
	// input
	scanf("%s", &str[1]);
	
	// init
	len = strlen(&str[1]);
	memset(dp, 0, sizeof(dp));
	memset(sum, 0, sizeof(sum));
	memset(left, 0, sizeof(left));
}

void run() {
	for (int i = 1; i <= len; ++i) {
		dp[i][i] = 1;
		sum[i][i] = 1;
		left[i] = 1;
	}

	fend = len - 1;
	for (int i = 1; i <= fend; ++i) {
		if (str[i] == str[i + 1]) {
			dp[i][i + 1] = 1;
			left[i] = (left[i] + dp[i][i + 1]) % MOD;
		} else {
			dp[i][i + 1] = 0;
		}
		sum[i][i + 1] = (2 + dp[i][i + 1]) % MOD;
	}

	for (int i = 3; i <= len; ++i) {
		fend = len - i + 1;
		for (int j = 1; j <= fend; ++j) {
			int x = j;
			int y = j + i - 1;
			if (str[x] == str[y]) {
				dp[x][y] = (sum[x + 1][y - 1] + 1) % MOD;
				left[x] = (left[x] + dp[x][y]) % MOD;
			}
			sum[x][y] = (sum[x + 1][y] + left[x]) % MOD;
		}
	}
}

void out(int cas) {
	printf("Case #%d: %d\n", cas, sum[1][len]);
}

int main() {
	freopen("data", "r", stdin);

	scanf("%d", &t);
	for (int i = 0; i < t; ++i) {
		in();
		run();
		out(i + 1);
	}

	return 0;
}
