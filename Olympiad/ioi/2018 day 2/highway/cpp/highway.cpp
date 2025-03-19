#include "highway.h"
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

const int mxn = 1e5 + 10;
vector<int> g[mxn], V[mxn];

void find_pair(int n, vector<int> u, vector<int> v, int A, int B) {
	int m = u.size();
	for(int i = 0; i < m; i++) {
		g[u[i]].pb(v[i]);
		g[v[i]].pb(u[i]);
		V[v[i]].pb(i);
		V[u[i]].pb(i);
	}
	long long tot = ask(vector<int>(m));
	int l = 0, r = m - 1;
	while(l < r) {
		int mid = (r + l) / 2;
		vector<int> q(m);
		for(int i = 0; i <= mid; i++) {
			q[i] = 1;
		}
		if(ask(q) == tot) l = mid + 1;
		else r = mid;
	}
	int x = u[l], y = v[l], ans1, ans2;

	auto bfs = [&](int st) -> vector<int> {
		vector<int> ret(n, -1);
		ret[st] = 0;
		queue<int> q;
		q.push(st);
		while(q.size()) {
			int x = q.front();
			q.pop();
			for(int y : g[x]) {
				if(ret[y] != -1) continue;
				ret[y] = ret[x] + 1;
				q.push(y);
			}
		}
		return ret;
	};

	auto disX = bfs(x);
	auto disY = bfs(y);

	vector<int> vec;
	for(int i = 0; i < n; i++) {
		if(disX[i] < disY[i]) vec.pb(i);
	}
	sort(all(vec), [&](int it1, int it2) {
		return disX[it1] < disX[it2];
	});

	l = 0, r = vec.size();

	while(r - l > 1) {
		int mid = (l + r) / 2;
		vector<int> q(m);
		for(int i = mid; i < vec.size(); i++) {
			for(int id : V[vec[i]]) {
				q[id] = 1;
			}
		}
		if(ask(q) == tot) r = mid;
		else l = mid;
	}

	ans1 = vec[l];

	vec.clear();

	for(int i = 0; i < n; i++) {
		if(disY[i] < disX[i]) vec.pb(i);
	}
	sort(all(vec), [&](int it1, int it2) {
		return disY[it1] < disY[it2];
	});

	l = 0, r = vec.size();

	while(r - l > 1) {
		int mid = (l + r) / 2;
		vector<int> q(m);
		for(int i = mid; i < vec.size(); i++) {
			for(int id : V[vec[i]]) {
				q[id] = 1;
			}
		}
		if(ask(q) == tot) r = mid;
		else l = mid;
	}

	ans2 = vec[l];

	answer(ans1, ans2);
}
