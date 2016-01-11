/*************************************************************************
    > Author: HouJP
    > Mail: houjp1992@gmail.com
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <map>

using namespace std;

#define LL long long

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x)	x.begin(), x.end()
#define rall(x)	x.rbegin(), x.rend()
#define sz(a)	int(a.size())
#define reset(a, x)	memset(a, x, sizeof(a))

#define MAX(a,b)		((a) > (b) ? (a) : (b))
#define MIN(a,b)		((a) > (b) ? (b) : (a))
#define ABS(a)			((a) > 0 ? (a) : (-(a)))
#define FOR(i, a, b)	for(int i = a; i <= b; ++i)
#define FORD(i, a, b)	for(int i = a; i >= b; --i)
#define REP(i, n)		for(int i = 0, _n = n; i < _n; ++i)
#define REPD(i, n)		for(int i = n - 1; i >= 0; --i)
#define FORSZ(i, x)		for(int i = 0; i < sz(x); ++i)

#define INF (0x3f3f3f3f)
#define NINF ((-1)*INF)
#define INFLL (0x3f3f3f3f3f3f3f3fLL)
#define NINFLL ((-1)*INFLL)

#define H (50 + 5)
#define N (100000 + 5)

int ii, ans, h, q;
LL l, r;
int cnt[2];
LL seg, seg_from, anss;
int level[2];

struct Node {
	LL  x;
	bool left;
	bool has;
	Node() {}
	Node(LL _x, bool _left, bool _has) : x(_x), left(_left), has(_has) {}
};

Node nodes[N * 2];
int cnt_nodes;

bool cmp(Node a, Node b) {
	return a.x < b.x;
}

void init() {
}

void in() {
	cnt_nodes = 0;
	seg_from = -1;
	seg = 0;
	reset(cnt, 0);
	reset(level, 0);

	REP(i, q) {
		scanf("%d%I64d%I64d%d", &ii, &l, &r, &ans);
		FOR(j, ii + 1, h) {
			l = 2 * l;
			r = 2 * r + 1;
		}
		nodes[cnt_nodes++] = Node(l, true, ans);
		nodes[cnt_nodes++] = Node(r + 1, false, ans);
		if (ans) {
			++cnt[1];
		} else {
			++cnt[0];
		}
	}

	l = 1; r = 1; ii = 1;
	FOR(j, ii + 1, h) {
		l = 2 * l;
		r = 2 * r + 1;
	}
	nodes[cnt_nodes++] = Node(l, true, true);
	nodes[cnt_nodes++] = Node(r + 1, false, true);
	++cnt[1];
}

void run() {
	sort(nodes, nodes + cnt_nodes, cmp);
	REP(i, cnt_nodes) {
		if (nodes[i].left) {
			++level[nodes[i].has];
			if ((level[1] == cnt[1]) && (level[0] == 0)) {
				seg_from = nodes[i].x;
			}
		} else {
			--level[nodes[i].has];
		}
		if ((level[1] == cnt[1]) && (level[0] == 0)) {
			seg_from = nodes[i].x;
		} else {
			if (-1 != seg_from) {
				seg += nodes[i].x - seg_from;
				if (nodes[i].x - seg_from > 0) { // !important
					anss = nodes[i].x - 1; 
				}
			}
			seg_from = -1;
		}
		//printf("i = %d, nodes[i].x = %I64d, nodes[i].left = %d, nodes[i].has = %d\n", i, nodes[i].x, nodes[i].left, nodes[i].has);
		//printf("seg = %I64d, seg_from = %I64d\n", seg, seg_from);
		//printf("level[0] = %d, level[1] = %d\n", level[0], level[1]);
	}
}

void out() {
	if (1 == seg) {
		printf("%I64d\n", anss);
	} else if (0 == seg) {
		printf("Game cheated!\n");
	} else {
		printf("Data not sufficient!\n");
	}
}

void out(int cas) {
}

int main() {
	//freopen("data", "r", stdin);

	init();
	while (~scanf("%d%d", &h, &q)) {
		in();
		run();
		out();
	}

	return 0;
}
