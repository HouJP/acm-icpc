/*************************************************************************
    > File Name: codeforces_549D.cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 一  6/ 8 17:14:06 2015
 ************************************************************************/

#include <cstdio>

using namespace std;

#define MAXN (100 + 2)

struct Point {
	int x;
	int y;
	Point() {}
	Point(int _x, int _y) : x(_x), y(_y) {}
};

int n, m, ans;
char s[MAXN];
int num[MAXN][MAXN];
Point end;

void in() {
	for (int i = 0; i < n; ++i) {
		scanf("%s", s);
		for (int j = 0; j < m; ++j) {
			if ('W' == s[j]) {
				num[i][j] = 1;
			} else {
				num[i][j] = -1;
			}
		}
	}
	end = Point(n, m);
	ans = 0;
}

void run() {
	while (true) {
		while (num[end.x][end.y] == 0) {
			--end.y;
			if (-1 == end.y) {
				end.y = m;
				--end.x;
			}
			if (-1 == end.x) {
				break;
			}
		}
		if (-1 == end.x) {
			break;
		} else {
			++ans;
			for (int i = 0; i <= end.x; ++i) {
				for (int j = 0; j <= end.y; ++j) {
					num[i][j] -= num[end.x][end.y];
				}
			}
		}
	}
}

void out() {
	printf("%d\n", ans);
}

int main() {
	//freopen("data", "r", stdin);

	while (~scanf("%d%d", &n, &m)) {
		in();
		run();
		out();
	}

	return 0;
}
