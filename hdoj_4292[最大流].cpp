/*************************************************************************
    > Author: HouJP
    > Mail: houjp1992@gmail.com
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <map>

using namespace std;

#define LL long long

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x)	x.begin(), x.end()
#define rall(x)	x.rbegin(), x.rend()
#define sz(a)	int(a.size())
#define reset(a, x)	memset(a, x, sizeof(a))

#define MAX(a,b)		((a) > (b) ? (a) : (b))
#define MIN(a,b)		((a) > (b) ? (b) : (a))
#define ABS(a)			((a) > 0 ? (a) : (-(a)))
#define FOR(i, a, b)	for(int i = a; i <= b; ++i)
#define FORD(i, a, b)	for(int i = a; i >= b; --i)
#define REP(i, n)		for(int i = 0, _n = n; i < _n; ++i)
#define REPD(i, n)		for(int i = n - 1; i >= 0; --i)
#define FORSZ(i, x)		for(int i = 0; i < sz(x); ++i)

#define INF (0x3f3f3f3f)
#define NINF ((-1)*INF)
#define INFLL (0x3f3f3f3f3f3f3f3fLL)
#define NINFLL ((-1)*INFLL)

const int MAXN = 1000;
const int MAXM = 100000;

struct Edge {
	int from;
	int to;
	int next;
	int cap;
} edge[2 * MAXM + 5]; 

int tol;
int head[MAXN + 5];
int dep[MAXN + 5];
int gap[MAXN + 5];
int n;

void ini() {
	tol = 0;
	memset(head, -1, sizeof(head));
}

inline void add_edge(int u, int v, int w, int rw = 0) {
	edge[tol].from = u;
	edge[tol].to = v;
	edge[tol].cap = w;
	edge[tol].next = head[u];
	head[u] = tol++;
	edge[tol].from = v;
	edge[tol].to = u;
	edge[tol].cap = rw;
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
			++gap[dep[v]];
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
				edge[S[i] ^ 1].cap += temp;
			}
			res += temp;
			top = inser;
			u = edge[S[top]].from;
		}
		if (u != end && gap[dep[u] - 1] == 0) break;
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
			for(i = head[u]; i != -1; i = edge[i].next) {
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

int nn, f, d;
char s[210];
int ff[210], dd[210];

void init() {
}

void in() {
	ini();
	n = 2 * nn + f + d + 2;
	for (int i = 0; i < nn; ++i) {
		add_edge(2 * i + 1, 2 * i + 2, 1);
	}

	for (int i = 0; i < f; ++i) {
		scanf("%d", &ff[i]);
		add_edge(2 * nn + f + d + 1, 2 * nn + i + 1, ff[i]);
	}
	for (int i = 0; i < d; ++i) {
		scanf("%d", &dd[i]);
		add_edge(2 * nn + f + i + 1, 2 * nn + f + d + 1 + 1, dd[i]);
	}
	for (int i = 0; i < nn; ++i) {
		scanf("%s", s);
		for (int j = 0; j < f; ++j) {
			if ('Y' == s[j]) {
				add_edge(2 * nn + j + 1, 2 * i + 1, 1);
			}
		}
	}
	for (int i = 0; i < nn; ++i) {
		scanf("%s", s);
		for (int j =0; j < d; ++j) {
			if ('Y' == s[j]) {
				add_edge(2 * i + 2, 2 * nn + f + j + 1, 1);
			}
		}
	}
}

void run() {
}

void out() {
	printf("%d\n", sap(2 * nn + f + d + 1, 2 * nn + f + d + 2));
}

void out(int cas) {
}

int main() {
	freopen("data", "r", stdin);

	init();
	while(~scanf("%d%d%d", &nn, &f, &d)) {
		in();
		run();
		out();
	}

	return 0;
}
