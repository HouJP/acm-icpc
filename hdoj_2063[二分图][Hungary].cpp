/*************************************************************************
    > File Name: hdoj_2063.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 三  3/25 19:03:47 2015
 ************************************************************************/

#include <cstdio>
#include <cstring>

int k, ans;

/*
 * 匈牙利算法的DFS实现，用于二分图匹配
 * INIT: gra[][]边的情况，点的划分情况，记得memset(gra, 0, sizeof(gra))
 * CALL: ans = hungary(); 输出最大匹配数
 * 优点: 适用于稠密图，DFS找增广路快，实现简单
 * 时间复杂度: O(VE)
 *
 * */

const int MAXN = (500 + 5);
int uN, vN; // 左侧和右侧点的个数
int gra[MAXN][MAXN]; // 编号是从0~n-1
int linker[MAXN];	// 右侧的点连接到的左侧的哪个
bool used[MAXN];

bool dfs(int u) {
	int v;
	for (v = 0; v < vN; ++v) {
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
	for (u = 0; u < uN; ++u) {
		memset(used, 0, sizeof(used));
		if (dfs(u)) {
			++res;
		}
	}
	return res;
}

void in() {
	scanf("%d%d", &uN, &vN);
	// init gra
	memset(gra, 0, sizeof(gra));
	for (int i = 0; i < k; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		gra[a - 1][b - 1] = 1;
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

	while (~scanf("%d", &k) && k) {
		in();
		run();
		out();
	}

	return 0;
}
