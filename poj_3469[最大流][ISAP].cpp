/*************************************************************************
    > File Name: poj_3469.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 一  3/23 18:09:21 2015
 ************************************************************************/

/*
 * ISAP算法着实纠结了好几天，看了一个人的博客，跟着他的程序走了一遍，终于感觉摸到了头绪。
 * 从源点到汇点，好比在平地上流淌的溪水，如果溪水流不通，就抬高上游的点，造成一个高地势，如此反复进行，求解增广路经。当出现断层的时候，就结束程序。
 *
 * */

#include <cstdio>
#include <cstring>
#include <climits>

#define DEBUG

#ifdef DEBUG
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...)
#endif

#define N (20000)
#define M (440000)

#define min(a,b) ((a) < (b) ? (a) : (b))

int n, m;

// 图的邻接表+静态链表表示法
struct Edge {
	int u, v, weight;
	int next;
};

struct Edge edge[M + 5];
int head[N + 5]; // head[u]表示顶点u第一条邻接边的序号，若head[u] = -1, u没有邻接边
int current; // 当前有多少条边

inline void add_edge(int u, int v, int weight) {
	/*
	int i;
	// 检查u->v是否存在
	for (i = head[u]; edge[i].v != v && i != -1; i = edge[i].next);
	if (i != -1) {
		edge[i].weight = weight;
		return;
	}
	*/
	// 添加正向边u->v
	edge[current].u = u;
	edge[current].v = v;
	edge[current].weight = weight;
	edge[current].next = head[u];
	head[u] = current++;
	// 添加反向边v->u
	edge[current].u = v;
	edge[current].v = u;
	edge[current].weight = 0;
	edge[current].next = head[v];
	head[v] = current++;
}

int isap(int s, int e) {
	int i, u, v, max_flow, aug, min_lev;

	/* 寻找增广路经的过程中，curedge[u]保存的是对于顶点u当前遍历的边，寻找顶点u的邻接边时，
	 * 不用每次都从head[u]开始找，而是从curedge[u]开始找，这样就减少了搜索次数
	 * 当增广路经找到后，curedge保存的就是一条增广路经了，
	 * 比如 0--四-->1--六-->2--七-->3--八-->4	0,1,2,3,4就是顶点号，四六七八是边的序号
	 * curedge[0]=四，curedge[1]=六,...curedge[3]=8，curedge[i]即保存找过的轨迹
	 * */
	int curedge[N + 5], parent[N + 5], level[N + 5];

	/* count[l]表示属于层次l的顶点个数，如果某个层次没有定点了，
	 * 就出现断层，意味着没有增广路经了，这就是gap优化，可以提前结束寻找过程
	 * augment[v]表示从源点到顶点v中允许的最大流量，即这条路径的最小权重
	 * */
	int count[N + 5], augment[N + 5];

	memset(level, 0, sizeof(level));
	memset(count, 0, sizeof(count));
	// 初始时，每个顶点都从第一条边开始找
	for (i = 0;i <= n; ++i) {
		curedge[i] = head[i];
	}
	max_flow = 0;
	augment[s] = INT_MAX;
	parent[s] = -1;
	u = s;

	while (level[s] < n) {
		if (u == e) { // 找到一条增广路
			max_flow += augment[e];
			aug = augment[e];
			debug("找到一条增广路经， augment = %d\n", aug);
			debug("%d", e);
			for (v = parent[e]; v != -1; v = parent[v]) { // 从后往前遍历
				i = curedge[v];
				debug(" <-- %d", v);
				edge[i].weight -= aug;
				edge[i ^ 1].weight += aug; // 如果i是偶数，i^1 = i + 1, 如果i是奇数，i^1 = i - 1
				augment[edge[i].v] -= aug;
				if (edge[i].weight == 0) u = v; // u指向增广路最后可达的顶点，下次就从它继续找
			}
			debug("\n");
		}
		// 从顶点u开始往下找临界点
		for (i = curedge[u]; i != -1; i = edge[i].next) { // 从coredge[u]开始找，而不是head[u]从头开始，curedge[u]保存的是上次找过的边
			v = edge[i].v;
			if (edge[i].weight > 0 && level[u] == (level[v] + 1)) { // 找到一条边就停止
				augment[v] = min(augment[u], edge[i].weight);
				curedge[u] = i;
				parent[v] = u;
				u = v;
				break;
			}
		}
		if (i == -1) { // 没有邻接点， 回溯到上一个点
			if (--count[level[u]] == 0) {
				debug("顶点%d在level%d断层\n", u, level[u]);
				break;
			}
			curedge[u] = head[u]; // 顶点u的所有边都试过了，没有出路，更新了u的level后，又从第一条边开始在找
			// 找出level最小的邻接点
			min_lev = n;
			for (i = head[u]; i != -1; i = edge[i].next) {
				if (edge[i].weight > 0) {
					min_lev = min(level[edge[i].v], min_lev);
				}
			}
			level[u] = min_lev + 1;
			++count[level[u]];
			debug("顶点%d的level=%d\n", u, level[u]);
			debug("顶点%d走不通，回到%d\n", u, edge[curedge[u]].u);
			if (u != s) u = parent[u]; // 回退到上一个顶点
		}
	}
	return max_flow;
}

int main() {
	freopen("data", "r", stdin);

	while (~scanf("%d%d", &n, &m)) {
		memset(edge, 0, sizeof(edge));
		memset(head, -1, sizeof(head));
		current = 0;

		for (int i = 1; i <= n; ++i) {
			int a, b;
			scanf("%d %d", &a, &b);
			add_edge(0, i, a);
			add_edge(i, n + 1, b);
		}
		for (int i = 0; i < m; ++i) {
			int a, b, w;
			scanf("%d%d%d", &a, &b, &w);
			// 添加正向边
			edge[current].u = a;
			edge[current].v = b;
			edge[current].weight = w;
			edge[current].next = head[a];
			head[a] = current++;
			// 添加反向边
			edge[current].u = b;
			edge[current].v = a;
			edge[current].weight = w;
			edge[current].next = head[b];
			head[b] = current++;
		}
		n += 2;
		printf("%d\n", isap(0, n - 1));
	}

	return 0;
}
