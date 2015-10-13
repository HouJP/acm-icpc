/*************************************************************************
    > Author: HouJP
    > Mail: houjp1992@gmail.com
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <map>

using namespace std;

#define LL long long

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x)	x.begin(), x.end()
#define rall(x)	x.rbegin(), x.rend()
#define sz(a)	int(a.size())
#define reset(a, x)	memset(a, x, sizeof(a))

#define MAX(a,b)		((a) > (b) ? (a) : (b))
#define MIN(a,b)		((a) > (b) ? (b) : (a))
#define ABS(a)			((a) > 0 ? (a) : (-(a)))
#define FOR(i, a, b)	for(int i = a; i <= b; ++i)
#define FORD(i, a, b)	for(int i = a; i >= b; --i)
#define REP(i, n)		for(int i = 0, _n = n; i < _n; ++i)
#define REPD(i, n)		for(int i = n - 1; i >= 0; --i)
#define FORSZ(i, x)		for(int i = 0; i < sz(x); ++i)

#define INF (0x3f3f3f3f)
#define NINF ((-1)*INF)
#define INFLL (0x3f3f3f3f3f3f3f3fLL)
#define NINFLL ((-1)*INFLL)

/* 求解反素数 */
#define RP 1000 // 反素数的个数
#define MAXN 500000 // 求maxn以内(包括maxn)的所有反素数

LL best_num; // 约数最多的数
LL best_sum; // 约数最多的约数个数
LL cntrp; // 反素数的个数
LL rpn = MAXN; // 求n以内的所有反素数
LL rprim[RP + 5][2];
LL prim[20] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}; // 枚举需要考虑的素数

// 当前走到num这个数，接着用第k个素数，num的约数个数为sum
// 第k个素数的个数上限为limit
void get_num(LL num, LL k, LL sum, LL limit) {
	if (num > rpn) return;
	if (sum > best_sum) {
		best_sum = sum;
		best_num = num;
	} else if (sum == best_sum && num < best_num) { // 约数个数一样时，取小的
		best_num = num;
	}
	if (k >= 10) return;

	for (int i = 1, p = 1; i <= limit; ++i) { // 素数k取i个
		p *= prim[k];
		get_num(num * p, k + 1, sum * (i + 1), i);
	}
}

// 求大于等于log2(n)的最小整数
LL log2(LL n) {
	LL i = 0;
	LL p = 1;
	while (p < n) {
		p *= 2;
		++i;
	}
	return i;
}

// 求反素数
void get_rprim() {
	cntrp = 0;
	while (rpn > 0) {
		best_num = 1;
		best_sum = 1;
		get_num(1, 0, 1, log2(rpn));
		rpn = best_num - 1;
		rprim[cntrp][0] = best_num;
		rprim[cntrp][1] = best_sum;
		++cntrp;
	}

	// printf("cntrp = %lld\n", cntrp);
	// for (int i = 0; i < cntrp; ++i) {
	// 	printf("best_num = %lld, best_sum = %lld\n", rprim[i][0], rprim[i][1]);
	// }
}

struct Seg {
	int sum;
};

Seg seg[(MAXN << 2) + 5];

char name[MAXN + 5][15];
LL rp[RP + 5];
LL nrp[RP + 5];
LL num[MAXN + 5];
int n, k;
int target;
int tid;
int query_id;

void push_down(int root) {

}

void push_up(int root) {
	seg[root].sum = seg[root << 1].sum + seg[root << 1 | 1].sum;
}

void build(int root, int l, int r) {
	if (l > r) {
		return;
	}

	seg[root].sum = 0;

	if (l == r) {
		seg[root].sum = 1;
		return;
	}

	push_down(root);

	int mid = (l + r) / 2;
	build(root << 1, l, mid);
	build(root << 1 | 1, mid + 1, r);

	push_up(root);
}

void update(int root, int l, int r, int sum) {
	if (l > r || seg[root].sum <= 0 || seg[root].sum < sum) {
		return;
	}

	//printf("l = %d, r = %d, sum = %d, sum = %d\n", l, r, seg[root].sum, sum);

	if (l == r) {
		seg[root].sum = 0;
		query_id = l;
		return;
	}

	push_down(root);

	int mid = (l + r) / 2;
	if (sum - seg[root << 1].sum <= 0) {
		update(root << 1, l, mid, sum);
	} else {
		update(root << 1 | 1, mid + 1, r, sum - seg[root << 1].sum);
	}

	push_up(root);
}

int mod(int num, int k) {
	return ((num % k) + k) % k;
}

void init() {
	get_rprim();

	for (int i = 0; i < cntrp; ++i) {
		rp[i] = rprim[cntrp - i - 1][0];
		nrp[i] = rprim[cntrp - i - 1][1];
	}
}

void in() {
	for (int i = 1; i <= n; ++i) {
		scanf("%s %lld", name[i], &num[i]);
	}

	build(1, 1, n);
	//printf("sum of root = %d\n", seg[1].sum);

	tid = upper_bound(rp, rp + cntrp, n) - rp - 1;
	target = rp[tid];
	//printf("target = %d\n", target);
}

void run() {
	int sum = k;
	for (int i = 1; i <= target; ++i) {
		update(1, 1, n, sum);
		//printf("i = %d, sum = %d, id = %d\n", i, sum, query_id);
		if (i != target) {
			if (num[query_id] > 0) {
				sum = mod(sum + num[query_id] - 1 - 1, n - i) + 1;
				//sum + num[query_id] - 1;
			} else {
				sum = mod(sum + num[query_id] - 1, n - i) + 1;
				//((sum + num[query_id] - 1) % (n - i) + n - i) % (n - i) + 1;
			}
		}
	}
}

void out() {
	printf("%s %d\n", name[query_id], (int)nrp[tid]);
}

void out(int cas) {
}

int main() {
	freopen("data", "r", stdin);

	init();
	while (~scanf("%d%d", &n, &k)) {
		in();
		run();
		out();
	}

	return 0;
}
