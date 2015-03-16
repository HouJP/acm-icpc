/*************************************************************************
    > File Name: poj_3259.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 三 10/22 21:05:28 2014
 ************************************************************************/

#include <cstdio>
#include <vector>
#include <queue>
#include <cstdlib>
#include <cstring>

using namespace std;

#define BF_MAX (500)
#define INF (1000000000)

int t, n, m, w;
int a, b, c;

struct Edge {
	int from;
	int to;
	int dist;
	Edge(int _from, int _to, int _dist) :
		from(_from), to(_to), dist(_dist) {}
};

struct BellmanFord {
	int n;
	vector<Edge> edges;
	vector<int> adj[BF_MAX + 5];
	bool inq[BF_MAX + 5];
	int min[BF_MAX + 5];
	int cnt[BF_MAX + 5];

	void init(int n) {
		this -> n = n;
		for (int i = 0; i < n; ++i) {
			adj[i].clear();
		}
		edges.clear();
	}

	void add_edge(int from, int to, int dist) {
		edges.push_back(Edge(from, to, dist));
		adj[from].push_back(edges.size() - 1);
	}

	bool negative_cycle() {
		queue<int> que;
		memset(inq, 0, sizeof(inq));
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; ++i) {
			min[i] = 0;
			inq[i] = true;
			que.push(i);
		}

		while (!que.empty()) {
			int u = que.front(); que.pop();
			inq[u] = false;
			for (int i = 0; i < adj[u].size(); ++i) {
				Edge& e = edges[adj[u][i]];
				if (min[e.to] > min[u] + e.dist) {
					min[e.to] = min[u] + e.dist;
					if (!inq[e.to]) {
						que.push(e.to);
						inq[e.to] = true;
						if (++cnt[e.to] >= n)
							return true;
					}
				}
			}
		}
		return false;
	}
};

void init() {
	scanf("%d %d %d", &n, &m, &w);
	BellmanFord bf;
	bf.init(n);
	for (int i = 0; i < m; ++i) {
		scanf("%d %d %d", &a, &b, &c);
		--a;
		--b;
		bf.add_edge(a, b, c);
		bf.add_edge(b, a, c);
	}
	for (int i = 0; i < w; ++i) {
		scanf("%d %d %d", &a, &b, &c);
		--a;
		--b;
		bf.add_edge(a, b, (-1) * c);
	}
	if (bf.negative_cycle()) {
		printf("YES\n");
	} else {
		printf("NO\n");
	}
}

int main() {
	freopen("data", "r", stdin);

	scanf("%d", &t);
	while (t--) {
		init();
	}

	return 0;
}
