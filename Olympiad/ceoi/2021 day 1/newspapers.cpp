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

const int mxn = 3e5 + 10;
vector<int> g[mxn];
int is[mxn], mx[mxn];

void dfs(int to, int fr = 0) {
	mx[to] = 0;
	for(int x : g[to]) {
		if(is[x] || x == fr) continue;
		dfs(x, to);
		mxx(mx[to], mx[x] + 1);
	}
}

void go() {
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= m; i++) {
		int x, y; cin >> x >> y;
		g[x].pb(y);
		g[y].pb(x);
	}
	if(m != n - 1) {
		cout << "NO\n";
		return;
	}
	if(n == 1) {
		cout << "YES\n1\n1\n";
		return;
	}
	auto bfs = [&](int st) -> vector<int> {
		vector<int> ret(n + 1, -1);
		ret[0] = -2;
		ret[st] = 0;
		queue<int> q;
		q.push(st);
		while(q.size()) {
			int x = q.front();
			q.pop();
			for(int y : g[x]) {
				if(ret[y] != -1) continue;
				ret[y] = ret[x] + 1;
				q.push(y);
			}
		}
		return ret;
	};
	auto dis = bfs(1);
	int l = max_element(all(dis)) - dis.begin();
	dis = bfs(l);
	int r = max_element(all(dis)) - dis.begin();
	vector<int> path;
	while(r != l) {
		path.pb(r);
		is[r] = 1;
		for(int x : g[r]) {
			if(dis[x] == dis[r] - 1) {
				r = x;
				break;
			}
		}
	}
	path.pb(l);
	is[l] = 1;
	for(int x : path) {
		dfs(x);
		if(mx[x] >= 3) {
			cout << "NO\n";
			exit(0);
		}
	}
	vector<int> ans;
	for(int x : path) {
		ans.pb(x);
		for(int y : g[x]) {
			if(is[y] || mx[y] == 0) continue;
			ans.pb(y);
			ans.pb(x);
		}
	}
	if(ans.size() > 1) {
		ans.erase(ans.begin());
	}
	if(ans.size() > 1) {
		ans.pop_back();
	}
	ans.insert(ans.end(), ans.rbegin(), ans.rend());
	cout << "YES\n";
	cout << ans.size() << '\n';
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