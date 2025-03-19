#include "werewolf.h"
#include<bits/stdc++.h>
using namespace std;

#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

template<typename T>
void mxx(T &a, T b){if(b > a) a = b;}
template<typename T>
void mnn(T &a, T b){if(b < a) a = b;}

const int mxn = 2e5 + 10;
int p[mxn], in[2][mxn], out[2][mxn], T;

int find(int x) {
	return p[x] == x ? x : p[x] = find(p[x]);
}

vector<vector<int>> adj[2], g;
vector<int> order[2];

void unite(int x, int y, int id) {
	x = find(x);
	y = find(y);
	if(x == y) return;
	p[y] = x;
	adj[id][x].pb(y);
}

void dfs(int to, int id) {
	in[id][to] = T++;
	order[id].pb(to);
	for(int x : adj[id][to]) {
		dfs(x, id);
	}
	out[id][to] = T - 1;
}

int d[mxn * 4];

void update(int l, int r, int i, int id, int x) {
	if(l == r) {
		d[i] = x;
		return;
	}
	int m = (l + r) / 2;
	if(id <= m) update(l, m, i * 2, id, x);
	else update(m + 1, r, i * 2 + 1, id, x);
	d[i] = min(d[i * 2], d[i * 2 + 1]);
}

int query(int l, int r, int i, int x, int y) {
	if(l >= x && r <= y) return d[i];
	int m = (l + r) / 2;
	if(y <= m) return query(l, m, i * 2, x, y);
	if(x > m) return query(m + 1, r, i * 2 + 1, x, y);
	return min(query(l, m, i * 2, x, y), query(m + 1, r, i * 2 + 1, x, y));
}

vector<int> check_validity(int n, vector<int> X, vector<int> Y, vector<int> S, vector<int> E, vector<int> L, vector<int> R) {
	int Q = E.size();
	vector<int> ret(Q);

	g = adj[0] = adj[1] = vector<vector<int>>(n);

	for(int i = 0; i < X.size(); i++) {
		g[X[i]].pb(Y[i]);
		g[Y[i]].pb(X[i]);
	}

	vector<int> pa(Q), pb(Q);
	vector<vector<int>> v;

	auto setDsu = [&]() -> void {
		v.clear();
		v.resize(n);
		for(int i = 0; i < n; i++) {
			p[i] = i;
		}
	};

	setDsu();
	{
		for(int i = 0; i < Q; i++) {
			v[L[i]].pb(i);
		}

		for(int i = n - 1; i >= 0; i--) {
			for(int x : g[i]) {
				if(x > i) {
					unite(i, x, 0);
				}
			}
			for(int id : v[i]) {
				pa[id] = find(S[id]);
			}
		}
	}

	setDsu();
	{
		for(int i = 0; i < Q; i++) {
			v[R[i]].pb(i);
		}

		for(int i = 0; i < n; i++) {
			for(int x : g[i]) {
				if(x < i) {
					unite(i, x, 1);
				}
			}
			for(int id : v[i]) {
				pb[id] = find(E[id]);
			}
		}
	}

	dfs(0, 0); T = 0;
	dfs(n - 1, 1); T = 0;

	vector<vector<pair<pair<int, int>, pair<int, int>>>> qu(n);
	for(int i = 0; i < Q; i++) {
		int l1 = in[0][pa[i]], r1 = out[0][pa[i]];
		int l2 = in[1][pb[i]], r2 = out[1][pb[i]];
		qu[l1].pb({{i, r1}, {l2, r2}});
	}

	for(int i = 0; i < n; i++) {
		update(0, n - 1, 1, in[1][order[0][i]], i);
	}

	for(int i = 0; i < n; i++) {
		for(auto it : qu[i]) {
			int r = it.ff.ss, L = it.ss.ff, R = it.ss.ss, id = it.ff.ff;
			int mn = query(0, n - 1, 1, L, R);
			if(mn <= r) ret[id] = 1;
			else ret[id] = 0;
		}
		update(0, n - 1, 1, in[1][order[0][i]], n + 10);
	}
	return ret;
}
