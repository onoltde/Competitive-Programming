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

const int mxn = 1010, inf = 1e9;
int dp[mxn][mxn];
bool con[mxn][mxn];
vector<int> g[mxn][26];

void go() {
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= m; i++) {
		int x, y;
		char c;
		cin >> x >> y >> c;
		c -= 'a';
		g[x][c].pb(y);
		g[y][c].pb(x);
		con[x][y] = 1;
		con[y][x] = 1;
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			dp[i][j] = inf;
		}
	}
	dp[1][n] = 0;
	int ans = inf;
	queue<array<int, 3>> q;
	q.push({0, 1, n});
	while(q.size()) {
		int x = q.front()[1];
		int y = q.front()[2];
		int my = q.front()[0];
		q.pop();
		if(x == y) {
			mnn(ans, my);
			continue;
		}
		if(con[x][y]) {
			mnn(ans, my + 1);
			continue;
		}
		if(dp[x][y] != my) continue;
		for(int i = 0; i < 26; i++) {
			for(int xx : g[x][i]) {
				for(int yy : g[y][i]) {
					if(dp[xx][yy] > my + 2) {
						dp[xx][yy] = my + 2;
						q.push({dp[xx][yy], xx, yy});
					}
				}
			}
		}
	}
	if(ans == inf) ans = -1;
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