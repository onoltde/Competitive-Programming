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
set<pair<int, int>> s[mxn];
vector<int> g[mxn];
int lz[mxn * 4], d[mxn * 4];
int in[mxn], out[mxn], tt;

void dfs(int to, int fr) {
	in[to] = ++tt;
	for(int x : g[to]) {
		if(x == fr) continue;
		dfs(x, to);
	}
	out[to] = tt;
}

void pro(int i, int l, int r) {
	d[i] += lz[i] * (r - l + 1);
	if(l < r) {
		lz[i * 2] += lz[i];
		lz[i * 2 + 1] += lz[i];
	}
	lz[i] = 0;
}

void update(int l, int r, int i, int x, int y, int val) {
	pro(i, l, r);
	if(l > y || r < x) {
		return;
	}
	if(l >= x && r <= y) {
		lz[i] += val;
		pro(i, l, r);
		return;
	}
	int m = (l + r) / 2;
	update(l, m, i * 2, x, y, val);
	update(m + 1, r, i * 2 + 1, x, y, val);
	d[i] = d[i * 2] + d[i * 2 + 1];
}

int query(int l, int r, int i, int x, int y) {
	pro(i, l, r);
	if(l > y || r < x) return 0;
	if(l >= x && r <= y) return d[i];
	int m = (l + r) / 2;
	return query(l, m, i * 2, x, y) + query(m + 1, r, i * 2 + 1, x, y);
}

void go() {
	int n, q;
	cin >> n >> q;
	for(int i = 1; i < n; i++) {
		int x, y;
		cin >> x >> y;
		g[x].pb(y);
		g[y].pb(x);
	}
	dfs(1, 0);
	for(int i = 1; i <= q; i++) {
		int tp, x;
		cin >> tp >> x;
		if(tp == 1) {
			int c;
			cin >> c;
			auto it = s[c].upper_bound({in[x], out[x]});
			if(it != s[c].begin()) {
				it--;
				auto val = *it;
				if(val.ff <= in[x] && val.ss >= out[x]) {
					continue;
				}
			}
			update(1, n, 1, in[x], out[x], 1);
			while(1) {
				auto it = s[c].lower_bound({in[x], out[x]});
				if(it == s[c].end()) break;
				auto val = *it;
				if(val.ff > out[x]) break;
				update(1, n, 1, val.ff, val.ss, -1);
				s[c].erase(it);
			}
			s[c].in({in[x], out[x]});
		} else {
			cout << query(1, n, 1, in[x], out[x]) << '\n';
		}
	}
}
 
signed main() {
	#ifndef ONO
	freopen("snowcow.in", "r", stdin);
	freopen("snowcow.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}