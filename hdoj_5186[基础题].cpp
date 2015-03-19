/*************************************************************************
    > File Name: hdoj_5186.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 二  3/17 18:57:09 2015
 ************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

int nn, bb;
char sum[205];
char num[205];

void inverse(char * s) {
	int len = strlen(s);
	for (int i = 0; i <= len / 2 - 1; ++i) {
		swap(s[i], s[len - 1 - i]);
	}
}

char update(char a, char b) {
	int sum = 0;
	if (('0' <= a) && ('9' >= a)) {
		sum += a - '0';
	} else {
		sum += 10 + a - 'a';
	} 
	if (('0' <= b) && ('9' >= b)) {
		sum += b - '0';
	} else {
		sum += 10 + b - 'a';
	}
	sum %= bb;
	if (sum <= 9) {
		return '0' + sum;
	} else {
		return 'a' + sum - 10;
	}
}

void init() {
}

void in() {
	memset(sum, 0, sizeof(sum));
	for (int i = 0; i < nn; ++i) {
		scanf("%s", num);
		inverse(num);

		int len_sum = strlen(sum);
		int len_num = strlen(num);
		for (int j = 0; j < min(len_sum, len_num); ++j) {
			sum[j] = update(sum[j], num[j]);
		}
		if (len_num > len_sum) {
			memcpy(&sum[len_sum], &num[len_sum], len_num - len_sum);
		}
		sum[max(len_sum, len_num)] = '\0';
	}
}

void run() {
	for (int i = strlen(sum) - 1; i >= 0; --i) {
		if (('0' == sum[i]) && (0 != i)) {
			sum[i] = '\0';
		} else {
			break;
		}
	}
	inverse(sum);
}

void out() {
	printf("%s\n", sum);
}

int main() {
	freopen("data", "r", stdin);

	init();
	while (~scanf("%d%d", &nn, &bb)) {
		in();
		run();
		out();
	}

	return 0;
}
