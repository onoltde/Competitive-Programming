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
 
typedef long long ll;
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

const int mxn = 1e6 + 10, inf = 1e9;
int par[mxn], cnt[mxn];
array<int, 2> dp[mxn];
vector<int> g[mxn];
bool vis[mxn];

void dfs(int to) {
	dp[to][1] = 1;
	vis[to] = 1;
	if(g[to].size() == 0) dp[to][0] = -inf;
	for(int x : g[to]) {
		if(vis[x]) continue;
		dfs(x);
		dp[to][0] += max(dp[x][0], dp[x][1]);
		dp[to][1] += dp[x][0];
	}
}

void go() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> par[i];
		g[par[i]].pb(i);
		cnt[par[i]]++;
	}
	int ans1 = 0, ans2 = 0;
	for(int i = 1; i <= n; i++) {
		if(cnt[i] == 0) ans1++;
	}
	for(int i = 1; i <= n; i++) {
		if(vis[i] == 0) {
			int x = i;
			int y = par[i];
			while(x != y) {
				x = par[x];
				y = par[par[y]];
			}
			vector<int> path;
			path.pb(x);
			while(par[path.back()] != x) {	
				path.pb(par[path.back()]);
			}
			if(path.size() == 1) {
				dfs(path[0]);
				ans2 += dp[path[0]][0];
				continue;
			}
			ans1++;
			for(int x : path) {
				if(g[x].size() != 1) {
					ans1--;
					break;
				}
			}
			for(int x : path) {
				vis[x] = 1;
			}
			for(int x : path) {
				dfs(x);
			}
			vector<array<int, 2>> k;
			for(int x : path) k.pb(dp[x]);
			k[0][0] = -inf;
			for(int i = 1; i < k.size(); i++) {
				k[i][0] += max(k[i - 1][0], k[i - 1][1]);
				k[i][1] += k[i - 1][0];
			}
			int mx = k.back()[0];
			k.clear();
			for(int x : path) k.pb(dp[x]);
			k[0][1] = -inf;
			for(int i = 1; i < k.size(); i++) {
				k[i][0] += max(k[i - 1][0], k[i - 1][1]);
				k[i][1] += k[i - 1][0];
			}
			mxx(mx, k.back()[0]);
			mxx(mx, k.back()[1]);
			ans2 += mx;
		}
	}
	cout << n - ans2 << ' ' << n - ans1 << '\n';
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