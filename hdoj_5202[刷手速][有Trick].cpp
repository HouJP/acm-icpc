/*************************************************************************
    > File Name: 1.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 六  4/11 19:02:04 2015
 ************************************************************************/

/*
 * 思路
 *
 * 被卡住的反例: a?a
 *
 * */

#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define N (1000)

char str[N + 5];
char ans[N + 5];
int n;
bool has_ans;
bool is_wrong;

void in() {
	scanf("%s", str);
	memcpy(ans, str, sizeof(str));
	has_ans = false;
}

void run() {
	int len = strlen(str);
	for (int i = 0; i < len; ++i) {
		if ('?' == ans[i]) {
			ans[i] = 'a';
		}
	}
	int end = len / 2 + len % 2;
	for (int i = 0; i < end; ++i) {
		if (ans[i] != ans[len - i - 1]) {
			has_ans = true;
			return;
		}
	}
	for (int i = len - 1; i >= 0; --i) {
		if ((1 == (len % 2)) && (i == (end - 1))) {
			continue;
		}
		if ('?' == str[i]) {
			if (ans[len - i - 1] == 'a') {
				ans[i] = 'b';
			} else {
				ans[i] = 'a';
			}
			has_ans = true;
			return;
		}
	}
}

void out() {
	if (has_ans) {
		printf("%s\n", ans);
	} else {
		printf("QwQ\n");
	}
}

int main() {
	freopen("data", "r", stdin);

	while (~scanf("%d", &n)) {
		in();
		run();
		out();
	}

	return 0;
}
