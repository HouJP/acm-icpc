/*************************************************************************
    > File Name: hdoj_4858.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 六  3/21 13:35:17 2015
 ************************************************************************/

/*
 * 思路
 *
 * 图的分治。最多有m条边，所以度数之和最多为2 * m，所以度数大于sqrt(n)的点最多为2*sqrt(n)个。
 * 将图上的点分为两个部分，度数大于等于sqrt(n)的点，以及度数小于sqrt(n)的点，对于每个操作，针对重点和轻点进行不同的操作。
 * 如果是加weight，将该点的weight值以及该点相邻点的sum值增加v，复杂度为sqrt(n)。
 * 如果是求sum，若该点是重点，直接输出sum，如果该点是轻点，遍历相邻点并求和，复杂度为sqrt(n)。
 *
 * 这样，成功的将复杂度从q * n降到了q * sqrt(n)，很巧妙。
 *
 * */

#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define LL long long
#define N (100000)
#define M (100010)

struct E {
	int a;
	int b;
};

int n, m, t, q, thresh, cmd, u, v;

E edges[M + 5];
int weight[N + 5];
int degree[N + 5];
int sum[N + 5];
vector<int> heavy_nodes[N + 5];
vector<int> adj_nodes[N + 5];

void init() {
	scanf("%d", &t);
}

void in() {
	memset(weight, 0, sizeof(weight));
	memset(degree, 0, sizeof(degree));
	memset(sum, 0, sizeof(sum));
	
	scanf("%d%d", &n, &m);
	thresh = (int)sqrt(n);

	for (int i = 0; i <= n; ++i) {
		heavy_nodes[i].clear();
		adj_nodes[i].clear();
	}

	for (int i = 0; i < m; ++i) {
		scanf("%d%d", &edges[i].a, &edges[i].b);
		++degree[edges[i].a];
		++degree[edges[i].b];
	}
	for (int i = 0; i < m; ++i) {
		if (thresh <= degree[edges[i].a]) {
			heavy_nodes[edges[i].b].push_back(edges[i].a);
		} else {
			adj_nodes[edges[i].a].push_back(edges[i].b);
		}
		if (thresh <= degree[edges[i].b]) {
			heavy_nodes[edges[i].a].push_back(edges[i].b);
		} else {
			adj_nodes[edges[i].b].push_back(edges[i].a);
		}
	}

	scanf("%d", &q);
}

void run() {
	for (int i = 0; i < q; ++i) {
		scanf("%d", &cmd);
		if (0 == cmd) {
			scanf("%d%d", &u, &v);
			weight[u] += v;
			for (int j = 0; j < heavy_nodes[u].size(); ++j) {
				sum[heavy_nodes[u][j]] += v;
			}
		} else {
			scanf("%d", &u);
			if (thresh <= degree[u]) {
				printf("%d\n", sum[u]);
			} else {
				sum[u] = 0;
				for (int j = 0; j < adj_nodes[u].size(); ++j) {
					sum[u] += weight[adj_nodes[u][j]];
				}
				printf("%d\n", sum[u]);
			}
		}
	}
}

void out() {
}

int main() {
	freopen("data", "r", stdin);

	init();
	for (int i = 0; i < t; ++i) {
		in();
		run();
		out();
	}

	return 0;
}
