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

void go() {
	int n;
	cin >> n;
	vector<map<int, int>> g(n);
	for(int i = 0; i < n; i++) {
		int x;
		cin >> x;
		g[i][x] = 1;
		if(i) {
			for(auto it : g[i - 1]) {
				mxx(g[i][__gcd(it.ff, x)], it.ss + 1);
			}
		}
	}
	vector<int> ans(n, 0);
	for(int i = 0; i < n; i++) for(auto it : g[i]) mxx(ans[it.ss - 1], it.ff);
	cout << ans << '\n';
}
 
signed main() {
	// #ifndef ONO
	// freopen("file.in", "r", stdin);
	// freopen("file.out", "w", stdout);
	// #endif
	fast;
	int t = 1;
	cin >> t;
	while(t--) {
		go();
	}
	return 0;
}