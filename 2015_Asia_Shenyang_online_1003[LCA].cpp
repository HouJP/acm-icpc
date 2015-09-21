/*************************************************************************
    > Author: HouJP
    > Mail: houjp1992@gmail.com
 ************************************************************************/

//#pragma comment(linker, "/STACK:102400000,102400000")
//extern int main2(void) __asm__ ("main2");  

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

#define N (20010) // 点数最大值
#define M (200010) // 询问最大值

#define L (15) // DP数组第二维长度,一般不发生变化

int t, n, m;
int a, b, c;

// LCA问题，在线算法 ST+DFS
// 时间复杂度 O(n * log(n) + q)，n为总节点数，q为询问节点对数

struct Edge {
	int u, v, w;
	int next;
};
Edge e[2 * N + 5]; // 存放边
int e_head[N + 5]; // 邻接表表头
int ver[2 * N + 5]; // 保存遍历的节点顺序
int dep[2 * N + 5]; // 保存遍历的节点对应的深度
int fir[N + 5]; // 保存每个节点在遍历过程中第一次出现的位置
int dis[N + 5]; // 每个节点到根节点的距离
int h_pow[L + 5]; // 事先保存2^x，不需要重复计算
int dp[2 * N + 5][L + 1]; // sparse table的DP数组
bool vis[N + 5]; // dfs的标记数组
int ind; // 生成邻接表指针，遍历树的顺序指针等

bool visit[N];
int cnt[N];
int ans;

inline void read(int &x) {
    char ch = getchar();
    int tag = 1;
    x = 0;
    while ((ch <'0' || ch > '9') && ch != '-') {
        ch = getchar();
    }
    if (ch == '-') {
        tag = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    x *= tag;
}

// 制作边表
inline void add_edge(Edge e[], int e_head[], int u, int v, int w, int &k) {
	e[k].u = u; e[k].v = v; e[k].w = w;
	e[k].next = e_head[u]; e_head[u] = k++;
	e[k].u = v; e[k].v = u; e[k].w = w;
	e[k].next = e_head[v]; e_head[v] = k++;
}

// 遍历树
void dfs(int u, int d) {
	vis[u] = true;
	ver[ind] = u; fir[u] = ind; dep[ind++] = d;
	for (int k = e_head[u]; -1 != k; k = e[k].next) {
		if (!vis[e[k].v]) {
			int v = e[k].v;
			dis[v] = dis[u] + e[k].w;
			dfs(v, d + 1);
			ver[ind] = u; dep[ind++] = d;
		}
	}
}

// init h_pow
void init_pow_2() {
	h_pow[0] = 1;
	for (int i = 1; i <= L; ++i) {
		h_pow[i] = 2 * h_pow[i - 1];
	}
}

// dp，从0的位置开始
void sparse_table(int len) {
	int k = (int)(log((double)len) / log(2.0));
	for (int i = 0; i < len; ++i) {
		dp[i][0] = i;
	}
	for (int j = 1; j <= k; ++j) {
		int end = len - h_pow[j];
		for (int i = 0; i <= end; ++i) {
			int a = dp[i][j - 1];
			int b = dp[i + h_pow[j- 1]][j - 1];
			if (dep[a] < dep[b]) {
				dp[i][j] = a;
			} else {
				dp[i][j] = b;
			}
		}
	}
}

int rmq(int x, int y) {
	int len = y - x + 1;
	int k = (int)(log((double)len) / log(2.0));
	int a = dp[x][k];
	int b = dp[y - h_pow[k] + 1][k];
	if (dep[a] < dep[b]) {
		return a;
	} else {
		return b;
	}
}

int lca(int u, int v) {
	int x = fir[u];
	int y = fir[v];
	if (x > y) {
		swap(x, y);
	}
	int pos = rmq(x, y);
	return ver[pos];
}


int dfs2(int root) {
	visit[root] = true;
	int tmp = e_head[root];
	int tmp_cnt = cnt[root];
	int ret;
	while (-1 != tmp) {
		if (!visit[e[tmp].v]) {
			tmp_cnt += dfs2(e[tmp].v);
		}
		tmp = e[tmp].next;
	}
	//printf("root = %d, cnt[root] = %d\n", root, cnt[root]);
	if (0 != root) {
		//sum += cnt[root];
		ans = MIN(ans, tmp_cnt);
	}
	return tmp_cnt;
}

void init() {
	scanf("%d", &t);
	init_pow_2();
}

void in() {
	reset(cnt, 0);
	reset(visit, 0);
	ans = INF;

	scanf("%d%d", &n, &m);
	//printf("n = %d, m = %d\n", n, m);
	memset(e_head, -1, sizeof(e_head));
	memset(vis, 0, sizeof(vis));
	dis[0] = 0;
	ind = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d%d", &a, &b);
		add_edge(e, e_head, a - 1, b - 1, 0, ind);
	}
	ind = 0;
	dfs(0, 0);
	sparse_table(2 * n - 1);
}

void run() {
	int tmp = m - n + 1;
	for(int i = 0; i < tmp; ++i) {
		scanf("%d%d", &a, &b);
		cnt[a - 1]++;
		cnt[b - 1]++;
		cnt[lca(a - 1, b - 1)] -= 2;
		//printf("%d, %d, lca = %d\n", a - 1, b - 1, lca(a - 1, b - 1));
	}
	dfs2(0);
}

void out() {
}

void out(int cas) {
	printf("Case #%d: %d\n", cas, ans + 1);
}

int main() {
	//freopen("data", "r", stdin);

	init();
	REP(i, t) {
		in();
		run();
		out(i + 1);
	}

	return 0;
}
