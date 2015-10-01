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
#include <iostream>

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

// 线性筛求解积性函数（莫比乌斯函数）
#define MAXN (100000)
bool check[MAXN + 5];
int prime[MAXN + 5];
int mu[MAXN + 5];
int cnt[MAXN + 5];
int ans[MAXN + 5];
int tot;

int n, cas;	
int a, b;
int value[MAXN + 5];
bool visit[MAXN + 5];

int yinzi[MAXN + 5][10];
int cntyz[MAXN + 5];

int zuhe[MAXN + 5][70];
int cntzh[MAXN + 5];

struct Edge {
	int t;
	int nxt;
};

Edge e[2 * MAXN + 5];
int head[MAXN + 5], cnte;

inline void add_edge(int f, int t) {
	e[cnte].t = t;
	e[cnte].nxt = head[f];
	head[f] = cnte++;
}

void dfs(int root) {
	//printf("dfs: root = %d\n", root);

	int rec[70];
	REP(i, cntzh[value[root]]) {
		rec[i] = cnt[zuhe[value[root]][i]];
		//printf("i = %d, zuhe = %d, cnt = %d\n", i, zuhe[value[root]][i], cnt[zuhe[value[root]][i]]);
	}
	rec[cntzh[value[root]]] = cnt[1];
	//printf("i = %d, zuhe = %d, cnt = %d\n", cntzh[value[root]], 1, cnt[1]);

	visit[root] = true;
	int nxt = head[root];
	while (-1 != nxt) {
		if (false == visit[e[nxt].t])
			dfs(e[nxt].t);
		nxt = e[nxt].nxt;
	}

	int ret;
	cnt[1]++;
	ret = cnt[1] - rec[cntzh[value[root]]];
	REP(i, cntzh[value[root]]) {
		++cnt[zuhe[value[root]][i]];
		ret += (cnt[zuhe[value[root]][i]] - rec[i]) * mu[zuhe[value[root]][i]];
	}
	ans[root] = ret;
	//printf("root = %d, ret = %d\n", root, ret);
}

void Moblus() {
	memset(check, false, sizeof(check));
	mu[1] = 1;
	tot = 0;
	for (int i = 2; i <= MAXN; ++i) {
		if (!check[i]) {
			prime[tot++] = i;
			mu[i] = -1;
		}
		for (int j = 0; j < tot; ++j) {
			if (i * prime[j] > MAXN) break;
			check[i * prime[j]] = true;
			if (i % prime[j] == 0) {
				mu[i * prime[j]] = 0;
				break;
			} else {
				mu[i * prime[j]] = -mu[i];
			}
		}
	}
}

void init() {
	cas = 0;
	Moblus();

	reset(cntyz, 0);
	REP(i, tot) {
		for (int j = prime[i]; j <= MAXN; j += prime[i]) {
			yinzi[j][cntyz[j]++] = prime[i];
		}
	}

	reset(cntzh, 0);
	FOR(i, 2, MAXN) {
		FOR(j, 1, (1 << cntyz[i]) - 1) {
			int ret = 1;
			REP(k, cntyz[i]) {
				if ((j >> k) & 0x01) {
					ret *= yinzi[i][k];
				}
			}
			zuhe[i][cntzh[i]++] = ret;
		}
	}
	// REP(i, 10) {
	// 	cout << "i = " << i << endl;
	// 	REP(j, cntyz[i]) {
	// 		cout << yinzi[i][j] << ", ";
	// 	}
	// 	cout << endl;
	// 	REP(j, cntzh[i]) {
	// 		cout << zuhe[i][j] << ", ";
	// 	}
	// 	cout << endl;
	// }

}

void in() {
	reset(cnt, 0);
	reset(visit, 0);

	reset(head, -1);
	cnte = 0;

	REP(i, n - 1) {
		scanf("%d%d", &a, &b);
		--a;
		--b;
		add_edge(a, b);
		add_edge(b, a);
	}
	REP(i, n) {
		scanf("%d", &value[i]);
	}
}

void run() {
	dfs(0);
}

void out() {
	printf("Case #%d:", ++cas);
	REP(i, n) {
		printf(" %d", ans[i]);
	}
	printf("\n");	
}

void out(int cas) {
}

int main() {
	freopen("data", "r", stdin);

	init();
	while (~scanf("%d", &n)) {
		in();
		run();
		out();
	}

	return 0;
}
