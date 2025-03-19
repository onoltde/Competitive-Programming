#include "seats.h"
#include<bits/stdc++.h>
using namespace std;

#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define x first
#define y second

const int mxn = 1e6 + 10, inf = 1e9;
int n, m, x[mxn], y[mxn], val[mxn];
vector<vector<int>> g;

// segtree
int d[mxn * 4], cnt[mxn * 4], lz[mxn * 4];

void pro(int i, int l, int r) {
	// if(lz[i] == 0) return;
	d[i] += lz[i];
	if(l < r) {
		lz[i * 2] += lz[i];
		lz[i * 2 + 1] += lz[i];
	}
	lz[i] = 0;
}

void build(int l, int r, int i) {
	if(l == r) {
		cnt[i] = 1;
		return;
	}
	int mid = (l + r) / 2;
	build(l, mid, i * 2);
	build(mid + 1, r, i * 2 + 1);
	cnt[i] = cnt[i * 2] + cnt[i * 2 + 1];
}

void update(int x, int y, int val, int l = 1, int r = n * m, int i = 1) {
	pro(i, l, r);
	if(l > y || r < x) return;
	if(x <= l && r <= y) {
		lz[i] += val;
		pro(i, l, r);
		return;
	}
	int mid = (l + r) / 2;
	update(x, y, val, mid + 1, r, i * 2 + 1);
	update(x, y, val, l, mid, i * 2);
	d[i] = d[i * 2]; cnt[i] = cnt[i * 2];
	if(d[i * 2 + 1] < d[i]) d[i] = d[i * 2 + 1], cnt[i] = cnt[i * 2 + 1];
	else if(d[i * 2 + 1] == d[i]) cnt[i] += cnt[i * 2 + 1];
}

int getAns() {
	return cnt[1];
}

int get(int i) {
	int ret = 0;
	for(int dx = -1; dx <= 0; dx++) {
		for(int dy = -1; dy <= 0; dy++) {
			int cnt = 0;
			for(int xx = 0; xx <= 1; xx++) {
				for(int yy = 0; yy <= 1; yy++) {
					int fx = x[i] + dx + xx;
					int fy = y[i] + dy + yy;
					if(g[fx][fy] > i) cnt++;
				}
			}
			if(cnt == 0) ret--;
			else if(cnt == 1) ret++;
			else if(cnt == 2) ret--;
			else ret++;
		}
	}
	return ret;
}

void printSegTree(int l = 1, int r = n * m, int i = 1) {
	pro(i, l, r);
	cout << l << ' ' << r << ' ' << d[i] << ' ' << cnt[i] << '\n';
	if(l == r) return;
	int mid = (l + r) / 2;
	printSegTree(l, mid, i * 2);
	printSegTree(mid + 1, r, i * 2 + 1);
}

void give_initial_chart(int H, int W, vector<int> R, vector<int> C) {
	n = H;
	m = W;
	build(1, n * m, 1);
	g = vector<vector<int>>(n + 10, vector<int>(m + 10, inf));
	for(int i = 1; i <= n * m; i++) {
		x[i] = R[i - 1] + 1;
		y[i] = C[i - 1] + 1;
		g[x[i]][y[i]] = i;
	}
	for(int i = 1; i <= n * m; i++) {
		val[i] = get(i);
		update(i, n * m, val[i]);
	}
	// printSegTree();
}

int swap_seats(int a, int b) {
	a++; b++;
	// return 1;
	swap(g[x[a]][y[a]], g[x[b]][y[b]]);
	swap(x[a], x[b]); swap(y[a], y[b]);
	for(int dx = -1; dx <= 1; dx++) {
		for(int dy = -1; dy <= 1; dy++) {
			int fx = x[a] + dx;
			int fy = y[a] + dy;
			int id = g[fx][fy];
			if(id == inf) continue;
			int tmp = get(id);
			update(id, n * m, -val[id] + tmp);
			val[id] = tmp;
		}
		for(int dy = -1; dy <= 1; dy++) {
			int fx = x[b] + dx;
			int fy = y[b] + dy;
			int id = g[fx][fy];
			if(id == inf) continue;
			int tmp = get(id);
			update(id, n * m, -val[id] + tmp);
			val[id] = tmp;
		}
	}
	return getAns();
}
