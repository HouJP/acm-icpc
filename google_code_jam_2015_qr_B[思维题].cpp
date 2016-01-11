/*************************************************************************
    > File Name: B.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 六  4/11 16:41:47 2015
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define MIN(a,b) ((a) > (b) ? (b) : (a))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define D (1000)

int t, d, ans, max_num;
int num[D + 5];

void init() {
	scanf("%d", &t);
}

void in() {
	scanf("%d", &d);
	ans = 0;
	for (int i = 0; i < d; ++i) {
		scanf("%d", &num[i]);
		ans = MAX(ans, num[i]);
	}
	max_num = ans;
}

void run() {
	for (int i = 1; i <= max_num; ++i) {
		int tmp = 0;
		for (int j = 0; j < d; ++j) {
			tmp += num[j] / i - 1;
			if (num[j] % i) {
				++tmp;
			}
		}
		ans = MIN(ans, tmp + i);
	}
}

void out(int cas) {
	printf("Case #%d: %d\n", cas, ans);
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
