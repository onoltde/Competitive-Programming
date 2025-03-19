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

const int mxn = 2e5 + 10, inf = 1e9 + 10;
int cnt[mxn];
vector<int> g[mxn];

void go() {
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		cnt[x]++;
		g[y].pb(x);
	}
	priority_queue<int> q;
	for(int i = 1; i <= n; i++) {
		if(cnt[i] == 0) q.push(i);
	}
	vector<int> ans;
	while(q.size()) {
		int x = q.top(); q.pop();
		ans.pb(x);
		for(int y : g[x]) {
			cnt[y]--;
			if(cnt[y] == 0) q.push(y);
		}
	}
	reverse(all(ans));
	for(int x : ans) {
		cout << x << ' ';
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