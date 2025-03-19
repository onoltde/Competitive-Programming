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

const int mod = 998244353;
const int N = 510;

int fpow(int a, int z) {
	int ret = 1;
	for(; z > 0; z >>= 1) {
		if(z & 1) ret = (ret * a) % mod;
		a = (a * a) % mod;
	}
	return ret;
}

vector<int> fac(1, 1), inv(1, 1);

void build() {
	for(int i = 1; i < N; i++) {
		fac.pb(fac.back() * i % mod);
		inv.pb(fpow(fac.back(), mod - 2));
	}
}

int C(int n, int k) {
	return (((fac[n] * inv[k]) % mod) * inv[n - k]) % mod; 
}

int dp[N][N];

void go() {
	int n, x;
	cin >> n >> x;
	int tp = 0;
	dp[n][0] = 1;
	for(int i = 0; i < x; i++) {
		for(int j = 1; j <= n; j++) {
			int nxt = min(x, i + j - 1);
			int d = nxt - i;
			for(int k = j; k >= 0; k--) {
				dp[k][nxt] = (dp[k][nxt] + dp[j][i] * C(j, k) % mod * fpow(d, j - k)) % mod;
			}
		}
	}
	int ans = 0;
	for(int i = 0; i <= x; i++) {
		ans = (ans + dp[0][i]) % mod;
	}
	cout << ans << '\n';
}
 
signed main() {
	// #ifndef ONO
	// freopen("file.in", "r", stdin);
	// freopen("file.out", "w", stdout);
	// #endif
	fast;
	int t = 1;
	// cin >> t;
	build();
	while(t--) {
		go();
	}
	return 0;
}