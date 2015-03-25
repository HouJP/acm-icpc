/*************************************************************************
    > File Name: poj_1273.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 日  3/22 10:55:56 2015
 ************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

#define MAX INT_MAX
#define N (15)
#define M (1000)

int n, m, ans, t;

int c[N + 5][N + 5];	// 边容量
int f[N + 5][N + 5];	// 边流量
int pre[N + 5];			// 记录增广路径
int res[N + 5];			// 记录残余网络
queue<int> que;			// bfs寻找增广路

void init() {
	scanf("%d", &t);
}

// 时间复杂度O(V*E*E)
int EK (int s, int t) {
	int i, j;
	int ans = 0;
	while (true) {
		memset(res, 0, sizeof(res));
		res[s] = MAX;	// 源点
		pre[s] = -1;
		que.push(s);
		// bfs寻找增广路
		while (!que.empty()) {
			int x = que.front();
			que.pop();
			for (int i = 1; i <= t; ++i) {
				if (!res[i] && f[x][i] < c[x][i]) {
					que.push(i);
					pre[i] = x;
					res[i] = min(c[x][i] - f[x][i], res[x]);
				}
			}
		}
		if (0 == res[t]) break;	//找不到增广路就退出
		int k = t;
		while (pre[k] != -1) {
			f[pre[k]][k] += res[t];	// 正向边加上新的流量
			f[k][pre[k]] -= res[t];	// 反向边减去新的流量
			k = pre[k];
		}
		ans += res[t];
	}
	return ans;
}

void in() {
	scanf("%d%d", &n, &m);

	while (!que.empty()) que.pop();
	memset(c, 0, sizeof(c));
	memset(f, 0, sizeof(f));

	for (int i = 0; i < m; ++i) {
		int a, b, v;
		scanf("%d%d%d", &a, &b, &v);
		c[a][b] += v;
	}
}

void run() {
	ans = EK(1, n);
}

void out(int cas) {
	printf("Case %d: %d\n", cas, ans);
}

int main() {
	freopen("data", "r", stdin);

	init();
	for (int i = 0; i < t; ++i) {
		in();
		run();
		out(i + 1);
	}

	return 0;
}
