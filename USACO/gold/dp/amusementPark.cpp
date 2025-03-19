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

const int mxn = 21, mod = 998244353;
int dp[1 << mxn], can[1 << mxn], cnt[1 << mxn], g[mxn];

void add(int &x, int y) {
	x += y;
	if(x >= mod) x -= mod;
}

void sub(int &x, int y) {
	x -= y;
	if(x < 0) x += mod;
}

void go() {
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y; x--; y--;
		g[x] |= (1 << y);
		g[y] |= (1 << x);
	}
	for(int i = 0; i < (1 << n); i++) {
		can[i] = 1;
		cnt[i] = cnt[i / 2] + (i & 1);
		for(int j = 0; j < n; j++) {
			if(((i >> j) & 1) && (i & g[j])) {
				can[i] = 0;
				break;
			}
		}
	}
	dp[0] = 1;
	for(int i = 1; i < (1 << n); i++) {
		for(int j = i; j; j = (j - 1) & i) {
			if(can[j]) {
				if(cnt[j] & 1) add(dp[i], dp[i ^ j]);
				else sub(dp[i], dp[i ^ j]);
			}
		}
	}
	cout << (dp[(1 << n) - 1] * m % mod * (mod + 1) / 2 % mod) << '\n';
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