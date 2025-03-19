#include "supertrees.h"
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

const int mxn = 1010;
int par[mxn];

int get(int x) {
	return (x == par[x] ? x : par[x] = get(par[x]));
}

void unite(int x, int y) {
	x = get(x); y = get(y);
	if(x == y) return;
	par[y] = x;
}

void setDsu(int n) {
	for(int i = 0; i < n; i++) {
		par[i] = i;
	}
}

int construct(vector<vector<int>> p) {
	int n = p.size();
	vector<vector<int>> answer(n, vector<int>(n));
	//1
	setDsu(n);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(p[i][j] != 0) {
				unite(i, j);
			}
		}
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(get(i) == get(j) && p[i][j] == 0) {
				return 0;
			}
		}
	}
	//2
	setDsu(n);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(p[i][j] == 1) {
				unite(i, j);
			}
		}
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(get(i) == get(j) && p[i][j] == 2) {
				return 0;
			}
		}
	}
	//3
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(p[i][j] == 3) {
				return 0;
			}
		}
	}
	//----------
	auto link = [&](int x, int y) -> void {
		if(x == y) return;
		answer[x][y] = answer[y][x] = 1;
	};
	vector<int> vis(n);
	for(int i = 0; i < n; i++) {
		if(vis[i]) continue;
		vector<int> line{i};
		vis[i] = 1;
		for(int j = i + 1; j < n; j++) {
			if(get(i) == get(j)) line.pb(j), vis[j] = 1;
		}
		set<int> s;
		for(int j = 0; j < n; j++) {
			if(p[i][j] == 2) {
				s.in(get(j));
			}
		}
		s.in(i);
		if(s.size() == 2) {
			return 0;
		}
		for(int j = 0; j + 1 < line.size(); j++) {
			link(line[j], line[j + 1]);
		}
		int ls = *s.rbegin();
		for(int x : s) {
			link(x, ls);
			ls = x;
		}
	}
	build(answer);
	return 1;
}
