/*************************************************************************
    > File Name: hdoj_2586.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 三  4/ 8 00:05:03 2015
 ************************************************************************/

#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>

// #pragma comment(linker, "/STACK:1024000000,1024000000")

using namespace std;

#define N (40000) // 节点个数
#define L (30) // DP数组第二维长度
#define M (200)	// 查询个数

int t, n, m;
int a, b, c;

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
int h_pow[M + 5]; // 事先保存2^x，不需要重复计算
int dp[2 * N + 5][L + 5]; // sparse table的DP数组
bool vis[N + 5]; // dfs的标记数组
int ind; // 生成邻接表指针，遍历树的顺序指针等

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

// dp，从0的位置开始
void sparse_table(int len) {
	// init h_pow
	h_pow[0] = 1;
	for (int i = 1; i <= M; ++i) {
		h_pow[i] = 2 * h_pow[i - 1];
	}
	// sparse table
	int k = (int)(long((double)len) / log(2.0));
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

int main() {
	int size = 256 << 20; // 256MB
	char *p = (char*)malloc(size) + size;
	__asm__("movl %0, %%esp\n" :: "r"(p));
	freopen("data", "r", stdin);

	scanf("%d", &t);
	while (t--) {
		read(n);
		read(m);
		// 初始化
		memset(e_head, -1, sizeof(e_head));
		memset(vis, 0, sizeof(vis));
		memset(dis, 0, sizeof(dis));
		// 建边
		ind = 0;
		for (int i = 1; i < n; ++i) {
			read(a);
			read(b);
			read(c);
			add_edge(e, e_head, a - 1, b - 1, c, ind);
		}
		// 遍历树
		ind = 0;
		dfs(0, 0);
		// sparse table
		sparse_table(2 * n - 1);
		// 询问
		for (int i = 0; i < m; ++i) {
			read(a);
			read(b);
			printf("%d\n", dis[a - 1] + dis[b - 1] - 2 * dis[lca(a - 1, b - 1)]);
		}
	}

	return 0;
}
