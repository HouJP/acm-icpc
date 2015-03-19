/*************************************************************************
    > File Name: hdoj_5188.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 三  3/18 22:15:51 2015
 ************************************************************************/

/*
 *
 * 笔记
 *
 *	在while或者for循环里面，使用了++，当while或者for循环结束之后，调用++的这个数值，忘了减一，导致WA。
 *
 * */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define LL long long

#define MAXN (30)
#define MAXW (1000000000)

struct Node {
	int t;
	LL v;
	int l;
} nodes[MAXN + 5];

struct Node2 {
	int endt;
	LL score;
} nodes2[(1 << 15) + 5], mono_que[(1 << 15) + 5];

int mono_que_len;
int n, w, t, v, l;
int ans, tmp;

bool cmp(Node a, Node b) {
	return a.l - a.t < b.l - b.t;
}

bool cmp2(Node2 a, Node2 b) {
	return a.score < b.score;
}

int binary_search(Node2 * a, int len, LL goal) {
	int low = 0;
	int high = len - 1;
	while (low <= high) {
		int middle = (low + high) / 2;
		if (a[middle].score >= goal) {
			high = middle - 1;
		} else {
			low = middle + 1;
		}
	}
	return low;
}

void init() {
}

void in() {
	for (int i = 0; i < n; ++i) {
		scanf("%d %d %d", &t, &v, &l);
		nodes[i].t = t;
		nodes[i].v = v;
		nodes[i].l = l;
	}
	ans = MAXW;
}

void run() {
	sort(nodes, nodes + n, cmp);

	int count = 1 << (n / 2);
	for (int i = 0; i < count; ++i) {
		nodes2[i].score = 0;
		nodes2[i].endt = 0;
		for (int j = 0; j < n / 2; ++j) {
			if ((i >> j) & 0x01) {
				nodes2[i].score += nodes[j].v;
				nodes2[i].endt = max(nodes2[i].endt, nodes[j].l - nodes[j].t) + nodes[j].t;
			}
		}
	}

	sort(nodes2, nodes2 + count, cmp2);

	mono_que_len = 0;
	for (int i = 0; i < count; ++i) {
		if (mono_que_len) {
			if (mono_que[mono_que_len - 1].endt >= nodes2[i].endt) {
				int j = 0;
				while ((mono_que_len - j) && (mono_que[mono_que_len - 1 - j].endt >= nodes2[i].endt)) {
					mono_que[mono_que_len - 1 - j++] = nodes2[i];
				}
				mono_que_len -= j - 1;	// 这里j需要减一，WA
			} else {
				mono_que[mono_que_len++] = nodes2[i];
			}
		} else {
			mono_que[mono_que_len++] = nodes2[i];
		}

	}

	if ((tmp = binary_search(mono_que, mono_que_len, w)) < mono_que_len) {
		ans = mono_que[tmp].endt;
	}

	count = 1 << (n - n / 2);
	for (int i = 0; i < count; ++i) {
		Node2 node2;
		node2.score = 0;
		for (int j = 0; j < n - n / 2; ++j) {
			if ((i >> j) & 0x01) {
				node2.score += nodes[j + n / 2].v;
			}
		}

		int left = w - node2.score;
		if (left < 0) left = 0;
		if ((tmp = binary_search(mono_que, mono_que_len, left)) < mono_que_len) {
			node2.endt = mono_que[tmp].endt;
		} else {
			continue;
		}
		for (int j = 0; j < n - n / 2; ++j) {
			if ((i >> j) & 0x01) {
				node2.endt = max(node2.endt, nodes[j + n / 2].l - nodes[j + n / 2].t) + nodes[j + n / 2].t;
			}
		}
		if (node2.endt < ans) {
			ans = node2.endt;
		}
	}
}

void out() {
	if (MAXW == ans) {
		printf("zhx is naive!\n");
	} else {
		printf("%d\n", ans);
	}
}

int main() {
	freopen("data", "r", stdin);

	init();
	while (~scanf("%d%d", &n, &w)) {
		in();
		run();
		out();
	}

	return 0;
}
