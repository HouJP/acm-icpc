/*************************************************************************
    > File Name: bc_2.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 日  3/29 08:50:40 2015
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#define MIN(a,b) (a < b ? (a) : (b))
#define MAX(a,b) (a < b ? (b) : (a))
#define INF (0x3fffffff)

#define N (100000)

struct Node {
	int indegree;
	int id;
} nodes[N + 5];

vector<vector<int> > adj;
int indegree[N + 5];

int n, m, k;
int a, b;

// segment tree
int st[4 * N + 5];

void push_up(int root) {
	st[root] = MIN(st[root << 1], st[root << 1 | 1]);
}

void build(int root, int l, int r) {
	if (l > r) {
		st[root] = INF;
		return;
	}
	if (l == r) {
		st[root] = indegree[l];
		return;
	}

	int mid = (l + r) / 2;
	build(root << 1, l, mid);
	build(root << 1 | 1, mid + 1, r);
	push_up(root);
}

int query(int root, int l, int r, int value) {
	if (l >= r) return r;

	int mid = (l + r) / 2;
	if (st[root << 1 | 1] <= value) {
		return query(root << 1 | 1, mid + 1, r, value);
	} else {
		return query(root << 1, l, mid, value);
	}
}

void update(int root, int l, int r, int id, int value) {
	if (l > r) return;
	if (l == r) {
		st[root] = value;
		return;
	}

	int mid = (l + r) / 2;
	if (id <= mid) {
		update(root << 1, l, mid, id, value);
	} else {
		update(root << 1 | 1, mid + 1, r, id, value);
	}

	push_up(root);
}

void in() {
	adj.assign(n, vector<int>());
/*
	for (int i = 0; i < n; ++i) {
		nodes[i].id = i;
		nodes[i].indegree = 0;
	}
*/
	memset(indegree, 0, sizeof(indegree));

	for (int i = 0; i < m; ++i) {
		scanf("%d%d", &a, &b);
		adj[a - 1].push_back(b - 1);
		++indegree[b - 1];
	}
}

void run() {
	build(1, 0, n - 1);

	bool first = true;
	for (int i = 0; i < n; ++i) {
		if (first) {
			first = false;
		} else {
			printf(" ");
		}

		int id = query(1, 0, n - 1, k);
		k = MAX(0, k - indegree[id]);
		update(1, 0, n - 1, id, INF);
		indegree[id] = INF;
		for (int j = 0; j < adj[id].size(); ++j) {
			if (indegree[adj[id][j]] != INF) {
				update(1, 0, n - 1, adj[id][j], indegree[adj[id][j]] - 1);
				--indegree[adj[id][j]];
			}
		}
		printf("%d", id + 1);
	}
}

void out() {
	printf("\n");
}

int main() {
	freopen("data", "r", stdin);

	while (~scanf("%d%d%d", &n, &m, &k)) {
		in();
		run();
		out();
	}

	return 0;
}
