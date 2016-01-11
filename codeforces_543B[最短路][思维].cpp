/*************************************************************************
    > File Name: 1.cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 五  5/15 10:13:44 2015
 ************************************************************************/

/*
 * edge 要开2m的空间，无向图，不要忘。。
 *
 * 任意两点最短路：floyd(O(n^3)), bfs(O(n * m))
 *
 * */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>

using namespace std;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define INF (0x1f1f1f1f)
#define MAXN (3000 + 2)

struct Edge {
	int to;
	int next;
	int w;
} edge[2 * MAXN];

int n, m;
int dis[MAXN][MAXN];
int s1, t1, l1, s2, t2, l2;
int ans;
int e_tol;
int e_head[MAXN];

void init_edge() {
	e_tol = 0;
	memset(e_head, -1, sizeof(e_head));
}

void add_edge(int from, int to, int w = 0, int rw = 0) {
	edge[e_tol].to = to; edge[e_tol].w = w;
	edge[e_tol].next = e_head[from]; e_head[from] = e_tol++;
	edge[e_tol].to = from; edge[e_tol].w = rw;
	edge[e_tol].next = e_head[to]; e_head[to] = e_tol++;
}

void bfs_f() {
	/*
	for (int i = 0; i < n; ++i) {
		int tmp = e_head[i];
		while (-1 != tmp) {
			printf("%d\t", edge[tmp].to);
			tmp = edge[tmp].next;
		}
		printf("\n");
	}
	*/
	for (int i = 0; i < n; ++i) {
		queue<int> q;
		dis[i][i] = 0;
		q.push(i);
		while (!q.empty()) {
			int now = q.front(); q.pop();
			int nxt = e_head[now];
			while (-1 != nxt) {
				if (INF != dis[i][edge[nxt].to]) {
				} else {
					dis[i][edge[nxt].to] = dis[i][now] + 1;
					q.push(edge[nxt].to);
				}
				nxt = edge[nxt].next;
			}
		}
	}
}

void init() {
}

void in() {
	init_edge();
	memset(dis, 0x1f, sizeof(dis));
	for (int i = 0; i < m; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		add_edge(a - 1, b - 1);
	}
	scanf("%d%d%d", &s1, &t1, &l1);
	--s1; --t1;
	scanf("%d%d%d", &s2, &t2, &l2);
	--s2; --t2;
}

void run() {
	bfs_f();
	if (!(dis[s1][t1] <= l1 && dis[s2][t2] <= l2)) {
		ans = -1;
		return;
	} else {
		ans = m - dis[s1][t1] - dis[s2][t2];
	}
	//printf("ans = %d\n", ans);
	for (int i = 0; i < n; ++i)  {
		for (int j = 0; j < n; ++j) {
			//printf("i = %d, j = %d\n",i, j);
			if ((dis[s1][i] + dis[t1][j] + dis[i][j] <= l1) && (dis[s2][i] + dis[t2][j] + dis[i][j] <= l2)) {
				ans = MAX(ans, m - (dis[s1][i] + dis[t1][j] + dis[s2][i] + dis[t2][j] + dis[i][j]));
			}
			//printf("ans = %d\n", ans);
			if ((dis[s1][i] + dis[t1][j] + dis[i][j] <= l1) && (dis[s2][j] + dis[t2][i] + dis[i][j] <= l2)) {
				ans = MAX(ans, m - (dis[s1][i] + dis[t1][j] + dis[s2][j] + dis[t2][i] + dis[i][j]));
			}
			//printf("ans = %d\n", ans);
		}
	}
}

void out() {
	printf("%d\n", ans);
}

int main() {
	//freopen("data", "r", stdin);

	while (~scanf("%d%d", &n, &m)) {
		in();
		run();
		out();
	}

	return 0;
}
