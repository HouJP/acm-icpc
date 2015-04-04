/*************************************************************************
    > File Name: bc_2.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 六  4/ 4 19:24:41 2015
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define N (1000000)

int n, m, a, cnt;
int lev[N + 5];
int num[N + 5];

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

void read(int &x) {
    char ch = getchar();
    int tag = 1;
    x = 0;
    while ((ch <'0' || ch > '9') && ch != '-') {
        ch = getchar();
    }
    if (ch == '-') {
        tag = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    x *= tag;
}

int main() {
	freopen("data", "r", stdin);

	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i < n; ++i) {
			read(lev[i]);
		}
		
		sort(lev, lev + n);
		cnt = 0;
		num[cnt] = 0;
		a = lev[0];
		for (int i = 0; i < n; ++i) {
			if (lev[i] == a) {
				++num[cnt];
			} else {
				a = lev[i];
				++cnt;
				num[cnt] = 1;
			}
		}
		unique(lev, lev + n);
		/*
		printf("%d\n", cnt + 1);
		for (int i = 0; i <= cnt; ++i) {
			printf("%d:%d\t", lev[i], num[i]);
		}
		printf("\n");
		*/
		++cnt;

		for (int i = 0; i < m; ++i) {
			read(a);
			a = binary_search(lev, cnt, a);
			if (a == -1) {
				printf("0\n");
			} else {
				printf("%d\n", num[a]);
				num[a] = 0;
			}
		}
	}

	return 0;
}
