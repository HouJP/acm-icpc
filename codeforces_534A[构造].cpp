/*************************************************************************
    > File Name: demo.cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 日  4/12 23:55:05 2015
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define LL long long
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) > (b) ? (b) : (a))

int n;

void init() {
}

void in() {
}

void run() {
	if ((1 == n) || (2 == n)) {
		printf("1\n");
	} else if (3 == n) {
		printf("2\n");
	} else {
		printf("%d\n", n);
	}

	if (4 == n) {
		printf("3 1 4 2\n");
		return;
	}

	bool fir = true;
	for (int i = 1; i <= n; i += 2) {
		if (!fir) {
			printf(" ");
		} else {
			fir = false;
		}

		printf("%d", i);
	}

	if (n <= 3) {
		printf("\n");
		return;
	} 

	for (int i = 2; i <= n; i += 2) {
		if (!fir) {
			printf(" ");
		} else {
			fir = false;
		}

		printf("%d", i);
	}
	printf("\n");
}

void out() {
}

int main() {
	//freopen("data", "r", stdin);

	while (~scanf("%d", &n)) {
		in();
		run();
		out();
	}

	return 0;
}
