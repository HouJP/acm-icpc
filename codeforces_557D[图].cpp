/*************************************************************************
    > Author: HouJP
    > Mail: houjp1992@gmail.com
 ************************************************************************/

/* 
	判断入度情况
 	1. 均为0
 	2. 最多为1
 	3. 存在大于1的，dfs，判断是否存在奇数环
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

#define N (200000 + 5)

struct Edge {
	int t;
	int w;
	int n;
};

int cnt_edge;
int head[N];
int dgr[N];
int max_dgr;
int cnt[3];
int flag[N];
Edge edge[2 * N];

int n, m;
int a, b;
LL anst, answ;

inline void add_edge(int a, int b) {
	edge[cnt_edge].t = b;
	edge[cnt_edge].w = 0;
	edge[cnt_edge].n = head[a];
	head[a] = cnt_edge++;
}

bool dfs(int id, int pre_id, int pre_flag) {
	//printf("id = %d, pre_id = %d, pre_flag = %d\n", id, pre_id, pre_flag);
	if (0 != flag[id]) {
		//printf("into 0 == flag[id]\n");
		if (0 == pre_flag) {
			return true;
		} else {
			if (flag[id] == pre_flag) {
				return false;
			} else {
				return true;
			}
		}
	} else {
		if (0 == pre_flag) {
			flag[id] = 1;
		} else {
			flag[id] = -1 * pre_flag;
		}
		++cnt[flag[id] + 1];
		int tmp = head[id];
		while (-1 != tmp) {
			if (edge[tmp].t != pre_id) {
				if (!dfs(edge[tmp].t, id, flag[id])) {
					return false;
				}
			}
			tmp = edge[tmp].n;
		}
	}
	return true;
}

void init() {
}

void in() {
	memset(head, -1, sizeof(head));
	memset(cnt, 0, sizeof(cnt));
	memset(dgr, 0, sizeof(dgr));
	memset(flag, 0, sizeof(flag));
	anst = answ = 0;
	max_dgr = 0;
	cnt_edge = 0;

	for (int i = 0; i < m; ++i) {
		scanf("%d%d", &a, &b);
		--a, --b;
		add_edge(a, b);
		add_edge(b, a);
		++dgr[a];
		++dgr[b];
	}

	for (int i = 0; i < n; ++i) {
		max_dgr = MAX(max_dgr, dgr[i]);
	}
}

void run() {
	if (0 == max_dgr) {
		anst = 3;
		answ = 1;
		answ = answ * n * (n - 1) * (n - 2) / (2 * 3);
	} else if (1 == max_dgr) {
		anst = 2;
		answ = 1;
		answ = answ * m * (n - 2);
	} else {
		anst = 1;
		answ = 0;
		for (int i = 0; i < n; ++i) {
			memset(cnt, 0, sizeof(cnt));
			if (dfs(i, -1, 0)) {
				//printf("%d, %d\n", cnt[0], cnt[2]);
				answ += (LL)cnt[0] * (LL)(cnt[0] - 1) / 2;
				answ += (LL)cnt[2] * (LL)(cnt[2] - 1) / 2;
			} else {
				anst = 0;
				answ = 1;
				break;
			}
		}
	}
}

void out() {
	printf("%I64d %I64d\n", anst, answ);
}

void out(int cas) {
}

int main() {
	//freopen("data", "r", stdin);

	init();
	while (~scanf("%d%d", &n, &m)) {
		in();
		run();
		out();
	}

	return 0;
}
