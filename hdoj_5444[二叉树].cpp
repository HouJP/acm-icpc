/*************************************************************************
    > Author: HouJP
    > Mail: houjp1992@gmail.com
 ************************************************************************/

/**
 *	如何根据先序和中序确定二叉树：
 *	中序决定了后出现的元素A一定是之前出现元素B的右孩子或者根，先序消除了这种不确定性，如果在先序中A排在B之前，那么A是根，否则是B是根，而A只能是右孩子。
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
#include <stack>

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

#define N (1010)

struct Node {
	int p;
	int l;
	int r;
	int v;
	Node() {}
	Node (int _p, int _l, int _r, int _v): p(_p), l(_l), r(_r), v(_v) {}
} tree[N];

int m[N];
int cnt;

int t, n, v;
int q, num;
int father[N];
char path[N];

void init() {
	scanf("%d", &t);
}

void in() {
	scanf("%d", &n);
	stack<int> sta;
	cnt = 0;

	REP(i, n) {
		scanf("%d", &v);
		//printf("v = %d\n", v);
		if (0 == i) {
			tree[cnt] = Node(-1, -1, -1, v);
			m[v] = cnt++;
		} else {
			if (v < sta.top()) {
				tree[cnt] = Node(m[sta.top()], -1, -1, v);
				tree[m[sta.top()]].l = cnt;
				m[v] = cnt++;
			} else {
				int f = sta.top(); sta.pop();
				//printf("v = %d\n", v);
				while (sta.size() > 0 && sta.top() < v) {
					f = sta.top();
					sta.pop();
				}
				//printf("f = %d\n", f);
				tree[cnt] = Node(m[f], -1, -1, v);
				tree[m[f]].r = cnt;
				m[v] = cnt++;
			}
		}
		sta.push(v);
	}
	scanf("%d", &q);
}

void run() {
	FOR(i, 1, n) {
		//printf("v = %d: id = %d, p = %d, l = %d, r = %d, v = %d\n", i, m[i], tree[m[i]].p, tree[m[i]].l, tree[m[i]].r, tree[m[i]].v);
	}
	REP(i, q) {
		scanf("%d", &num);
		int tmp = m[num];
		int tmp_cnt = 0;
		while (tree[tmp].p != -1) {
			//printf("num = %d, tmp = %d\n", num, tmp);
			if (tree[tree[tmp].p].l == tmp) {
				path[tmp_cnt++] = 'E';
			} else {
				path[tmp_cnt++] = 'W';
			}
			tmp = tree[tmp].p;
		}
		FORD(j, tmp_cnt - 1, 0) {
			printf("%c", path[j]);
		}
		printf("\n");
	}
}

void out() {
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
