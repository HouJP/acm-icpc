/*************************************************************************
    > File Name: 1.cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 四  5/14 10:44:21 2015
 ************************************************************************/

/*
 * 思路：
 *
 * 同种颜色相对位置不会变，所以，假设我们知道答案是什么，就可以先把边上的颜色整理好（也就是挪到边上去），这样就减少了一种颜色，递归考虑剩下的颜色。
 * 递归的思想出来了，也就意味着可以DP去做。枚举哪种颜色在边上，依次类推。
 *
 * 没想明白贪心为什么是错的。闹心。
 *
 * 答案是LL啊，WA了半天。
 *
 * */

#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define LL long long

#define INF (0x3f3f3f3f3f3f3f3f)
#define MAXN (100000 + 2)
#define MAXK (16 + 2)
#define MAX ((1 << 17) + 2)

int arr[MAXN];
LL cnt[MAXK][MAXK][2];
LL dp[MAX];
int t, n, k;
LL ans;

void init() {
	scanf("%d", &t);
}

void in() {
	memset(cnt, 0, sizeof(cnt));
	ans = 0;

	scanf("%d%d", &n, &k);
	for (LL i = 0; i < n; ++i) {
		scanf("%d", &arr[i]);
	}
}

LL min_cos(LL (&cnt)[MAXK][MAXK][2], LL status, LL id) {
	if (0 == ((status >> (id - 1)) & 0x01)) {
		return INF;
	}

	LL cos1 = 0;
	LL cos2 = 0;
	for (LL i = 1; i <= k; ++i) {
		if (1 == ((status >> (i - 1)) & 0x01)) {
			cos1 += cnt[id][i][0];
		}
	}
	for (LL i = 1; i <= k; ++i) {
		if (1 == ((status >> (i - 1)) & 0x01)) {
			cos2 += cnt[id][i][1];
		}
	}

	return MIN(cos1, cos2);
}

void run() {
	for (LL i = 0; i < n; ++i) {
		LL num = arr[i];
		++cnt[num][0][0];
		for (LL j = 1; j <= k; ++j) {
			if (j == num) {
				continue;
			}
			cnt[num][j][0] += cnt[j][0][0];
		}
	}
	for (LL i = n - 1; i >= 0; --i) {
		LL num = arr[i];
		++cnt[num][0][1];
		for (LL j = 1; j <= k; ++j) {
			if (j == num) {
				continue;
			} 
			cnt[num][j][1] += cnt[j][0][1];
		}
	}
	dp[0] = 0;
	LL endf = 1 << k;
	for (LL i = 1; i < endf; ++i) {
		dp[i] = INF;
		for (LL j = 1; j <= k; ++j) {
			dp[i] = MIN(dp[i], dp[i & (~(1 << (j - 1)))] + min_cos(cnt, i, j));
		}
	}
	ans = dp[endf - 1];
}

void out(int cas) {
	printf("Case #%d: %lld\n", cas, ans);
}

int main() {
	freopen("data", "r", stdin);

	init();
	for (int cas = 1; cas <= t; ++cas) {
		in();
		run();
		out(cas);
	}

	return 0;
}
