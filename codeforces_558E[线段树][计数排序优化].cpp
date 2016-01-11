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

#define N (100000 + 5)
#define Q (50000 + 5)

struct Node {
	int lazy;
	int cnt;
};

Node seg[26][4 * N];
char s[N];
int n, q;
int a, b, c, len;
int cnt[26];

void push_down(int id, int root, int l, int r) {
	if (seg[id][root].lazy == -1) {

	} else {
		int mid = (l + r) / 2;
		seg[id][root << 1].lazy = seg[id][root << 1 | 1].lazy = seg[id][root].lazy;
		seg[id][root << 1].cnt = (mid - l + 1) * seg[id][root].lazy;
		seg[id][root << 1 | 1].cnt = (r - mid) * seg[id][root].lazy;
		seg[id][root].lazy = -1;
	}
}

void push_up(int id, int root, int l, int r) {
	if (seg[id][root].lazy == -1) {
		seg[id][root].cnt = seg[id][root << 1].cnt + seg[id][root << 1 | 1].cnt;
	} else {
		seg[id][root].cnt = (r - l + 1) * seg[id][root].lazy;
	}
}

void build(int id, int root, int l, int r) {
	if (l > r) {
		return;
	}
	seg[id][root].lazy = -1;
	seg[id][root].cnt = 0;
	if (l == r) {
		if (s[l] - 'a' == id) {
			seg[id][root].lazy = 1;
			seg[id][root].cnt = 1;
		} else {
			seg[id][root].lazy = 0;
			seg[id][root].cnt = 0;
		}
		return;
	}

	int mid = (l + r) / 2;
	build(id, root << 1, l, mid);
	build(id, root << 1 | 1, mid + 1, r);

	push_up(id, root, l, r);
}

void update(int id, int root, int l, int r, int ll, int rr, int val) {
	if (l > r || ll > rr || l > rr || ll > r) {
		return;
	}
	if (l >= ll && r <= rr) {
		seg[id][root].lazy = val;
		seg[id][root].cnt = (r - l + 1) * val;
		return;
	}

	push_down(id, root, l, r);

	int mid = (l + r) / 2;
	update(id, root << 1, l, mid, ll, rr, val);
	update(id, root << 1 | 1, mid + 1, r, ll, rr, val);

	push_up(id, root, l, r);
}

int query(int id, int root, int l, int r, int ll, int rr) {
	if (l > r || ll > rr || l > rr || ll > r) {
		return 0;
	}
	if (l >= ll && r <= rr) {
		return seg[id][root].cnt;
	}

	push_down(id, root, l, r);

	int mid = (l + r) / 2;
	return query(id, root << 1, l, mid, ll, rr) + query(id, root << 1 | 1, mid + 1, r, ll, rr);
}

void show(int id, int root, int l, int r) {
	if (l > r) {
		return;
	}
	if (l == r) {
		printf("id = %d, root = %d, l = %d, r = %d, lazy = %d, cnt = %d\n", id, root, l, r, seg[id][root].lazy, seg[id][root].cnt);
		return;
	}
	printf("id = %d, root = %d, l = %d, r = %d, lazy = %d, cnt = %d\n", id, root, l, r, seg[id][root].lazy, seg[id][root].cnt);
	int mid = (l + r) / 2;
	show(id, root << 1, l, mid);
	show(id, root << 1 | 1, mid + 1, r);
}

void init() {
}

void in() {
	scanf("%s", &s[1]);

	len = strlen(&s[1]);
}

void run() {
	REP(i, 26) {
		build(i, 1, 1, len);
	}

	REP(i, q) {
		scanf("%d%d%d", &a, &b, &c);
		reset(cnt, 0);
		//printf("a = %d, b = %d\n", a, b);
		REP(j, 26) {
			cnt[j] = query(j, 1, 1, len, a, b);
			//printf("%d ", cnt[j]);
		}
		//printf("\n");
		if (1 == c) {
			int index = a;
			REP(j, 26) {
				update(j, 1, 1, len, a, b, 0);
				update(j, 1, 1, len, index, index + cnt[j] - 1, 1);
				index += cnt[j];
			}
		} else {
			int index = a;
			REPD(j, 26) {
				update(j, 1, 1, len, a, b, 0);
				update(j, 1, 1, len, index, index + cnt[j] - 1, 1);
				index += cnt[j];
			}
		}
	}

	/*
	REP(i, 26) {
		show(i, 1, 1, len);
		printf("\n\n");
	}
	*/
}

void out() {
	FOR(i, 1, len) {
		REP(j, 26) {
			if (query(j, 1, 1, len, i, i)) {
				printf("%c", 'a' + j);
				break;
			}
		}
	}
	printf("\n");
}

void out(int cas) {
}

int main() {
	//freopen("data", "r", stdin);

	init();
	while (~scanf("%d%d", &n, &q)) {
		in();
		run();
		out();
	}

	return 0;
}
