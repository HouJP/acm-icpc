/*************************************************************************
    > File Name: hdoj_4883.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 六  3/28 16:43:59 2015
 ************************************************************************/

/* 
 * 思路
 *
 * 这是BestCoder Round#2 的第一题，结果！一直TLE！！
 *
 * 刚开始的思路是把客人拆成两个时间点，来的时候和走的时候，然后按序，ans按照时间顺序进行加减操作。结果T了。恩，好吧，然后换成线段树，结果，又T了！！
 *
 * 所以就回去修改原来的代码，去掉了结构体里面一个没用的变量，删除没用的if语句，然后就过了。。。
 *
 * 去掉一个变量，以及相关赋值语句，和一个if --> 795ms
 * 每五个输入用三个scanf，变成每五个输入用一个scanf --> 639ms
 *
 * 结论，代码的精简真是太重要了。。。手贱脑残多加了点东西，华丽丽的T到死。
 *
 * 1. 减少变量的定义，以及么用的代码，if等。
 * 2. 减少函数的调用次数，如scanf。
 *
 * */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define N (10000 + 5)

struct Node {
	//int type; 简直T到死
	int num;
	int time;
} nodes[2 * N];

int t, n, ans;
int num, t1, t2, m1, m2;

bool cmp(const Node &a, const Node &b) {
	if (a.time != b.time) {
		return a.time < b.time;
	} else {
		return a.num < b.num;
	}
}

void init() {
	scanf("%d", &t);
}

void in() {
	scanf("%d", &n);
	int tmp = 0;
	for (int i = 0; i < n; ++i) {
		scanf("%d%d:%d%d:%d", &num, &t1, &m1, &t2, &m2);
		nodes[tmp].num = num;
		nodes[tmp++].time = t1 * 60 + m1;
		nodes[tmp].num = -num;
		nodes[tmp++].time = t2 * 60 + m2;
	}
	ans = 0;
}

void run() {
	sort(nodes, nodes + 2 * n, cmp);

	int cnt = 0;
	for (int i = 0; i < 2 * n; ++i) {
		cnt += nodes[i].num;
		ans = MAX(ans, cnt);
	}
}

void out() {
	printf("%d\n", ans);
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

/*

#define MAX_MINUTE (1440)

int t, n, num, h1, m1, h2, m2, ans;

int arr[MAX_MINUTE + 5];

inline int lowbit(int x) {
	return x & (-x);
}

inline void modify(int x, int add) {
	while (x <= MAX_MINUTE) {
		arr[x] += add;
		x += lowbit(x);
	}
}

inline int get_sum(int x) {
	int ret = 0;
	while (x != 0) {
		ret += arr[x];
		x -= lowbit(x);
	}
	return ret;
}

int main() {
	freopen("data", "r", stdin);

	scanf("%d", &t);
	while (t--) {
		// init
		ans = 0;
		memset(arr, 0, sizeof(arr));
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d%d:%d%d:%d", &num, &h1, &m1, &h2, &m2);
			modify(h1 * 60 + m1, num);
			modify(h2 * 60 + m2, (-1) * num);
		}

		// run
		for (int i = 0; i < MAX_MINUTE; ++i) {
			ans = MAX(ans, get_sum(i));
		}

		// out
		printf("%d\n", ans);
	}

	return 0;
}

*/
