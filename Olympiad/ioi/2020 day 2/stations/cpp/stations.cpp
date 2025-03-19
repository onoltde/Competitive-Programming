#include "stations.h"
#include<bits/stdc++.h>
using namespace std;

#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

// #define int long long
 
typedef long long ll;
typedef vector<int> vi;
typedef set<int> si;
typedef multiset<int> msi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

vector<int> label(int n, int k, vector<int> u, vector<int> v) {
	vector<vector<int>> g(n);
	for(int i = 0; i < n - 1; i++) {
		g[u[i]].pb(v[i]);
		g[v[i]].pb(u[i]);
	}
	int t = 0;
	vector<int> ret(n);
	function<void(int, int, bool)> dfs = [&](int to, int fr, bool fl) {
		if(fl) ret[to] = t++;
		fl = !fl;
		for(int x : g[to]) {
			if(x == fr) continue;
			dfs(x, to, fl);
		}
		if(fl) ret[to] = t++;
	};
	dfs(0, -1, false);
	return ret;
}

int find_next_station(int s, int t, vector<int> c) {
	if(c.back() > s) {
		for(int i = 0; i + 1 < c.size(); i++) {
			if(t >= s && t <= c[i]) return c[i];
		}
		return c.back();
	} else {
		for(int i = (int)c.size() - 1; i > 0; i--) {
			if(t >= c[i] && t <= s) return c[i];
		}
		return c[0];
	}
	return 69;
}
