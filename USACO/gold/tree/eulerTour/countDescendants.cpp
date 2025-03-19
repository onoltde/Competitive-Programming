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
int d[mxn], in[mxn], out[mxn], tt;
vector<int> g[mxn], k[mxn];

void dfs(int to) {
	in[to] = ++tt;
	for(int x : g[to]) {
		d[x] = d[to] + 1;
		dfs(x);
	}
	out[to] = tt;
}

void go() {
	int n;
	cin >> n;
	for(int i = 2; i <= n; i++) {
		int x;
		cin >> x;
		g[x].pb(i);
	}
	dfs(1);
	for(int i = 1; i <= n; i++) {
		k[d[i]].pb(in[i]);
	}
	for(int i = 0; i <= n; i++) {
		sort(all(k[i]));
	}
	int q;
	cin >> q;
	while(q--) {
		int u, d;
		cin >> u >> d;
		int l = lower_bound(all(k[d]), in[u]) - k[d].begin() - 1;
		int r = upper_bound(all(k[d]), out[u]) - k[d].begin() - 1;
		cout << r - l << '\n';
	}
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