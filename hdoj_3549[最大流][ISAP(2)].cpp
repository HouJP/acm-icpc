/*************************************************************************
    > File Name: hdoj_4859.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 二  3/24 10:29:19 2015
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <climits>

int t, n, m, ans;

const int MAXN = 2500; // 点数的最大值
const int MAXM = 7500; // 边数的最大值
const int INF = 0x3f3f3f3f;

struct ISAP {
	struct Node {
		int from, to, next;
		int cap;
	} edge[MAXM + 5];

	int tol;
	int head[MAXN + 5];
	int dep[MAXN + 5];
	int gap[MAXN + 5]; // gap[x] = y 说明残留网络中dep[i] == x的个数为y

	int n; // n是总的点的个数，包括源点和汇点

	void init(int _n) {
		n = _n;
		tol = 0;
		memset(head, -1, sizeof(head));
	}

	void add_edge(int u, int v, int w, int type) {
		edge[tol].from = u;
		edge[tol].to = v;
		edge[tol].cap = w;
		edge[tol].next = head[u];
		head[u] = tol++;
		edge[tol].from = v;
		edge[tol].to = u;
		if (!type) {
			edge[tol].cap = 0;
		} else {
			edge[tol].cap = w;
		}
		edge[tol].next = head[v];
		head[v] = tol++;
	}

	void bfs(int start, int end) {
		memset(dep, -1, sizeof(dep));
		memset(gap, 0, sizeof(gap));
		gap[0] = 1;
		int que[MAXN + 5];
		int front, rear;
		front = rear = 0;
		dep[end] = 0;
		que[rear++] = end;
		while (front != rear) {
			int u = que[front++];
			if (front == MAXN) front = 0;
			for (int i = head[u]; i != -1; i = edge[i].next) {
				int v = edge[i].to;
				if (dep[v] != -1) continue;
				que[rear++] = v;
				if (rear == MAXN) rear = 0;
				dep[v] = dep[u] + 1;
				++ gap[dep[v]];
			}
		}
	}

	int sap(int start, int end) {
		int res = 0;
		bfs(start, end);
		int cur[MAXN + 5];
		int S[MAXN + 5];
		int top = 0;
		memcpy(cur, head, sizeof(head));
		int u = start;
		int i;
		while (dep[start] < n) {
			if (u == end) {
				int temp = INF;
				int inser;
				for (i = 0; i < top; ++i) {
					if (temp > edge[S[i]].cap) {
						temp = edge[S[i]].cap;
						inser = i;
					}
				}
				for (i = 0; i < top; ++i) {
					edge[S[i]].cap -= temp;
					edge[S[i]^1].cap += temp;
				}
				res += temp;
				top = inser;
				u = edge[S[top]].from;
			}
			if (u != end && gap[dep[u] - 1] == 0) // 出现断层，无增广路
				break;
			for (i = cur[u]; i != -1; i = edge[i].next) {
				if (edge[i].cap != 0 && dep[u] == dep[edge[i].to] + 1) {
					break;
				}
			}
			if (-1 != i) {
				cur[u] = i;
				S[top++] = i;
				u = edge[i].to;
			} else {
				int min = n;
				for (i = head[u]; i != -1; i = edge[i].next) {
					if (0 == edge[i].cap) continue;
					if (min > dep[edge[i].to]) {
						min = dep[edge[i].to];
						cur[u] = i;
					}
				}
				--gap[dep[u]];
				dep[u] = min + 1;
				++gap[dep[u]];
				if (u != start) {
					u = edge[S[--top]].from;
				}
			}
		}
		return res;
	}
} isap;

void init() {
	scanf("%d", &t);
}

void in() {
	scanf("%d%d", &n, &m);
	isap.init(n);
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		isap.add_edge(u, v, w, 0);
	}
}

void run() {
	ans = isap.sap(1, n);
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
