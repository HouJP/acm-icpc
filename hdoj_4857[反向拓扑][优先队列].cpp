/*************************************************************************
    > File Name: hdoj_4857.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 六  3/21 14:41:32 2015
 ************************************************************************/

/*
 * 思路
 *
 * 这道题很有意思，如果只是拓扑排序就WA了，因为最终的结果不是字典序的第一个，而是要求，数字最小的尽可能靠前，然后次小的尽可能靠前，依次类推，这里是一个陷阱。
 * 所以，反过来进行拓扑排序，然后逆序输出即可。用优先队列优化。
 *
 * 从后向前拓扑，意味着，当存在歧义的情况下，标号小的先留着不输出，而输出大，只有当退无可退的情况下，才输出小编号，这样就保证了编号小的尽量靠前，有点贪心的意思。
 *
 * */

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

#define N (30000)

int n, m, t, a, b;
vector<int> adj[N + 5];
int indeg[N + 5];
priority_queue<int, vector<int>, less<int> > que;
int ans[N + 5], ans_length;

void init() {
	scanf("%d", &t);
}

void in() {
	scanf("%d%d", &n, &m);

	for (int i = 0; i <= n; ++i) {
		adj[i].clear();
		indeg[i] = 0;
	}

	for (int i = 0; i < m; ++i) {
		scanf("%d%d", &a, &b);
		++indeg[a];
		adj[b].push_back(a);
	}

	while (!que.empty()) {
		que.pop();
	}

	ans_length = 0;
}

void run() {
	for (int i = 1; i <= n; ++i) {
		if (0 == indeg[i]) {
			que.push(i);
		}
	}

	while (!que.empty()) {
		int tmp = que.top();
		que.pop();
		ans[ans_length++] = tmp;

		for (int i = 0; i < adj[tmp].size(); ++i) {
			--indeg[adj[tmp][i]];
			if (0 == indeg[adj[tmp][i]]) {
				que.push(adj[tmp][i]);
			}
		}
	}
}

void out() {
	for (int i = ans_length - 1; i >= 0; --i) {
		if (i) {
			printf("%d ", ans[i]);
		} else {
			printf("%d\n", ans[i]);
		}
	}
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
