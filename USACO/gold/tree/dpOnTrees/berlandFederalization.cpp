#include<bits/stdc++.h>
using namespace std;

#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

// #define int long long
 
// typedef long long ll;
typedef vector<int> vi;
typedef set<int> si;
typedef multiset<int> msi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

template<typename T, typename U>
ostream & operator << (ostream &out, const pair<T, U> &c) {
	out << c.first << ' ' << c.second;
    return out;
}

template<typename T>
ostream & operator << (ostream &out, vector<T> &v) {
	const int sz = v.size();
	for (int i = 0; i < sz; i++) {
		if (i) out << ' ';
		out << v[i];
	}
    return out;
}

template<typename T>
istream & operator >> (istream &in, vector<T> &v) {
	for (T &x : v) in >> x;
    return in;
}


template<typename T>
void mxx(T &a, T b){if(b > a) a = b;}
template<typename T>
void mnn(T &a, T b){if(b < a) a = b;}

const int mxn = 410, inf = 1e9;
int id[mxn], par[mxn];
vector<vector<int>> ll[mxn];
vector<pii> g[mxn];
vector<int> dp[mxn];
int k;

void dfs(int to, int fr) {
	par[to] = fr;
	int sz = 0;
	for(auto it : g[to]) {
		int x = it.ff;
		int i = it.ss;
		if(x == fr) continue;
		sz++;
		id[x] = i;
		dfs(x, to);
	}
	dp[to][1] = sz;
	ll[to][1].pb(to);
	for(auto it : g[to]) {
		int x = it.ff;
		if(x == fr) continue;
		vector<vector<int>> nwll = ll[to];
		vector<int> nwdp = dp[to];
		for(int i = 1; i < k; i++) {
			for(int j = 1; j + i <= k; j++) {
				if(dp[to][i] == inf || dp[x][j] == inf) continue;
				if(nwdp[i + j] > dp[to][i] + dp[x][j] - 1) {
					nwdp[i + j] = dp[to][i] + dp[x][j] - 1;
					nwll[i + j].clear();
					nwll[i + j].insert(nwll[i + j].end(), ll[x][j].begin(), ll[x][j].end());
					nwll[i + j].insert(nwll[i + j].end(), ll[to][i].begin(), ll[to][i].end());
				}
			}
		}
		swap(dp[to], nwdp);
		swap(ll[to], nwll);
	}
	if(fr && dp[to][k] != inf) dp[to][k]++;
}

void go() {
	int n;
	cin >> n >> k;
	for(int i = 1; i < n; i++) {
		int x, y;
		cin >> x >> y;
		g[x].eb(y, i);
		g[y].eb(x, i);
	}
	for(int i = 1; i <= n; i++) {
		dp[i].resize(k + 1, inf);
		ll[i].resize(k + 1);
	}
	dfs(1, 0);
	int kk = 0;
	int ans = inf;
	for(int i = 1; i <= n; i++) {
		if(dp[i][k] <= ans) {
			ans = dp[i][k];
			kk = i;
		}
	}
	cout << ans << '\n';
	vector<int> v;
	vector<int> vis(n + 10, 0);
	for(int it : ll[kk][k]) {
		vis[it] = 1;
	}
	for(int it : ll[kk][k]) {
		for(auto tt : g[it]) {
			if(vis[tt.ff] == 0) {
				v.pb(tt.ss);
			}
		}
	}
	sort(all(v));
	cout << v << '\n';
}
 
signed main() {
	// #ifndef ONO
	// freopen("file.in", "r", stdin);
	// freopen("file.out", "w", stdout);
	// #endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}