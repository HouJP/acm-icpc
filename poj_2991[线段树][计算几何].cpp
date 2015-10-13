/*************************************************************************
    > Author: HouJP
    > Mail: houjp1992@gmail.com
 ************************************************************************/

/**
 * 对于线段树和树状数组的思考：
 *
 *	树状数组可以进行区间更新，但是更新完毕之后，我们只能知道单点的额状态，对于某个区间的状态是没有办法知道的。
 *	以上树状数组无法完成的事情可以通过线段树来实现。
 */

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

#define MAXN (10000)

struct Seg {
	//int lazy;
	int v; // lazy标记，记录转过的角度
	double x;
	double y;
	Seg(): v(0), x(0), y(0) {}
	Seg(int _v, double _x, double _y): v(_v), x(_x), y(_y) {}
};

Seg seg[4 * MAXN + 5];
int len[MAXN + 5];
int n, c;
int a, b;
int cas;

void rotate(int id, int v) {
	double x, y;
	double pv = v * acos(-1.0) / 180.0;
	x = seg[id].x * cos(pv) - seg[id].y * sin(pv);
	y = seg[id].x * sin(pv) + seg[id].y * cos(pv);

	seg[id].x = x;
	seg[id].y = y;
}

void push_down(int root) {
	seg[root << 1].v += seg[root].v;
	seg[root << 1 | 1].v += seg[root].v;

	rotate(root << 1, seg[root].v);
	rotate(root << 1 | 1, seg[root].v);

	seg[root].v = 0;
}

void push_up(int root) {
	int lr = root << 1;
	int rr = root << 1 | 1;
	seg[root].x = seg[lr].x + seg[rr].x;
	seg[root].y = seg[lr].y + seg[rr].y;
}

void build(int root, int l, int r) {
	if (l > r) return;

	seg[root].v = 0;

	if (l == r) {
		seg[root].v = 180;
		seg[root].x = 0;
		seg[root].y = len[l];
		return;
	}

	int mid = (l + r) / 2;
	push_down(root);
	build(root << 1, l, mid);
	build(root << 1 | 1, mid + 1, r);
	push_up(root);
}

void update(int root, int l, int r, int ll, int rr, int v) {
	if (l > r || ll > rr || l > rr || ll > r) {
		return;
	}

	if (ll <= l && rr >= r) {
		seg[root].v += v;
		rotate(root, v);
		return;
	}

	int mid = (l + r) / 2;
	push_down(root);
	update(root << 1, l, mid, ll, rr, v);
	update(root << 1 | 1, mid + 1, r, ll, rr, v);
	push_up(root);
}

int query(int root, int l, int r, int id) {
	if (id < l || id > r || l > r) {
		return 0;
	}

	if (l == r) {
		if (l == id) {
			return seg[root].v;
		} else {
			return 0;
		}
	}

	int mid = (l + r) / 2;
	push_down(root);
	return query(root << 1, l, mid, id) + query(root << 1 | 1, mid + 1, r, id);
}

void init() {
	cas = 0;
}

void in() {
	++cas;
	if (1 != cas) {
		printf("\n");
	}

	for (int i = 1; i <= n; ++i) {
		scanf("%d", &len[i]);
	}

	build(1, 1, n);
	//printf("init: (%f, %f)\n", seg[1].x, seg[1].y);

	for (int i = 0; i < c; ++i) {
		scanf("%d%d", &a, &b);
		int v1 = query(1, 1, n, a);
		int v2 = query(1, 1, n, a + 1);
		int bv = ((v2 - v1 + 180) % 360 + 360) % 360;
		//printf("need rotate %d\n", b - bv);
		update(1, 1, n, a + 1, n, b - bv);
		printf("%.2f %.2f\n", seg[1].x, seg[1].y);
	}
}

void run() {
}

void out() {
}

void out(int cas) {
}

int main() {
	freopen("data", "r", stdin);

	init();
	while (~scanf("%d%d", &n, &c)) {
		in();
		run();
		out();
	}

	return 0;
}
