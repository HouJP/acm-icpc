/*************************************************************************
    > File Name: hdoj_5187.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 三  3/18 13:45:51 2015
 ************************************************************************/

#include <cstdio>
#include <cmath>

#define LL long long 

LL n, p;

LL fast_mul(LL a, LL b) {
	LL mul = 0;
	while (b) {
		if (b & 0x01) {
			mul = (mul + a) % p;
		}
		a = (a + a) % p;
		b >>= 1;
	}
	return mul;
}

// 因为有可能在快速幂的相乘中溢出，所以采用快速乘
LL fast_exp(LL a, LL e) {
	LL exp = 1;
	while (e) {
		if (e & 0x01) {
			exp = fast_mul(exp, a) % p;
		}
		a = fast_mul(a, a) % p;
		e >>= 1;
	}
	return exp;
}

int main() {
	freopen("data", "r", stdin);

	while (~scanf("%lld%lld", &n, &p)) {
		if (1 == p) {
			printf("0\n");
		} else if (1 == n) {
			printf("1\n");
		} else {
			printf("%lld\n", (fast_exp(2, n) - 2 + p) % p);
		}
	}

	return 0;
}
