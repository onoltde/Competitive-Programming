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

const int mxn = 2e5 + 10;
int b[mxn], p[mxn * 2], pth[mxn], in[mxn], out[mxn], tt, lz[mxn * 4], mn[mxn * 4];
vector<pair<int, int>> g[mxn];
tuple<int, int, int> edges[mxn];

void dfs(int to) {
	in[to] = ++tt;
	for(auto it : g[to]) {
		int x = it.ff;
		int c = it.ss;
		pth[x] = pth[to] + c;
		dfs(x);
	}
	out[to] = tt;
}

void pro(int i, int l, int r) {
	mn[i] += lz[i];
	if(l < r) {
		lz[i * 2] += lz[i];
		lz[i * 2 + 1] += lz[i];
	}
	lz[i] = 0;
}

void update(int l, int r, int i, int x, int y, int val) {
	pro(i, l, r);
	if(l > y || r < x) return;
	if(l >= x && r <= y) {
		lz[i] += val;
		pro(i, l, r);
		return;
	}
	int m = (l + r) / 2;
	update(l, m, i * 2, x, y, val);
	update(m + 1, r, i * 2 + 1, x, y, val);
	mn[i] = min(mn[i * 2], mn[i * 2 + 1]);
}

int getMin(int l, int r, int i, int x, int y) {
	pro(i, l, r);
	if(l >= x && r <= y) return mn[i];
	int m = (l + r) / 2;
	if(y <= m) return getMin(l, m, i * 2, x, y);
	else if(x > m) return getMin(m + 1, r, i * 2 + 1, x, y);
	else return min(getMin(m + 1, r, i * 2 + 1, x, y), getMin(l, m, i * 2, x, y));
}

void go() {
	int n, q;
	cin >> n >> q;
	for(int i = 1; i <= 2 * n - 2; i++) {
		int x, y, c;
		cin >> x >> y >> c;
		if(i >= n) {
			p[i] = x;
			b[x] = c;
		}
		else {
			edges[i] = {x, y, c};
			g[x].pb({y, c});
		}
	}
	dfs(1);
	for(int i = 1; i <= n; i++) {
		update(1, n, 1, in[i], in[i], pth[i] + b[i]);
	}
	while(q--) {
		int tp, x, y;
		cin >> tp >> x >> y;
		if(tp == 1) {
			if(x >= n) {
				update(1, n, 1, in[p[x]], in[p[x]], y - b[p[x]]);
				b[p[x]] = y;
				continue;
			}
			int fr, to, cs;
			tie(fr, to, cs) = edges[x];
			update(1, n, 1, in[to], out[to], y - cs);
			edges[x] = {fr, to, y};
		}
		else {
			if(in[y] >= in[x] && in[y] <= out[x]) {
				cout << getMin(1, n, 1, in[y], in[y]) - getMin(1, n, 1, in[x], in[x]) + b[x] - b[y] << '\n';
			} else {
				cout << getMin(1, n, 1, in[y], in[y]) - b[y] + getMin(1, n, 1, in[x], out[x]) - getMin(1, n, 1, in[x], in[x]) + b[x] << '\n';
			}
		}
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