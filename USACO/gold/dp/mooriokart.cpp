#include<bits/stdc++.h>
using namespace std;

#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

#define int long long

#define ll long long

template<typename T>
void mxx(T &a, T b){if(b>a) a=b;}
template<typename T>
void mnn(T &a, T b){if(b<a) a=b;}

const int mxn = 2510;
const int mod = 1e9 + 7;

vector<int> c[mxn];
vector<pair<int, int>> g[mxn];

int a[mxn][20];
int d[mxn];
int dd[mxn];
int cmp;
int vis[mxn];

void dfs(int to, int fr, int l) {
	vis[to] = 1;
	c[cmp].pb(to);
	d[to] = l;
	dd[to] = dd[fr] + 1;
	a[to][0] = fr;
	for(int i = 1; i < 15; i++) {
		a[to][i] = a[a[to][i - 1]][i - 1];
	}
	for(auto it : g[to]) {
		int x = it.ff;
		int d = it.ss;
		if(x == fr) {
			continue;
		}
		dfs(x, to, l + d);
	}
}

int lca(int x, int y) {
	if(dd[x] < dd[y]) {
		swap(x, y);
	}
	int dis = dd[x] - dd[y];
	for(int i = 0; i < 15; i++) {
		int l = (1 << i);
		if(l & dis) {
			x = a[x][i];
		}
	}
	if(x == y) {
		return x;
	}
	for(int i = 14; i >= 0; i--) {
		if(a[x][i] != a[y][i]) {
			x = a[x][i];
			y = a[y][i];
		}
	}
	return a[x][0];
}

int dis(int x, int  y) {
	int z = lca(x, y);
	return d[x] + d[y] - d[z] * 2;
}

signed main() {
	fast;
	#ifndef ONO
	freopen("mooriokart.in", "r", stdin);
	freopen("mooriokart.out", "w", stdout);
	#endif
	int n, m, x, y;
	cin >> n >> m >> x >> y;
	for(int i = 1; i <= m; i++) {
		int x, y, d;
		cin >> x >> y >> d;
		g[x].pb({y, d});
		g[y].pb({x, d});
	}
	for(int i = 1; i <= n; i++) {
		if(vis[i] == 0) {
			cmp++;
			dfs(i, 0, 0);
		}
	}

	vector<pair<int, int>> dp(y + 10, {0, 0});
	vector<pair<int, int>> tmp(y + 10, {0, 0});

	tmp[0].ff = 1; 

	int g1 = 1;
	for(int i = 1; i < cmp; i++) {
		g1 = (g1 * 2) % mod;
	}
	int g2 = 1;
	for(int i = 1; i < cmp; i++) {
		g2 = (g2 * i) % mod;
	}

	for(int i = 1; i <= cmp; i++) {
		dp = vector<pair<int, int>>(y + 10, {0, 0});
		vector<int> vis(y + 10, -1);
		vector<pair<int, int>> gg;
		int sum = 0, occ = 0;
		for(int ii = 0; ii < c[i].size(); ii++) {
			for(int jj = ii + 1; jj < c[i].size(); jj++) {
				int z = dis(c[i][ii], c[i][jj]) + x;
				occ++;
				sum = (sum + z) % mod;
				if(z > y) {
					gg.eb(z, 1);
				}
				else if(vis[z] == -1) {
					vis[z] = (int)gg.size();
					gg.eb(z, 1);
				}
				else {
					gg[vis[z]].ss++;
				}
				// for(int k = y; k >= 0 ; k--) {
				// 	int nxt = min(k + z, y);
				// 	dp[nxt].ff = (dp[nxt].ff + tmp[k].ff) % mod;
				// 	dp[nxt].ss = (dp[nxt].ss + z * tmp[k].ff + tmp[k].ss) % mod;
				// }
			}
		}
		sort(all(gg));
		vector<pair<int, int>> gp = gg;
		reverse(all(gp));
		for(int j = y; j >= 0; j--) {
			while(gp.size() && j + gp.back().ff < y) {
				sum -= gp.back().ff * gp.back().ss;
				occ -= gp.back().ss;
				while(sum < 0) {
					sum += mod;
				} 
				while(occ < 0) {
					occ += mod;
				}
				gp.pop_back();
			}
			dp[y].ff = (dp[y].ff + tmp[j].ff * occ) % mod;
			dp[y].ss = (dp[y].ss + (sum * tmp[j].ff % mod + tmp[j].ss * occ % mod)) % mod;
		}
		for(int j = y - 1; j >= 0; j--) {
			while(gg.size() && gg.back().ff > j) {
				gg.pop_back();
			}
			for(auto it : gg) {
				int k = j - it.ff;
				int z = it.ff;
				int cof = it.ss;
				dp[j].ff = (dp[j].ff + tmp[k].ff * cof) % mod;
				dp[j].ss = (dp[j].ss + ((z * tmp[k].ff) % mod * cof) % mod
									 + (tmp[k].ss * cof) % mod) % mod;
			}
		}
		swap(tmp, dp);
	}
	cout << (tmp[y].ss * g1 % mod * g2) % mod << '\n';
	return 0;
}