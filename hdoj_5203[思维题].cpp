/*************************************************************************
    > File Name: 2.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 六  4/11 19:41:45 2015
 ************************************************************************/

/*
 * 思路
 *
 * 思路很好想，计算边界的时候，向上取整还是向下取整的地方被卡住了，以后这种地方要小心。
 *
 * */

#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

#define LL long long
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) > (b) ? (b) : (a))
#define M (1000)

struct Seg {
	int l;
	int r;
	int len;
} bad;

int n, m;
LL ans;

inline int count(int left, int right) {
	if (left == right) {
		return 0;
	} else {
		// left is short
		if (left > right) {
			swap(left, right);
		}
		// count
		int b = (right + left) / 2;
		if ((right + left) % 2 == 0) {
			--b;
		}
		int a = (right - left) / 2 + 1;
		return b - a + 1;
	}
}

void in() {
	int a = n, b = 1, c;
	for (int i = 0; i < m; ++i) {
		scanf("%d", &c);
		a = MIN(a,c);
		b = MAX(b,c);
	}
	bad.l = a;
	bad.r = b;
	ans = 0;
}

void run() {
	if (bad.l == 1) {
		int left = bad.r + 1;
		int right = n; 
		if (right - left + 1<= 2) {
			ans = 0;
		} else {
			int mid = (right - left + 1) / 2 + left - 1;
			for (int i = left; i <= mid; ++i) {
				ans += count(i - left + 1, right - i);
			}
		}
	} else if (bad.r == n) {
		int left = 1;
		int right = bad.l - 1;
		if (right - left + 1 <= 2) {
			ans = 0;
		} else {
			int mid = (right - left + 1) / 2 + left - 1;
			for (int i = left; i <= mid; ++i) {
				ans += count(i - left + 1, right - i);
			}
		}
	} else {
		int left = bad.l - 1;
		int right = n - bad.r;
		ans += count(left, right);
	}
}

void out() {
	printf("%lld\n", ans);
}

int main() {
	freopen("data", "r", stdin);

	while (~scanf("%d%d", &n, &m)) {
		in();
		run();
		out();
	}

	return 0;
}
