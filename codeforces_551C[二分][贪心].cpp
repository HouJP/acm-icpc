/*************************************************************************
    > Author: HouJP
    > Mail: houjp1992@gmail.com
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define LL long long

#define MAX(a,b)		((a) > (b) ? (a) : (b))
#define MIN(a,b)		((a) > (b) ? (b) : (a))

#define N (100000 + 2)
#define INF (0x3f3f3f3f3f3f3f3fLL)

int n, m;
LL a[N], pmax;
LL ans;

bool judge(LL ans) {
	LL p = 0;
	LL r = 0;
	for (int i = n - 1; i >= 0; --i) {
		if (a[i] == 0) {
			continue;
		}
		if (ans - (i + 2) < 0 ) {
			return false;
		}
		p += (a[i] - MIN(a[i], r)) / (ans - (i + 1));
		if (0 != ((a[i] - MIN(a[i], r)) % (ans - (i + 1)))) {
			++p;
			r = ans - (i + 1) - (a[i] - r) % (ans - (i + 1));
		} else {
			r -= a[i];
		}
		//printf("ans = %I64d, p = %I64d, r = %I64d\n",ans,  p, r);
	}
	if (p <= m)  {
		return true;
	} else {
		return false;
	}
}

void init() {
}

void in() {
	for (int i = 0; i < n; ++i) {
		scanf("%I64d", &a[i]);
	}
}

void run() {
	LL l = 0, r = INF;
	while (l <= r) {
		ans = (l + r) / 2;
		if (judge(ans)) {
			r = ans - 1;
		} else {
			l = ans + 1;
		}
	}
	ans = l;
}

void out() {
	printf("%I64d\n", ans);
}

void out(int cas) {
}

int main() {
	//freopen("data", "r", stdin);

	init();
	while (~scanf("%d%d", &n, &m)) {
		in();
		run();
		out();
	}

	return 0;
}
