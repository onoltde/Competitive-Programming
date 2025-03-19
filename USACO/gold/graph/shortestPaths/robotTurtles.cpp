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
int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};
int dp[10][10][(1 << 11)][5], g[10][10];
int vis[10][10][(1 << 11)][5];
int cm[10][10][(1 << 11)][5];
array<int, 5> par[10][10][(1 << 11)][5];

void go() {
	int tot = 0;
	pair<int, int> st, en;
	for(int i = 1; i <= 8; i++) {
		for(int j = 1; j <= 8; j++) {
			char ch;
			cin >> ch;
			if(ch == 'T') {
				st = {i, j};
				g[i][j] = -1;
			}
			else if(ch == 'D') {
				en = {i, j};
				g[i][j] = -1;
			}
			else if(ch == 'C') {
				g[i][j] = -100;
			}
			else if(ch == 'I') {
				g[i][j] = tot++;
			}
			else if(ch == '.') {
				g[i][j] = -1;
			}
		}
	}
	for(int i = 1; i <= 8; i++) {
		for(int j = 1; j <= 8; j++) {
			for(int k = 0; k < (1 << tot); k++) {
				for(int dir = 0; dir < 4; dir++) {
					dp[i][j][k][dir] = inf;
					cm[i][j][k][dir] = -1;
				}
			}
		}
	}
	priority_queue<array<int, 5>> q;
	dp[st.ff][st.ss][0][2] = 0;
	q.push({dp[st.ff][st.ss][0][2], st.ff, st.ss, 0, 2});
	while(q.size()) {
		array<int, 5> tmp = q.top(); q.pop();
		int my = -tmp[0];
		int x = tmp[1];
		int y = tmp[2];
		int bit = tmp[3];
		int dir = tmp[4];
		if(vis[x][y][bit][dir]) continue;
		vis[x][y][bit][dir] = 1;
		int fx = x + dx[dir];
		int fy = y + dy[dir];
		if(fx >= 1 && fx <= 8 && fy >= 1 && fy <= 8) {
			if(g[fx][fy] == -1 && dp[fx][fy][bit][dir] > my + 1) {
				dp[fx][fy][bit][dir] = my + 1;
				cm[fx][fy][bit][dir] = 0;
				par[fx][fy][bit][dir] = tmp;
				q.push({-my - 1, fx, fy, bit, dir});
			}
			if(g[fx][fy] >= 0) {
				if(bit & (1 << g[fx][fy])) {
					if(dp[fx][fy][bit][dir] > my + 1) {
						dp[fx][fy][bit][dir] = my + 1;
						cm[fx][fy][bit][dir] = 0;
						par[fx][fy][bit][dir] = tmp;
						q.push({-my - 1, fx, fy, bit, dir});			
					}
				} 
				else {
					int nwbit = bit ^ (1 << g[fx][fy]);
					if(dp[fx][fy][nwbit][dir] > my + 2) {
						dp[fx][fy][nwbit][dir] = my + 2;
						cm[fx][fy][nwbit][dir] = 1;
						par[fx][fy][nwbit][dir] = tmp;
						q.push({-my - 2, fx, fy, nwbit, dir});
					}
				}
			}
		}
		int nx = (dir + 1) % 4;
		int pr = (dir + 3) % 4;
		if(dp[x][y][bit][nx] > my + 1) {
			dp[x][y][bit][nx] = my + 1;
			cm[x][y][bit][nx] = 2;
			par[x][y][bit][nx] = tmp;
			q.push({-my - 1, x, y, bit, nx});
		}
		if(dp[x][y][bit][pr] > my + 1) {
			dp[x][y][bit][pr] = my + 1;
			cm[x][y][bit][pr] = 3;
			par[x][y][bit][pr] = tmp;
			q.push({-my - 1, x, y, bit, pr});
		}
	}
	int mx = inf;
	int x = en.ff, y = en.ss, bit, dir;
	for(int i = 0; i < (1 << tot); i++) {
		for(int j = 0; j < 4; j++) {
			if(mx > dp[en.ff][en.ss][i][j]) {
				mx = dp[en.ff][en.ss][i][j];
				bit = i;
				dir = j;
			}
		}
	}
	if(mx == inf) {
		cout << "no solution\n";
		return;
	}
	vector<char> ans;
	while(cm[x][y][bit][dir] != -1) {
		if(cm[x][y][bit][dir] == 0) ans.pb('F');
		else if(cm[x][y][bit][dir] == 1) ans.pb('F'), ans.pb('X');
		else if(cm[x][y][bit][dir] == 2) ans.pb('R');
		else ans.pb('L');
		array<int, 5> tmp = par[x][y][bit][dir];
		x = tmp[1];
		y = tmp[2];
		bit = tmp[3];
		dir = tmp[4];
	}
	reverse(all(ans));
	for(char ch : ans) {
		cout << ch;
	}
	cout << '\n';
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