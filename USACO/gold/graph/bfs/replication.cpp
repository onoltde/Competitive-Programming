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

const int mxn = 1010, inf = 1e9 + 10;
char g[mxn][mxn];
int dis[mxn][mxn], mn1[mxn][mxn], mn2[mxn][mxn], mn[mxn][mxn], dp[mxn][mxn],  cnt[mxn][mxn], mx[mxn][mxn];
vector<int> gg[mxn];

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void go() {
	int n, s;
	cin >> n >> s;
	queue<pair<int, int>> q;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> g[i][j];
			dp[i][j] = inf;
			if(g[i][j] == '#') gg[j].pb(i);
			if(g[i][j] == 'S') q.push({i, j}), dp[i][j] = 0;
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(g[i][j] == '#') {
				dis[i][j] = 0;
				continue;
			}
			int nx = lower_bound(all(gg[j]), i) - gg[j].begin();
			int pr = nx - 1;
			dis[i][j] = min(gg[j][nx] - i, i - gg[j][pr]);
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(g[i][j] == '#') continue;
			mn1[i][j] = min(mn1[i][j - 1] + 1, dis[i][j]);
		}
		for(int j = n; j >= 1; j--) {
			if(g[i][j] == '#') continue;
			mn2[i][j] = min(mn2[i][j + 1] + 1, dis[i][j]);
		}
		for(int j = 1; j <= n; j++) {
			mn[i][j] = min(mn1[i][j], mn2[i][j]);
		}
	}
	while(q.size()) {
		int x = q.front().ff;
		int y = q.front().ss;
		q.pop();
		int now = dp[x][y] / s + 1;
		if(now > mn[x][y]) continue;
		for(int i = 0; i < 4; i++) {
			int fx = x + dx[i];
			int fy = y + dy[i];
			if(mn[fx][fy] < now || dp[fx][fy] != inf) continue;
			dp[fx][fy] = dp[x][y] + 1;
			q.push({fx, fy});
		}
	}
	for(int i = 1; i <= n; i++) {
		int tt = 0;
		for(int j = 1; j <= n; j++) {
			if(g[i][j] == '#') {
				tt = 0;
				continue;
			}
			if(dp[i][j] == inf) tt--;
			else tt = max(tt - 1, min(dp[i][j] / s + 1, mn[i][j]));
			if(tt > 0) {
				cnt[i - tt + 1][j]++;
				cnt[i + tt][j]--;
			}
			mx[i][j] = tt;
		}
		tt = 0;
		for(int j = n; j >= 1; j--) {
			if(g[i][j] == '#') {
				tt = 0;
				continue;
			}
			if(dp[i][j] == inf) tt--;
			else tt = max(tt - 1, min(dp[i][j] / s + 1, mn[i][j]));
			if(tt > 0) {
				cnt[i - tt + 1][j]++;
				cnt[i + tt][j]--;
			}
			mx[i][j] = tt;
		}
	}
	int ans = 0;
	for(int j = 1; j <= n; j++) {
		for(int i = 1; i <= n; i++) {
			cnt[i][j] += cnt[i - 1][j];
			ans += (cnt[i][j] > 0);
		}
	}
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