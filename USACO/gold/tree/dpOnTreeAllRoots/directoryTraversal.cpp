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

const int mxn = 1e5 + 10;
int a[mxn], cnt[mxn], in[mxn], out[mxn];
vector<int> g[mxn];

void dfs1(int to, int fr) {
	if(g[to].empty()) {
		cnt[to] = 1;
		return;
	}
	for(int x : g[to]) {
		if(x == fr) continue;
		dfs1(x, to);
		cnt[to] += cnt[x];
		in[to] += in[x] + (a[x] + 1) * cnt[x];
	}
}

void dfs2(int to, int fr) {
	int sum = 0;
	for(int x : g[to]) {
		if(x == fr) continue;
		sum += in[x] + (a[x] + 4) * cnt[x];
	}
	for(int x : g[to]) {
		if(x == fr) continue;
		out[x] = out[to] + (cnt[1] - cnt[to]) * 3 + sum - (in[x] + (a[x] + 4) * cnt[x]);
		dfs2(x, to);
	}
}

void go() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		string str;
		cin >> str;
		a[i] = str.size();
		int k;
		cin >> k;
		g[i].resize(k);
		cin >> g[i];
	}
	dfs1(1, 0);
	dfs2(1, 0);
	int ans = 1e18;
	for(int i = 1; i <= n; i++) {
		if(g[i].size() == 0) continue;
		mnn(ans, -cnt[1] + in[i] + out[i]);
	}
	cout << ans << '\n';
}
 
signed main() {
	#ifndef ONO
	freopen("dirtraverse.in", "r", stdin);
	freopen("dirtraverse.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}