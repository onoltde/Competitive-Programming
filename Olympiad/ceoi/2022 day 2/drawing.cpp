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

const int mxn = 2e5 + 10;
int vis[mxn], ans[mxn];
vector<int> g[mxn];

void go() {
	int n;
	cin >> n;
	for(int i = 1, x, y; i < n; i++) {
		cin >> x >> y;
		g[x].pb(y);
		g[y].pb(x);
	}
	queue<int> q;
	vector<pair<pair<int, int>, int>> v;
	for(int i = 1; i <= n; i++) {
		int x, y;
		cin >> x >> y;
		v.eb(make_pair(x, y), i);
	}
	sort(all(v));
	int l = 0;
	q.push(1);
	vis[1] = 1;
	while(q.size()) {
		int x = q.front();
		q.pop();
		ans[x] = v[l++].ss;
		for(int y : g[x]) {
			if(vis[y]) continue;
			q.push(y);
			vis[y] = 1;
		}
	}
	for(int i = 1; i <= n; i++) {
		vis[ans[i]] = i;
	}
	for(int i = 1; i <= n; i++) {
		cout << vis[i] << ' ';
	}
	cout << '\n';
}

signed main() {
	//#ifndef ONO
	//freopen("file.in", "r", stdin);
	//freopen("file.out", "w", stdout);
	//#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}