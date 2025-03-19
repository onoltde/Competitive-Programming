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
const int inf = 1e9 + 10;
int par[mxn], a[mxn], n;
bool vis[mxn];
queue<int> q;
ll k;
vector<int> g[mxn];
pair<int, int> in[mxn], out[mxn], nx[mxn];

void dfs1(int to, int fr) {
	in[to] = {-inf, -inf};
	for(int x : g[to]) {
		if(x == fr) continue;
		dfs1(x, to);
		in[x].ff--;
		mxx(in[to], in[x]);
		mxx(in[to], nx[x]);
		in[x].ff++;
	}
}

multiset<pair<int, int>> s;

void dfs2(int to, int fr) {
	int sz = 0;
	s.clear();
	for(int x : g[to]) {
		if(x == fr) continue;
		sz++;
		s.in(nx[x]);
	}
	s.in(max(make_pair(out[to].ff - 1, out[to].ss), make_pair(a[to] - 1, -to)));
	sz = 0;
	for(int x : g[to]) {
		if(x == fr) continue;
		sz++;
		s.erase(s.find(nx[x]));
		out[x] = *s.rbegin();
		s.in(nx[x]);
	}
	for(int x : g[to]) {
		if(x == fr) continue;
		dfs2(x, to);
	}
}

int dfs(int to) {
	vis[to] = 1;
	q.push(to);
	if(vis[par[to]] == 0) return dfs(par[to]);
	else {
		while(q.front() != par[to]) {
			k--;
			q.pop();
			if(k == 0) return q.front();
		}
		ll tm = k % q.size();
		while(tm--) {
			q.pop();
		}
		return q.front();
	}
}

void go() {
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		nx[i] = make_pair(a[i] - 1, -i);
	}
	for(int i = 1; i < n; i++) {
		int x, y;
		cin >> x >> y;
		g[x].pb(y);
		g[y].pb(x);
	}
	if(n == 1) {
		cout << 1 << '\n';
		return;
	}
	dfs1(1, 0);
	for(int i = 1; i <= n; i++) {
		nx[i].ff--;
		nx[i] = max(nx[i], make_pair(in[i].ff - 2, in[i].ss));
	}
	out[1] = {-inf, -inf};
	dfs2(1, 0);
	for(int i = 1; i <= n; i++) {
		mxx(in[i], out[i]);
		par[i] = -in[i].ss;
	}
	cout << dfs(1) << '\n';
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