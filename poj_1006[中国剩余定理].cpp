/*************************************************************************
    > File Name: poj_1006.cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 一  5/ 4 14:35:43 2015
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

#define LL long long
#define MAXN (100)

int a, b, c, d, cas;
LL ans;

LL ca[MAXN + 5], cm[MAXN + 5];

LL exgcd2_f(LL m, LL n, LL &x, LL &y) {
    LL x1, y1, x0, y0;
    x0 = 1; y0 = 0;
    x1 = 0; y1 = 1;
    x = 0; y1 = 1;
    x = 0; y = 1;
    LL r = m % n;
    LL q = (m - r) / n;
    while (r) {
        x = x0 - q * x1;
        y = y0 - q * y1;
        x0 = x1; y0 = y1;
        x1 = x; y1 = y;
        m = n;
        n = r;
        r = m % n;
        q = (m - r) / n;
    }
    return n;
}

LL crt_f(int len) {
    LL d, x, y, m, n, ret;
    ret = 0; n = 1;
    for (int i = 0; i < len; ++i) {
        n *= cm[i];
    }
    for (int i = 0; i < len; ++i) {
        m = n / cm[i];
        d = exgcd2_f(cm[i], m, x, y);
        ret = (ret + y * m * ca[i]) % n;
    }
	ret = (n + ret % n) % n;
	if (!ret) {
		ret = n;
	}
    return ret;
}

int main() {
	freopen("data", "r", stdin);

	cas = 0;
	while (~scanf("%d%d%d%d", &a, &b, &c, &d) && (-1 != a)) {
		++cas;

		ca[0] = ((a - d) % 23 + 23) % 23;
		ca[1] = ((b - d) % 28 + 28) % 28;
		ca[2] = ((c - d) % 33 + 33) % 33;
		cm[0] = 23;
		cm[1] = 28;
		cm[2] = 33;
		ans = crt_f(3);

		printf("Case %d: the next triple peak occurs in %lld days.\n", cas, ans);
	}

	return 0;
}
