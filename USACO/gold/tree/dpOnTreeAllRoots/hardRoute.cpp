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

const int mxn = 5e5 + 10;
int n, ans1, ans2;
vector<int> g[mxn];
pair<int, int> d[mxn];

void init(int to, int fr) {
	auto it = find(all(g[to]), fr);
	if(it != g[to].end()) {
		g[to].erase(it);
	}
	d[to] = {0, 1};
	for(int x : g[to]) {
		init(x, to);
		if(d[x].ff + 1 > d[to].ff) {
			d[to] = d[x];
			d[to].ff++;
		} else if(d[x].ff + 1 == d[to].ff) {
			d[to].ss += d[x].ss;
		}
	}
}

void dfs(int to, int mx, int cnt) {
	vector<pair<int, int>> v;
	if(to != 1 && cnt) {
		v.pb({mx, cnt});
	}
	for(int x : g[to]) {
		v.pb({d[x].ff + 1, d[x].ss});
	}
	sort(v.rbegin(), v.rend());
	if(v.size() >= 3) {
		int nmx = (v[0].ff * (v[1].ff + v[2].ff)), ncnt = 0;
		int sum = 0;
		for(auto it : v) {
			if(it.ff == v[2].ff) {
				sum += it.ss;
			}
		}
		if(v[1].ff == v[2].ff) {
			ncnt = sum * sum;
			for(auto it : v) {
				if(it.ff == v[2].ff) {
					ncnt -= it.ss * it.ss;
				}
			}
			ncnt /= 2;
		} else if(v[1].ff == v[0].ff) {
			ncnt = (v[0].ss + v[1].ss) * sum;
		} else {
			ncnt = v[1].ss * sum;
		}
		if(nmx > ans1) {
			ans1 = nmx;
			ans2 = ncnt;
		} else if(nmx == ans1) {
			ans2 += ncnt;
		}
	}
	pair<int, int> mx1, mx2;
	mx1 = mx2 = make_pair(0, 0);
	if(cnt) mx1 = make_pair(mx + 1, cnt);
	for(int x : g[to]) {
		if(d[x].ff + 2 > mx1.ff) {
			mx2 = mx1;
			mx1 = d[x];
			mx1.ff += 2;
		} else if(d[x].ff + 2 == mx1.ff) {
			mx1.ss += d[x].ss;
		} else if(d[x].ff + 2 > mx2.ff) {
			mx2 = d[x];
			mx2.ff += 2;
		} else if(d[x].ff + 2 == mx2.ff) {
			mx2.ss += d[x].ss;
		}
	}
	for(int x : g[to]) {
		if(d[x].ff + 2 == mx1.ff) {
			if(d[x].ss == mx1.ss) {
				dfs(x, mx2.ff, mx2.ss);
			} else {
				dfs(x, mx1.ff, mx1.ss - d[x].ss);
			}
		} else {
			dfs(x, mx1.ff, mx1.ss);
		}
	}
}

void go() {
	cin >> n;
	for(int i = 1; i < n; i++) {
		int x, y;
		cin >> x >> y;
		g[x].pb(y);
		g[y].pb(x);
	}
	ans1 = 0;
	ans2 = 1;
	if(n == 2) {
		cout << ans1 << ' ' << ans2 << '\n';
		return;
	}
	int root = 1;
	for(int i = 1; i <= n; i++) {
		if(g[i].size() > 1) {
			root = i;
		}
	}
	init(root, 0);
	dfs(root, 0, 0);
	cout << ans1 << ' ' << ans2 << '\n';
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