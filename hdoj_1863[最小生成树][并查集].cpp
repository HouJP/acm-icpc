/*************************************************************************
    > File Name: hdoj_1863.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 二  4/ 7 10:10:54 2015
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define N (100)
#define M (100)

struct Edge {
	int a;
	int b;
	int value;
} e[N + 5];

int n, m;
int a, b, c;
int ans;
bool can;

// 并查集
// 时间复杂度 O(m * α(n)) α是 Ackerman 函数的某个反函数，在极大的范围内（比可观察到的宇宙中估计的原子数量 1080 还大很多）都可以认为是不大于 4 的。

int uset[M + 5]; // 记录对应根节点
int urank[M + 5];

// 初始化，节点编号从0开始
// 参数：并查集节点个数
void make_set(int size) {
	for (int i = 0; i < size; ++i) {
		uset[i] = i;
		urank[i] = 0;
	}
}

// 查找
int find(int x) {
	if (uset[x] != x) {
		uset[x] = find(uset[x]);
	}
	return uset[x];
}

// 合并
void union_set(int x, int y) {
	if ((x = find(x)) == (y = find(y))) return;
	if (urank[x] > urank[y]) uset[y] = x;
	else {
		uset[x] = y;
		if (urank[x] == urank[y]) ++urank[y];
	}
}

bool cmp(Edge a, Edge b) {
	return a.value < b.value;
}

int main() {
	freopen("data", "r", stdin);
	
	while (~scanf("%d", &n) && n) {
		// in
		scanf("%d", &m);
		for (int i = 0; i < n; ++i) {
			scanf("%d%d%d", &e[i].a, &e[i].b, &e[i].value);
			--e[i].a;
			--e[i].b;
		}
		ans = 0;
		can = true;
		make_set(m);
		// run
		sort(e, e + n, cmp);
		for (int i = 0; i < n; ++i) {
			if (find(e[i].a) == find(e[i].b)) continue;
			union_set(e[i].a, e[i].b);
			ans += e[i].value;
		}
		for (int i = 1; i < m; ++i) {
			if (find(i) != find(i - 1)) {
				can = false;
				break;
			}
		}
		// out
		if (can) {
			printf("%d\n", ans);
		} else {
			printf("?\n");
		}
	}

	return 0;
}
	
