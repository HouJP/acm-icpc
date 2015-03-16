/*************************************************************************
    > File Name: hdoj_5001.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 六 10/18 14:07:19 2014
 ************************************************************************/

/* *
 *
 * 思路
 * 1. 假设经过d步之后，位于点i的概率为p(d,i)，共有n个点，那么n个概率可以组成一个向量P(d)，这个向量的值可以通过一个概率转移矩阵与P(d-1)的乘积得到。
 * 2. 本题中，假设经过d步之后，不经过点j，且位于点i的概率为p(d,i)，n - 1个概率组成了一个向量P(d)，同样的道理，这个向量可以通过一个概率转移矩阵与P(d - 1)的乘积得到。
 * 3. 用矩阵的快速幂来降低复杂度。
 *
 * */

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define N (50)
#define D (10000)

void print(int);

int t, n, m, d;
double adj[N + 5][N + 5];
double adj_now[N + 5][N + 5];
int adj_len[N + 5];
double n_p[N + 5];
double n_p_now[N + 5];
double ans;

void print(int id) {
	printf("-------------------\n");
	if (id == 1) {
		for (int i = 0; i < n; ++i) {
			printf("%.2lf\t", n_p[i]);
		}
		printf("\n\n");
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				printf("%.2lf\t", adj[i][j]);
			}
			printf("\n");
		}
	}
	if (id == 2) {
		for (int i = 0; i < n - 1; ++i) {
			printf("%.2lf\t", n_p_now[i]);
		}
		printf("\n\n");
		for (int i = 0; i < n - 1; ++i) {
			for (int j = 0; j < n - 1; ++j) {
				printf("%.2lf\t", adj_now[i][j]);
			}
			printf("\n");
		}
	}
}

void matrix_fast_exp_1() {
	double adj_tmp[N + 5][N + 5];
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < n - 1; ++j) {
			adj_tmp[i][j] = 0;
			for (int k = 0; k < n - 1; ++k) {
				adj_tmp[i][j] += adj_now[i][k] * adj_now[k][j];
			}
		}
	}
	memcpy(adj_now, adj_tmp, sizeof(adj_tmp));
}

void matrix_fast_exp_2() {
	double n_p_tmp[N + 5];
	for (int i = 0; i < n - 1; ++i) {
		n_p_tmp[i] = 0;
		for (int j = 0; j < n - 1; ++j) {
			n_p_tmp[i] += adj_now[i][j] * n_p_now[j];
		}
	}
	memcpy(n_p_now, n_p_tmp, sizeof(n_p_tmp));
}

void matrix_fast_exp() {
	int e = d;
	while (e) {
		if (e & 0x01) {
			matrix_fast_exp_2();
			--e;
		} else {
			matrix_fast_exp_1();
			e >>= 1;
		}
	}
}

void get_ans(int id) {
	int tmpx = 0, tmpy = 0;
	for (int i = 0; i < n; ++i) {
		if (i != id) {
			n_p_now[tmpx++] = n_p[i];
		}
	}
	tmpx = tmpy = 0;
	for (int i = 0; i < n; ++i) {
		if (i != id) {
			tmpy = 0;
			for (int j = 0; j < n; ++j) {
				if (j != id) {
					adj_now[tmpx][tmpy] = adj[i][j];
					++tmpy;
				}
			}
			++tmpx;
		}
	}
	matrix_fast_exp();
	ans = 0;
	for (int i = 0; i < n - 1; ++i) {
		ans += n_p_now[i];
	}
	printf("%.10lf\n", ans);
}

void init() {
	int a, b, tmp;

	memset(adj, 0, sizeof(adj));
	memset(adj_len, 0, sizeof(adj_len));
	scanf("%d %d %d", &n, &m, &d);
	for (int i = 0; i < m; ++i) {
		scanf("%d %d", &a, &b);
		--a;
		--b;
		adj[a][b] = 1;
		adj[b][a] = 1;
		++adj_len[a];
		++adj_len[b];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (adj[i][j] > 0) {
				adj[i][j] /= adj_len[i];
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		n_p[i] = 1.0 / n;
	}
}

int main() {
	freopen("data", "r", stdin);

	scanf("%d", &t);
	while (t--) {
		init();
		for (int i = 0; i < n; ++i) {
			get_ans(i);
		}
	} 
	return 0;
}
