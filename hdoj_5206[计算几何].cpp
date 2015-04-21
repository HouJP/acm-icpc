/*************************************************************************
    > File Name: demo.cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 二  4/14 23:36:55 2015
 ************************************************************************/

/* 
 * 思路
 *
 * 这道题判断三维空间的正方形，而比赛的时候。。。我判断成了。。。。矩形。。。
 *
 * */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define LL long long
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) > (b) ? (b) : (a))
#define ABS(a) ((a) > 0 ? (a) : (-(a)))

struct Node {
	LL x;
	LL y;
	LL z;
}a, b, c, d;

LL t;

bool judge(Node a, Node b, Node c) {
	LL ea = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
	LL eb = (a.x - c.x) * (a.x - c.x) + (a.y - c.y) * (a.y - c.y) + (a.z - c.z) * (a.z - c.z);
	LL ec = (b.x - c.x) * (b.x - c.x) + (b.y - c.y) * (b.y - c.y) + (b.z - c.z) * (b.z - c.z);
	if (ea > eb) {
		swap(ea, eb);
	}
	if (eb > ec) {
		swap(eb, ec);
	}
	if ((ea + eb == ec) || (ea + ec == eb) || (eb + ec == ea)) {
		if (ea == eb) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool judge2(Node a, Node b, Node c, Node d) {
	LL left = (d.x - a.x) * (b.y - a.y) * (c.z - a.z) + (b.x - a.x) * (c.y - a.y) * (d.z - a.z) + (c.x - a.x) * (d.y - a.y) * (b.z - a.z);
	LL right = (d.z - a.z) * (b.y - a.y) * (c.x - a.x) + (d.y - a.y) * (b.x - a.x) * (c.z - a.z) + (d.x - a.x) * (b.z - a.z) * (c.y - a.y);
	if (left == right) {
		return true;
	} else {
		return false;
	}
}

void in() {
}

void run() {
}

void out() {
}

void out(int cas) {
}

int main() {
	freopen("data", "r", stdin);

	scanf("%I64d", &t);
	for (int i = 0; i < t; ++i) {
		scanf("%I64d%I64d%I64d%I64d%I64d%I64d%I64d%I64d%I64d%I64d%I64d%I64d", &a.x, &a.y, &a.z, &b.x, &b.y, &b.z, &c.x, &c.y, &c.z, &d.x, &d.y, &d.z);
		if (judge(a, b, c) && (judge(a, b, d)) && judge(a, c, d) && judge(b, c, d) && judge2(a, b, c, d)) {
			printf("Case #%d: Yes\n", i + 1);
		} else {
			printf("Case #%d: No\n", i + 1);
		}
	}

	return 0;
}
