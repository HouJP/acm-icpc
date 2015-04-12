/*************************************************************************
    > File Name: C.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 日  4/12 07:34:15 2015
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define L (10000)

int trans[5][5] = {
	{},
	{0, 1, 2, 3, 4},
	{0, 2, -1, 4, -3},
	{0, 3, -4, -1, 2},
	{0, 4, 3, -2, -1},
};

int t, l, x;
char str[L + 5];
bool ans;

void init() {
	scanf("%d", &t);
}

int fast_exp(int a, int e) {
	int exp = 1;
	bool neg = false;
	while (e) {
		if (e & 0x01) {
			if (a < 0) {
				neg = !neg;
				a = -a;
			}
			exp = trans[exp][a];
			if (exp < 0) {
				neg = !neg;
				exp = -exp;
			}
			--e;
		} else {
			if (a < 0) {
				a = -a;
			}
			a = trans[a][a];
			e >>= 1;
		}
	}
	if (neg) {
		return -exp;
	} else {
		return exp;
	}
}

int mul() {
	int now = 1, tmp;
	for (int i = 0; i < l; ++i) {
		if (now < 0) {
			tmp = -now;
		} else {
			tmp = now;
		}
		now = trans[tmp][str[i] - 'g'] * now / tmp;
	}
	//printf("mul = %d\n", now);
	return now;
}

void in() {
	scanf("%d%d%s", &l, &x, str);
}

void run() {
	int now = 1, tmp;
	bool fir = false, sec = false;
	for (int i = 0; (i < 8) && (i < x); ++i) {
		for (int j = 0; j < l; ++j) {
			if (now < 0) {
				tmp = -now;
			} else {
				tmp = now;
			}
			now = trans[tmp][str[j] - 'g'] * now / tmp;
			//printf("i = %d, j = %d, now = %d\n", i, j, now);
			if (2 == now) {
				fir = true;
			}
			if (fir && (4 == now)) {
				sec = true;
				break;
			}
		}
		if (sec) {
			break;
		}
	}
	if (sec && (-1 == fast_exp(mul(), x))) {
		ans = true;
	} else {
		ans = false;
	}
}

void out(int cas) {
	printf("Case #%d: ", cas);
	if (ans) {
		printf("YES\n");
	} else {
		printf("NO\n");
	}
}

int main() {
	//freopen("/Users/hugh_627/Downloads/data", "r", stdin);

	init();
	for (int i = 1; i <= t; ++i) {
		in();
		run();
		out(i);
	}

	return 0;
}
