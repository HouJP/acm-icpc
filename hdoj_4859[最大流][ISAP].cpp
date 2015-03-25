/*************************************************************************
    > File Name: hdoj_4859.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 二  3/24 14:26:51 2015
 ************************************************************************/


#include <cstdio>
#include <cstring>
#include <climits>

int t, nn, mm, ans;
char gra[50][50];
int id[50][50];
int move[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

const int MAXN = 2500; // 点数的最大值
const int MAXM = 7500; // 边数的最大值
const int INF = 0x3f3f3f3f;

struct Node {
    int from, to, next;
    int cap;
} edge[MAXM + 5];

int tol;
int head[MAXN + 5];
int dep[MAXN + 5];
int gap[MAXN + 5]; // gap[x] = y 说明残留网络中dep[i] == x的个数为y
int n; // n是总的点的个数，包括源点和汇点

void init() {
    tol = 0;
    memset(head, -1, sizeof(head));
}

inline void add_edge(int u, int v, int w, int rw = 0) {
    edge[tol].from = u;
    edge[tol].to = v;
    edge[tol].cap = w;
    edge[tol].next = head[u];
    head[u] = tol++;
    edge[tol].from = v;
    edge[tol].to = u;
    edge[tol].cap = rw;
    edge[tol].next = head[v];
    head[v] = tol++;
}

void bfs(int start, int end) {
    memset(dep, -1, sizeof(dep));
    memset(gap, 0, sizeof(gap));
    gap[0] = 1;
    int que[MAXN + 5];
    int front, rear;
    front = rear = 0;
    dep[end] = 0;
    que[rear++] = end;
    while (front != rear) {
        int u = que[front++];
        if (front == MAXN) front = 0;
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if (dep[v] != -1) continue;
            que[rear++] = v;
            if (rear == MAXN) rear = 0;
            dep[v] = dep[u] + 1;
            ++ gap[dep[v]];
        }
    }
}

int sap(int start, int end) {
    int res = 0;
    bfs(start, end);
    int cur[MAXN + 5];
    int S[MAXN + 5];
    int top = 0;
    memcpy(cur, head, sizeof(head));
    int u = start;
    int i;
    while (dep[start] < n) {
        if (u == end) {
            int temp = INF;
            int inser;
            for (i = 0; i < top; ++i) {
                if (temp > edge[S[i]].cap) {
                    temp = edge[S[i]].cap;
                    inser = i;
                }
            }
            for (i = 0; i < top; ++i) {
                edge[S[i]].cap -= temp;
                edge[S[i]^1].cap += temp;
            }
            res += temp;
            top = inser;
            u = edge[S[top]].from;
        }
        if (u != end && gap[dep[u] - 1] == 0) // 出现断层，无增广路
            break;
        for (i = cur[u]; i != -1; i = edge[i].next) {
            if (edge[i].cap != 0 && dep[u] == dep[edge[i].to] + 1) {
                break;
            }
        }
        if (-1 != i) {
            cur[u] = i;
            S[top++] = i;
            u = edge[i].to;
        } else {
            int min = n;
            for (i = head[u]; i != -1; i = edge[i].next) {
                if (0 == edge[i].cap) continue;
                if (min > dep[edge[i].to]) {
                    min = dep[edge[i].to];
                    cur[u] = i;
                }
            }
            --gap[dep[u]];
            dep[u] = min + 1;
            ++gap[dep[u]];
            if (u != start) {
                u = edge[S[--top]].from;
            }
        }
    }
    return res;
}

int main() {
	freopen("data", "r", stdin);

	scanf("%d", &t);

	for (int cas = 0; cas < t; ++cas) {
		// in
		scanf("%d%d", &nn, &mm);
		for (int i = 1; i <= nn; ++i) {
			scanf("%s", &gra[i][1]);
		}
		for (int i = 0; i <= nn + 1; ++i) {
			gra[i][0] = gra[i][mm + 1] = 'D';
		}
		for (int i = 0; i <= mm + 1; ++i) {
			gra[0][i] = gra[nn + 1][i] = 'D';
		}
		int cnt = 0;
		for (int i = 0; i <= nn + 1; ++i) {
			for (int j = 0; j <= mm + 1; ++j) {
				id[i][j] = ++cnt;
			}
		}
		init();
		n = cnt + 2;
		int start = 0, end = cnt + 1;
		ans = 0;
		for (int i = 0; i <= nn + 1; ++i) {
			for (int j = 0; j <= mm + 1; ++j) {
				for (int k = 0; k < 4; ++k) {
					int x = i + move[k][0];
					int y = j + move[k][1];
					if (x < 0 || x > nn + 1 || y < 0 || y > mm + 1) {
						continue;
					}
					ans++;
					add_edge(id[i][j], id[x][y], 1);
				}
				if (gra[i][j] != 'E') {
					if (((i + j) % 2 == 1 && gra[i][j] == '.') || ((i + j) % 2 == 0 && gra[i][j] == 'D')) {
						add_edge(start, id[i][j], INF);
					} else {
						add_edge(id[i][j], end, INF);
					}
				}
			}
		}
		printf("Case %d: %d\n", cas +1, ans / 2 - sap(start, end));
	}

	return 0;
}
