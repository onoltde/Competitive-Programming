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

const int inf = 1e9 + 10;
int dp[22][22][22][22][5][5], n;
char g[22][22];

int dx[] = {0, -1, 0, 1, 0};
int dy[] = {0, 0, 1, 0, -1};

int next(int x) {
	x--;
	if(x == 0) x = 4;
	return x;
}

int prev(int x) {
	x++;
	if(x == 5) x = 1;
	return x;
}

pair<int, int> get(int x, int y, int d) {
	pair<int, int> ret = {x, y};
	if(x == 1 && y == n) return ret;
	ret.ff += dx[d];
	ret.ss += dy[d];
	if(g[ret.ff][ret.ss] == 'H') ret = {x, y};
	return ret;
}

void go() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> g[i][j];
		}
	}
	for(int i = 0; i <= n + 1; i++) {
		g[i][0] = 'H';
		g[0][i] = 'H';
		g[i][n + 1] = 'H';
		g[n + 1][i] = 'H';
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			for(int ii = 1; ii <= n; ii++) {
				for(int jj = 1; jj <= n; jj++) {
					for(int p1 = 1; p1 <= 4; p1++) {
						for(int p2 = 1; p2 <= 4; p2++) {
							dp[i][j][ii][jj][p1][p2] = inf;
						}
					}
				}
			}
		}
	}
	dp[n][1][n][1][1][2] = 0;
	queue<array<int, 6>> q;
	q.push({n, 1, n, 1, 1, 2});
	while(q.size()) {
		array<int, 6> tmp = q.front(); q.pop();
		int x1 = tmp[0], y1 = tmp[1];
		int x2 = tmp[2], y2 = tmp[3];
		int d1 = tmp[4], d2 = tmp[5];
		int my = dp[x1][y1][x2][y2][d1][d2];
		if(dp[x1][y1][x2][y2][next(d1)][next(d2)] == inf) {
			dp[x1][y1][x2][y2][next(d1)][next(d2)] = my + 1;
			q.push({x1, y1, x2, y2, next(d1), next(d2)});
		}
		if(dp[x1][y1][x2][y2][prev(d1)][prev(d2)] == inf) {
			dp[x1][y1][x2][y2][prev(d1)][prev(d2)] = my + 1;
			q.push({x1, y1, x2, y2, prev(d1), prev(d2)});
		}
		pair<int, int> move1 = get(x1, y1, d1);
		pair<int, int> move2 = get(x2, y2, d2);
		x1 = move1.ff;
		y1 = move1.ss;
		x2 = move2.ff;
		y2 = move2.ss;
		if(dp[x1][y1][x2][y2][d1][d2] == inf) {
			dp[x1][y1][x2][y2][d1][d2] = my + 1;
			q.push({x1, y1, x2, y2, d1, d2});
		}
	}
	int ans = inf;
	for(int i = 1; i <= 4; i++) {
		for(int j = 1; j <= 4; j++) {
			mnn(ans, dp[1][n][1][n][i][j]);
		}
	}
	cout << ans << '\n';
}
 
signed main() {
	#ifndef ONO
	freopen("cownav.in", "r", stdin);
	freopen("cownav.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}