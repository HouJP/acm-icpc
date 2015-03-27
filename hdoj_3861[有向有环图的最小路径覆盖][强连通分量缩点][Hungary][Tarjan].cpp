/*************************************************************************
    > File Name: hdoj_3861.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 四  3/26 18:50:10 2015
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

#define N (5000 + 5)
#define M (100000 + 5)

int t, ans;

// tarjan 参数
int  dindex, top, bcnt;
int dfn[N], low[N], belong[N], sta[N];
bool instack[N];

int n; // 节点个数
int m; // 原始有向图边数
vector<vector<int> > adj; // 原图，邻接表形式
vector<vector<int> > dag; // 缩点后的有向无环图

// hungary
int linker[N];
int used[N];

bool dfs(int u) {
	for (int k = 0; k < dag[u].size(); ++k) {
		int v = dag[u][k];
		if (!used[v]) {
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
	memset(linker, -1, sizeof(linker));
	for (int u = 0; u < bcnt; ++u) {
		memset(used, 0, sizeof(used));
		if (dfs(u)) {
			++res;
		}
	}
	return res;
}

void tarjan(int i) {
	int j;
	dfn[i] = low[i] = ++dindex;
	instack[i] = true;
	sta[++top] = i;
	for (int k = 0; k < adj[i].size(); ++k) {
		j = adj[i][k];
		if (!dfn[j]) {
			tarjan(j);
			if (low[j] < low[i]) low[i] = low[j];
		} else if (instack[j] && dfn[j] < low[i]) {
			low[i] = dfn[j];
		}
	}
	if (dfn[i] == low[i]) {
		do {
			j = sta[top--];
			instack[j] = false;
			belong[j] = bcnt;
		} while (j != i);
		++bcnt;
	}
}

void run_tarjan() {
	top = bcnt = dindex = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(instack, false, sizeof(instack));
	for (int i = 0; i < n; ++i) {
		if (!dfn[i]) tarjan(i);
	}
}

void get_dag() {
	dag.assign(bcnt, vector<int>());
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < adj[i].size(); ++j) {
			if (belong[i] != belong[adj[i][j]]) {
				dag[belong[i]].push_back(belong[adj[i][j]]);
			}
		}
	}
}

void build_adj() {
	scanf("%d", &n); // 读取点的个数
	scanf("%d", &m); // 读取边的个数
	adj.assign(n, vector<int>());
	for (int i = 0; i < m; ++i) {
		int a, b;
		scanf("%d%d", &a, &b); // 读取有向边
		adj[a - 1].push_back(b - 1);
	}
}

void print_dag() {
	printf("强连通分量的个数 = %d\n", bcnt);
	for (int i = 0; i < bcnt; ++i) {
		printf("%d\t:", i);
		for (int j = 0; j < dag[i].size(); ++j) {
			printf("\t%d", dag[i][j]);
		}
		printf("\n");
	}
}

void init() {
	scanf("%d", &t);
}

void in() {
	build_adj();
}

void run() {
	run_tarjan();
	get_dag();
	ans = bcnt - hungary();
}

void out() {
	//print_dag();
	printf("%d\n", ans);
}

int main() {
	freopen("data", "r", stdin);

	init();
	for (int i = 0; i < t; ++i) {
		in();
		run();
		out();
	}

	/* tarjan */
	//build_adj();
	//run_tarjan();
	//get_dag();
	//print_dag();

	return 0;
}




