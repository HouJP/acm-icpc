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
#include <iostream>

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

#define MAXN (300000 + 5)

struct Edge {
    int to, next;
    LL w;
} edge[2 * MAXN];
int tol;
int head[MAXN];
int n, m, a, b, c, u;
LL sum[MAXN];
LL pre_e[MAXN];
int pre_e_id[MAXN];
LL ans;

struct Node {
	int id;
	LL sum;
	Node(int _id, LL _sum) : id(_id), sum(_sum) {}
	bool operator < (const Node & a) const {
		return sum > a.sum;
	}
};

void add_edge(int u, int v, int w, int rw) {
    edge[tol].to = v;
    edge[tol].w = w;
    edge[tol].next = head[u];
    head[u] = tol++;
    edge[tol].to = u;
    edge[tol].w = rw;
    edge[tol].next = head[v];
    head[v] = tol++;
}

void init() {
}

void bfs() {
	priority_queue<Node> nodes;
	sum[u] = 0;
	nodes.push(Node(u, 0));
	while (!nodes.empty()) {
		Node now = nodes.top(); nodes.pop();
		if (sum[now.id] < now.sum) {
			continue;
		}
		int tmp = head[now.id];
		while (-1 != tmp) {
			int nxt = edge[tmp].to;
			if (sum[nxt] > sum[now.id] + edge[tmp].w) {
				sum[nxt] = sum[now.id] + edge[tmp].w;
				pre_e_id[nxt] = tmp;
				pre_e[nxt] = edge[tmp].w;
				nodes.push(Node(nxt, sum[nxt]));
			} else if (sum[nxt] == (sum[now.id] + edge[tmp].w)) {
				if (pre_e[nxt] > edge[tmp].w) {
					pre_e_id[nxt] = tmp;
					pre_e[nxt] = edge[tmp].w;
				}
			}

			tmp = edge[tmp].next;
		}
	}
}

void in() {
	memset(sum, 0x3f, sizeof(sum));
    memset(head, -1, sizeof(head));
    tol = 0;
	ans = 0;
    
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &a, &b, &c);
		--a;
		--b;
        add_edge(a, b, c, c);
    }
    scanf("%d", &u);
	--u;
	/*
	for (int i = 0; i < n; ++i) {
		int tmp = head[i];
		printf("%d : ", i);
		while (-1 != tmp) {
			printf("%d,%d\t", edge[tmp].to, edge[tmp].w);
			tmp = edge[tmp].next;
		}
		printf("\n");
	}
	*/
}

void run() {
	bfs();

	for (int i = 0; i < n; ++i) {
		if (i != u) {
			ans += pre_e[i];
		}
	}
}

void out() {
	cout << ans << endl;
	bool fir = true;
	for (int i = 0; i < n; ++i) {
		if (i != u) {
			if (!fir) {
				printf(" ");
			} else {
				fir = false;
			}
			printf("%d", pre_e_id[i] / 2 + 1);
		}
	}
	if (n > 1) {
		printf("\n");
	}
}

void out(int cas) {
}

int main() {
	//freopen("data", "r", stdin);

	init();
    while (~scanf("%d%d", &n, &m)) {
        in();
        run();
        out();
    }

	return 0;
}
