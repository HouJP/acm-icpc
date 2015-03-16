/*************************************************************************
    > File Name: hdoj_3954.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 日 10/26 09:35:25 2014
 ************************************************************************/

/* *
 *
 * 思路
 *
 * 刚开始的时候始终想不通为什么可以用线段树，后来才明白，英雄的级别最多只有十级，所以即使升级是一个退化操作（也就是说每个英雄都更新），那么所有英雄升到满级需要的操作步数为n * log(n) * k，可以接受。
 *
 * 教训
 *
 * WA了无数次，最后发现是因为初始化没有初始化所有的参数，遗漏了Node中的ei变量 -> 如果初始化线段树的时候，每个叶子的状态相同，是没有必要使用push_up操作的，如果想用的话，一定要注意有没有遗漏状态没有更新。
 *
 * */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define N (10000)
#define K (10)

int t, n, k, qw;
int needk[K + 5];
int li, ri, ei;
char s[5];
int ans;

struct Node {
	int max_exp[K + 5];
	int ei;
};

Node st[4 * N + 5];

void push_up(int root) {
	for (int i = 1; i <= k ; ++i) {
		st[root].max_exp[i] = -1;
		if (st[root << 1].max_exp[i] != -1) {
			st[root].max_exp[i] = max(st[root].max_exp[i], st[root << 1].max_exp[i] + st[root << 1].ei * i);
		}
		if (st[root << 1 | 1].max_exp[i] != -1) {
			st[root].max_exp[i] = max(st[root].max_exp[i], st[root << 1 | 1].max_exp[i] + st[root << 1 | 1].ei * i);
		}
	}
}

void build(int root, int l, int r) {
	if (l > r) return;
	st[root].max_exp[1] = 0;
	for (int i = 2; i <= k; ++i) {
		st[root].max_exp[i] = -1;
	}
	st[root].ei = 0;
	if (l == r) {
		return;
	}
	int mid = (l + r) / 2;
	build(root << 1, l, mid);
	build(root << 1 |1 , mid + 1, r);
	//push_up(root);
}

void push_down(int root) {
	st[root << 1].ei += st[root].ei;
	st[root << 1 | 1].ei += st[root].ei;
	st[root].ei = 0;
}

void update(int root, int l, int r, int ll, int rr, int ei) {
	if (ll > r || rr < l || l > r) return;
	if (ll <= l && rr >= r) {
		if (l == r) {
			if (st[root].max_exp[k] != -1) {
				st[root].max_exp[k] += (st[root].ei + ei) * k;
			}
			for (int i = k - 1; i >= 1; --i) {
				if (st[root].max_exp[i] != -1) {
					st[root].max_exp[i] += (st[root].ei + ei) * i;
					for (int j = k; j > i; --j) {
						if (st[root].max_exp[i] >= needk[j]) {
							st[root].max_exp[j] = st[root].max_exp[i];
							st[root].max_exp[i] = -1;
							break;
						}
					}
					break;
				}
			}
			st[root].ei = 0;
			return;
		} else {
			bool is_rec = false;
			for(int i = k - 1; i >= 1; --i) {
				if (st[root].max_exp[i] != -1) {
					if (st[root].max_exp[i] + (st[root].ei + ei)* i >= needk[i + 1]) {
						is_rec = true;
						break;
					}
				}
			}
			if (!is_rec) {
				st[root].ei += ei;
				return;
			}
		}
	}
	push_down(root);
	int mid = (l + r) / 2;
	update(root << 1, l, mid, ll, rr,  ei);
	update(root << 1 | 1, mid + 1, r, ll, rr, ei);
	push_up(root);
}

int query(int root, int l, int r, int ll, int rr) {
	if (ll > r || rr < l || l > r) return 0;
	if ((l == r) || (ll <= l && rr >= r)) {
		int ret = 0;
		for (int i = 1; i <= k; ++i) {
			if (st[root].max_exp[i] != -1) {
				if (st[root].max_exp[i] + st[root].ei * i > ret) {
					ret = st[root].max_exp[i] + st[root].ei * i;
				}
			}
		}
		return ret;
	}
	push_down(root);
	int mid = (l + r) / 2;
	int ret = 0;
	ret = max(query(root << 1, l, mid, ll, rr), query(root << 1 | 1, mid + 1, r, ll, rr));
	push_up(root);
	return ret;
}

void print(int root, int l, int r) {
	if (l > r) return;
	printf("-------\n");
	printf("%d %d %d %d:\n", root, l, r, st[root].ei);
	for (int i = 1; i <= k; ++i) {
		printf("%d\t", st[root].max_exp[i]);
	}
	printf("\n");
	if (l == r) return;
	int mid = (l + r) / 2;
	print(root << 1, l , mid);
	print(root << 1 | 1, mid + 1, r);
}

int main() {
	freopen("data", "r", stdin);

	scanf("%d", &t);
	for (int ii = 1; ii <= t; ++ii) {
		printf("Case %d:\n", ii);
		scanf("%d %d %d", &n, &k, &qw);
		for (int i = 2; i <= k; ++i) {
			scanf("%d", &needk[i]);
		}
		build(1, 1, n);
		for (int i = 1; i <= qw; ++i) {
			scanf("%s", s);
			if (strcmp(s, "W") == 0) {
				scanf("%d %d %d", &li, &ri, &ei);
				update(1,1, n, li, ri, ei);
				print(1,1,n);
			} else {
				scanf("%d %d", &li, &ri);
				printf("%d\n", query(1, 1, n, li, ri));
			}
		}
		printf("\n");
	}

	return 0;
}
