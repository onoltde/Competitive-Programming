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
int t[mxn], h[mxn], in[mxn], out[mxn], dp1[mxn], dp2[mxn];
bool vis[mxn];
vector<int> g[mxn];

void dfs(int to, int fr) {
	vis[to] = 1;
	vector<int> v;
	int now = 0;
	int sz = 0;
	for(int x : g[to]) {
		if(x == fr) continue;
		dfs(x, to);
		sz++;
		now += dp1[x];
		v.pb(dp2[x] - dp1[x]);
	}
	sort(v.rbegin(), v.rend());
	if(fr) {
		mxx(dp1[to], min(in[to] + 1, out[to] + sz) * t[to] + now);
		mxx(dp2[to], min(in[to], out[to] + sz + 1) * t[to] + now);
	} else {
		mxx(dp1[to], min(in[to], out[to] + sz) * t[to] + now);
	}
	int cnt = 0;
	for(int x : v) {
		cnt++;
		sz--;
		now += x;
		if(fr) {
			mxx(dp1[to], min(in[to] + 1 + cnt, out[to] + sz) * t[to] + now);
			mxx(dp2[to], min(in[to] + cnt, out[to] + sz + 1) * t[to] + now);
		} else {
			mxx(dp1[to], min(in[to] + cnt, out[to] + sz) * t[to] + now);
		}
	}
}

void go() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> t[i];
	}
	for(int i = 1; i <= n; i++) {
		cin >> h[i];
	}
	int ans = 0;
	for(int i = 1; i < n; i++) {
		int x, y;
		cin >> x >> y;
		ans += t[x] + t[y];
		if(h[x] < h[y]) swap(x, y);
		if(h[x] == h[y]) {
			g[x].pb(y);
			g[y].pb(x);
		} else {
			out[x]++;
			in[y]++;
		}
	}
	for(int i = 1; i <= n; i++) {
		if(vis[i]) continue;
		dfs(i, 0);
		ans -= dp1[i];
	}
	cout << ans << '\n';
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