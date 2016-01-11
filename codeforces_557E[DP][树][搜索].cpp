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

#define N (5000 + 5)

struct Node {
	int c[2];
	int num;
};

Node br[N * N];
bool dp[2 * N][N][2];
int cnt_br;
char s[N];
char ans[N];
int len;
int k;
int dep;
int tol;

void dfs_br(int id) {
	tol += br[id].num;
	if (tol >= k) {
		return;
	}
	if (0 != br[id].c[0]) {
		ans[dep] = 'a';
		++dep;
		dfs_br(br[id].c[0]);
		if (tol >= k) {
			return;
		}
		--dep;
	}
	if (0 != br[id].c[1]) {
		ans[dep] = 'b';
		++dep;
		dfs_br(br[id].c[1]);
		if (tol >= k) {
			return;
		}
		--dep;
	}
}

int add_string(int pre_id, int pre_end, int end) {
	if (!(pre_end < end)) {
		return pre_id;
	}
	FOR(i, pre_end + 1, end) {
		if (0 == br[pre_id].c[s[i] - 'a']) {
			memset(br[cnt_br].c, 0, sizeof(br[cnt_br].c));
			br[cnt_br].num = 0;
			br[pre_id].c[s[i] - 'a'] = cnt_br;
			pre_id = cnt_br++;
		} else {
			pre_id = br[pre_id].c[s[i] - 'a'];
		}
	}
	++br[pre_id].num;
	return pre_id;
}

void init() {
}

void in() {
	memset(br[0].c, 0, sizeof(br[0].c));
	br[0].num = 0;
	cnt_br = 1;
	scanf("%d", &k);
	len = strlen(s);
	memset(dp, 0, sizeof(dp));
	dep = 0;
}

void run() {
	// 枚举中心点，长度，复杂度 O(n * n)
	REP(i, len) {
		int tmp_len = MAX(MIN(i, len - i - 1), 0);
		REP(j, tmp_len + 1) {
			if (j < 3) {
				if (!(s[i - j] == s[i + j])) {
					dp[i][j][0] = true;
				}
			} else {
				if (!((s[i - j] == s[i + j]) && (false == dp[i][j - 2][0]))) {
					dp[i][j][0] = true;
				}
			}
		}
	}
	// 枚举中间间隔，长度，复杂度 O(n * n)
	REP(i, len - 1) {
		int tmp_len = MAX(MIN(i + 1, len - i - 1), 0);
		REP(j, tmp_len + 1) {
			if (0 == j) {
				continue;
			}
			if (j < 3) {
				if (!(s[i - j + 1] == s[i + j])) {
					dp[i][j][1] = true;
				} 
			} else {
				if (!((s[i - j + 1] == s[i + j]) && (false == dp[i][j - 2][1]))) {
					dp[i][j][1] = true;
				}
			}
		}
	}
	// 按顺序遍历，枚举起点和长度，复杂度 O(n * n)
	REP(i, len) {
		int pre_id = 0, pre_end = i - 1;
		REP(j, (len - i) / 2 + 1) {
			if (false == dp[i + j - 1][j][1]) {
				pre_id = add_string(pre_id, pre_end, i + 2 * j - 1);
				pre_end = i + 2 * j - 1;
				//dfs_br(0);
			}
			if (false == dp[i + j][j][0]) {
				if (i + 2 * j >= len) {
				} else {
					pre_id = add_string(pre_id, pre_end, i + 2 * j);
					pre_end = i + 2 * j;
				}
			}
		}
	}
	dep = 0;
	tol = 0;
	dfs_br(0);
}

void out() {
	ans[dep] = '\0';
	printf("%s\n", ans);
}

void out(int cas) {
}

int main() {
	//freopen("data", "r", stdin);

	init();
	while(~scanf("%s", s)) {
		in();
		run();
		out();
	}

	return 0;
}
