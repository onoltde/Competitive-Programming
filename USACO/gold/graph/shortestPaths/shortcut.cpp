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

const int inf = 1e18;
const int mxn = 1e4 + 10;
pair<int, int> mn[mxn];
vector<pair<int, int>> g[mxn];
int c[mxn], vis[mxn], cnt[mxn];

void go() {
	int n, m, t;
	cin >> n >> m >> t;
	for(int i = 1; i <= n; i++) {
		cin >> c[i];
		mn[i] = {1e18, 0};
	}
	for(int i = 1; i <= m; i++) {
		int x, y, d;
		cin >> x >> y >> d;
		g[x].pb({y, d});
		g[y].pb({x, d});
	}
	mn[1] = {0, 1};
	priority_queue<pair<int, int>> q;
	q.push({0, -1});
	while(q.size()) {
		int x = -q.top().ss; q.pop();
		if(vis[x]) continue;
		vis[x] = 1;
		for(auto [y, d] : g[x]) {
			if(mn[y] > make_pair(mn[x].ff + d, x)) {
				mn[y] = make_pair(mn[x].ff + d, x);
				q.push({-mn[y].ff, -y});
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		int tmp = i;
		while(tmp != 1) {
			cnt[tmp] += c[i];
			tmp = mn[tmp].ss;
		}
		cnt[1] += c[i];
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		if(mn[i].ff > t) {
			mxx(ans, cnt[i] * (mn[i].ff - t));
		}
	}
	cout << ans << '\n';
}
 
signed main() {
	#ifndef ONO
	freopen("shortcut.in", "r", stdin);
	freopen("shortcut.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}