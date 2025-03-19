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

const int mxn = 2e5 + 10;
int v[mxn][2], done[mxn], tp[mxn], tot;
vector<int> g[mxn][2];
set<int> em;
vector<pair<int, int>> ans;

void add(int x, int y) {
	ans.eb(x, y);
	int id1 = (v[x][1] > 0), id2 = (v[y][0] > 0);
	int val = v[x][id1];
	g[val][id1].erase(find(all(g[val][id1]), x));
	g[val][id2].pb(y);
	v[x][id1] = 0;
	v[y][id2] = val;
	if(id1 == 0) em.in(x);
	if(id2 == 0) em.erase(y);
}

void clearTop(int x) {
	if(done[x] || tp[x] != 2) return;
	if(em.size() == 0) {
		cout << -1 << '\n';
		exit(0);
	}
	int emp = *em.begin();
	add(g[x][1][0], emp);
	add(g[x][1][1], emp);
	done[x] = 1;
	tot--;
}

void dfs1(int x) {
	if(done[x] || tp[x] != 3) return;
	if(v[g[x][0][0]][1] == 0) {
		int nxt = g[x][1][0];
		add(g[x][1][0], g[x][0][0]);
		done[x] = 1;
		tot--;
		dfs1(v[nxt][0]);
	}
}

void dfs2(int x) {
	if(done[x] || tp[x] == 2) return;
	if(tp[x] == 1) {
		int x1 = g[x][0][0], x2 = g[x][0][1];
		if(v[x1][1] == 0 && v[x2][1] == 0) {
			add(x1, x2);
			done[x] = 1;
			tot--;
		} else if(v[x1][1] == 0 || v[x2][1] == 0) {
			int obs = max(v[x2][1], v[x1][1]);
			int pos = (v[x1][1] ? x1 : x2);
			if(tp[obs] != 2) return;
			int nxt = g[obs][1][0] ^ g[obs][1][1] ^ pos;
			nxt = v[nxt][0];
			clearTop(obs);
			add(x1, x2);
			done[x] = 1;
			tot--;
			dfs2(nxt);
		}
	} else {
		int pos = g[x][0][0], nxt = v[g[x][1][0]][0];
		if(v[pos][1]) return;
		add(g[x][1][0], g[x][0][0]);
		done[x] = 1;
		tot--;
		dfs2(nxt);
	}	
}

void go() {
	int n, m;
	cin >> n >> m;
	tot = n;
	for(int i = 1; i <= m; i++) {
		for(int j = 0; j < 2; j++) {
			cin >> v[i][j];
			if(v[i][j]) g[v[i][j]][j].pb(i);
		}
		if(v[i][0] == 0 && v[i][1] == 0) em.in(i);
	}

	for(int i = 1; i <= n; i++) {
		if(g[i][0].size() && g[i][1].size()) tp[i] = 3;
		else if(g[i][0].size()) tp[i] = 1;
		else tp[i] = 2;
	}
	for(int i = 1; i <= n; i++) {
		if(tp[i] == 3 && g[i][0][0] == g[i][1][0]) done[i] = 1;
		else if(tp[i] == 1) {
			int x = g[i][0][0], y = g[i][0][1];
			if(v[x][1] == 0 && v[y][1] == 0) {
				done[i] = 1;
				add(x, y);
			}
		}
		tot -= done[i];
	}
	while(tot > 0) {
		for(int i = 1; i <= n; i++) {
			if(done[i]) continue;
			dfs1(i);
		}

		for(int i = 1; i <= n; i++) {
			if(done[i]) continue;
			dfs2(i);
		}
		bool found = 0;
		for(int i = 1; i <= n; i++) {
			if(tp[i] != 3 || done[i]) continue;
			int x1 = g[i][1][0], x2 = g[i][1][1];
			int val1 = v[x1][0], val2 = v[x2][0];
			if(tp[val1] == 3 || tp[val2] == 3) {
				clearTop(i);
				found = 1;
				break;
			}
		}
		if(!found) {
			for(int i = 1; i <= n; i++) {
				if(tp[i] != 3 || done[i]) continue;
				clearTop(i);
				found = 1;
				break;
			}
		}
		if(!found) {
			cout << -1 << '\n';
			return;
		}
	}

	cout << ans.size() << '\n';
	for(auto it : ans) {
		cout << it << '\n';
	}
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