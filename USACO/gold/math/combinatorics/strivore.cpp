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

// const int mod = 998244353;
const int mod = 1e9 + 7;
const int N = 2e6 + 10;

int fpow(int a, int z) {
	int ret = 1;
	for(; z > 0; z >>= 1) {
		if(z & 1) ret = (ret * a) % mod;
		a = (a * a) % mod;
	}
	return ret;
}

vector<int> fac(1, 1), inv(1, 1);

void init() {
	for(int i = 1; i < N; i++) {
		fac.pb(fac.back() * i % mod);
		inv.pb(fpow(fac.back(), mod - 2));
	}
}

int C(int n, int k) {
	if(k > n) return 0;
	return (((fac[n] * inv[k]) % mod) * inv[n - k]) % mod; 
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void go() {
	int n;
	string str;
	cin >> n >> str;
	int m = str.size();
	int ans = 0;
	for(int i = m; i <= m + n; i++) {
		ans = (ans + C(i - 1, m - 1) * fpow(25, i - m) % mod * fpow(26, n + m - i)) % mod;
	}
	cout << ans << '\n';
}

signed main() {
	fast;
	init();
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
}