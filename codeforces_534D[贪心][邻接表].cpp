/*************************************************************************
    > File Name: demo.cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 日  4/12 23:55:05 2015
 ************************************************************************/

/*
 * 思路
 *
 * 这是一道贪心的题目，
 *
 * 根据握手的次数，划分level，从低level向高level逐级升高，直到高level的人不存在，那么回退3个level，继续向高level走。当level < 0时终止。
 *
 * 比赛的时候，我想多了，先把012012012这样的循环走完才进入345，这样wa了。
 * 反例还没有找到，不过确实不符合贪心的思想，不自然。
 *
 * */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define LL long long
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) > (b) ? (b) : (a))

#define N (200000)

struct Node {
	int id;
	int next;
} a[N + 5];
int a_head[N + 5], a_index;

int n, tmp;
int ans[N + 5], ans_cnt;
bool has_ans;

void init() {
}

inline void add_node(Node a[], int a_head[], int id, int num, int &a_index) {
	a[a_index].id = id;
	a[a_index].next = a_head[num];
	a_head[num] = a_index++;
}

void in() {
	memset(a_head, -1, sizeof(a_head));
	a_index = 0;
	for (int i = 0; i < n; ++i) {
		scanf("%d", &tmp);
		add_node(a, a_head, i + 1, tmp, a_index);
	}
	/*
	for (int i = 0; i < n; ++i) {
		int p = a_head[i];
		while (p != -1) {
			printf("a[%d] = %d\t", p, a[p].id);
			p = a[p].next;
		}
		printf("\n");
	}
	*/
	ans_cnt = 0;
}

void run() {
	int index = 0;
	while (true) {
		if (index < 0) {
			break;
		}
		
		if (-1 != a_head[index]) {
			ans[ans_cnt++] = a[a_head[index]].id;
			a_head[index] = a[a_head[index]].next;
			++index;
		} else {
			index -= 3;
		}
	}
}


void out() {
	if (ans_cnt == n) {
		printf("Possible\n");
		for (int i = 0; i < n; ++i) {
			if (i) {
				printf(" ");
			}
			printf("%d", ans[i]);
		}
		printf("\n");
	} else {
		printf("Impossible\n");
	}
}

int main() {
	//freopen("data", "r", stdin);

	while (~scanf("%d", &n)) {
		in();
		run();
		out();
	}

	return 0;
}
