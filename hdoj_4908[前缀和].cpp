/*************************************************************************
    > File Name: hdoj_4908.cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 日  5/ 3 23:00:02 2015
 ************************************************************************/

/* 
 * 笔记
 *
 * 这题刚开始用了map来存，应该可以，但是其实直接开数组就好了，如果key范围不大的话，直接用数组代替map,节省时间。
 *
 * */

#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

#define MAXN (40000)

int ans;
int arr[MAXN + 5];
int n, m, pos;
int bis = 0;
int cnt[2 * MAXN + 5];

int main() {
	freopen("data", "r", stdin);

	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", &arr[i]);
			if (m == arr[i]) {
				pos = i;
			}
		}
			
		ans = 0;
		bis = 0;
		memset(cnt, 0, sizeof(cnt));

		for (int i = pos; i >= 0; --i) {
			if (arr[i] > m) {
				++bis;
			} else if (arr[i] < m) {
				--bis;
			}
			++cnt[bis + MAXN];
		}
		bis = 0;
		for (int i = pos; i < n; ++i) {
			if (arr[i] > m) {
				--bis;
			} else if (arr[i] < m) {
				++bis;
			}
			ans += cnt[bis + MAXN];
		}
		printf("%d\n", ans);
	}

	return 0;
}
