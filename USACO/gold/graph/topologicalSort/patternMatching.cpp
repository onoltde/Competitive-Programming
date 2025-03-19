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
vector<int> g[mxn], ans;
int vis[mxn];
bool ok;

void dfs(int to) {
	vis[to] = 1;
	for(int x : g[to]) {
		if(!vis[x]) dfs(x);
		else if(vis[x] == 1) ok = 0;
		if(!ok) return;
	}
	vis[to] = 2;
	ans.pb(to);
}

void go() {
	int n, m, k;
	cin >> n >> m >> k;
	map<string, int> mp;
	for(int i = 1; i <= n; i++) {
		string str;
		cin >> str;
		mp[str] = i;
	}
	for(int i = 1; i <= m; i++) {
		string str;
		int x;
		cin >> str >> x;
		bool is = 0;
		for(int j = 0; j < (1 << k); j++) {
			string ss = "";
			for(int p = 0; p < k; p++) {
				if(j >> p & 1) ss.pb('_');
				else ss.pb(str[p]);
			}
			if(mp.find(ss) != mp.end()) {
				int ret = mp[ss];
				if(ret == x) is = 1;
				else g[x].pb(ret);
			}
		}
		if(!is) {
			cout << "NO\n";
			return;
		}
	}
	ok = 1;
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) {
			dfs(i);
		}
	}
	if(!ok) {
		cout << "NO\n";
		return;
	}
	reverse(all(ans));
	cout << "YES\n" << ans << '\n';
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