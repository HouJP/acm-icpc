/*************************************************************************
    > File Name: demo.cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 二  4/14 23:36:55 2015
 ************************************************************************/

/*
 * 思路
 *
 * 抽象出来，求1~100000之间所有整数各自的因子。
 *
 * */

#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define LL long long
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) > (b) ? (b) : (a))
#define ABS(a) ((a) > 0 ? (a) : (-(a)))

#define N (100000)

int t, n, num, ans;
vector<vector<int> > yz;
bool flag[N + 5];

void init() {
	yz.assign(N + 1, vector<int>());
	for (int i = 1; i <= N; ++i) {
		int end = (int)sqrt((double)i);
		for (int j = 1; j <= end; ++j) {
			if (0 == (i % j)) {
				yz[i].push_back(j);
				if (j != (i / j)) {
					yz[i].push_back(i / j);
				}
			}
		}
	}

	/*
	printf("12 :\t");
	for (int i = 0; i < yz[12].size(); ++i) {
		printf("%d\t", yz[12][i]);
	}
	printf("\n");
	*/
	
	scanf("%d", &t);
}

void in() {
	memset(flag, 0, sizeof(flag));
	ans = 0;

	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &num);
		for (int i = 0; i < yz[num].size(); ++i) {
			if (flag[yz[num][i]]) {
				ans = MAX(ans, yz[num][i]);
			} else {
				flag[yz[num][i]] = true;
			}
		}
	}
}

void run() {
}

void out() {
}

void out(int cas) {
	printf("Case #%d: %d\n", cas, ans);
}

int main() {
	freopen("data", "r", stdin);

	init();
	for (int i = 1; i <= t; ++i) {
		in();
		run();
		out(i);
	}

	return 0;
}
