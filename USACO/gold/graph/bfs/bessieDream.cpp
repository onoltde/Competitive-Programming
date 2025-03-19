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

const int mxn = 1001, inf = 1e9 + 10;
int g[mxn][mxn], dp[mxn][mxn][5][2];

int dx[] = {0, -1, 0, 1, 0};
int dy[] = {0, 0, 1, 0, -1};

void go() {
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			for(int ii = 0; ii <= 4; ii++) {
				dp[i][j][ii][0] = dp[i][j][ii][1] = inf;
			}
			cin >> g[i][j];
		}
	}
	queue<array<int, 4>> q;
	q.push({1, 1, 0, 0});
	dp[1][1][0][0] = 0;

	while(q.size()) {
		array<int, 4> tmp = q.front(); q.pop();
		int x = tmp[0];
		int y = tmp[1];
		int s = tmp[3];
		int d = tmp[2];
		int my = dp[x][y][d][s];
		if(g[x][y] == 4) {
			int fx = x + dx[d];
			int fy = y + dy[d];
			if(!(fx > n || fx < 1 || fy > m || fy < 1) && g[fx][fy] != 0 && g[fx][fy] != 3) {
				int nwd = (g[fx][fy] == 4 ? d : 0);
				int nws = (g[fx][fy] == 2 ? 1 : s);
				if(dp[fx][fy][nwd][nws] > my + 1) {
					dp[fx][fy][nwd][nws] = my + 1;
					q.push({fx, fy, nwd, nws});
				}
				continue;
			}
		}
		for(int i = 1; i <= 4; i++) {
			int fx = x + dx[i];
			int fy = y + dy[i];
			if(fx > n || fy > m || fx < 1 || fy < 1 || g[fx][fy] == 0) continue; 
			if(g[fx][fy] == 4 && dp[fx][fy][i][0] > my + 1) {
				dp[fx][fy][i][0] = my + 1;
				q.push({fx, fy, i, 0});
			}
			else if(g[fx][fy] == 3 && s && dp[fx][fy][0][s] > my + 1) {
				dp[fx][fy][0][s] = my + 1;
				q.push({fx, fy, 0, s});
			}
			else if(g[fx][fy] == 2 && dp[fx][fy][0][1] > my + 1) {
				dp[fx][fy][0][1] = my + 1;
				q.push({fx, fy, 0, 1});
			}
			else if(g[fx][fy] == 1 && dp[fx][fy][0][s] > my + 1) {
				dp[fx][fy][0][s] = my + 1;
				q.push({fx, fy, 0, s});

			}
		}
	}
	int ans = inf;
	for(int i = 0; i <= 4; i++) {
		for(int j = 0; j < 2; j++) {
			mnn(ans, dp[n][m][i][j]);
		}
	}
	if(ans == inf) ans = -1;
	cout << ans << '\n';
}
 
signed main() {
	#ifndef ONO
	freopen("dream.in", "r", stdin);
	freopen("dream.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}