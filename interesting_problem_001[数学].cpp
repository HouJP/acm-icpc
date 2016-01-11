/*************************************************************************
    > File Name: interesting_problem_001[数学].cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 一  4/20 22:53:30 2015
 ************************************************************************/

/* 
 * Problem
 *
 *		Assume we have a sequence that contains N numbers of type long. And we know for sure that among this sequence each nuber does occur exactly n times except for the one number that occurs exactly m times(0 < m < n). How do we find that number with O(N) operations and O(1) additional memory?
 *
 * Input
 *		3 3 2	(N, n, m)
 *		5 11 5 2 11 5 2 11	(each number)
 * Output
 *		2	(because it occurs only twice)
 *
 * Answer
 *
 *		do 64 sums, one for each bit, for each of the sums you calculate sum mod n, this calculation return m for each bit that should to be set in the result, and 0 for each bit that should not be set.
 *
 * */

#include <cstdio>
#include <cstring>

using namespace std;

#define LL long long
#define BIT_CNT (64)

LL N, n, m, num, ans;
LL cnt[BIT_CNT + 5];

void init() {
}

void in() {
	memset(cnt, 0, sizeof(cnt));
	ans = 0;

	int endf = (N - 1) * n + m;
	for (int i = 0; i < endf; ++i) {
		scanf("%lld", &num);
		int tmp = 0;
		while (num) {
			if (num & 0x01) {
				++cnt[tmp];
			}
			++tmp;
			num >>= 1;
		}
	}
}

void run() {
	for (int i = 0; i < BIT_CNT; ++i) {
		if (cnt[i] % n) {
			ans |= (1 << i);
		}
	}
}

void out() {
	printf("%lld\n", ans);
}

int main() {
	freopen("data", "r", stdin);

	init();
	while (~scanf("%lld%lld%lld", &N, &n, &m)) {
		in();
		run();
		out();
	}

	return 0;
}
