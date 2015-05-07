/*************************************************************************
    > File Name: poj_1061.cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 三  5/ 6 07:43:20 2015
 ************************************************************************/

#include <cstdio>
#include <cstring>

using namespace std;

#define LL long long

LL x, y, m, n, l, ans;

LL exgcd2(LL m, LL n, LL &x, LL &y) {
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

bool modular_linear_equation(LL a, LL b, LL &ax, LL n)
{
    LL x, y, x0, i;
    LL d = exgcd2(a, n, x, y);
    if(b%d)
        return false;
	// ax为最小正整数解
	ax = ((x * (b / d)) % (n / d) + (n / d)) % (n / d);
	// 输出所有解
	/*
    x0=x*(b/d)%n;   //特解
    for(i=0;i<d;i++)
        printf("%lld\n",(x0+i*(n/d))%n);
	*/
    return true;
}

int main() {
	LL a, b, x, n;
	while (~scanf("%lld%lld%lld%lld%lld", &x, &y, &m, &n, &l)) {
		if (modular_linear_equation(n - m, x - y, ans, l)) {
			printf("%lld\n", ans);
		} else {
			printf("Impossible\n");
		}
	}
}
