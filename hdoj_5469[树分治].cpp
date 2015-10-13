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
#define ULL unsigned long long

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

// 树，找重心，用于树分治
#define MAXN (10000)
struct Edge{
	int to;
	int nxt;
};
Edge e[2 * MAXN + 5];
int head[MAXN + 5], cnte;

int n; // 节点数目
int fa[MAXN + 5]; // 记录节点的父亲，注意根节点的父亲要为-1
int que[MAXN + 5]; // 宽搜用到的队列
int sz[MAXN + 5]; // 记录子树大小
bool vis[MAXN + 5]; // 标记该节点是否处理完毕，如果处理完毕，不参与下一轮计算

inline void add_edge(int u, int v) {
	e[cnte].to = v;
	e[cnte].nxt = head[u];
	head[u] = cnte++;
}

int get_root(int root) {
	int l = 0, r = 0, res = n + 1;
	fa[root] = -1;
	for (que[r++] = root; l < r; ++l) {
		int now = que[l];
		for (int i = head[now]; ~i; i = e[i].nxt) {
			int u = e[i].to;
			if (vis[u] || fa[now] == u) continue;
			fa[u] = now;
			que[r++] = u;
		}
	}
	for (; r; --r) {
		int now = que[r - 1], m = 0;
		sz[now] = 1;
		for (int i = head[now]; ~i; i = e[i].nxt) {
			int u = e[i].to;
			if (vis[u] || fa[now] == u) continue;
			sz[now] += sz[u];
			m = MAX(m, sz[u]);
		}
		m = MAX(m, l - sz[now]);
		if (res > m) {
			res = m;
			root = now;
		}
	}
	return root;	
}

int t;
char s1[MAXN + 5];
char s2[MAXN + 5];
int a, b;
int ans;
ULL pre[MAXN + 5];
ULL suf[MAXN + 5];
ULL left[MAXN + 5];
ULL right[MAXN + 5];
ULL base = 31;
int len;
ULL os[MAXN + 5]; // 根据base计算字符串哈希的系数
int dep[MAXN + 5]; // 记录搜索的深度
int cnt[MAXN + 5]; // 记录长度为i的后缀的出现次数

void init() {
	reset(sz, 0);

	scanf("%d", &t);
	os[0] = 1;
	for (int i = 1; i <= MAXN; ++i) {
		os[i] = os[i - 1] * base;
	}
}

void in() {
	reset(head, -1);
	cnte = 0;
	reset(vis, 0);
	ans = 0;

	scanf("%d", &n);
	REP(i, n - 1) {
		scanf("%d%d", &a, &b);
		--a;
		--b;
		add_edge(a, b);
		add_edge(b, a);
	}

	scanf("%s%s", s1, s2);
	len = strlen(s2);
	pre[0] = 0;
	for (int i = 1; i <= len; ++i) {
		pre[i] = pre[i - 1] * base + s2[i - 1];
	}
	reverse(s2, s2 + len);
	suf[0] = 0;
	for (int i = 1; i <= len; ++i) {
		suf[i] = suf[i - 1] * base + s2[i - 1];
	}

	for (int i = 0; i <= len; ++i) {
		cnt[i] = 0;
	}

	// for (int i = 0; i <= len; ++i) {
	// 	printf("pre = %lld, suf = %lld\n", pre[i], suf[i]);
	// }
}

int bfs(int root) {
	//printf("nbfs root = %d\n", root);
	int ret = 0;

	int l = 0, r = 0;
	que[r++] = root;
	while (l < r) {
		int now = que[l++];
		//printf("now = %d\n", now);
		if (dep[now] <= len && right[now] == suf[dep[now]]) {
			cnt[dep[now]]++;
			//printf("\tnow = %d, cnt[%d] = %d\n", now, dep[now], cnt[dep[now]]);
		}

		int id = head[now];
		while (~id) {
			int nxt = e[id].to;
			if (!vis[nxt] && (fa[now] != nxt)) {
				que[r++] = nxt;
				fa[nxt] = now;
				dep[nxt] = dep[now] + 1;
				left[nxt] = left[now] + s1[nxt] * os[dep[nxt]];
				right[nxt] = right[now] + s1[nxt] * os[dep[nxt] - 1];

				//printf("\tnxt = %d, char = %c, left[nxt] = %lld, right[nxt] = %lld\n", nxt, s1[nxt], left[nxt], right[nxt]);
			}
			id = e[id].nxt;
		}
	}

	for (int i = 0; i < r; ++i) {
		int node = que[i];
		if ((dep[node] + 1 <= len) && (left[node] == pre[dep[node] + 1])) {
			//printf("\tnode = %d, match pre, cnt[len - dep[node] - 1] = %d\n", node, cnt[len - dep[node] - 1]);
			ret += cnt[len - dep[node] - 1];
		}
	}

	for (int i = 0; i < r; ++i) {
		int node = que[i];
		cnt[dep[node]] = 0;
	}

	return ret;
}

/* 找anode所在的子树 */
void run(int anode) {
	int root = get_root(anode);

	vis[root] = true; // 遍历过的根节点一定要标记为已访问
	dep[root] = 0;
	fa[root] = -1;
	//for (int i = 0; i <= len; ++i) cnt[i] = 0;

	left[root] = s1[root]; // 从根节点开始
	right[root] = 0; // 从根节点的下一个节点开始

	//printf("root = %d\n", root);

	ans += bfs(root);
	//printf("\tans(add) = %d\n", ans);

	int id = head[root];
	while (~id) {
		int nxt = e[id].to;

		if (!vis[nxt]) {
			//for (int i = 0; i <= len; ++i) cnt[i] = 0;
			ans -= bfs(nxt);
		}

		id = e[id].nxt;
	}
	//printf("\tans(sub) = %d\n", ans);

	if (ans > 0) {
		return;
	}

	id = head[root];
	while (~id) {
		int nxt = e[id].to;

		if (!vis[nxt]) { // 如果没有找到解，则需要递归在其子树中继续寻找解
			run(nxt);
			if (ans) { // 剪枝
				return;
			}
		}

		id = e[id].nxt;
	}
}

void out() {
}

void out(int cas) {
	printf("Case #%d: ", cas);
	if (ans) {
		printf("Find\n");
	} else {
		printf("Impossible\n");
	}
}

int main() {
	freopen("data", "r", stdin);

	init();
	REP(i, t) {
		in();
		run(0);
		out(i + 1);
	}

	return 0;
}
