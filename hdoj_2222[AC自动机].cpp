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

#define N (500000) // 字典树中的节点数目
#define M (26) // 字母范围

struct Trie {
	int nxt[N + 5][M], fail[N + 5], end[N + 5];
	int root, cnt;

	int new_node() {
		for (int i = 0; i < M; ++i) {
			nxt[cnt][i] = -1;
		}
		end[cnt++] = 0;
		return cnt - 1;
	}

	void init() {
		cnt = 0;
		root = new_node();
	}

	void insert(char buf[]) {
		int len = strlen(buf);
		int now = root;
		for (int i = 0; i < len; ++i) {
			if (nxt[now][buf[i] - 'a'] == -1) {
				nxt[now][buf[i] - 'a'] = new_node();
			}
			now = nxt[now][buf[i] - 'a'];
		}
		++end[now];
	}

	void build() {
		queue<int> que;
		fail[root] = root;
		for (int i = 0; i < M; ++i) {
			if (nxt[root][i] == -1) {
				nxt[root][i] = root;
			} else {
				fail[nxt[root][i]] = root;
				que.push(nxt[root][i]);
			}
		}
		while (!que.empty()) {
			int now = que.front();
			que.pop();
			for (int i = 0; i < M; ++i) {
				if (nxt[now][i] == -1) {
					nxt[now][i] = nxt[fail[now]][i];
				} else {
					fail[nxt[now][i]] = nxt[fail[now]][i];
					que.push(nxt[now][i]);
				}
			}
		}
	}

	int query(char buf[]) {
		int len = strlen(buf);
		int now = root;
		int res = 0;

		for (int i = 0; i < len; ++i) {
			now = nxt[now][buf[i] - 'a'];
			int tmp = now;
			while (tmp != root) {
				res += end[tmp];
				end[tmp] = 0;
				tmp = fail[tmp];
			}
		}
		return res;
	}

	void show(int dep, int root) {
		for (int i = 0; i < M; ++i) {
			if (nxt[root][i] != 0) {
				for (int j = 0; j < dep; ++j) {
					printf(" ");
				}
				printf("%c: ", i + 'a');
				if (nxt[root][i] <= root) {
					printf("%d\n", nxt[root][i]);
				} else {
					printf("\n");
					show(dep + 1, nxt[root][i]);
				}
			}
		}
	}
};

char s[1000000 + 5];
char w[10000 + 5];
int t, n;
Trie ac;

void init() {
	scanf("%d", &t);
}

void in() {
	ac.init();

	scanf("%d", &n);
	REP(i, n) {
		scanf("%s", w);
		ac.insert(w);
	}
	ac.build();
	//ac.show(0, 0);
	scanf("%s", s);
}

void run() {
}

void out() {
	printf("%d\n", ac.query(s));
}

void out(int cas) {
}

int main() {
	freopen("data", "r", stdin);

	init();
	while (t--) {
		in();
		run();
		out();
	}

	return 0;
}
