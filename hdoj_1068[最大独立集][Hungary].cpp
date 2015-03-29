/*************************************************************************
    > File Name: hdoj_1068.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 五  3/27 18:41:20 2015
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#define N (10000 + 5)

int ans;

/*
 * 匈牙利算法，不区分左侧右侧点
 *
 * 采用邻接表形式
 *
 * 调用: ans = hungary() / 2
 *
 * */

// hungary
int n;
vector<vector<int> > adj;
int linker[N];
bool used[N];

bool dfs(int u) {
	for (int k = 0; k < adj[u].size(); ++k) {
		int v = adj[u][k];
		if (!used[v]) {
			used[v] = true;
			if (-1 == linker[v] || dfs(linker[v])) {
				linker[v] = u;
				//linker[u] = v; // 加上就错了，会互相干扰
				return true;
			}
		}
	}
	return false;
}

int hungary() {
	int res = 0;
	memset(linker, -1, sizeof(linker));
	for (int i = 0; i < n; ++i) {
		memset(used, 0, sizeof(used));
		if (dfs(i)) {
			++res;
		}
	}
	return res;
}

void init() {
}

void in() {
	adj.assign(n, vector<int>());

	for (int i = 0; i < n; ++i) {
		int a, b, k;
		scanf("%d: (%d)", &a, &k);
		for (int j = 0; j < k; ++j) {
			scanf("%d", &b);
			adj[a].push_back(b);
		}
	}
}

void run() {
	ans = n - hungary() / 2;
}

void out() {
	printf("%d\n", ans);
}

int main() {
	freopen("data", "r", stdin);

	init();
	while (~scanf("%d", &n)) {
		in();
		run();
		out();
	}

	return 0;
}
