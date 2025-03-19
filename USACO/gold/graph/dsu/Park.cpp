#include<bits/stdc++.h>
using namespace std;
 
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define PP make_pair

#define int long long
 
typedef long long ll;

typedef pair<int, int> P;
typedef pair<P, P> L;

template<typename T>
void mxx(T &a, T b){if(b > a) a = b;}
template<typename T>
void mnn(T &a, T b){if(b < a) a = b;}

const int mxn = 2010;
const int mxm = 1e5 + 10;
const int inf = 1e18 + 10
;
array<int, 3> a[mxn], b[mxm];
vector<array<int, 3>> g;
array<int, 4> mm[mxn];
int is[10][10];
string ans[mxm];
int h, w, now, par[mxn];

int dis(int x1, int y1, int x2, int y2) {
	return (int)(sqrt(double((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))) * 1e6);
}

int get(int x) {
	return par[x] == x ? x : par[x] = get(par[x]);
}

void untie(int x, int y) {
	x = get(x); y = get(y);
	if(x == y) return;
	par[y] = x;
	mnn(mm[x][0], mm[y][0]);
	mnn(mm[x][1], mm[y][1]);
	mnn(mm[x][2], mm[y][2]);
	mnn(mm[x][3], mm[y][3]);
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			mnn(is[i][j], max(mm[x][i], mm[x][j]) * (int)1e6);			
		}
	}
}

string getAns(int x) {
	string ans = "";
	for(int i = 1; i <= 4; i++) {
		if(x == i) {
			ans.pb(i + '0');
			continue;
		}
		if(is[i - 1][(i - 2 + 4) % 4] < now) continue;
		if(is[x - 1][(x - 2 + 4) % 4] < now) continue;
		if(min(x, i) <= 2 && max(x, i) > 2 && is[1][3] < now) continue;
		if(x + i != 5 && is[0][2] < now) continue;
		ans.pb(i + '0');
	}
	return ans;
}

void go() {
	int n, m;
	cin >> n >> m;
	cin >> w >> h;
	vector<array<int, 3>> g;
	for(int i = 1, x, y, r; i <= n; i++) {
		cin >> x >> y >> r;
		a[i] = {x, y, r};
		par[i] = i;
		mm[i][3] = x - r;
		mm[i][2] = h - y - r;
		mm[i][1] = w - x - r;
		mm[i][0] = y - r;
	}
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			is[i][j] = inf;
		}
	}
	for(int i = 1, p, r; i <= m; i++) {
		cin >> p >> r;
		b[i] = {p * (int)1e6, r, i};
	}
	sort(b + 1, b + m + 1);
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			g.pb({dis(a[i][0], a[i][1], a[j][0], a[j][1]) - (a[i][2] + a[j][2]) * (int)1e6, i, j});
		}
	}
	sort(all(g));
	int idx = 0;

	for(int i = 1; i <= m; i++) {
		now = b[i][0] * 2;
		while(idx < g.size() && g[idx][0] < now) {
			untie(g[idx][1], g[idx][2]);
			idx++;
		}
		ans[b[i][2]] = getAns(b[i][1]);
	}

	for(int i = 1; i <= m; i++) {
		cout << ans[i] << '\n';
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