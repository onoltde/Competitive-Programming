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

const int mxn = 510, inf = 1e9 + 10;
vector<int> g[mxn], p[mxn][mxn], adj[mxn];
int tmp[mxn], mn[mxn][mxn];

void go() {
	int m, n, l;
	cin >> m >> n >> l;
	vi gg(l);
	cin >> gg;
	for(int i = 1; i <= m; i++) {
		int sz;
		cin >> sz;

		for(int j = 1; j <= sz; j++) {
			cin >> tmp[j];
			g[tmp[j]].pb(i);
		}
		tmp[0] = tmp[sz];
		for(int j = 1; j <= sz; j++) {
			p[tmp[j]][tmp[j - 1]].pb(i);
			p[tmp[j - 1]][tmp[j]].pb(i);
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			for(int ii = 0; ii < p[i][j].size(); ii++) {
				for(int jj = ii + 1; jj < p[i][j].size(); jj++) {
					adj[p[i][j][ii]].pb(p[i][j][jj]);
					adj[p[i][j][jj]].pb(p[i][j][ii]);
				}
			}
		}
	}
	for(int i = 0; i < l; i++) {
		for(int j = 1; j <= m; j++) {
			mn[i][j] = inf;
		}
		int now = gg[i];
		queue<int> q;
		for(int x : g[now]) {
			mn[i][x] = 0;
			q.push(x);
		}
		while(q.size()) {
			int x = q.front(); q.pop();
			for(int nxt : adj[x]) {
				if(mn[i][nxt] == inf) {
					mn[i][nxt] = mn[i][x] + 1;
					q.push(nxt);
				}
			}
		}
	}
	pair<int, int> ans = {inf, inf};
	for(int i = 1; i <= m; i++) {
		int sum = 0;
		for(int j = 0; j < l; j++) {
			sum += mn[j][i];
		}
		mnn(ans, {sum, i});
	}
	cout << ans.ff << '\n' << ans.ss << '\n';
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