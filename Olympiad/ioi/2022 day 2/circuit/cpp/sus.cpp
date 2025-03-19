#include "circuit.h"
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

const int mxn = 2e5 + 10;
const long long mod = 1000002022;
int n, m, par[mxn];
long long pp[mxn][2];
vector<long long> dp[mxn];
bool a[mxn];
vector<int> g[mxn];

void dfs(int to) {
	pp[to][0] = pp[to][1] = 0;
	if(to >= n) {
		if(a[to]) pp[to][1] = 1;
		else pp[to][0] = 1;
		return;
	}
	dp[to].clear();
	dp[to].resize(g[to].size() + 1);
	dp[to][0] = 1;
	for(int x : g[to]) {
		dfs(x);
		for(int j = g[to].size(); j > 0; j--) {
			dp[to][j] = ((dp[to][j] * pp[x][0]) + (dp[to][j - 1] * pp[x][1])) % mod;
		}
		dp[to][0] = (dp[to][0] * pp[x][0]) % mod;
	}
	pp[to][0] = (dp[to][0] * (long long)g[to].size()) % mod;
	for(int i = 1; i <= g[to].size(); i++) {
		pp[to][1] = (pp[to][1] + dp[to][i] * (long long)i) % mod;
		pp[to][0] = (pp[to][0] + dp[to][i] * (long long)(g[to].size() - i)) % mod;
	}
}

void dfsup(int to) {
	pp[to][0] = pp[to][1] = 0;
	if(to >= n) {
		if(a[to]) pp[to][1] = 1;
		else pp[to][0] = 1;
		dfsup(par[to]);
		return;
	}
	dp[to].clear();
	dp[to].resize(g[to].size() + 1);
	dp[to][0] = 1;
	for(int x : g[to]) {
		for(int j = g[to].size(); j > 0; j--) {
			dp[to][j] = ((dp[to][j] * pp[x][0]) + (dp[to][j - 1] * pp[x][1])) % mod;
		}
		dp[to][0] = (dp[to][0] * pp[x][0]) % mod;
	}
	pp[to][0] = (dp[to][0] * (long long)g[to].size()) % mod;
	for(int i = 1; i <= g[to].size(); i++) {
		pp[to][1] = (pp[to][1] + dp[to][i] * (long long)i) % mod;
		pp[to][0] = (pp[to][0] + dp[to][i] * (long long)(g[to].size() - i)) % mod;
	}
	if(to) dfsup(par[to]);
}

void init(int n, int m, vector<int> p, vector<int> a) {
	::n = n;
	::m = m;
	par[0] = -1;
	for(int i = 1; i < n + m; i++) {
		g[p[i]].pb(i);
		par[i] = p[i];
	}
	for(int i = 0; i < m; i++) {
		::a[i + n] = a[i];
	}
	dfs(0);
}

int count_ways(int L, int R) {
	for(int i = L; i <= R; i++) {
		a[i] = a[i] ^ 1;
	}
	if(L < R) dfs(0);
	else dfsup(L);
	// cout << pp[0][1] << '\n';
	// for(int i = 0; i < n + m; i++) {
	// 	cout << pp[i][0] << ' ' << pp[i][1] << '\n';
	// }
	// cout << " sus \n";
	return pp[0][1];
}
