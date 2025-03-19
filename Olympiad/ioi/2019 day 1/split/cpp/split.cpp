#include "split.h"
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
int a, b, c, n, t, in[mxn], lo[mxn], par[mxn], sub[mxn];
vector<int> ans, g[mxn];
bool vis[mxn];
pair<int, int> M;

void dfs(int to, int fr) {
	in[to] = lo[to] = ++t;
	vis[to] = true;
	sub[to] = 1;
	par[to] = fr;
	for(int x : g[to]) {
		if(x == fr) continue;
		if(vis[x]) {
			lo[to] = min(lo[to], in[x]);
		} else {
			dfs(x, to);
			sub[to] += sub[x];
			lo[to] = min(lo[to], lo[x]);
		}
	}
	if(sub[to] >= a) {
		M = min(M, {sub[to], to});
	}
}

void dfs2(int to) {
	if(n - M.ff >= a) return;
	if(lo[to] < in[M.ss] && M.ss != to) {
		vis[to] = 1;
		M.ff -= sub[to];
		return;
	}
	for(int x : g[to]) {
		if(par[x] == to) {
			dfs2(x);
		}
	}
}

int cnt;
void dfs3(int to) {
	if(vis[to] || cnt == a) return;
	ans[to] = 1;
	cnt++;
	for(int x : g[to]) {
		if(par[x] == to) {
			dfs3(x);
		}
	}
}

vector<int> find_split(int N, int A, int B, int C, vector<int> p, vector<int> q) {
	n = N;
	ans.resize(n);
	for(int i = 0; i < q.size(); i++) {
		g[p[i]].pb(q[i]);
		g[q[i]].pb(p[i]);
	}
	vector<pair<int, int>> pos{{A, 1}, {B, 2}, {C, 3}};
	sort(all(pos));
	a = pos[0].ff; b = pos[1].ff; c = pos[2].ff;
	M = {n + 1, -1};
	dfs(0, -1);
	for(int i = 0; i < n; i++) {
		vis[i] = 0;
	}
	dfs2(M.ss);
	if(n - M.ff < a) return vector<int>(n);
	bool did = (n - M.ff < b);
	if(did) swap(a, b);
	dfs3(M.ss);
	for(int i = 0; i < n; i++) {
		vis[i] = false;
	}
	for(int i = 0; i < n; i++) {
		if(vis[i] || ans[i]) continue;
		queue<int> q;
		q.push(i);
		vector<int> ver;
		while(q.size()) {
			int to = q.front(); q.pop();
			ver.pb(to);
			vis[to] = 1;
			for(int x : g[to]) {
				if(ans[x] || vis[x]) continue;
				vis[x] = 1;
				q.push(x);
			}
		}
		if(ver.size() >= b) {
			for(int i = 0; i < b; i++) {
				ans[ver[i]] = 2;
			}
			break;
		}
	}
	for(int i = 0; i < n; i++) {
		if(!ans[i]) ans[i] = 3;
		else if(did) ans[i] ^= 3;
		ans[i] = pos[ans[i] - 1].ss;
	}
	return ans;
}
