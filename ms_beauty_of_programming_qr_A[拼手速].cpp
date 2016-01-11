/*************************************************************************
    > File Name: demo.cpp
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 二  4/14 23:36:55 2015
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <iostream>

using namespace std;

#define LL long long
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) > (b) ? (b) : (a))
#define ABS(a) ((a) > 0 ? (a) : (-(a)))

char month[][20] = {
	"",
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December",
};

int t;
map<string, int> mon;
string s1, s2;
int year1, year2, m1, m2, d1, d2;
int ans;

bool judge(int year) {
	if ((0 == year % 4) && (0 != year % 100)) {
		return true;
	}
	if (0 == year % 400) {
		return true;
	}
	return false;
}

void init() {
	scanf("%d", &t);

	for (int i = 1; i <= 12; ++i) {
		mon[month[i]] = i;
	}
}

void in() {
	cin >> s1;
	scanf("%d,%d", &d1, &year1);
	cin >> s2;
	scanf("%d,%d", &d2, &year2);
	m1 = mon[s1];
	m2 = mon[s2];

	ans = 0;
}

void run() {
	if (year2 == year1) {
		if (judge(year1) && (m1 <= 2)) {
			if ((m2 > 2) || ((m2 == 2) && (d2 == 29))) {
				++ans;
			}
		}
	}
	if (year2 > year1) {
		if (judge(year1) && (m1 <= 2)) {
			++ans;
		}
		if ((judge(year2) && (m2 > 2)) 
			|| (judge(year2) && m2 == 2 && d2 == 29)) {
			++ ans;
		}
		ans += ((year2 - 1) / 4 - (year1) / 4);
		ans -= ((year2 - 1) / 100 - (year1) / 100);
		ans += ((year2 - 1) / 400 - (year1) / 400);
	}
}

void out(int cas) {
	printf("Case #%d: %d\n", cas, ans);
}

int main() {
	freopen("data", "r", stdin);

	init();
	for (int i = 1; i <= t; ++i) {
		in();
		run();
		out(i);
	}
	return 0;
}
