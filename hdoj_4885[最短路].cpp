/*************************************************************************
    > File Name: hdoj_4885.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 四  4/ 9 11:42:35 2015
 ************************************************************************/

/* 
 * 思路
 *
 * 这道题没有复杂的知识点，只要能转到求最短路上就可以了，bfs。
 * 有个坑是不能在三点共线的时候越过中间的点到达后边的点。怎么处理呢？先按距离排序，然后计算斜率，如果斜率发生重复，则舍弃。
 *
 * 如果判断一个数字是否存在，可以使用set，set用红黑树实现，复杂度log(n).
 *
 * */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <set>

using namespace std;

#define LL long long
#define ABS(a) ((a) < 0 ? (-(a)) : (a))
#define N (1000)

struct BNode {
	int id;
	int dep;

	BNode(int _id = 0, int _dep = 0) : id(_id), dep(_dep) {}
} b_que[N + 5];
int b_que_beg, b_que_end;

struct Pos{
	int x;
	int y;
} pos[N + 5], des;
int des_id;

struct Dis {
	int id;
	LL dis;
} dis[N + 5];
int dis_index;

struct Edge {
	int v;
	int next;
} e[500 * N + 5];
int e_head[N + 5];
int e_index;

int t, n, l, tot_n, tmp;
bool vis[N + 5];
LL lon_l;

set<LL> slope;

LL get_gcd(LL a, LL b) {
	if (0 > b) {
		b = -b;
	}
	if (0 > a) {
		a = -a;
	}
	if (0 == b) {
		return a;
	}
	if (0 == a) {
		return b;
	}
	int c = a % b;
	while (c) {
		a = b;
		b = c;
		c = a % b;
	}
	return b;
}

bool cmp(Dis a, Dis b) {
	return a.dis < b.dis;
}

void add_edge(Edge e[], int e_head[], int u, int v, int & e_index) {
	e[e_index].v = v; e[e_index].next = e_head[u]; e_head[u] = e_index++;
	e[e_index].v = u; e[e_index].next = e_head[v]; e_head[v] = e_index++;
}

void in() {
	scanf("%d%d", &n, &l);
	scanf("%d%d", &pos[0].x, &pos[0].y);
	scanf("%d%d", &pos[1].x, &pos[1].y);
	des.x = pos[1].x; des.y = pos[1].y;
	tmp = n + 2;
	for (int i = 2; i < tmp; ++i) {
		scanf("%d%d", &pos[i].x, &pos[i].y);
	}

	e_index = 0;
	memset(e_head, -1, sizeof(e_head));

	b_que_beg = b_que_end = 0;
	memset(vis, 0, sizeof(vis));

	lon_l = (LL)l * (LL)l;
}

void run() {
	tmp = n + 1;
	for (int i = 0; i < tmp; ++i) {
		dis_index = 0;
		for (int j = i + 1; j <= tmp; ++j) {
			LL lon = (pos[i].x - pos[j].x) * (pos[i].x - pos[j].x) + (pos[i].y - pos[j].y) * (pos[i].y - pos[j].y);
			if (lon <= lon_l) {
				dis[dis_index].id = j;
				dis[dis_index++].dis = lon;
			}
		}
		//printf("dis_index = %d\n", dis_index);

		sort(dis, dis + dis_index, cmp);
		slope.clear();
		for (int j = 0; j < dis_index; ++j) {
			LL dx = pos[dis[j].id].x - pos[i].x;
			LL dy = pos[dis[j].id].y - pos[i].x;
			LL gcd = get_gcd(dx, dy);
			dx /= gcd;
			dy /= gcd;
			// dx在后边是有原因的，因为dx一定为正数
			LL slp = dy * 10000000 + dx;
			if (slope.find(slp) == slope.end()) {
				add_edge(e, e_head, i, dis[j].id, e_index);
				slope.insert(slp);
			} 
		}
	}
	//printf("e_index = %d\n", e_index);

	b_que[b_que_end++] = BNode(0, 0);
	vis[0] = true;
	while (b_que_end != b_que_beg) {
		BNode now = b_que[b_que_beg];
		//printf("%d : %d\n", now.dep, now.id);
		if (now.id == 1) {
			break;
		} else {
			++b_que_beg;
		}
		for (int k = e_head[now.id]; -1 != k; k = e[k].next) {
			if (vis[e[k].v]) {
				continue;
			} else {
				b_que[b_que_end++] = BNode(e[k].v, now.dep + 1);
				vis[e[k].v] = true;
			}
		}
	}
}

void out() {
	if (b_que_end == b_que_beg) {
		printf("impossible\n");
	} else {
		printf("%d\n", b_que[b_que_beg].dep - 1);
	}
}

int main() {
	freopen("data", "r", stdin);

	scanf("%d", &t);
	while (t--) {
		in();
		run();
		out();
	}

	return 0;
}
