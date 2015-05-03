/*************************************************************************
    > File Name: hdoj_4909.cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 日  5/ 3 21:33:53 2015
 ************************************************************************/

/*
 * 思路
 *
 * 如果知道a1a2...ax中各字母出现的次数，那么a1a2...ay中各字母出现的次数减a1a2...ax中各字母出现的次数，如果均为偶数，那么a(x+1)a(x+2)...ay序列满足要求。
 * 进一步化简：其实记录次数是没必要的，只要知道各字母出现次数的奇偶性就足够了，如果两个前缀各字母出现次数的奇偶性均相同，那么前缀之间的那段序列即满足要求。
 * 加入'?'该怎么办：'?'号只出现一次！所以很好办，将答案分为三部分，1. '?'前的子串，2.'?'后的子串，3.'?'包含在其中的子串（枚举26字母+delete）。
 *
 * */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

#define LL long long
#define MAXN (20000)

char str[MAXN + 5];
int t;
int ans;

int main() {
	freopen("data", "r", stdin);

	scanf("%d", &t);
	while (t--) {
		scanf("%s", str);
		int len = strlen(str);
		map<int, int> mp1;
		map<int, int> mp2;
		++mp1[0];
		ans = 0;
		int s = 0;
		bool flag = false;

		for (int i = 0; i < len; ++i) {
			if ('?' != str[i]) {
				s ^= (1 << (str[i] - 'a'));
			} else {
				flag = true;
				//mp2[s] = 1;
			}
			if (!flag) {
				// part 1
				if (mp1.count(s)) {
					ans += mp1[s];
				}
				++mp1[s];
			} else {
				// part 2
				if (mp2.count(s)) {
					ans += mp2[s];
				}
				++mp2[s];
				// part 3
				// delete '?'
				if (mp1.count(s)) {
					ans += mp1[s];
				}
				// change '?'
				for (int j = 0; j < 26; ++j) {
					if (mp1.count(s ^ (1 << j))) {
						ans += mp1[s ^ (1 << j)];
					}
				}
			}
		}
		printf("%d\n", ans);
	}

	return 0;
}
