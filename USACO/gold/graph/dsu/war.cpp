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
int e[mxn], par[mxn];

int get(int x) {
	return par[x] == x ? x : par[x] = get(par[x]);
}

int getE(int x) {
	return get(e[get(x)]);
}

void unite(int x, int y) {
	x = get(x);
	y = get(y);
	if(x == y) return;
	par[x] = y;
	e[x] = getE(x);
	e[y] = getE(y);
	if(e[x] && e[y]) {
		unite(e[x], e[y]);
		e[x] = get(e[x]);
	} else if(e[y]) {
		e[x] = e[y];
	}
}

bool isSame(int x, int y) {
	return get(x) == get(y);
}

void setE(int x, int y) {
	x = get(x);
	y = get(y);
	if(e[x]) unite(e[x], y);
	if(e[y]) unite(e[y], x);
	if(!e[x] && !e[y]) e[x] = y, e[y] = x;
}

void go() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		par[i] = i;
	}
	int c, x, y;
	while(1) {
		cin >> c >> x >> y;
		if(c == 0) break;
		x++;
		y++;
		if(c == 1) {
			if(getE(x) == y) cout << -1 << '\n';
			else unite(x, y);
		} else if(c == 2) {
			if(isSame(x, y)) cout << -1 << '\n';
			else setE(x, y);
		} else if(c == 3) {
			cout << (int)isSame(x, y) << '\n';
		} else {
			cout << (int)(getE(x) == get(y)) << '\n';
		}
	}
}
 
signed main() {
	#ifndef ONO
	freopen("file.in", "r", stdin);
	freopen("file.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}