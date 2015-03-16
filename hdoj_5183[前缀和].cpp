/*************************************************************************
    > File Name: template.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 日  3/ 8 21:45:31 2015
 ************************************************************************/

#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define LL long long

using namespace std;

const int MOD = 1000007;
const int MAX = 1000000;

struct HashNode {
	LL x;
	HashNode * next; 
	HashNode() : x(0), next(NULL) {}
	HashNode(int _x, HashNode * _next) : x(_x), next(_next) {}
} *arr[2][MOD + 5];

HashNode nodes[MAX + 5];
int nodes_length;
LL t, n, k, sum, num;
bool ret;

void read(LL &x) {
    char ch = getchar();
    int tag = 1;
    x = 0;
    while ((ch <'0' || ch > '9') && ch != '-') {
        ch = getchar();
    }
    if (ch == '-') {
        tag = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    x *= tag;
}

bool hash_find(LL x, HashNode ** arr_p) {
	int id = (x % MOD + MOD) % MOD;
	HashNode * & p = arr_p[id];
	while (p) {
		if (p->x == x) {
			return true;
		}
		p = p->next;
	}
	return false;
}

void hash_insert(LL x, HashNode ** arr_p) {
	int id = (x % MOD + MOD) % MOD;
	HashNode *& p =  arr_p[id];
	while (p) {
		if (p->x == x) {
			return;
		}
		p = p->next;
	}
	nodes[nodes_length].x = x;
	nodes[nodes_length].next = NULL;
	p = & nodes[nodes_length++];
}

void init() {
}

void in() {
	read(n);
	read(k);
	ret = false;
	sum = 0;
	nodes_length = 0;
	memset(arr, 0, sizeof(arr));
	hash_insert(0, arr[0]);
}

void run() {
	for (int i = 0; i < n; ++i) {
		read(num);
		if (!ret) {
			if (0 == (i % 2)) {
				sum += num;
			} else {
				sum -= num;
			}
			if (hash_find(k + sum, arr[1])
					|| hash_find(sum - k, arr[0])) {
				ret = true;
			}
			if (0 == (i % 2)) {
				hash_insert(sum, arr[1]);
			} else {
				hash_insert(sum, arr[0]);
			}
		}
	}
}

void out(int cas) {
	printf("Case #%d: ", cas);
	if (ret) {
		printf("Yes.\n");
	} else {
		printf("No.\n");
	}
}
int main() {
	freopen("data", "r", stdin);

	read(t);
	init();
	for (int i = 0; i < t; ++i) {
		in();
		run();
		out(i + 1);
	}

	return 0;
}
