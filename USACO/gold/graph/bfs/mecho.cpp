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

const int mxn = 810, inf = 1e9 + 10;
int g[mxn][mxn], n, s, bee[mxn][mxn], mn[mxn][mxn];
pii en, st;
vector<pii> h;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool ch(int m) {
	queue<pair<int, int>> q;
	if(bee[st.ff][st.ss] * s < m) return 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			mn[i][j] = inf;
	mn[st.ff][st.ss] = m;
	q.push(st);
	while(q.size()) {
		int x = q.front().ff;
		int y = q.front().ss;
		q.pop();
		for(int i = 0; i < 4; i++) {
			int fx = x + dx[i];
			int fy = y + dy[i];
			if(max(fx, fy) > n || min(fx, fy) < 1 || mn[fx][fy] != inf || g[fx][fy] || mn[x][y] + 1 > bee[x][y] * s) continue;
			mn[fx][fy] = mn[x][y] + 1;
			q.push({fx, fy});
		}
	}
	return mn[en.ff][en.ss] != inf;
}

void go() {
	cin >> n >> s;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			char ch;
			cin >> ch;
			if(ch == 'M') st = {i, j};
			else if(ch == 'D') en = {i, j};
			else if(ch == 'H') h.pb({i, j});
			else if(ch == 'T') g[i][j] = 1;
		}
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			bee[i][j] = inf;

	queue<pair<int, int>> q;
	for(auto it : h)
		q.push(it), bee[it.ff][it.ss] = 0;
	while(q.size()) {
		int x = q.front().ff;
		int y = q.front().ss;
		q.pop();
		for(int i = 0; i < 4; i++) {
			int fx = x + dx[i];
			int fy = y + dy[i];
			if(max(fx, fy) > n || min(fx, fy) < 1 || bee[fx][fy] != inf || g[fx][fy] || en == make_pair(fx, fy)) continue;
			bee[fx][fy] = bee[x][y] + 1;
			q.push({fx, fy});
		}	
	}
	int l = -1, r = (int)1e9;
	while(r - l > 1) {
		int m = (r + l) / 2;
		if(ch(m)) l = m;
		else r = m;
	}
	if(l != -1) l /= s;
	cout << l << '\n';
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