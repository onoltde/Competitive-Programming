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
int p[mxn], in[mxn], out[mxn], tt;
vector<int> g[mxn];

void dfs(int to) {
	in[to] = ++tt;
	for(int x : g[to]) {
		dfs(x);
	}
	out[to] = tt;
}

void go() {
	int n;
	cin >> n;
	vector<int> val;
	for(int i = 1; i <= n; i++) {
		cin >> p[i];
		val.pb(p[i]);
	}
	sort(all(val));
	val.erase(unique(all(val)), val.end());
	vector<vector<int>> pp(n + 10); 
	for(int i = 1; i <= n; i++) {
		p[i] = lower_bound(all(val), p[i]) - val.begin() + 1;
		pp[p[i]].pb(i);
	}
	for(int i = 2; i <= n; i++) {
		int x;
		cin >> x;
		g[x].pb(i);
	}
	dfs(1);
	vector<int> fn(n + 10, 0), ans(n + 10, 0);
	auto get = [&](int l, int r) -> int {
		l--;
		int ret = 0;
		for(; l; l -= (l&-l)) ret -= fn[l];
		for(; r; r -= (r&-r)) ret += fn[r];
		return ret;
	};

	auto up = [&](int l) {
		for(; l <= n; l += (l&-l)) fn[l]++;
	};

	for(int i = n; i >= 1; i--) {
		for(int x : pp[i]) {
			ans[x] = get(in[x], out[x]);
		}
		for(int x : pp[i]) {
			up(in[x]);
		}
	}
	for(int i = 1; i <= n; i++) {
		cout << ans[i] << '\n';
	}
}
 
signed main() {
	#ifndef ONO
	freopen("promote.in", "r", stdin);
	freopen("promote.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}