/*************************************************************************
    > File Name: bc_3.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 六  4/ 4 20:13:01 2015
 ************************************************************************/

/*
 * 思路
 *
 * BestCoder第三题。。。。心碎了。。。有个地方忘了+1，结果没交上。。。。
 * 无限接近3题。。。。最终还是两题。。。
 *
 * */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define N (50005)

int n, q, a, cnt;
int h[N + 5];
int hh[N + 5];
int array[N + 5];
bool fly;

int binary_search_2(int* a, int len, int goal)
{
    int low = 0;
    int high = len - 1;
    while(low <= high)
    {
        int middle = (low + high)/2;
        if(a[middle] == goal)
            return middle;
        //在左半边
        else if(a[middle] > goal)
            high = middle - 1;
        //在右半边
        else
            low = middle + 1;
    }
    //没找到
    return high;
}

int binary_search(int* a, int len, int goal)
{
    int low = 0;
    int high = len - 1;
    while(low <= high)
    {
        int middle = (low + high)/2;
        if(a[middle] == goal)
            return middle;
        //在左半边
        else if(a[middle] > goal)
            high = middle - 1;
        //在右半边
        else
            low = middle + 1;
    }
    //没找到
    return -1;
}

int lowbit(int x) {
    return x & (-x);
}

void modify(int x, int add) {
    while (x <= N) {
        array[x] += add;
        x += lowbit(x);
    }
}

int get_sum(int x) {
    int ret = 0;
    while (x != 0) {
        ret += array[x];
        x -= lowbit(x);
    }
    return ret;
}

int main() {
	freopen("data", "r", stdin);

	while (~scanf("%d%d", &n, &q)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a);
			h[i] = hh[i] = a;
		}
		h[n] = hh[n] = 0;
		sort(hh, hh + n + 1);
		cnt = unique(hh, hh + n + 1) - hh;
		memset(array, 0, sizeof(array));
		
		for (int i = 1; i <= n; ++i) {
			if (h[i] < h[i - 1]) {
				int begin = binary_search(hh, cnt, h[i]);
				int end = binary_search(hh, cnt, h[i - 1]);
				modify(begin + 1, 1);
				modify(end + 1, -1);
			}
		}

		for (int i = 0; i < q; ++i) {
			scanf("%d", &a);
			int id = binary_search_2(hh, cnt, a);
			printf("%d\n", get_sum(id + 1));
		}
	}

	return 0;
}
