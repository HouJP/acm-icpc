/*************************************************************************
    > File Name: hdoj_1542.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 六 10/18 11:15:46 2014
 ************************************************************************/

/* *
 *
 * 思路
 *
 * 扫描线求解矩形面积并，用到了线段树+离散化
 * 1. 数据范围很大，所以需要离散化
 * 2. 扫描线：模拟一条与Y轴平行的直线从左向右扫描，每次碰到矩形的左边或者右边，计算增加的面积。
 *
 * */

#include <cstdio>
#include <algorithm>

#define N (100)

void print(int);

struct PointDD {
	double x;
	double y;
};

struct PointDI {
	double x;
	int y;
};

struct Rec {
	PointDD lb;
	PointDD rt;
};

struct Seg {
	int y1, y2;
	double x;
	bool cover;
};

struct SegTree {
	double x;	// 上一条扫描线的位置
	int cover;	// 该子树下所有叶子节点的统一增量
};

int n;
Rec rec[N + 5];
Seg seg[2 * N + 5];
double map[2 * N + 5];
int map_len;
SegTree seg_tree[8 * N + 5];
double ans;
int cas;

int binary_search(int low, int high, double value) {
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (map[mid] == value) {
			return mid;
		}
		if (map[mid] > value) {
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	return -1;
}

bool compare(Seg a, Seg b) {
	return a.x < b.x;
}

void init() {
	int y1, y2;
	
	++cas;
	map_len = 0;
	ans = 0;
	for (int i = 0; i < n; ++i) {
		scanf("%lf%lf%lf%lf", &rec[i].lb.x, &rec[i].lb.y, &rec[i].rt.x, &rec[i].rt.y);
		map[map_len++] = rec[i].lb.y;
		map[map_len++] = rec[i].rt.y;
	}

	std::sort(map, map + map_len);
	map_len = std::unique(map, map + map_len) - map;
	
	for (int i = 0; i < n; ++i) {
		y1 = binary_search(0, map_len - 1, rec[i].lb.y);
		y2 = binary_search(0, map_len - 1, rec[i].rt.y);
		seg[2 * i].x = rec[i].lb.x;
		seg[2 * i].y1 = y1;
		seg[2 * i].y2 = y2;
		seg[2 * i].cover = true;
		seg[2 * i + 1].x = rec[i].rt.x;
		seg[2 * i + 1].y1 = y1;
		seg[2 * i + 1].y2 = y2;
		seg[2 * i + 1].cover = false;
	}
	std::sort(seg, seg + 2 * n, compare);
	//print(1);
}

void print(int id) {
	if (id == 0) {
		for (int i = 0; i < map_len; ++i) {
			printf("%lf\t", map[i]);
		}
		printf("\n");
	}
	if (id == 1) {
		for (int i = 0; i < 2 * n; ++i) {
			printf("%.2lf\t%d(%.2lf)\t%d(%.2lf)\t%d\n", seg[i].x, seg[i].y1, map[seg[i].y1], seg[i].y2, map[seg[i].y2], seg[i].cover);
		}
	}
}

void build(int root, int l, int r) {
	if (r - l <= 1) {
		seg_tree[root].x = 0;
		seg_tree[root].cover = 0;
		return;
	} else {
		int mid = (l + r) / 2;
		build(root << 1, l, mid);
		build(root << 1 | 1, mid, r);
	}
}

void insert(int root, int l, int r, int y1, int y2, double x, bool cover) {
	if (l >= y2 || r <= y1) {
		return;
	}

	if (r - l <= 1) {
		if (seg_tree[root].cover) {
			ans += (map[r] - map[l]) * (x - seg_tree[root].x);
		}
		seg_tree[root].x = x;
		seg_tree[root].cover += cover ? 1 : -1;
	} else {
		int mid = (l + r) / 2;
		insert(root << 1, l, mid, y1, y2, x, cover);
		insert(root << 1 | 1, mid, r, y1, y2, x, cover);
	}
}

void print() {
	printf("Test case #%d\n", cas);
	printf("Total explored area: %.2lf\n\n", ans); 
}

int main() {
	freopen("data", "r", stdin);

	cas = 0;

	while (~scanf("%d", &n) && n) {
		init();
		build(1, 0, map_len - 1);
		for (int i = 0; i < 2 * n; ++i) {
			insert(1, 0, map_len - 1, seg[i].y1, seg[i].y2, seg[i].x, seg[i].cover);
		}
		print();
	}

	return 0;
}


