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

#define INF (0x3f3f3f3f3f3f3f3fLL)
#define NINF ((-1)*INF)

#define N (100000 + 5)

struct Point {
	LL x;
	LL y;
};

Point points[N], p1, p2;

struct Node {
	LL lazy[2];
	LL max_v[2];
	int cnt;
};

Node tree[4 * N];

int n, m, t;
int l, r, id;
LL d;
int opt[N][4];
Point p4[4];
int cnt[N][4];

void push_down(int root) {
	REP(i, 2) {
		tree[root << 1].lazy[i] += tree[root].lazy[i];
		tree[root << 1 | 1].lazy[i] += tree[root].lazy[i];
		tree[root].lazy[i] = 0;
	}
}

void push_up(int root) {
	REP(i, 2) {
		tree[root].max_v[i] = MAX(tree[root << 1].max_v[i] + tree[root << 1].lazy[i], tree[root << 1 | 1].max_v[i] + tree[root << 1 | 1].lazy[i]);
	}
	tree[root].cnt = tree[root << 1].cnt + tree[root << 1 | 1].cnt;
}

void build(int root, int l, int r) {
	if (l > r) return;
	if (l == r) {
		tree[root].max_v[0] = points[l].x;
		tree[root].max_v[1] = points[l].y;
		tree[root].cnt = 1;
		reset(tree[root].lazy, 0);
		return;
	}

	reset(tree[root].lazy, 0);

	int mid = (l + r) / 2;
	build(root << 1, l, mid);
	build(root << 1 | 1, mid + 1, r);

	push_up(root);
}

void update(int root, int l, int r, int ll, int rr, int id, LL d) {
	if (ll > rr || l > r || ll > r || l > rr) {
		return;
	}
	if (l >= ll && r <= rr) {
		tree[root].lazy[id] += d;
		return;
	}

	push_down(root);

	int mid = (l + r) / 2;
	update(root << 1, l, mid, ll, rr, id, d);
	update(root << 1 | 1, mid + 1, r, ll, rr, id, d);

	push_up(root);
}

void del(int root, int l, int r, int ll, int rr, Point& p) {
	if (ll > rr || l > r || ll > r || l > rr) {
		return;
	}
	if ((tree[root].max_v[0] + tree[root].lazy[0] <= p.x) 
		&& (tree[root].max_v[1] + tree[root].lazy[1] <= p.y)) {
		return;
	}
	if (l == r) {
		tree[root].max_v[0] = tree[root].max_v[1] = NINF;
		tree[root].cnt = 0;
		return;
	}

	push_down(root);

	int mid = (l + r) / 2;
	del(root << 1, l, mid, ll, rr, p);
	del(root << 1 | 1, mid + 1, r, ll, rr, p);

	push_up(root);

	return;
}

int query(int root, int l, int r, int ll, int rr) {
	if (ll > rr || l > r || ll > r || l > rr) {
		return 0;
	}
	if (l >= ll && r <= rr) {
		return tree[root].cnt;
	}

	int mid = (l + r) / 2;

	return query(root << 1, l, mid, ll, rr) + query(root << 1 | 1, mid + 1, r, ll, rr);
}

void show(int root, int l, int r) {
	if (l > r) return;
	printf("root = %d, l = %d, r = %d\n", root, l, r);
	if (l == r) {
		REP(i, 2) {
			printf("lazy = %I64d, max_v = %I64d, cnt = %d\t", tree[root].lazy[i], tree[root].max_v[i], tree[root].cnt);
		}
		printf("\n");
		return;
	}
	REP(i, 2) {
		printf("lazy = %I64d, max_v = %I64d, cnt = %d\t", tree[root].lazy[i], tree[root].max_v[i], tree[root].cnt);
	}
	printf("\n");
	int mid = (l + r) / 2;
	show(root << 1, l, mid);
	show(root << 1 | 1, mid + 1, r);
}

void init() {
	scanf("%d", &t);
}

void in() {
	reset(cnt, 0);

	scanf("%d", &n);
	scanf("%I64d%I64d%I64d%I64d", &p1.x, &p1.y, &p2.x, &p2.y);
	for (int i = 1; i <= n; ++i) {
		scanf("%I64d%I64d", &points[i].x, &points[i].y);
	}
	scanf("%d", &m);
	REP(i, m) {
		scanf("%d", &opt[i][0]);
		switch(opt[i][0]) {
		case 1:
			scanf("%d%d%d", &opt[i][1], &opt[i][2], &opt[i][3]);
			break;
		case 2:
			scanf("%d%d%d", &opt[i][1], &opt[i][2], &opt[i][3]);
			break;
		default:
			scanf("%d%d", &opt[i][1], &opt[i][2]);
			break;
		}
	}
}

void run() {
	p4[0].x = p1.x - 1;	p4[0].y = p1.y - 1;
	p4[1].x = p2.x; 	p4[1].y = p1.y - 1;
	p4[2].x = p1.x - 1; p4[2].y = p2.y;
	p4[3].x = p2.x;		p4[3].y = p2.y;

	REP(i, 4) {
		build(1, 1, n);

		REP(j, m) {
			switch(opt[j][0]) {
			case 1:
				update(1, 1, n, opt[j][1], opt[j][2], 0, opt[j][3]);
				break;
			case 2:
				update(1, 1, n, opt[j][1], opt[j][2], 1, opt[j][3]);
				break;		
			default:
				del(1, 1, n, opt[j][1], opt[j][2], p4[i]);
				cnt[j][i] = query(1, 1, n, opt[j][1], opt[j][2]);
				break;	
			}
		}
	}
}

void out() {
	REP(i, m) {
		if (3 == opt[i][0]) {
			printf("%d\n", cnt[i][3] - cnt[i][2] - cnt[i][1] + cnt[i][0]);
		}
	}
}

void out(int cas) {
}

int main() {
	freopen("data", "r", stdin);

	init();
	REP(i, t) {
		in();
		run();
		out();
	}

	return 0;
}
