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

const int mod = 1e9 + 7;
const int N = 3e5 + 10;

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
	if(k > n) return 0;
	return (((fac[n] * inv[k]) % mod) * inv[n - k]) % mod; 
}

int a[N], dp[N], cnt[N];
vector<int> pr[N];

void build(int n) {
	for(int i = 1; i <= n; i++) {
		for(int j = i; j <= n; j += i) {
			pr[j].pb(i);
		}
	}
}

void go() {
	int n;
	cin >> n;
	int MX = 0;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		mxx(MX, a[i]);
	}
	for(int i = 1; i <= n; i++) {
		if(a[i] == 1) {
			cout << 1 << '\n';
			return;
		}
		for(int x : pr[a[i]]) {
			cnt[x]++;
		}
	}
	for(int _ = 1; _ < 20; _++) {
		for(int j = 1; j <= MX; j++) {
			dp[j] = 0;
		}
		for(int j = MX; j >= 1; j--) {
			dp[j] = C(cnt[j], _);
			for(int k = j + j; k <= MX; k += j) {
				dp[j] = (dp[j] - dp[k] + mod) % mod;
			}
		}
		if(dp[1]) {
			cout << _ << '\n';
			return;
		}
	}
	cout << "-1\n";
}
 
signed main() {
	// #ifndef ONO
	// freopen("file.in", "r", stdin);
	// freopen("file.out", "w", stdout);
	// #endif
	fast;
	int t = 1;
	// cin >> t;
	build(3e5);
	build();
	while(t--) {
		go();
	}
	return 0;
}