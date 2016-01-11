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

#define N (100000 + 5)
#define INF (0x3f3f3f3f)

priority_queue<int> que;

struct Node {
	int l;
	int d;
};

int n;
int cnt[N];
int maxx[N];
int pre[N];
int cnt_max_len[N];
int cnt_now_len[N];
int total;
Node nodes[N];
int ans;

bool cmp1(Node a, Node b) {
	return a.l > b.l;
}

bool cmp2(Node a, Node b) {
	return a.d < b.d;
}

void init() {
}

void in() {
	total = 0;
	memset(cnt, 0, sizeof(cnt));
	memset(cnt_max_len, 0, sizeof(cnt_max_len));
	memset(cnt_now_len, 0, sizeof(cnt_now_len));
	memset(pre, 0, sizeof(pre));
	for (int i = 0; i < n; ++i) {
		scanf("%d", &nodes[i].l);
		++cnt[nodes[i].l];
	}
	for (int i = 0; i < n; ++i) {
		scanf("%d", &nodes[i].d);
		cnt_now_len[nodes[i].l] += nodes[i].d;
		total += nodes[i].d;
	}
	ans = INF;
	while (!que.empty()) {
		que.pop();
	}
}

void run() {
	// sort by length
	sort(nodes, nodes + n, cmp1);
	int tmp_len = 100000;
	cnt_max_len[tmp_len + 1] = 0;
	for (int i = 0; i < n; ) {
		if (nodes[i].l > tmp_len) {
			++cnt_max_len[tmp_len];
			++i;
		} else {
			cnt_max_len[tmp_len] += cnt_max_len[tmp_len + 1];
			--tmp_len;
		}
	}
	for (int i = 0; i < n; ++i) {
		pre[i + 1] = pre[i] + nodes[i].d;
	}
	int tmp_tmp = n;
	for (int i = 1; i <= 100000; ++i) {
		if (!cnt[i]) {
			continue;
		}
		int tmp_ans = pre[cnt_max_len[i]];
		for (int j = cnt_max_len[i] + cnt[i]; j < tmp_tmp; ++j) {
			que.push(nodes[j].d);
		}
		tmp_tmp = cnt_max_len[i] + cnt[i];
		if (!(cnt_max_len[i] < (n - 2 * cnt[i] + 1))) {
			ans = MIN(ans, tmp_ans);
		} else {
			queue<int> q2;
			int tmp_cnt = 0;
			int tmp_ans = 0;
			while ((tmp_cnt < cnt[i] - 1) && !que.empty()) {
				int c = que.top(); que.pop();
				q2.push(c);
				tmp_ans += c;
				tmp_cnt++;
			}
			while (!q2.empty()) {
				que.push(q2.front());
				q2.pop();
			}
			ans = MIN(ans, total - tmp_ans - cnt_now_len[i]);
		}
	}
}

void out() {
	printf("%d\n", ans);
}

void out(int cas) {
}

int main() {
	//freopen("data", "r", stdin);

	init();
	while (~scanf("%d", &n)) {
		in();
		run();
		out();
	}

	return 0;
}
