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

const int mxn = 110, inf = 1e9 + 10;
int a[mxn][mxn], mn[mxn][mxn][4], vis[mxn][mxn][4];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void go() {
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> a[i][j];
			for(int k = 0; k < 3; k++) {
				mn[i][j][k] = inf;
			}
		}
	}
	a[1][1] = 0;
	mn[1][1][0] = 0;
	priority_queue<array<int, 4>> q;
	q.push({mn[1][1][0], 1, 1, 0});
	while(q.size()) {
		array<int, 4> tmp = q.top(); q.pop();
		int x = tmp[1];
		int y = tmp[2];
		int tp = tmp[3];
		if(vis[x][y][tp]) continue;
		vis[x][y][tp] = 1;
		for(int i = 0; i < 4; i++) {
			int fx = x + dx[i];
			int fy = y + dy[i];
			if(fx < 1 || fx > n || fy < 1 || fy > n) continue;
			int nx = (tp + 1) % 3;
			int add = (nx == 0 ? a[fx][fy] : 0);
			if(mn[fx][fy][nx] > mn[x][y][tp] + m + add) {
				mn[fx][fy][nx] = mn[x][y][tp] + m + add;
				q.push({-mn[fx][fy][nx], fx, fy, nx});
			}
		}
	}
	cout << min({mn[n][n][0], mn[n][n][1], mn[n][n][2]}) << '\n';
}
 
signed main() {
	#ifndef ONO
	freopen("visitfj.in", "r", stdin);
	freopen("visitfj.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}