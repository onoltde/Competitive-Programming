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

const int mxn = 2e5 + 10;
int deg[mxn], ban[mxn], vis[mxn], x[mxn], y[mxn], anc;
vector<int> tmp;
vector<vector<pair<int, int>>> g;

void dfs(int to, int fr) {
	for(auto it : g[to]) {
		if(it.ff == fr) continue;
		deg[to]++;
		dfs(it.ff, to);
	}
	for(auto it : g[to]) {
		if(it.ff == fr) continue;
		if(deg[it.ff] == 2) {
			deg[to]--;
			ban[it.ss] = 1;
		}
	}
	for(auto it : g[to]) {
		if(it.ff == fr) continue;
		if(ban[it.ss]) continue;
		if(deg[to] <= 2) break;
		deg[to]--;
		ban[it.ss] = 1;
	}
}

void dds(int to, int fr) {
	vis[to] = 1;
	int cnt = 0;
	for(auto it : g[to]) {
		if(it.ff == fr) continue;
		if(ban[it.ss]) continue;
		dds(it.ff, to);
		cnt++;
	}
	if(to == anc && cnt <= 1) {
		tmp.pb(to);
	}
	else if(cnt == 0) {
		tmp.pb(to);
	}
}

void go() {
	int n;
	cin >> n;
	g.clear();
	g.resize(n + 10);
	for(int i = 1; i < n; i++) {
		cin >> x[i] >> y[i];
		g[x[i]].eb(y[i], i);
		g[y[i]].eb(x[i], i);
	}
	dfs(1, 0);
	vector<pair<pii, pii>> ans;
	vector<pair<int, int>> sks;
	for(int i = 1; i <= n; i++) {
		if(vis[i] == 1) continue;
		tmp.clear();
		anc = i;
		dds(i, 0);
		sks.pb({tmp[0], tmp.back()});
	}
	for(int i = 1; i < sks.size(); i++) {
		ans.pb({{sks[i - 1].ss, sks[i].ff}, {0, 0}});
	}
	int now = 0;
	for(int i = 1; i < n; i++) {
		if(ban[i]) {
			ans[now].ss = {x[i], y[i]};
			now++;
		}
	}
	cout << ans.size() << '\n';
	for(auto it : ans) {
		cout << it.ss << ' ' << it.ff << '\n';
	}
	for(int i = 1; i <= n; i++) {
		ban[i] = 0;
		deg[i] = 0;
		vis[i] = 0;
	}
}
 
signed main() {
	// #ifndef ONO
	// freopen("file.in", "r", stdin);
	// freopen("file.out", "w", stdout);
	// #endif
	fast;
	int t = 1;
	cin >> t;
	while(t--) {
		go();
	}
	return 0;
}