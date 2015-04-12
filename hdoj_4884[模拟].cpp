/*************************************************************************
    > File Name: hdoj_4884.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 四  4/ 9 10:13:34 2015
 ************************************************************************/

/*
 * 思路
 *
 * 模拟题，题目没看明白就去做，wa了一上午，最后总算知道为什么了，教训啊！
 *
 * 不是意味着后来的一定会后走，如果后来的人的饭先做好了，那么他就可以走了，这取决于之前的人有没有和他点一样的饭，带上他一起做。
 * begin数组记录某类型的饭最后一次做的开始时间，left数组记录某类型的饭最后一次做还可以多做的份数。来了一个人先检查begin是否在到来的时间之后，如果是，那么可以在上一次做饭的时候顺带帮他做一些，如果顺带做的份数可以满足他的需求，那么他就可以走人了。
 *
 * */

#include <cstdio>
#include <cstring>

using namespace std;

#define MAX(a,b) (a > b ? (a) : (b))
#define N (1000)

int begin[N + 5];
int left[N + 5];

int tt;
int n, t, k, m;
int hh, mm, id, num;

int now, intime, time;

int main() {
	freopen("data", "r", stdin);

	scanf("%d", &tt);
	while (tt--) {
		scanf("%d%d%d%d", &n, &t, &k, &m);
		memset(begin, -1, sizeof(begin));
		memset(left, 0, sizeof(left));
		now = 0;
		for (int i = 0; i < m; ++i) {
			scanf("%d:%d %d %d", &hh, &mm, &id, &num);
			intime = hh * 60 + mm;
			now = MAX(now, intime);
			if (begin[id] >= intime) {
				if (num > left[id]) {
					num -= left[id];
					left[id] = 0;
				} else {
					left[id] -= num;
					num = 0;
				}
			}
			if (num) {
				time = num / k;
				if (num % k) {
					++time;
				}
				begin[id] = now + (time - 1) * t;
				left[id] = time * k - num;
				now += time * t;
				printf("%02d:%02d\n", (now / 60) % 24, now % 60);
			} else {
				printf("%02d:%02d\n", ((begin[id] + t) / 60) % 24, (begin[id] + t) % 60);
			}
		}
		if (tt) {
			printf("\n");
		}
	}

	return 0;
}
