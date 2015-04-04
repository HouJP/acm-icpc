/*************************************************************************
    > File Name: bc_1.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 六  4/ 4 19:01:37 2015
 ************************************************************************/

#include <cstdio>
#include <cstring>

char str[20];

int main() {
	freopen("data", "r", stdin);

	while (~scanf("%s", str)) {
		int a, b, c, i;
		char aa, bb, cc;
		a = b = c = 0;
		aa = bb = cc = 0;
		aa = str[0];
		for (i = 0; i < strlen(str); ++i) {
			if (str[i] == aa) {
				++a;
				continue;
			} else {
				bb = str[i];
				break;
			}
		}
		if (!bb) {
			printf("NO\n");
			continue;
		}
		for (; i < strlen(str); ++i) {
			if (str[i] == bb) {
				++b;
				continue;
			} else {
				cc = str[i];
				break;
			}
		}
		if (!cc || cc == aa) {
			printf("NO\n");
			continue;
		}
		for (; i < strlen(str); ++i) {
			if (str[i] == cc) {
				++c;
				continue;
			} else {
				break;
			}
		}
		//printf("%d\t%d\t%d\n", a, b, c);
		if ((a == b) && (b == c) && (a + b + c == strlen(str))) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
}
