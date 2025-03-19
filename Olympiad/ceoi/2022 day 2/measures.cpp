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

const int mxn = 4e5 + 10, inf = 1e18 + 10;
int a[mxn], id[mxn], d[mxn * 4], lz[mxn * 4], mn[mxn * 4], mx[mxn * 4], fn[mxn], t;

void pro(int i, int l, int r) {
	mn[i] += lz[i];
	mx[i] += lz[i];
	if(l < r) {
		lz[i * 2] += lz[i];
		lz[i * 2 + 1] += lz[i];
	}
	lz[i] = 0;
}

void up(int i, int l, int r) {
	if(l == r) return;
	int m = (l + r) / 2;
	pro(i * 2, l, m);
	pro(i * 2 + 1, m + 1, r);
	d[i] = max(d[i * 2], d[i * 2 + 1]);
	mxx(d[i], mx[i * 2] - mn[i * 2 + 1]);
	mx[i] = max(mx[i * 2], mx[i * 2 + 1]);
	mn[i] = min(mn[i * 2], mn[i * 2 + 1]);
}

void build(int l, int r, int i) {
	mn[i] = inf;
	mx[i] = -inf;
	d[i] = lz[i] = 0;
	if(l == r) return;
	int m = (l + r) >> 1;
	build(l, m, i * 2);
	build(m + 1, r, i * 2 + 1);
}

void assign(int l, int r, int i, int x, int val) {
	pro(i, l, r);
	if(l == r) {
		mn[i] = mx[i] = val;
		d[i] = 0;
		return;
	}
	int m = (l + r) >> 1;
	if(x <= m) assign(l, m, i * 2, x, val);
	else assign(m + 1, r, i * 2 + 1, x, val);
	up(i, l, r);
}

void update(int l, int r, int i, int x, int y, int val) {
	if(x > y) return;
	pro(i, l, r);
	if(l >= x && r <= y) {
		lz[i] += val;
		pro(i, l, r);
		return;
	}
	int m = (l + r) / 2;
	if(x <= m) update(l, m, i * 2, x, y, val);
	if(y > m) update(m + 1, r, i * 2 + 1, x, y, val);
	up(i, l, r);
}

int get(int i) {
	int ret = 0;
	for(; i; i -= (i & -i)) {
		ret += fn[i];
	}
	return ret;
}

void up(int i) {
	for(; i <= t; i += (i & -i)) {
		fn[i]++;
	}
}

string getAns() {
	int ans = d[1];
	string str = to_string(ans / 2);
	if(ans & 1) str += ".5";
	return str;
}

void go() {
	int n, m, d;
	cin >> n >> m >> d;
	vector<pair<int, int>> comp;
	for(int i = 1; i <= n + m; i++) {
		cin >> a[i];
		comp.eb(a[i], i);
	}
	sort(all(comp));
	t = 0;
	for(auto it : comp) {
		id[it.ss] = ++t;
	}
	build(1, t, 1);
	for(int i = 1; i <= n + m; i++) {
		int cnt = get(id[i]);
		up(id[i]);
		assign(1, t, 1, id[i], a[i] - cnt * d);
		update(1, t, 1, id[i] + 1, t, -d);
		if(i > n) cout << getAns() << ' ';
	}
}

signed main() {
	// #ifndef ONO
	// freopen("file.in", "r", stdin);
	// freopen("file.out", "w", stdout);
	// #endif
	fast;
	int T = 1;
	// cin >> t;
	while(T--) {
		go();
	}
	return 0;
}