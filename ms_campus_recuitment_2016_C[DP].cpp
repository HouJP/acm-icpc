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
#include <string>
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

#define N (110)

int n, m;
int tmp;
int dd, rr;
string mm[N];
int dp[N][N][2];

void init() {
}

void in() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> mm[i];
		mm[i] = "b" + mm[i] + "b";
	}
	mm[n + 1] = string(m + 2, 'b');
	for (int i = 0; i < m + 2; ++i) {
		dp[0][i][0] = dp[0][i][1] = INF;
	}
	for (int i = 0; i < n + 2; ++i) {
		dp[i][0][0] = dp[i][0][1] = INF;
	}
	if (mm[1][1] == 'b') {
		dp[1][1][0] = 1;
		if (mm[1][2] == 'b') {
			dp[1][1][1] = 1;
		} else {
			dp[1][1][1] = 2;
		}
		// dp[1][1][0] = dp[1][1][1] = 1;
	} else {
		dp[1][1][0] = 0;
		if (mm[1][2] == 'b') {
			dp[1][1][1] = 0;
		} else {
			dp[1][1][1] = 1;
		}
		// dp[1][1][0] = dp[1][1][1] = 0;
	}
}

void run() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if ((i == 1) && (j == 1)) {
				continue;
			}
			if (mm[i][j] == 'b') {
				tmp = 1;
			} else {
				tmp = 0;
			}
			if (mm[i][j + 1] == 'b') {
				dd = min(dp[i][j - 1][0], dp[i - 1][j][1]);
			} else {
				dd = min(dp[i][j - 1][0] + 1, dp[i - 1][j][1]);
			}
			if (mm[i + 1][j] == 'b') {
				rr = min(dp[i][j - 1][0], dp[i - 1][j][1]);
			} else {
				rr = min(dp[i][j - 1][0], dp[i - 1][j][1] + 1);
			}
			dp[i][j][0] = rr + tmp;
			dp[i][j][1] = dd + tmp;
		}
	}
	// for (int i = 1; i <= n; ++i) {
	// 	for (int j = 1; j <= m; ++j) {
	// 		cout << dp[i][j][0] << "/" << dp[i][j][1] << "\t";
	// 	}
	// 	cout << endl;
	// }
}

void out() {
	cout << min(dp[n][m][0], dp[n][m][1]) << endl;
}

void out(int cas) {
}

int main() {
	freopen("data", "r", stdin);

	init();
	in();
	run();
	out();

	return 0;
}
