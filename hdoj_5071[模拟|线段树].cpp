/*************************************************************************
    > File Name: B.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 六 10/25 16:38:39 2014
 ************************************************************************/

/* *
 *
 * 思路
 *
 * 这题数据比较弱，其实暴力就能出，我用的五个标记的线段树。
 *
 * 题目描述实在是太渣了。
 *
 * */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define LL long long
#define MAX (5000)



struct STNode {
    int min;
    int max;
	int sum;
	int max_u;
	int link;
};

struct Node {
    LL value;
    int link;
};

int opt[MAX + 5][2];
int tmp, n, t;
char s[10];
int map[MAX + 5];
int map_len, map_value;
Node person[MAX + 5];
STNode st[8 * MAX + 5];
int st_len;
int que_head, que_tail, que_top;

int binary_search(int * a, int low, int high, int value) {
    while (low <= high) {
        int mid = (low + high) / 2;
        if (a[mid] == value) {
            return mid;
        } else if (a[mid] > value) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

void push_up(int root) {
    st[root].min = st[root << 1].min;
    st[root].max = st[root << 1 | 1].max;
	st[root].max_u = max(st[root << 1].max_u, st[root << 1 | 1].max_u);
    st[root].sum = st[root << 1].sum + st[root << 1 | 1].sum;
}

void build(int root, int l, int r) {
    if (l > r) return;
    if (l == r) {
        st[root].min = st[root].max = st_len++;
        st[root].sum = 0;
        st[root].link = -1;
		st[root].max_u = -1;
        return;
    }
    int mid = (l + r) / 2;
    build(root << 1, l, mid);
    build(root << 1 | 1, mid + 1, r);
    push_up(root);
}

void init() {
    map_len = 0;
    st_len = 0;

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        if (strcmp(s, "Add") == 0) {
            scanf("%d", &tmp);
            opt[i][0] = 1;
            opt[i][1] = tmp;
            map[map_len++] = tmp;
        } else if (strcmp(s, "Close") == 0) {
            scanf("%d", &tmp);
            opt[i][0] = 2;
            opt[i][1] = tmp;
            map[map_len++] = tmp;
        } else if (strcmp(s, "Chat") == 0) {
            scanf("%d", &tmp);
            opt[i][0] = 3;
            opt[i][1] = tmp;
            map[map_len++] = tmp;
        } else if (strcmp(s, "Rotate") == 0) {
            scanf("%d", &tmp);
            opt[i][0] = 4;
            opt[i][1] = tmp;
            map[map_len++] = tmp;
        } else if (strcmp(s, "Prior") == 0) {
            opt[i][0] = 5;
        } else if (strcmp(s, "Choose") == 0) {
            scanf("%d", &tmp);
            opt[i][0] = 6;
            opt[i][1] = tmp;
            map[map_len++] = tmp;
        } else if (strcmp(s, "Top") == 0) {
            scanf("%d", &tmp);
            opt[i][0] = 7;
            opt[i][1] = tmp;
            map[map_len++] = tmp;
        } else if (strcmp(s, "Untop") == 0) {
            opt[i][0] = 8;
        } else {
            printf("[ERROR]\n");
        }
    }

    sort(map, map + map_len);
    map_len = unique(map, map + map_len) - map;

    for (int i = 0; i < map_len; ++i) {
        person[i].value = 0;
        person[i].link = -1;
    }

    build(1, 0, 2 * map_len);
	que_head = map_len - 1;
	que_tail = map_len;
	que_top = -1;
}

void update_insert(int root, int l, int r, int leaf) {
	if (leaf < l || leaf > r) return;
	if (l == r) {
		if (l == leaf) {
			st[root].sum = 1;
			st[root].max_u = map[map_value];
			st[root].link = map_value;
			return;
		} else {
			printf("[ERROR]\n");
			return;
		}
	}
	int mid = (l + r) / 2;
	if (mid >= leaf) {
		update_insert(root << 1, l, mid, leaf);
	} else {
		update_insert(root << 1 | 1, mid + 1, r, leaf);
	}
	push_up(root);
}

void update_delete(int root, int l, int r, int leaf) {
	if (leaf < l || leaf > r) return;
	if (l == r) {
		if (l == leaf) {
			st[root].sum = 0;
			st[root].max_u = -1;
			st[root].link = -1;
			return;
		} else {
			printf("[ERROR]\n");
			return;
		}
	}
	int mid = (l + r) / 2;
	if (mid >= leaf) {
		update_delete(root << 1, l, mid, leaf);
	} else {
		update_delete(root << 1 | 1, mid + 1, r, leaf);
	}
	push_up(root);
}

int query(int root, int l, int r, int rank) {
	if (rank > st[root].sum || rank < 1) return -1;
	if (l == r) {
		return st[root].link;
	}
	int mid = (l + r) / 2;
	if (rank <= st[root << 1].sum) {
		return query(root << 1, l, mid, rank);
	} else {
		return query(root << 1 | 1, mid + 1, r, rank - st[root << 1].sum);
	}
}

int main() {
    freopen("data", "r", stdin);

    scanf("%d", &t);
    while (t--) {
        init();
		for (int i = 0; i < n; ++i) {
			if (opt[i][0] == 1) {
				map_value = binary_search(map, 0, map_len - 1, opt[i][1]);
				if (person[map_value].link != -1) {
					printf("Operation #%d: same priority.\n", i + 1);
				} else {
					update_insert(1, 0, 2 * map_len, que_tail);
					person[map_value].link = que_tail++;
					printf("Operation #%d: success.\n", i + 1);
				}
			} else if (opt[i][0] == 2) {
				map_value = binary_search(map, 0, map_len - 1, opt[i][1]);
				if (person[map_value].link == -1) {
					printf("Operation #%d: invalid priority.\n", i + 1);
				} else {
					printf("Operation #%d: close %d with %lld.\n", i + 1, opt[i][1], person[map_value].value);
					if (que_top == map_value) {
						if (person[map_value].value > 0) {
							printf("Bye %d: %lld\n", opt[i][1], person[map_value].value);
						}
						que_top = -1;
					} else if (query(1, 0, 2 * map_len, 1) == map_value) {
						if (person[map_value].value > 0) {
							printf("Bye %d: %lld\n", opt[i][1], person[map_value].value);
						}
					}
					update_delete(1, 0, 2 * map_len, person[map_value].link);
					person[map_value].value = 0;
					person[map_value].link = -1;
				}
			} else if (opt[i][0] == 3) {
				if (que_top != -1) {
					person[que_top].value += opt[i][1];
					printf("Operation #%d: success.\n", i + 1);
				} else {
					map_value = (query(1, 0, 2 * map_len, 1));
					if (map_value != -1) {
						person[map_value].value += opt[i][1];
						printf("Operation #%d: success.\n", i + 1);
					} else {
						printf("Operation #%d: empty.\n", i + 1);
					}
				}
			} else if (opt[i][0] == 4) {
				map_value = query(1, 0, 2 * map_len, opt[i][1]);
				if (map_value == -1) {
					printf("Operation #%d: out of range.\n", i + 1);
				} else {
					update_delete(1, 0, 2 * map_len, person[map_value].link);
					update_insert(1, 0, 2 * map_len, que_head);
					person[map_value].link = que_head--;
					printf("Operation #%d: success.\n", i + 1);
				}
			} else if (opt[i][0] == 5) {
				if (st[1].max_u == -1) {
					printf("Operation #%d: empty.\n", i + 1);
				} else {
					map_value = binary_search(map, 0, map_len - 1, st[1].max_u);
					update_delete(1, 0, 2 * map_len, person[map_value].link);
					update_insert(1, 0, 2 * map_len, que_head);
					person[map_value].link = que_head--;
					printf("Operation #%d: success.\n", i + 1);
				}
			} else if (opt[i][0] == 6) {
				map_value = binary_search(map, 0, map_len - 1, opt[i][1]);
				if (person[map_value].link != -1) {
					update_delete(1, 0, 2 * map_len, person[map_value].link);
					update_insert(1, 0, 2 * map_len, que_head);
					person[map_value].link = que_head--;
					printf("Operation #%d: success.\n", i + 1);
				} else {
					printf("Operation #%d: invalid priority.\n", i + 1);
				}
			} else if (opt[i][0] == 7) {
				map_value = binary_search(map, 0, map_len - 1, opt[i][1]);
				if (person[map_value].link != -1) {
					que_top = map_value;
					printf("Operation #%d: success.\n", i + 1);
				} else {
					printf("Operation #%d: invalid priority.\n", i + 1);
				}
			} else if (opt[i][0] == 8) {
				if (que_top != -1) {
					que_top = -1;
					printf("Operation #%d: success.\n", i + 1);
				} else {
					printf("Operation #%d: no such person.\n", i + 1);
				}
			} else {
				printf("[ERROR]\n");
			}
		}
		if (que_top != -1) {
			map_value = que_top;
			if (person[map_value].value > 0) {
				printf("Bye %d: %lld\n", map[map_value], person[map_value].value);
			}
			person[map_value].value = 0;
		}
		for (int i = 1; ; ++i) {
			map_value = query(1, 0, 2 * map_len, i);
			if (map_value == -1) {
				break;
			} else {
				if (person[map_value].value > 0) {
					printf("Bye %d: %lld\n", map[map_value], person[map_value].value);
				}
			}
		}
    }

    return 0;
}

