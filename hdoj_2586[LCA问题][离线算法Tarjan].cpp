/*************************************************************************
    > File Name: hdoj_2586.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 二  4/ 7 11:39:20 2015
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define N (40000)
#define M (200)

int n, m, t;
int a, b, c;

// LCA问题，离线算法 Tarjan
// 时间复杂度 O(n + q), n为总节点数，q为询问节点对数

// LCA--并查集部分
int uroot[N + 5];

void make_set(int size) {
	for (int i = 0; i < size; ++i) {
		uroot[i] = i;
	}
}

int find_root(int x) {
	if (uroot[x] != x) uroot[x] = find_root(uroot[x]);
	return uroot[x];
}

// LCA--通过边表，构造树
struct Edge {
	int u, v, w, next;
};

Edge e[2 * N + 5]; // 保存边，w表示权重
Edge q[2 * M + 5]; // 保存询问，w存放lca
int e_head[N + 5]; // 邻接表表头
int q_head[N + 5]; // 询问的邻接表表头
int e_index;

int dis[N + 5]; // 保存到根节点的距离
bool vis[N + 5]; // 遍历时的标记数组

inline void add_edge(Edge e[], int e_head[], int u, int v, int w, int &k) {
	e[k].u = u; e[k].v = v; e[k].w = w;
	e[k].next = e_head[u]; e_head[u] = k++;
	e[k].u = v; e[k].v = u; e[k].w = w;
	e[k].next = e_head[v]; e_head[v] = k++;
}

void tarjan(int u) {
	vis[u] = true;

	for (int k = e_head[u]; -1 != k; k = e[k].next) {
		if (!vis[e[k].v]) {
			int v = e[k].v;
			dis[v] = dis[u] + e[k].w;
			tarjan(v);
			uroot[v] = u;
		}
	}
	for (int k = q_head[u]; -1 != k; k = q[k].next) {
		if (vis[q[k].v]) {
			int v = q[k].v;
			q[k].w = q[k ^ 1].w = find_root(v);
		}
	}
}

int main() {
	freopen("data", "r",stdin);

	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		// 初始化
		memset(e_head, -1, sizeof(e_head));
		memset(q_head, -1, sizeof(q_head));
		memset(vis, 0, sizeof(vis));
		memset(dis, 0, sizeof(dis));
		make_set(n);
		// 建树
		e_index = 0; 
		for (int i = 1; i < n; ++i) {
			scanf("%d%d%d", &a, &b, &c);
			add_edge(e, e_head, a - 1, b - 1, c, e_index);
		}
		// 保存询问
		e_index = 0;
		for (int i = 0; i < m; ++i) {
			scanf("%d%d", &a, &b);
			add_edge(q, q_head, a - 1, b - 1, -1, e_index);
		}
		/*
		for (int i = 0; i < n ; ++i) {
			int index = e_head[i];
			while (-1 != index) {
				printf("%d\t%d\t%d\t%d\t%d\n", index, e[index].u, e[index].v, e[index].w, e[index].next);
				index = e[index].next;
			}
		}
		for (int i = 0; i < n; ++i) {
			int index = q_head[i];
			while (-1 != index) {
				printf("%d\t%d\t%d\t%d\t%d\n", index, q[index].u, q[index].v, q[index].w, q[index].next);
				index = q[index].next;
			}
		}
		*/
		// dfs，寻找LCA
		tarjan(0);
		// 输出
		for (int i = 0; i < m; ++i) {
			int k = 2 * i;
			//printf("u = %d, v = %d, root = %d, dis = %d\n", q[k].u, q[k].v, q[k].w, dis[q[k].u] + dis[q[k].v] - 2 * dis[q[k].w]);
			printf("%d\n", dis[q[k].u] + dis[q[k].v] - 2 * dis[q[k].w]);
		}
	}

	return 0;
}
