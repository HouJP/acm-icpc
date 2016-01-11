/*************************************************************************
    > File Name: google_code_jam_2015_qr_A.cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 六  4/11 11:38:56 2015
 ************************************************************************/

#include <cstdio>
#include <cstring>

using namespace std;

#define S (1000)

int t, s;
char num[S + 5];
int ans, tot;

void in() {
	ans = 0;
	tot = 0;

	scanf("%d %s", &s, num);
	for (int i = 0; i <= s; ++i) {
		if (tot < i) {
			ans += i - tot;
			tot = i;
		}
		tot += num[i] - '0';
	}
}

void run() {
}

void out(int cas) {
	printf("Case #%d: %d\n", cas, ans);
}

int main() {
	//freopen("data", "r", stdin);

	scanf("%d", &t);
	for (int cas = 1; cas <= t; ++cas) {
		in();
		run();
		out(cas);
	}

	return 0;
}
