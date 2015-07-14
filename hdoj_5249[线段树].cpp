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

#define MAXN (10000 + 5)

struct Node {
	int cnt;
	int val;
} st[4 * MAXN];

int t;
int n, x;
char s[10];
int num[MAXN];
int srt[MAXN];
map<int, int> id;
int cnt_id;

void build(int root, int l, int r) {
	if (l > r) return;
	st[root].cnt = 0;
	if (l == r) {
		st[root].val = srt[l];
		//printf("build root = %d, l = %d, st[%d].val = %d\n", root, l, root, st[root].val);
		return;
	}
	int mid = (l + r) / 2;
	build(root << 1, l, mid);
	build(root << 1 | 1, mid + 1, r);
}

void push_up(int root) {
	st[root].cnt = st[root << 1].cnt + st[root << 1 | 1].cnt;
	//printf("push_up st[%d].cnt = %d\n", root, st[root].cnt);
}

void push_down(int root) {
}

void update(int root, int l, int r, int id, int val) {
	if (id > r || id < l || l > r) return;
	if (l != r) {
		int mid = (l + r) / 2;
		update(root << 1, l, mid, id, val);
		update(root << 1 | 1, mid + 1, r, id, val);
		push_up(root);
	} else {
		st[root].cnt += val;
		//printf("update st[%d].cnt = %d\n", root, st[root].cnt);
	}
}

int query(int root, int l, int r, int cnt) {
	//printf("query root = %d, l = %d, r = %d, cnt = %d\n", root, l, r, cnt);
	if (l != r) {
		int mid = (l + r) / 2;
		//printf("query st[root << 1].cnt = %d, st[root << 1 | 1].cnt = %d\n", st[root << 1].cnt, st[root << 1 | 1].cnt);
		//printf("query st[root << 1].cnt = %d, cnt = %d\n", st[root << 1].cnt, cnt);
		if (st[root << 1].cnt < cnt) {
			//printf("query into r\n");
			return query(root << 1 | 1, mid + 1, r, cnt - st[root << 1].cnt);
		} else {
			//printf("query into l\n");
			return query(root << 1, l, mid, cnt);
		}
	} else {
		return st[root].val;
	}
}

void init() {
	t = 0;
}

void in() {
	cnt_id = 0;
	id.clear();
	for (int i = 0; i < n; ++i) {
		scanf("%s", s);
		if (0 == strcmp(s, "in")) {
			scanf("%d", &x);
			srt[cnt_id] = x;
            ++cnt_id;
			//id[x] = cnt_id++;
			num[i] = x;
		} else if (0 == strcmp(s, "out")) {
			num[i] = -1;
		} else {
			num[i] = -2;
		}
	}
	//printf("cnt_id = %d\n", cnt_id);
	sort(srt, srt + cnt_id);
    for (int i = 0; i < cnt_id; ++i) {
        id[srt[i]] = i;
    }
}

void run() {
	queue<int> que;

	build(1, 0, cnt_id - 1);

	for (int i = 0; i < n; ++i) {
        //printf("%d\n", num[i]);
		if (num[i] >= 0) {
			//printf("num[%d] = %d, id[num[%d]] = %d\n", i, num[i], i, id[num[i]]);
			update(1, 0, cnt_id - 1, id[num[i]], 1);
			que.push(num[i]);
		} else if (num[i] == -1) {
			int tmp = que.front(); que.pop();
			update(1, 0, cnt_id - 1, id[tmp], -1);
		} else {
			printf("%d\n", query(1, 0, cnt_id - 1, que.size() / 2 + 1));
		}
	}
}

void out() {
}

void out(int cas) {
}

int main() {
	freopen("data", "r", stdin);

	init();
	while (~scanf("%d", &n)) {
		++t;
		printf("Case #%d:\n", t);
		in();
		run();
		out();
	}

	return 0;
}
