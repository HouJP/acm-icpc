/*************************************************************************
    > File Name: hdoj_5180.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 三  3/11 11:26:40 2015
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define LL long long 
#define N (15)
#define MAX_LEGAL (1600)
#define MAX_CBNT (6500)
#define MOD (1000000007)

int dp[N + 5][N + 5][MAX_LEGAL + 5];
int king[N + 5][N + 5];
int statuses[MAX_LEGAL + 5];
int count_status;
vector<vector<int> > adj;
vector<vector<int> > dvd;
int arr_dfs[N + 5];
int t;
int ans[][16] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{5,8,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{35,72,36,6,0,0,0,0,0,0,0,0,0,0,0,0},
	{314,940,702,192,24,0,0,0,0,0,0,0,0,0,0,0},
	{6427,20953,18778,6528,1200,120,0,0,0,0,0,0,0,0,0,0},
	{202841,724224,766278,310368,63000,8640,720,0,0,0,0,0,0,0,0,0},
	{12727570,45687569,51049098,22486656,4751400,648000,70560,5040,0,0,0,0,0,0,0,0},
	{355115594,736342192,480159099,593158322,564699600,71527200,7161840,645120,40320,0,0,0,0,0,0,0},
	{718817248,766062498,551790315,804772379,958725252,916206996,91739593,85155840,6531840,362880,0,0,0,0,0,0},
	{789281595,29367309,234810099,689850602,160354814,575223606,565338593,166965641,87551353,72576000,3628800,0,0,0,0,0},
	{245046738,212490784,527909966,404618207,648188905,539918379,532542087,165451585,428944600,878079902,878169600,39916800,0,0,0,0},
	{681555006,278546674,315035573,624869750,794507062,84429000,792648481,661448548,160683200,93278547,346974481,496038323,479001600,0,0,0},
	{413451720,259920010,496775457,225920769,842092390,332550368,221710589,232620660,166171087,462729811,955852083,835265947,902539673,227020758,0,0},
	{571703274,654602013,270251289,900887757,942422378,974702258,610771898,46596778,844659211,467836761,298284961,960033762,424915175,992136520,178290591,0},
	{7017421,361818480,635021015,633194321,924790619,16861446,556906023,606568231,432184532,717658304,181068670,990596447,108561136,862468715,230765390,674358851},
};
int n,k;

void init();
void init_king();
void init_king_sub(int);
void get_dvd();

void dfs(int id, int left) {
	if (k == id) {
		arr_dfs[id] = left;
		vector<int> tmp;
		for (int i = 0; i <= id; ++i) {
			tmp.push_back(arr_dfs[i]);
		}
		dvd.push_back(tmp);
		return;
	}
	for (int i = 0; i <= left; ++i) {
		arr_dfs[id] = i;
		dfs(id + 1, left - i);
	}
}

void get_dvd() {
	for (int i = 0; i < dvd.size(); ++i) {
		dvd[i].clear();
	}
	dvd.clear();
	dfs(0, n - k);
	//printf("n = %d, k = %d, dvd.size = %d\n", n, k, dvd.size());
}

void init() {
	init_king();
}

void init_king() {
	memset(king, 0, sizeof(king));
	memset(dp, 0, sizeof(dp));
	count_status = 0;
	int tmp = 1 << N;
	for (int i = 0; i < tmp; ++i) {
		if (0 != (i & (i << 1))) {
			continue;
		}
		if (0 != (i & (i >> 1))) {
			continue;
		}
		statuses[count_status++] = i;
	}
	for (int i = 0; i < adj.size(); ++i) {
		adj[i].clear();
	}
	adj.clear();
	for (int i = 0; i < count_status; ++i) {
		vector<int> tmp;
		tmp.clear();
		for (int j = 0; j < count_status; ++j) {
			if (0 != (statuses[i] & statuses[j])) {
				continue;
			}
			if (0 != (statuses[i] & (statuses[j] << 1))) {
				continue;
			}
			if (0 != (statuses[i] & (statuses[j] >> 1))) {
				continue;
			}
			tmp.push_back(j);
		}
		adj.push_back(tmp);
	}
	for (int i = 1; i <= N; ++i) {
		init_king_sub(i);
	}
}

void init_ans() {
	for (n = 0; n <= N; ++n) {
		for (k = 0; k <= N; ++k) {
			if (0 == n) {
				ans[n][k] = 0;
			} else if (n < k) {
				ans[n][k] = 0;
			} else {
				get_dvd();
				ans[n][k] = 0;
				for (int i = 0; i < dvd.size(); ++i) {
					for (int j = 0; j < dvd.size(); ++j) {
						int tmp = 1;
						for (int mm = 0; mm < dvd[i].size(); ++mm) {
							if (0 == dvd[i][mm]) {
								continue;
							}
							for (int nn = 0; nn < dvd[j].size(); ++nn) {
								if (0 == dvd[j][nn]) {
									continue;
								} else {
									tmp = ((LL)tmp * king[dvd[i][mm]][dvd[j][nn]]) % MOD;
								}
							}
						}
						ans[n][k] = (ans[n][k] + tmp) % MOD;
					}
				}
				for (int i = 2; i <= k; ++i) {
					ans[n][k] = ((LL)ans[n][k] * (LL)i) % MOD;
				}
			}
		}
	}
	for (int i = 0; i <= N; ++i) {
		printf("\t");
		for (int j = 0; j <= N; ++j) {
			if (j < N) {
				printf("%d,", ans[i][j]);
			} else {
				printf("%d\n", ans[i][j]);
			}
		}
	}
}

void init_king_sub(int n) {
	int status_max = (1 << n) - 1;
	for (int i = 0; i < count_status; ++i) {
		if (statuses[i] > status_max) {
			break;
		}
		dp[1][n][i] = 1;
	}
	for (int i = 1; i < N; ++i) {
		for (int j = 0; j < count_status; ++j) {
			if (statuses[j] > status_max){
				break;
			}
			if (0 == dp[i][n][j]) {
				continue;
			}
			for (int k = 0; k < adj[j].size(); ++k) {
				if (statuses[adj[j][k]] > status_max) {
					break;
				}
				dp[i + 1][n][adj[j][k]] = (dp[i + 1][n][adj[j][k]] + dp[i][n][j]) % MOD;
			}
		}
	}
	for (int i = 0; i <= N; ++i) {
		for (int j = 0; j < count_status; ++j) {
			if (statuses[j] > status_max) {
				break;
			}
			king[i][n] = (king[i][n] + dp[i][n][j]) % MOD;
		}
	}
}

void in() {
	scanf("%d %d", &n, &k);
}

void out() {
	printf("%d\n", ans[n][k]);
}

int main() {
	freopen("data", "r", stdin);

	scanf("%d", &t);
	while (t--) {
		in();
		out();
	}

	return 0;
}
