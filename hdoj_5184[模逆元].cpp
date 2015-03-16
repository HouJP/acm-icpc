/*************************************************************************
    > File Name: hdoj_5184.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 一  3/ 9 18:19:44 2015
 ************************************************************************/

#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define LL long long

const int MOD = 1000000007;
const int MAX = 1000000;

int fac[MAX + 5];
int ans;
char input[MAX + 5];
int n;
int l, r;

void cal_factorial() {
	fac[0] = 1;
	for (int i = 1; i <= MAX; ++i) {
		fac[i] = (i * (LL)fac[i - 1]) % MOD;
	}
}

LL fast_exp(LL a, int e) {
	LL exp = 1;
	while (e) {
		if (e & 0x01) {
			exp = (exp * a) % MOD;
			--e;
		} else {
			a = (a * a) % MOD;
			e >>= 1;
		}
	}
	return exp;
}

void init(){
	cal_factorial();
}

void in() {
	scanf("%s", input);
	ans = 0;
}

void run() {
	if (0 != (n % 2)) {
		ans = 0;
		return;
	} else {
		l = r = 0;
		int len = strlen(input);
		for (int i = 0; i < len; ++i) {
			if ('(' == input[i]) {
				++l;
			} else {
				++r;
			}
			if (l < r) {
				ans = 0;
				return;
			}
		}
		if (l > n / 2) {
			ans = 0;
			return;
		} else if (r > n / 2) {
			ans = 0;
			return;
		}
		LL ans_l = fac[n - l - r] % MOD;
		ans_l = (ans_l * fast_exp(fac[n / 2 - l], MOD - 2)) % MOD;
		ans_l = (ans_l * fast_exp(fac[n / 2 - r], MOD - 2)) % MOD;
		LL ans_r = fac[n - l - r] % MOD;
		ans_r = (ans_r * fast_exp(fac[n / 2 - l - 1], MOD - 2)) % MOD;
		ans_r = (ans_r * fast_exp(fac[n / 2 - r + 1], MOD - 2)) % MOD;
		ans = (ans_l - ans_r + MOD) % MOD;
	}
}

void out() {
	printf("%d\n", ans);
}

int main() {
	freopen("data", "r", stdin);

	init();

	while (~scanf("%d", &n)) {
		in();
		run();
		out();
	}

	return 0;
}
