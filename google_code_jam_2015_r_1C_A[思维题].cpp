/*************************************************************************
    > File Name: 1.cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 5/13 19:45:00 2015
 ************************************************************************/

/* 思路
 *
 * Google的思维题，真是强啊，智商严重下降。
 *
 * 首先需要明确一点，如果船还有躲闪的余地，那么在第一次命中船体后，还需w发炮弹才能完全击沉船（w次中，w - 1发命中船体，还有一发因为欺骗而落空）；如果船没有躲闪的余地，那么在第一次命中船体后，还需w - 1发炮弹即可完全击沉船。
 *
 * 那么接下来，如果 c / w 有余数，那么一定是 第 c / w 发炮弹才能命中船体。
 * 而如果 c / w 没有余数，这里有一个问题，brother让第 c/w 发炮弹命中船体好，还是 c/w - 1发命中船体好：对于前一种，共需 c / w + w - 1；对于后一种，需 c / w - 1 + w。结果是一样的。
 *
 * */

#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

int t, r, c, w, ans;

int main() {
	freopen("data", "r", stdin);

	scanf("%d", &t);
	for (int cas = 1; cas <= t; ++cas) {
		scanf("%d%d%d", &r, &c, &w);
		ans = r * (c / w) + w - 1;
		if (0 != c % w) {
			++ans;
		}
		printf("Case #%d: %d\n", cas, ans);
	}

	return 0;
}
