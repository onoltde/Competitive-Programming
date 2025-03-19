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

const int mxn = 2e5 + 10, inf = 1e9;
int n, k, par[mxn], d[mxn];
bool on[mxn];
vector<int> g[mxn];
pair<int, int> in1[mxn], in2[mxn], out[mxn];

void init(int to, int fr) {
	auto it = find(all(g[to]), fr);
	par[to] = fr;
	d[to] = d[fr] + 1;
	if(it != g[to].end()) {
		g[to].erase(it);
	}
	for(int x : g[to]) {
		init(x, to);
	}
}

void dfs1(int to) {
	for(int x : g[to]) {
		dfs1(x);
		int tmp = in1[x].ff + 1;
		if(on[to] && on[x]) {
			tmp -= 2;
		}
		if(tmp > in1[to].ff) {
			in2[to] = in1[to];
			in1[to] = in1[x];
			in1[to].ff = tmp;
		} else if(tmp > in2[to].ff) {
			in2[to] = in1[x];
			in2[to].ff = tmp;
		}
	}
}

void dfs2(int to) {
	for(int x : g[to]) {
		int tmp = out[to].ff + 1;
		if(on[x] && on[to]) {
			tmp -= 2;
		}
		if(tmp > out[x].ff) {
			out[x] = out[to];
			out[x].ff = tmp;
		}
		int id = 0;
		tmp = 0;
		if(on[x] && on[to]) {
			tmp -= 2;
		}
		if(in1[to].ss == in1[x].ss) {
			tmp += in2[to].ff + 1;
			id = in2[to].ss;
		} else {
			tmp += in1[to].ff + 1;
			id = in1[to].ss;
		}
		if(tmp > out[x].ff) {
			out[x].ff = tmp;
			out[x].ss = id;
		}
		dfs2(x);
	}
}

void col(int to, int e) {
	if(to == e) {
		on[to] = 1;
		return;
	}
	for(int x : g[to]) {
		col(x, e);
		on[to] |= on[x];
	}
}

void go() {
	cin >> n >> k;
	for(int i = 1; i < n; i++) {
		int x, y;
		cin >> x >> y;
		g[x].pb(y);
		g[y].pb(x);
	}
	init(1, 0);
	for(int i = 1; i <= n; i++) {
		in1[i] = in2[i] = out[i] = make_pair(0, i);
	}
	dfs1(1);
	dfs2(1);
	int ans1 = 0;
	int s = 1, e = 1;
	for(int i = 1; i <= n; i++) {
		if(out[i].ff + in1[i].ff > ans1) {
			ans1 = out[i].ff + in1[i].ff;
			s = out[i].ss;
			e = in1[i].ss;
		}
		if(in2[i].ff + in1[i].ff > ans1) {
			ans1 = in2[i].ff + in1[i].ff;
			s = in2[i].ss;
			e = in1[i].ss;
		}
	}
	if(k == 1) {
		cout << n * 2 - 2 - (ans1 - 1) << '\n';
		return;
	}
	while(e != s) {
		if(d[e] < d[s]) swap(e, s);
		on[e] = 1;
		e = par[e];
	}
	on[e] = 1;
	for(int i = 1; i <= n; i++) {
		in1[i] = in2[i] = out[i] = make_pair(0, i);
	}
	dfs1(1);
	dfs2(1);
	int ans2 = 0;
	for(int i = 1; i <= n; i++) {
		mxx(ans2, in1[i].ff + in2[i].ff);
		mxx(ans2, in1[i].ff + out[i].ff);
	}
	cout << n * 2 - 2 - (ans1 + ans2 - 2) << '\n';
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