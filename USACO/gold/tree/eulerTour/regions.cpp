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

const int mxn = 2e5 + 10, B = 400;
int cnt[610][25010], in[mxn], out[mxn], tt, kk[25010], s[mxn], h[mxn];
vector<int> g[mxn], p[25010], d[25010];

void dfs(int to) {
	in[to] = ++tt;
	d[h[to]].pb(in[to]);
	for(int x : g[to]) {
		dfs(x);
	}
	out[to] = tt;
}

void solve(int to, int cn, int id) {
	if (kk[id] > 600) exit(1);
	cnt[kk[id]][h[to]] += cn;
	cn += (h[to] == id);
	for(int x : g[to]) {
		solve(x, cn, id);
	}
	cn -= (h[to] == id);
}

void go() {
	int n, r, q;
	cin >> n >> r >> q;
	for(int i = 1; i<= n; i++) {
		if(i == 1)
			cin >> h[i];
		else
			cin >> s[i] >> h[i];
		p[h[i]].pb(i);
		if(i > 1) g[s[i]].pb(i);
	}
	dfs(1);
	tt = 0;
	for(int i = 1; i <= r; i++) {
		if(p[i].size() >= B) {
			kk[i] = ++tt;
			solve(1, 0, i);
		}
		sort(all(d[i]));
	}
	assert(tt <= 600);
	while(q--) {
		int r1, r2;
		cin >> r1 >> r2;
		if(p[r1].size() >= B) {
			cout << cnt[kk[r1]][r2] << '\n';
		}
		else {
			int ans = 0;
			for(int x : p[r1]) {
				int ll = lower_bound(all(d[r2]), in[x]) - d[r2].begin();
				int rr = upper_bound(all(d[r2]), out[x]) - d[r2].begin();
				ans += rr - ll;
			}
			cout << ans << '\n';
		}
		cout.flush();
	}
}
 
signed main() {
	// #ifndef
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