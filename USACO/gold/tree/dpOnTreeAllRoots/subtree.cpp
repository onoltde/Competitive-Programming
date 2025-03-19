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
int n, m, in[mxn], out[mxn], a[mxn], b[mxn];
vector<int> g[mxn];

void dfs1(int to, int fr) {
	in[to] = 1;
	for(int x : g[to]) {
		if(x == fr) continue;
		dfs1(x, to);
		in[to] = (in[to] * (in[x] + 1)) % m;
	}
}

void dfs2(int to, int fr) {
	int sz = 0;
	for(int x : g[to]) {
		if(x == fr) continue;
		sz++;
		a[sz] = in[x] + 1;
		b[sz] = in[x] + 1;
	}
	a[0] = 1;
	b[sz + 1] = 1;
	for(int i = 1; i <= sz; i++) {
		a[i] = (a[i] * a[i - 1]) % m;
	}
	for(int i = sz; i >= 1; i--) {
		b[i] = (b[i] * b[i + 1]) % m;
	}
	sz = 0;
	for(int x : g[to]) {
		if(x == fr) continue;
		sz++;
		out[x] = (out[to] * a[sz - 1] % m * b[sz + 1] + 1) % m;
	}
	for(int x : g[to]) {
		if(x == fr) continue;
		dfs2(x, to);
	}
}

void go() {
	cin >> n >> m;
	for(int i = 1; i < n; i++) {
		int x, y;
		cin >> x >> y;
		g[x].pb(y);
		g[y].pb(x);
	}
	dfs1(1, 0);
	out[1] = 1;
	dfs2(1, 0);
	for(int i = 1; i <= n; i++) {
		cout << (in[i] * out[i] % m) << '\n';
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