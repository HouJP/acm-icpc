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

#define N (3200010)

struct Node {
	int order;
	int c[2];
	bool a_or_d;
	bool flag;
	Node(): a_or_d(false),flag(false){
		c[0] = c[1] = -1;
	}
	Node(int _l, int _r, bool _a, bool _f): a_or_d(_a), flag(_f){
		c[0] = c[1] = -1;
	}
};

Node nodes[N];
int cnt;
int n, m;
string ad;
string ip;
int mask;
bool flag_ad;
bool bip[32];
bool ans;
int order;

void judge() {
	int now = 0;
	if (nodes[now].flag) {
		if (nodes[now].a_or_d) {
			//cout << "YES " << nodes[now].order << endl;
			if (nodes[now].order < order) {
				order = nodes[now].order;
				ans = true;
			}
		} else {
			//cout << "NO " << nodes[now].order << endl;
			if (nodes[now].order < order) {
				order = nodes[now].order;
				ans = false;
			}
		}
	}
	for (int i = 0; i < mask; ++i) {
		if (nodes[now].c[bip[i]] == -1) {
			break;
		}
		now = nodes[now].c[bip[i]];
		if (nodes[now].flag) {
			if (nodes[now].a_or_d) {
				//cout << "YES " << nodes[now].order << endl;
				if (nodes[now].order < order) {
					order = nodes[now].order;
					ans = true;
				}
			} else {
				//cout << "NO " << nodes[now].order << endl;
				if (nodes[now].order < order) {
					order = nodes[now].order;
					ans = false;
				}
			}
		}
	}
}

void build(int o) {
	int now = 0;
	for (int i = 0; i < mask; ++i) {
		if (nodes[now].c[bip[i]] == -1) {
			nodes[now].c[bip[i]] = cnt;
			nodes[cnt] = Node(-1, -1, false, false);
			++cnt;
		}
		now = nodes[now].c[bip[i]];
		if (nodes[now].flag) {
			break;
		}
	}
	if (!nodes[now].flag) {
		nodes[now].flag = true;
		nodes[now].a_or_d = flag_ad;
		nodes[now].order = o;
	}
}

void tob(string s, int b) {
	int num = atoi(s.c_str());
	for (int i = 0; i < 8; ++i) {
		bool bit = (num >> i) & 0x01;
		bip[b * 8 + 7 - i] = bit;
	}
}

void split(string s) {
	int start = 0, end = 0;
	string f[4];
	for (int i = 0; i < 3; ++i) {
		end = s.find('.', start);
		f[i] = s.substr(start, end - start);
		start = end + 1;
	}
	end = s.find('/', start);
	f[3] = s.substr(start, end - start);
	start = end + 1;
	for (int i = 0;i < 4; ++i) {
		tob(f[i], i);
	}
	// for (int i = 0; i < 32; ++i) {
	// 	cout << bip[i];
	// 	if (i % 8 == 7) {
	// 		cout << " ";
	// 	}
	// }
	// cout << endl;

	mask  = atoi(s.substr(start).c_str());
	// cout << "mask " << mask << endl;
}

void init() {
	nodes[0] = Node(-1, -1, false, false);
	cnt = 1;
}

void in() {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		cin >> ad >> ip;
		if ("deny" == ad) {
			flag_ad = false;
		} else {
			flag_ad = true;
		}
		if (ip.find('/') == string::npos) {
			ip += "/32";
		}
		//cout << flag_ad << " " << ip << endl;
		split(ip);
		build(i);
		//cout << "cnt " << cnt << endl;
	}

	//cout << endl;

	for (int i = 0; i < m; ++i) {
		ans = true;
		order = 0x3f3f3f3f;
		cin >> ip;
		ip += "/32";
		split(ip);
		judge();
		if (ans) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
}

void run() {
}

void out() {
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
