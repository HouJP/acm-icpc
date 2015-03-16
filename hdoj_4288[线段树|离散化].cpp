/*************************************************************************
    > File Name: hdoj_4288.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 四 10/23 18:14:47 2014
 ************************************************************************/

/* *
 *
 * 思路
 *
 * 单点更新，区间查询的线段树。
 *
 * */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define LL long long
#define MAX (100000)
#define MOD (5)

struct SegTreeNode {
	LL sum[5];
	int cnt;
};

int n, num;
int opp[MAX + 5][2];
int map[MAX + 5];
int map_len;
char s[5];
SegTreeNode seg_tree[4 * MAX + 5];

int binary_search(int a[], int low, int high, int value) {
	while (low <= high) {
		int mid = (low + high) / 2;
		if (a[mid] >= value) {
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	return low;
}

void init() {
	map_len = 0;
	for (int i = 0; i < n; ++i) {
		scanf("%s",  s);
		if (!strcmp(s, "add")) {
			scanf("%d", &num);
			opp[i][0] = 0;
			opp[i][1] = num;
			map[map_len++] = num;
		} else if (!strcmp(s, "sum")) {
			opp[i][0] = 1;
		} else {
			scanf("%d", &num);
			opp[i][0] = 2;
			opp[i][1] = num;
		}
	}

	sort(map, map + map_len);
	unique(map, map + map_len);
}

void build(int root, int l, int r) {
	memset(seg_tree[root].sum, 0, sizeof(seg_tree[root].sum));
	seg_tree[root].cnt = 0;
	if (l >= r) {
		return;
	} else {
		int mid = (l + r) / 2;
		build(root << 1, l, mid);
		build(root << 1 | 1, mid + 1, r);
	}
}

void push_down(int root) {
}

void push_up(int root) {
	int l = root << 1;
	int r = root << 1 | 1;
	int l_cnt = seg_tree[l].cnt;
	int r_cnt = seg_tree[r].cnt;
	for (int i = 0; i < MOD; ++i) {
		seg_tree[root].sum[i] = seg_tree[l].sum[i] + seg_tree[r].sum[(i - l_cnt % 5 + 5) % 5];
	}
	seg_tree[root].cnt = l_cnt + r_cnt;
}

void update(int root, int l, int r, int leaf, int type) {
	if (leaf < l || leaf > r) return;

	if (l == leaf && r == leaf) {
		if (type == 0) {
			++seg_tree[root].cnt;
			seg_tree[root].sum[ seg_tree[root].cnt % MOD ] += map[leaf];
		} else {
			seg_tree[root].sum[ seg_tree[root].cnt % MOD ] -= map[leaf];
			--seg_tree[root].cnt;
		}
	} else {
		int mid = (l + r) / 2;
		push_down(root);
		update(root << 1, l, mid, leaf, type);
		update(root << 1 | 1, mid + 1, r, leaf, type);
		push_up(root);
	}
}

void query(int root, int l, int r) {
	printf("%lld\n", seg_tree[root].sum[3]);
}

int main() {
	freopen("data", "r", stdin);

	while (~scanf("%d", &n)) {
		init();
		build(1, 0, map_len - 1);
		for (int i = 0; i < n; ++i) {
			if (opp[i][0] == 0) {
				update(1, 0, map_len - 1, binary_search(map, 0, map_len, opp[i][1]), 0);
			} else if (opp[i][0] == 1) {
				query(1, 0, map_len - 1);
			} else {
				update(1, 0, map_len - 1, binary_search(map, 0, map_len, opp[i][1]), 1);
			}
		}
	}

	return 0;
}
