#include "deliveries.h"
#include<bits/stdc++.h>
using namespace std;

#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

//#define int long long

typedef long long ll;
typedef vector<int> vi;
typedef set<int> si;
typedef multiset<int> msi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

const int mxn = 1e5 + 10;
int w[mxn], n;
long long sum;

namespace segTree {
	long long lz[mxn * 4], mn[mxn * 4], mx[mxn * 4], sumt[mxn * 4], sum[mxn * 4];
	void up(int i) {
		sumt[i] = sumt[i * 2] + sumt[i * 2 + 1];
		sum[i] = sum[i * 2] + sum[i * 2 + 1];
		mx[i] = max(mx[i * 2], mx[i * 2 + 1]);
		mn[i] = min(mn[i * 2], mn[i * 2 + 1]);
	}

	void pro(int i, int l, int r) {
		if(lz[i] == 0 || l == r) return;

		lz[i * 2] += lz[i];
		lz[i * 2 + 1] += lz[i];

		mx[i * 2] += lz[i];
		mx[i * 2 + 1] += lz[i];

		mn[i * 2] += lz[i];
		mn[i * 2 + 1] += lz[i];

		sum[i * 2] += sumt[i * 2] * lz[i];
		sum[i * 2 + 1] += sumt[i * 2 + 1] * lz[i];

		lz[i] = 0;
	}

	void addX(int l, int r, int i, int x, int y, long long val) {
		pro(i, l, r);
		if(l >= x && r <= y) {
			lz[i] += val;
			mn[i] += val;
			mx[i] += val;
			sum[i] += sumt[i] * val;
			pro(i, l, r);
			return;
		}
		int m = (l + r) / 2;
		if(x <= m) addX(l, m, i * 2, x, y, val);
		if(y > m) addX(m + 1, r, i * 2 + 1, x, y, val);
		up(i);
	}

	void setT(int l, int r, int i, int x, long long val) {
		pro(i, l, r);
		if(l == r) {
			sumt[i] = val;
			assert(mx[i] == mn[i]);
			sum[i] = mx[i] * val;
			return;
		}
		int m = (l + r) / 2;
		if(x <= m) setT(l, m, i * 2, x, val);
		else setT(m + 1, r, i * 2 + 1, x, val);
		up(i);
	}

	long long getAns(int l, int r, int i, long long val) {
		pro(i, l, r);
		if(mx[i] <= val - mx[i] + 1) return sum[i]; 
		if(mn[i] >= val - mn[i] + 1) return sumt[i] * (val + 1) - sum[i];
		int m = (l + r) / 2;
		return getAns(l, m, i * 2, val) + getAns(m + 1, r, i * 2 + 1, val);
	}
}

namespace tree {
	vector<int> g[mxn];
	int anc[mxn], par[mxn], dep[mxn], pos[mxn], sub[mxn], t;
	long long sumX;

	void add(int x, int y) {
		g[x].pb(y);
		g[y].pb(x);
	}

	void precal(int to, int fr) {
		par[to] = fr;
		sub[to] = 1;
		for(int x : g[to]) {
			if(x == fr) continue;
			dep[x] = dep[to] + 1;
			precal(x, to);
			sub[to] += sub[x];
		}
	}

	void buildHLD(int to, int top) {
		anc[to] = top;
		pos[to] = ++t;
		int nxt = -1;
		for(int x : g[to]) {
			if(x == par[to]) continue;
			if(nxt == -1 || sub[x] > sub[nxt]) nxt = x;
		}
		if(~nxt) buildHLD(nxt, top);
		for(int x : g[to]) {
			if(x == par[to] || x == nxt) continue;
			buildHLD(x, x);
		}
	}

	void build() {
		sumX = 0;
		precal(0, -1);
		buildHLD(0, 0);
	}

	void addX(int x, long long val) {
		sumX += val;
		while(1) {
			if(anc[x] == 0) {
				segTree::addX(1, n, 1, pos[0], pos[x], val);
				break;
			} else {
				segTree::addX(1, n, 1, pos[anc[x]], pos[x], val);
				x = par[anc[x]];
			}
		}
	}
}

void init(int N, vector<int> U, vector<int> V, vector<int> T, vector<int> W) {
	n = N;
	for(int i = 0; i < n - 1; i++) {
		tree::add(U[i], V[i]);
	}
	tree::build();
	for(int i = 0; i < n; i++) {
		w[i] = W[i];
		tree::addX(i, w[i]);
	}
	for(int i = 0; i < n - 1; i++) {
		if(tree::dep[U[i]] > tree::dep[V[i]]) swap(U[i], V[i]);
		segTree::setT(1, n, 1, tree::pos[V[i]], T[i]);
	}
}

long long max_time(int S, int X) {
	tree::addX(S, -w[S] + X);
	w[S] = X;
	return segTree::getAns(1, n, 1, tree::sumX) * 2;
}
