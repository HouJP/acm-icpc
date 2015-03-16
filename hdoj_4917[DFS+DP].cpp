/*************************************************************************
    > File Name: hdoj_4917.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 六 10/11 19:38:30 2014
 ************************************************************************/

/* *
 * 
 * 思路：
 * 1. 通过DFS求连通分量。
 * 2. 对每个连通分量进行DP，求解全排列个数。
 * 3. 通过排练组合，将各个连通分量的结果合并。
 *
 * */

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define N (40)
#define M (20)
#define MOD (1000000007)


vector<int> gra[N + 5];
bool isvisited[N + 5];
int c_num; // 连通分支个数
int num[N + 5]; // 连通分支中点个数
int idd[N + 5]; // 点在连通分支中的编号
int map[N + 5][N + 5]; // 每个连通分支中的点映射到原来的序列上
int pre[N + 5]; // 记录每个点的直接前驱
int dp[1 << 21 + 5];
int edg[M + 5][2]; // 记录边
int ans[N + 5];
int jie[N + 5][N + 5];


int n, m;
int a, b;

void get_jie(int n_max) {
	for (int i = 0; i <= n_max; ++i) {
		jie[i][0] = jie[i][i] = 1;
	}
	for (int i = 1; i <= n_max; ++i) {
		for (int j = 1; j < i; ++j) {
			jie[i][j] = (jie[i - 1][j - 1] + jie[i - 1][j]) % MOD;
		}
	}
}

// 通过深搜获取连通分支
void dfs(int id) {
	for (int i = 0; i < gra[id].size(); ++i) {
		if (!isvisited[gra[id][i]]) {
			isvisited[gra[id][i]] = true;
			idd[gra[id][i]] = num[c_num];
			map[c_num][num[c_num]] = gra[id][i];
			++num[c_num];
			dfs(gra[id][i]);
		}
	}
}

void get_connected() {
	c_num = 0;
	for (int i = 0; i < n; ++i) {
		if (isvisited[i] == false) {
			isvisited[i] = true;
			idd[i] = num[c_num];
			map[c_num][num[c_num]] = i;
			++num[c_num];
			dfs(i);
			++c_num;
		}
	}
}

void init() {
	memset(ans, 0, sizeof(ans));
	memset(isvisited, false, sizeof(isvisited));
	memset(num, 0, sizeof(num));
	memset(pre, 0, sizeof(pre));
	for (int i = 0; i < n; ++i) {
		gra[i].clear();
	}

	for (int i = 0; i < m; ++i) {
		scanf("%d %d", &a, &b);
		a -= 1;
		b -= 1;
		gra[a].push_back(b);
		gra[b].push_back(a);
		edg[i][0] = a;
		edg[i][1] = b;
	}
}

void dp_f() {
	int tmp;

	for (int i = 0; i < c_num; ++i) {
		tmp = 1 << num[i];
		for (int j = 1; j < tmp; ++j) {
			dp[j] = 0;
		}
		dp[0] = 1;

		for (int j = 0; j < tmp - 1; ++j) {
			if (dp[j] == 0) continue;
			else {
				for(int k = 0; k < num[i]; ++k) {
					if ((j & pre[map[i][k]]) == pre[map[i][k]] && (j & (1 << k)) == 0) {
						dp[j | (1 << k)] = (dp[j | (1 << k)] + dp[j]) % MOD;
					}
				}
			}
		}
		ans[i] = dp[tmp - 1];
	}
}

void get_pre() {
	for (int i = 0; i < m; ++i) {
		a = edg[i][0];
		b = edg[i][1];
		pre[b] |= 1 << idd[a];
	}
}

void get_ans() {
	for (int i = 1; i < c_num; ++i) {
		ans[0] = (int)(((((__int64)jie[num[0] + num[i]][num[i]] * ans[0]) % MOD) * ans[i]) % MOD);
		num[0] += num[i];
	}
	printf("%d\n", ans[0]);
}

int main() {
	freopen("data", "r", stdin);

	get_jie(N);

	while (~scanf("%d %d", &n, &m)) {
		init();
		get_connected();
		get_pre();
		dp_f();
		get_ans();
	}

	return 0;
}
