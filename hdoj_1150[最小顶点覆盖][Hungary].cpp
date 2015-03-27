/*************************************************************************
    > File Name: hdoj_1150.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 四  3/26 14:59:28 2015
 ************************************************************************/

/* 
 * 思路
 *
 * 关于怎么处理mode_0蛋疼好久，最后才发现，其实把包含0的边删除了就行了，因为机器初始处于0状态，可以在初始的时候把0状态可以完成的任务全部完成，而没有花费。
 *
 * */

#include <cstdio>
#include <cstring>

#define MAXN (100 + 5)

int n, m, k, ans;

int gra[MAXN][MAXN];
int linker[MAXN];
int used[MAXN];

bool dfs(int u) {
	for (int v = 0; v < m; ++v) {
		if (gra[u][v] && !used[v]) {
			used[v] = true;
			if (-1 == linker[v] || dfs(linker[v])) {
				linker[v] = u;
				return true;
			}
		}
	}
	return false;
}

int hungary() {
	int res = 0;
	int u;
	memset(linker, -1, sizeof(linker));
	for (u = 0; u < n; ++u) {
		memset(used, 0, sizeof(used));
		if (dfs(u)) {
			++res;
		}
	}
	return res;
}

void in() {
	scanf("%d%d", &m, &k);
	memset(gra, 0, sizeof(gra));
	for (int i = 0; i < k; ++i) {
		int a, b, id;
		scanf("%d%d%d", &id, &a, &b);
		if ((0 == a) || (0 == b)) {
			continue;
		} else {
			gra[a][b] = 1;
		}
	}
}

void run() {
	ans = hungary();
}

void out() {
	printf("%d\n", ans);
}

int main() {
	freopen("data", "r", stdin);

	while (~scanf("%d", &n) && n) {
		in();
		run();
		out();
	}

	return 0;
}
